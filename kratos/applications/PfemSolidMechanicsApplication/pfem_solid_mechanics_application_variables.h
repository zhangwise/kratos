//-------------------------------------------------------------
//         ___  __           ___      _ _    _ 
//  KRATOS| _ \/ _|___ _ __ / __| ___| (_)__| |
//        |  _/  _/ -_) '  \\__ \/ _ \ | / _` |
//        |_| |_| \___|_|_|_|___/\___/_|_\__,_|MECHANICS
//                                            
//  License:(BSD)    PfemSolidMechanicsApplication/license.txt
//
//  Main authors:    Josep Maria Carbonell
//                   Lluis Monforte 
//
//-------------------------------------------------------------
//
//   Project Name:        KratosPfemSolidMechanicsApplication $
//   Last modified by:    $Author:                JMCarbonell $
//   Date:                $Date:                February 2016 $
//   Revision:            $Revision:                      0.0 $
//
//


#if !defined(KRATOS_PFEM_SOLID_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED )
#define  KRATOS_PFEM_SOLID_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED

// System includes

// External includes


// Project includes
#include "includes/define.h"
#include "includes/kratos_application.h"
#include "includes/variables.h"

#include "solid_mechanics_application_variables.h"

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

  //solution
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, int, NUMBER_OF_ACTIVE_CONTACTS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, int, NUMBER_OF_STICK_CONTACTS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, int, NUMBER_OF_SLIP_CONTACTS )

  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, IMPOSED_WATER_PRESSURE )
  //geometrical

  //constitutive law   
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, MEAN_ERROR )

  //material
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, PRE_CONSOLIDATION_STRESS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, OVER_CONSOLIDATION_RATIO )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, INITIAL_SHEAR_MODULUS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, WATER_BULK_MODULUS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, PERMEABILITY )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, NORMAL_COMPRESSION_SLOPE )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, SWELLING_SLOPE )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, CRITICAL_STATE_LINE )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, ALPHA_SHEAR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, INITIAL_POROSITY )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, COHESION )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, INTERNAL_DILATANCY_ANGLE )

  //element
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, Matrix, TOTAL_CAUCHY_STRESS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, Vector, DARCY_FLOW )

  // transfer and initial state (set and get)
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, Matrix, KIRCHHOFF_STRESS_TENSOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, Vector, ELASTIC_LEFT_CAUCHY_FROM_KIRCHHOFF_STRESS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, Matrix, ELASTIC_LEFT_CAUCHY_GREEN_TENSOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, Vector, ELASTIC_LEFT_CAUCHY_GREEN_VECTOR )

  //thermal

  //mechanical

  //nodal dofs
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( PFEM_SOLID_MECHANICS_APPLICATION, OFFSET )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, Vector, BOUNDARY_NORMAL )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, SHRINK_FACTOR )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION,  double, MEAN_RADIUS )

  //domain definition
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, unsigned int, DOMAIN_LABEL )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, int         , RIGID_WALL )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double      , WALL_TIP_RADIUS )
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( PFEM_SOLID_MECHANICS_APPLICATION, WALL_REFERENCE_POINT )
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( PFEM_SOLID_MECHANICS_APPLICATION, WALL_VELOCITY )

  //contact condition
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, Condition::Pointer, MASTER_CONDITION )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, WeakPointerVector< Element >, MASTER_ELEMENTS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, WeakPointerVector< Node<3> >, MASTER_NODES )

  //contact properties
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, bool, FRICTION_ACTIVE )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, PENALTY_PARAMETER )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, LAGRANGE_MULTIPLIER_NORMAL )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, LAGRANGE_MULTIPLIER_NORMAL_REACTION )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, TAU_STAB )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, MU_STATIC )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, MU_DYNAMIC )

  // contact postprocess
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( PFEM_SOLID_MECHANICS_APPLICATION, CONTACT_STRESS )
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( PFEM_SOLID_MECHANICS_APPLICATION, EFFECTIVE_CONTACT_STRESS )
  KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( PFEM_SOLID_MECHANICS_APPLICATION, EFFECTIVE_CONTACT_FORCE )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, CONTACT_ADHESION )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, CONTACT_FRICTION_ANGLE)
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, TANGENTIAL_PENALTY_RATIO )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, CONTACT_PLASTIC_SLIP )

  // some post process variables + stress invariants
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, PRECONSOLIDATION )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, STRESS_INV_P )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, STRESS_INV_J2 )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, STRESS_INV_THETA )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, VOLUMETRIC_PLASTIC )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, INCR_SHEAR_PLASTIC )


  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, M_MODULUS )
  KRATOS_DEFINE_APPLICATION_VARIABLE( PFEM_SOLID_MECHANICS_APPLICATION, double, SIMILAR_YOUNG_MODULUS )

  ///@}

}

#endif	/* KRATOS_PFEM_SOLID_MECHANICS_APPLICATION_VARIABLES_H_INCLUDED */