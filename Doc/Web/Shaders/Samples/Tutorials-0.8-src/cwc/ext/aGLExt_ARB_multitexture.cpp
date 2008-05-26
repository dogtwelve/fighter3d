
GLboolean use_ARB_multitexture = GL_FALSE;

// Functions pointers for ARB_multitexture Extension:

PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;
PFNGLMULTITEXCOORD1DARBPROC glMultiTexCoord1dARB = NULL;
PFNGLMULTITEXCOORD1DVARBPROC glMultiTexCoord1dvARB = NULL;
PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB = NULL;
PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB = NULL;
PFNGLMULTITEXCOORD1IARBPROC glMultiTexCoord1iARB = NULL;
PFNGLMULTITEXCOORD1IVARBPROC glMultiTexCoord1ivARB = NULL;
PFNGLMULTITEXCOORD1SARBPROC glMultiTexCoord1sARB = NULL;
PFNGLMULTITEXCOORD1SVARBPROC glMultiTexCoord1svARB = NULL;
PFNGLMULTITEXCOORD2DARBPROC glMultiTexCoord2dARB = NULL;
PFNGLMULTITEXCOORD2DVARBPROC glMultiTexCoord2dvARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;
PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB = NULL;
PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB = NULL;
PFNGLMULTITEXCOORD2IVARBPROC glMultiTexCoord2ivARB = NULL;
PFNGLMULTITEXCOORD2SARBPROC glMultiTexCoord2sARB = NULL;
PFNGLMULTITEXCOORD2SVARBPROC glMultiTexCoord2svARB = NULL;
PFNGLMULTITEXCOORD3DARBPROC glMultiTexCoord3dARB = NULL;
PFNGLMULTITEXCOORD3DVARBPROC glMultiTexCoord3dvARB = NULL;
PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB = NULL;
PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB = NULL;
PFNGLMULTITEXCOORD3IARBPROC glMultiTexCoord3iARB = NULL;
PFNGLMULTITEXCOORD3IVARBPROC glMultiTexCoord3ivARB = NULL;
PFNGLMULTITEXCOORD3SARBPROC glMultiTexCoord3sARB = NULL;
PFNGLMULTITEXCOORD3SVARBPROC glMultiTexCoord3svARB = NULL;
PFNGLMULTITEXCOORD4DARBPROC glMultiTexCoord4dARB = NULL;
PFNGLMULTITEXCOORD4DVARBPROC glMultiTexCoord4dvARB = NULL;
PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB = NULL;
PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB = NULL;
PFNGLMULTITEXCOORD4IARBPROC glMultiTexCoord4iARB = NULL;
PFNGLMULTITEXCOORD4IVARBPROC glMultiTexCoord4ivARB = NULL;
PFNGLMULTITEXCOORD4SARBPROC glMultiTexCoord4sARB = NULL;
PFNGLMULTITEXCOORD4SVARBPROC glMultiTexCoord4svARB = NULL;



bool init_ARB_multitexture(void)
{
  int error = 0;
  
  error |= aLoadExtension(PFNGLACTIVETEXTUREARBPROC, glActiveTextureARB );
  error |= aLoadExtension(PFNGLCLIENTACTIVETEXTUREARBPROC, glClientActiveTextureARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD1DARBPROC, glMultiTexCoord1dARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD1DVARBPROC, glMultiTexCoord1dvARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD1FARBPROC, glMultiTexCoord1fARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD1FVARBPROC, glMultiTexCoord1fvARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD1IARBPROC, glMultiTexCoord1iARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD1IVARBPROC, glMultiTexCoord1ivARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD1SARBPROC, glMultiTexCoord1sARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD1SVARBPROC, glMultiTexCoord1svARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD2DARBPROC, glMultiTexCoord2dARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD2DVARBPROC, glMultiTexCoord2dvARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD2FARBPROC, glMultiTexCoord2fARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD2FVARBPROC, glMultiTexCoord2fvARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD2IARBPROC, glMultiTexCoord2iARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD2IVARBPROC, glMultiTexCoord2ivARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD2SARBPROC, glMultiTexCoord2sARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD2SVARBPROC, glMultiTexCoord2svARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD3DARBPROC, glMultiTexCoord3dARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD3DVARBPROC, glMultiTexCoord3dvARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD3FARBPROC, glMultiTexCoord3fARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD3FVARBPROC, glMultiTexCoord3fvARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD3IARBPROC, glMultiTexCoord3iARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD3IVARBPROC, glMultiTexCoord3ivARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD3SARBPROC, glMultiTexCoord3sARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD3SVARBPROC, glMultiTexCoord3svARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD4DARBPROC, glMultiTexCoord4dARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD4DVARBPROC, glMultiTexCoord4dvARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD4FARBPROC, glMultiTexCoord4fARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD4FVARBPROC, glMultiTexCoord4fvARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD4IARBPROC, glMultiTexCoord4iARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD4IVARBPROC, glMultiTexCoord4ivARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD4SARBPROC, glMultiTexCoord4sARB );
  error |= aLoadExtension(PFNGLMULTITEXCOORD4SVARBPROC, glMultiTexCoord4svARB );

  if (error) return false;
  
  return true;
}