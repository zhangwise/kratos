// System includes
#include <string>
#include <iostream>

// External includes


// Project includes
#include "DEM_application.h"
#include "DEM_Dempack_torque_CL.h"
#include "custom_elements/spheric_particle.h"

namespace Kratos {

    DEMContinuumConstitutiveLaw::Pointer DEM_Dempack_torque::Clone() const {
        DEMContinuumConstitutiveLaw::Pointer p_clone(new DEM_Dempack_torque(*this));
        return p_clone;
    }

    void DEM_Dempack_torque::SetConstitutiveLawInProperties(Properties::Pointer pProp) const {
        std::cout << "Assigning DEM_Dempack_torque to properties " << pProp->Id() << std::endl;
        pProp->SetValue(DEM_CONTINUUM_CONSTITUTIVE_LAW_POINTER, this->Clone());
    }




    void DEM_Dempack_torque::ComputeParticleRotationalMoments(SphericContinuumParticle* element,
                                                    SphericContinuumParticle* neighbor,
                                                    double equiv_young,
                                                    double distance,
                                                    double calculation_area,
                                                    double LocalCoordSystem[3][3],
                                                    array_1d<double, 3>& mContactMoment) {

        double LocalRotationalMoment[3]      = {0.0};
        double GlobalDeltaRotatedAngle[3]    = {0.0};
        double LocalDeltaRotatedAngle[3]     = {0.0};
        double TargetTotalRotatedAngle[3]    = {0.0};
        double NeighborTotalRotatedAngle[3]  = {0.0};
        double TargetAngularVelocity[3]      = {0.0};
        double NeighborAngularVelocity[3]    = {0.0};
        double GlobalDeltaAngularVelocity[3] = {0.0};
        double LocalDeltaAngularVelocity[3]  = {0.0};

        for (int i = 0; i < 3; i++) { //VectorGlobal2Local arrays
            TargetTotalRotatedAngle[i]    = element->GetGeometry()[0].FastGetSolutionStepValue(PARTICLE_ROTATION_ANGLE)[i];
            NeighborTotalRotatedAngle[i]  = neighbor->GetGeometry()[0].FastGetSolutionStepValue(PARTICLE_ROTATION_ANGLE)[i];
            GlobalDeltaRotatedAngle[i]    = TargetTotalRotatedAngle[i] - NeighborTotalRotatedAngle[i];
            TargetAngularVelocity[i]      = element->GetGeometry()[0].FastGetSolutionStepValue(ANGULAR_VELOCITY)[i];
            NeighborAngularVelocity[i]    = neighbor->GetGeometry()[0].FastGetSolutionStepValue(ANGULAR_VELOCITY)[i];
            GlobalDeltaAngularVelocity[i] = TargetAngularVelocity[i] - NeighborAngularVelocity[i];
        }

        GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, GlobalDeltaRotatedAngle, LocalDeltaRotatedAngle);
        GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, GlobalDeltaAngularVelocity, LocalDeltaAngularVelocity);
        GeometryFunctions::VectorGlobal2Local(LocalCoordSystem, mContactMoment, LocalRotationalMoment);

        const double equivalent_radius = sqrt(calculation_area / KRATOS_M_PI);
        const double Inertia_I = 0.25 * KRATOS_M_PI * equivalent_radius * equivalent_radius * equivalent_radius * equivalent_radius;
        const double Inertia_J = 2.0 * Inertia_I; // This is the polar inertia
        const double rot_k = 1.0; // Hardcoded only for testing purposes. Obviously, this parameter should be always 1.0
                        
        const double element_mass  = element->GetMass();
        const double neighbor_mass = neighbor->GetMass();
        const double equiv_mass    = element_mass * neighbor_mass / (element_mass + neighbor_mass);
        
        // Viscous parameter taken from J.S.Marshall, 'Discrete-element modeling of particle aerosol flows', section 4.3. Twisting resistance
        const double alpha = 0.9; // Hardcoded only for testing purposes. This value depends on the restitution coefficient and goes from 0.1 to 1.0
        const double visc_param = 0.5 * equivalent_radius * equivalent_radius * alpha * sqrt(1.33333333333333333 * equiv_mass * equiv_young * equivalent_radius);
             

        //equiv_young or G in torsor??
        LocalRotationalMoment[0] -= (rot_k * equiv_young * Inertia_I * LocalDeltaRotatedAngle[0] / distance + visc_param * LocalDeltaAngularVelocity[0]);
        LocalRotationalMoment[1] -= (rot_k * equiv_young * Inertia_I * LocalDeltaRotatedAngle[1] / distance + visc_param * LocalDeltaAngularVelocity[1]);
        LocalRotationalMoment[2] -= (rot_k * equiv_young * Inertia_J * LocalDeltaRotatedAngle[2] / distance + visc_param * LocalDeltaAngularVelocity[2]);

        // Judge if the rotation spring is broken or not
        /*
        double ForceN  = LocalElasticContactForce[2];
        double ForceS  = sqrt(LocalElasticContactForce[0] * LocalElasticContactForce[0] + LocalElasticContactForce[1] * LocalElasticContactForce[1]);
        double MomentS = sqrt(LocalRotaSpringMoment[0] * LocalRotaSpringMoment[0] + LocalRotaSpringMoment[1] * LocalRotaSpringMoment[1]);
        double MomentN = LocalRotaSpringMoment[2];
        // bending stress and axial stress add together, use edge of the bar will failure first
        double TensiMax = -ForceN / calculation_area + MomentS        / Inertia_I * equiv_radius;
        double ShearMax =  ForceS  / calculation_area + fabs(MomentN)  / Inertia_J * equiv_radius;
        if (TensiMax > equiv_tension || ShearMax > equiv_cohesion) {
            mRotaSpringFailureType[i_neighbor_count] = 1;
            LocalRotaSpringMoment[0] = LocalRotaSpringMoment[1] = LocalRotaSpringMoment[2] = 0.0;
            //LocalRotaSpringMoment[1] = 0.0;
            //LocalRotaSpringMoment[2] = 0.0;
        }
        */
        GeometryFunctions::VectorLocal2Global(LocalCoordSystem, LocalRotationalMoment, mContactMoment);

    }//ComputeParticleRotationalMoments

} /* namespace Kratos.*/