#include "RendererGL.h"
#include "../GLAnimSkeletal.h"

/********************************* ambient model ************************************/
void RenderElementAmbientLST(bool transparent, const xFieldOfView &FOV, const xLightVector &lights,
                    xElement *elem, xModelInstance &modelInstance)
{
    for (xElement *selem = elem->L_kids; selem; selem = selem->Next)
        RenderElementAmbientLST(transparent, FOV, lights, selem, modelInstance);

    if (!elem->renderData.I_vertices
        || (transparent && !elem->FL_transparent)
        || (!transparent && !elem->FL_opaque)) return;

    xElementInstance &instance = modelInstance.L_elements[elem->ID];
    xMatrix mtxTrasformation = elem->MX_MeshToLocal * modelInstance.MX_LocalToWorld;
    xVector3 center = mtxTrasformation.preTransformP(instance.bsCenter);
    if (!FOV.CheckSphere(center, instance.bsRadius) ||
        !FOV.CheckBox(instance.bbBox.fillCornersTransformed(mtxTrasformation)) )
    {
        ++Performance.CulledElements;
        return;
    }

    int lightsC = 0;
    xColor ambient; ambient.init(0.f,0.f,0.f,1.f);
    xLightVector::const_iterator iterL = lights.begin(), endL = lights.end();
    for (; iterL != endL; ++iterL)
        if (iterL->elementReceivesLight(center, instance.bsRadius))
        {
            ambient.vector3 += iterL->ambient.vector3;
            ++lightsC;
        }
    if (!lightsC) return;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient.xyzw);

    /************************** PREPARE LST  ****************************/
    xDWORD &listID    = elem->FL_skeletized
		? transparent ? instance.gpuMain.listIDTransp : instance.gpuMain.listID
		: transparent ? elem->renderData.gpuMain.listIDTransp : elem->renderData.gpuMain.listID;
	xDWORD &listIDTex = elem->FL_skeletized
		? transparent ? instance.gpuMain.listIDTexTransp : instance.gpuMain.listIDTex
		: transparent ? elem->renderData.gpuMain.listIDTexTransp : elem->renderData.gpuMain.listIDTex;
	xGPURender::Mode &mode = elem->FL_skeletized ? instance.mode : elem->renderData.mode;
    bool textured = false;

    if (elem->FL_skeletized)
        GLShader::EnableSkeleton(xState_On);

    if (!listID)
    {
        mode = xGPURender::LIST;
        glNewList(listID = glGenLists(1), GL_COMPILE);

        if (elem->FL_skeletized) {
            g_AnimSkeletal.BeginAnimation();
            g_AnimSkeletal.SetBones (modelInstance.I_bones, modelInstance.MX_bones, modelInstance.QT_bones, elem, false);
            g_AnimSkeletal.SetElement(elem, &instance);
        }
        else
        {
            if (elem->FL_textured)
                glVertexPointer   (3, GL_FLOAT, sizeof(xVertexTex), elem->renderData.L_verticesT);
            else
                glVertexPointer   (3, GL_FLOAT, sizeof(xVertex), elem->renderData.L_vertices);
            /////////////////////////// LOAD NORMALS ///////////////////////////
            if (elem->renderData.L_normals)
            {
                glNormalPointer (GL_FLOAT, sizeof(xVector3), elem->renderData.L_normals);
                glEnableClientState(GL_NORMAL_ARRAY);
            }
        }

        xFaceList *faceL = elem->L_faceLists;
        xMaterial *m_currentMaterial = (xMaterial*)1;
        for(int i=elem->I_faceLists; i; --i, ++faceL)
        {
            if ((transparent && (!faceL->Material || faceL->Material->transparency == 0.f)) ||
                (!transparent && faceL->Material && faceL->Material->transparency > 0.f) )
                continue;
            if (elem->FL_textured && faceL->Material && faceL->Material->texture.htex)
            {
                textured = true;
                continue;
            }
            if (faceL->Material != m_currentMaterial)
                RendererGL::SetMaterial(elem->Color, m_currentMaterial = faceL->Material, false);
            glDrawElements(GL_TRIANGLES, 3*faceL->I_count, GL_UNSIGNED_SHORT, elem->renderData.L_faces+faceL->I_offset);
        }
        if (!textured && elem->renderData.L_normals) glDisableClientState(GL_NORMAL_ARRAY);
        if (!textured && elem->FL_skeletized)
            g_AnimSkeletal.EndAnimation();

        glEndList();
    }

    if (textured && elem->FL_textured && !listIDTex)
    {
        glNewList(listIDTex = glGenLists(1), GL_COMPILE);

        if (elem->FL_skeletized) {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (2, GL_FLOAT, sizeof(xVertexTexSkel), &(elem->renderData.L_verticesTS->tx));
            g_AnimSkeletal.SetBones (modelInstance.I_bones, modelInstance.MX_bones, modelInstance.QT_bones, elem, false);
        }
        else {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (2, GL_FLOAT, sizeof(xVertexTex), &(elem->renderData.L_verticesT->tx));
        }

        xFaceList *faceL = elem->L_faceLists;
        xMaterial *m_currentMaterial = (xMaterial*)1;
        for(int i=elem->I_faceLists; i; --i, ++faceL)
        {
            if ((transparent && (!faceL->Material || faceL->Material->transparency == 0.f)) ||
                (!transparent && faceL->Material && faceL->Material->transparency > 0.f) )
                continue;
            if (!faceL->Material || !faceL->Material->texture.htex)
                continue;
            if (faceL->Material != m_currentMaterial)
                RendererGL::SetMaterial(elem->Color, m_currentMaterial = faceL->Material, false);
            glDrawElements(GL_TRIANGLES, 3*faceL->I_count, GL_UNSIGNED_SHORT, elem->renderData.L_faces+faceL->I_offset);
        }
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        if (elem->renderData.L_normals) glDisableClientState(GL_NORMAL_ARRAY);
        if (elem->FL_skeletized)
            g_AnimSkeletal.EndAnimation();
        
        glEndList();
    }

    /************************* USE LST ****************************/
    if (listID)
    {
        glPushMatrix();
        {
            glMultMatrixf(&elem->MX_MeshToLocal.x0);
            GLShader::EnableTexturing(xState_Off);
            GLShader::Start();
            glCallList(listID);
            if (listIDTex)
            {
                GLShader::EnableTexturing(xState_On);
                GLShader::Start();
                glCallList(listIDTex);
            }
        }
        glPopMatrix();
    }
    GLShader::EnableSkeleton(xState_Off);
}
void RenderElementAmbientVBO(bool transparent, const xFieldOfView &FOV, const xLightVector &lights,
                    xElement *elem, xModelInstance &modelInstance)
{
    for (xElement *selem = elem->L_kids; selem; selem = selem->Next)
        RenderElementAmbientVBO(transparent, FOV, lights, selem, modelInstance);

    if (!elem->renderData.I_vertices
        || (transparent && !elem->FL_transparent)
        || (!transparent && !elem->FL_opaque)) return;

    xElementInstance &instance = modelInstance.L_elements[elem->ID];
    xMatrix mtxTrasformation = elem->MX_MeshToLocal * modelInstance.MX_LocalToWorld;
    xVector3 center = mtxTrasformation.preTransformP(instance.bsCenter);
    if (!FOV.CheckSphere(center, instance.bsRadius) ||
        !FOV.CheckBox(instance.bbBox.fillCornersTransformed(mtxTrasformation)) )
    {
        ++Performance.CulledElements;
        return;
    }

    int lightsC = 0;
    xColor ambient; ambient.init(0.f,0.f,0.f,0.f);
    xLightVector::const_iterator iterL = lights.begin(), endL = lights.end();
    for (; iterL != endL; ++iterL)
    {
        if (iterL->elementReceivesLight(center, instance.bsRadius))
        {
            ambient.vector3 += iterL->ambient.vector3;
            ++lightsC;
        }
    }
    if (!lightsC) return;
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient.xyzw);

    /************************* INIT VBO ****************************/
    if (elem->renderData.mode == xGPURender::NONE)
        RendererGL::InitVBO(elem);

    /************************* LOAD VERTICES ****************************/
    glPushMatrix();
    glMultMatrixf(&elem->MX_MeshToLocal.matrix[0][0]);

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, elem->renderData.gpuMain.vertexB );
    if (elem->FL_skeletized) {
        if (elem->FL_textured) {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (2, GL_FLOAT, sizeof(xVertexTexSkel), (void *)(7*sizeof(xFLOAT)));
        }
        GLShader::EnableSkeleton(xState_On);
        GLShader::Start();
        g_AnimSkeletal.BeginAnimation();
        g_AnimSkeletal.SetBones  (modelInstance.I_bones, modelInstance.MX_bones, modelInstance.QT_bones, elem, true);
        g_AnimSkeletal.SetElement(elem, &instance, true);
    }
    else
    {
        if (elem->FL_textured) {
            glVertexPointer   (3, GL_FLOAT, sizeof(xVertexTex), 0);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer (2, GL_FLOAT, sizeof(xVertexTex), (void *)(3*sizeof(xFLOAT)));
        }
        else
            glVertexPointer   (3, GL_FLOAT, sizeof(xVertex), 0);
    }

    /************************* RENDER FACES ****************************/
    glBindBufferARB ( GL_ELEMENT_ARRAY_BUFFER_ARB, elem->renderData.gpuMain.indexB );
    xMaterial *m_currentMaterial = (xMaterial*)1;
    xFaceList *faceL = elem->L_faceLists;
    for(int i=elem->I_faceLists; i; --i, ++faceL)
    {
        if ((transparent && (!faceL->Material || faceL->Material->transparency == 0.f)) ||
            (!transparent && faceL->Material && faceL->Material->transparency > 0.f) )
            continue;
        if (faceL->Material != m_currentMaterial)
        {
            RendererGL::SetMaterial(elem->Color, m_currentMaterial = faceL->Material);
            if (elem->FL_skeletized) g_AnimSkeletal.SetBones  (modelInstance.I_bones, modelInstance.MX_bones, modelInstance.QT_bones, elem, true);
        }
        glDrawElements(GL_TRIANGLES, 3*faceL->I_count, GL_UNSIGNED_SHORT, (void*)(faceL->I_offset*3*sizeof(xWORD)));
    }
    glBindBufferARB ( GL_ELEMENT_ARRAY_BUFFER_ARB, 0 );
    glBindBufferARB ( GL_ARRAY_BUFFER_ARB, 0 );

    if (elem->FL_textured)
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    if (elem->FL_skeletized)
        g_AnimSkeletal.EndAnimation();
    GLShader::EnableSkeleton(xState_Off);

    glPopMatrix();
}

void RendererGL :: RenderAmbient(xModel &model, xModelInstance &instance, const xLightVector &lights,
                              bool transparent, const xFieldOfView &FOV)
{
    if ((transparent  && !model.FL_transparent) ||
        (!transparent && !model.FL_opaque)) return;

    InitTextures(model);
    glEnableClientState(GL_VERTEX_ARRAY);

    glPushMatrix();
    glMultMatrixf(&instance.MX_LocalToWorld.x0);

    for (xElement *elem = model.L_kids; elem; elem = elem->Next)
        if (UseVBO)
            RenderElementAmbientVBO(transparent, FOV, lights, elem, instance);
        else
            RenderElementAmbientLST(transparent, FOV, lights, elem, instance);

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
}