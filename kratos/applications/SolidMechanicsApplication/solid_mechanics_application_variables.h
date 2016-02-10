//--------------------------------------------------------------------
//    |  /           |                                               .
//    ' /   __| _` | __|  _ \   __|                                  .
//    . \  |   (   | |   (   |\__ \                                  .
//   _|\_\_|  \__,_|\__|\___/ ____/                                  .
//                 KRATOS  __|   _ \  |   |  _ \                     .
//                       \__ \  (   | |   | | , )                    .      
//                       |___/ \___/ ___|_| ___/ MECHANICS           .            
//			                                             .
//   License:(BSD)	  SolidMechanicsApplication/license.txt      .
//   Main authors:        Josep Maria Carbonell                      .
//                        ..                                         .
//--------------------------------------------------------------------
//
//   Project Name:        KratosSolidMechanicsApplication $
//   Last modified by:    $Author:            JMCarbonell $
//   Date:                $Date:            February 2016 $
//   Revision:            $Revision:                  0.0 $
//
//

#if !defined(KRATOS_SOLID_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED )
#define  KRATOS_SOLID_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED

// System includes

// External includes


// Project includes
#include "includes/define.h"
#include "includes/kratos_application.h"
#include "includes/variables.h"

namespace Kratos
{
  ///@name Type Definitions
  ///@{
  typedef array_1d<double,3> Vector3;
  typedef array_1d<double,6> Vector6;
  ///@}

  ///@name Kratos Globals
  ///@{

  //Define Variables

  //for explicit schemes
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( SOLID_MECHANICS_APPLICATION, MIDDLE_VELOCITY )

  //solution
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, bool, COMPUTE_DYNAMIC_TANGENT )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, int, WRITE_ID )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, PREVIOUS_DELTA_TIME )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, NEWMARK_BETA )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, NEWMARK_GAMMA )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, RAYLEIGH_ALPHA )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, RAYLEIGH_BETA )

  //constitutive law
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, std::string, CONSTITUTIVE_LAW_NAME )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, ConstitutiveLaw::Pointer, CONSTITUTIVE_LAW_POINTER )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Matrix, CONSTITUTIVE_MATRIX )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Matrix, DEFORMATION_GRADIENT )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, DETERMINANT_F )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, bool, IMPLEX  )

  //condition nodal load variables
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( SOLID_MECHANICS_APPLICATION, POINT_LOAD )
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( SOLID_MECHANICS_APPLICATION, LINE_LOAD )
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( SOLID_MECHANICS_APPLICATION, SURFACE_LOAD )

  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( SOLID_MECHANICS_APPLICATION, LOCAL_POINT_LOAD )
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( SOLID_MECHANICS_APPLICATION, LOCAL_LINE_LOAD )
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( SOLID_MECHANICS_APPLICATION, LOCAL_SURFACE_LOAD )

  //material orientation
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector3, MATERIAL_ORIENTATION_DX )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector3, MATERIAL_ORIENTATION_DY )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector3, MATERIAL_ORIENTATION_DZ )

  //othotropic/anisotropic constants
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, YOUNG_MODULUS_X )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, YOUNG_MODULUS_Y )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, YOUNG_MODULUS_Z )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, SHEAR_MODULUS_XY )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, SHEAR_MODULUS_YZ )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, SHEAR_MODULUS_XZ )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, POISSON_RATIO_XY )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, POISSON_RATIO_YZ )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, POISSON_RATIO_XZ )

  //material : hyperelastic_plastic
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, NORM_ISOCHORIC_STRESS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, PLASTIC_STRAIN )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, DELTA_PLASTIC_STRAIN )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, ISOTROPIC_HARDENING_MODULUS  )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, KINEMATIC_HARDENING_MODULUS  )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, HARDENING_EXPONENT )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, REFERENCE_HARDENING_MODULUS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, INFINITY_HARDENING_MODULUS )

  //material : isotropic damage
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, DAMAGE_VARIABLE )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, DAMAGE_THRESHOLD )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, STRENGTH_RATIO )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, FRACTURE_ENERGY )

  //thermal
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, THERMAL_EXPANSION_COEFFICIENT )  
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, REFERENCE_TEMPERATURE )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, PLASTIC_DISSIPATION )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, DELTA_PLASTIC_DISSIPATION )

  //element
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector, RESIDUAL_VECTOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector, EXTERNAL_FORCES_VECTOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector, INTERNAL_FORCES_VECTOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector, CONTACT_FORCES_VECTOR )

  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector, CAUCHY_STRESS_VECTOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector, PK2_STRESS_VECTOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Matrix, ALMANSI_STRAIN_TENSOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector, GREEN_LAGRANGE_STRAIN_VECTOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Vector, ALMANSI_STRAIN_VECTOR )

  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Matrix, MATERIAL_STIFFNESS_MATRIX )
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Matrix, GEOMETRIC_STIFFNESS_MATRIX )

  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, VON_MISES_STRESS )

  //nodal dofs
  KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, double, PRESSURE_REACTION )

  //deprecated
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( SOLID_MECHANICS_APPLICATION, IMPOSED_DISPLACEMENT )

  //already in kratos core
  //KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Matrix, CAUCHY_STRESS_TENSOR );
  //KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Matrix, PK2_STRESS_TENSOR );
  //KRATOS_DEFINE_APPLICATION_VARIABLE( SOLID_MECHANICS_APPLICATION, Matrix, GREEN_LAGRANGE_STRAIN_TENSOR );


  ///@}

}

#endif	/* KRATOS_SOLID_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED */