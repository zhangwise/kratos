//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Jordi Cotela
//


#if !defined(KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED )
#define  KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED

// System includes

// External includes


// Project includes
#include "includes/define.h"
#include "includes/kratos_application.h"
#include "includes/variables.h"
#include "includes/dem_variables.h"  //TODO: must be removed eventually
#include "includes/legacy_structural_app_vars.h"  //TODO: must be removed eventually

namespace Kratos
{
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, int,PATCH_INDEX)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,TAUONE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,TAUTWO)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,PRESSURE_MASSMATRIX_COEFFICIENT)
//KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,Y_WALL)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,SUBSCALE_PRESSURE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,C_DES)
//    KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,C_SMAGORINSKY)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, SUBSCALE_VELOCITY)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, VORTICITY)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, COARSE_VELOCITY)

// Non-Newtonian constitutive relations
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, REGULARIZATION_COEFFICIENT)

// To be removed
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, BINGHAM_SMOOTHER)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, GEL_STRENGTH)

// Q-Criterion (for vortex visualization)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,Q_VALUE)

// Vorticity
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,VORTICITY_MAGNITUDE)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS(FLUID_DYNAMICS_APPLICATION, RECOVERED_PRESSURE_GRADIENT)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, Vector,NODAL_WEIGHTS)
}

#endif	/* KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED */
