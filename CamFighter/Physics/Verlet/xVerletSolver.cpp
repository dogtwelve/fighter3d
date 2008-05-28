#include "xVerletSolver.h"

const float xVerletSolver :: FRICTION_AIR = 0.5f;
const float xVerletSolver :: GRAVITY      = 10.f;

void xVerletSolver :: SatisfyConstraints()
{
    for (xBYTE pi = I_passes; pi; --pi)
    {
        if (system->C_collisions)
        {
            xVConstraintCollisionVector::iterator iter = system->C_collisions->begin(),
                                                  end  = system->C_collisions->end();
            for (; iter != end; ++iter)
                iter->Satisfy(system);
        }

        if (system->C_lengthConst)
        {
            xVConstraintLengthEql * iterL = system->C_lengthConst;
            xVConstraintLengthEql * endL  = system->C_lengthConst + system->I_particles-1;
            for (; iterL != endL; ++iterL)
                iterL->Satisfy(system);
        }

        xVConstraint **constr = system->C_constraints;
        for (xWORD i = system->I_constraints; i; --i, ++constr)
            (*constr)->Satisfy(system);
    }
}

void xVerletSolver :: AccumulateForces()
{
    xVector3 *A_iter = system->A_forces;
    for (xWORD i = system->I_particles; i; --i, ++A_iter) *A_iter += A_gravity;
}

void xVerletSolver :: Verlet()
{
    xVector3 *P_cur  = system->P_current;
    xVector3 *P_old  = system->P_previous;
    xVector3 *A_iter = system->A_forces;
    xFLOAT    T_step_Sqr = system->T_step*system->T_step;
    
    if (A_iter)
        for (xWORD i = system->I_particles; i; --i, ++P_cur, ++P_old, ++A_iter)
            *P_old = *P_cur /*+ 0.9f * (*P_cur - *P_old)*/ + *A_iter * T_step_Sqr;
    else
        for (xWORD i = system->I_particles; i; --i, ++P_cur, ++P_old)
            *P_old = *P_cur /*+ 0.9f * (*P_cur - *P_old)*/;

    system->SwapPositions();
}

void xVerletSolver :: VerletFull()
{
    xVector3 *P_cur  = system->P_current;
    xVector3 *P_old  = system->P_previous;
    xVector3 *A_iter = system->A_forces;
    xFLOAT    T_step_Sqr = system->T_step*system->T_step;
    xFLOAT    F_friction_Inv = 1.f - (FRICTION_AIR * system->T_step);
    if (system->T_step_Old > 0.f)
        F_friction_Inv *= system->T_step / system->T_step_Old;
    
    if (A_iter)
        for (xWORD i = system->I_particles; i; --i, ++P_cur, ++P_old, ++A_iter)
            *P_old = *P_cur + F_friction_Inv * (*P_cur - *P_old) + *A_iter * T_step_Sqr;
    else
        for (xWORD i = system->I_particles; i; --i, ++P_cur, ++P_old)
            *P_old = *P_cur + F_friction_Inv * (*P_cur - *P_old);

    system->SwapPositions();
}