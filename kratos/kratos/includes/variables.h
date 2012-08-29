/*
==============================================================================
Kratos
A General Purpose Software for Multi-Physics Finite Element Analysis
Version 1.0 (Released on march 05, 2007).

Copyright 2007
Pooyan Dadvand, Riccardo Rossi
pooyan@cimne.upc.edu
rrossi@cimne.upc.edu
CIMNE (International Center for Numerical Methods in Engineering),
Gran Capita' s/n, 08034 Barcelona, Spain

Permission is hereby granted, free  of charge, to any person obtaining
a  copy  of this  software  and  associated  documentation files  (the
"Software"), to  deal in  the Software without  restriction, including
without limitation  the rights to  use, copy, modify,  merge, publish,
distribute,  sublicense and/or  sell copies  of the  Software,  and to
permit persons to whom the Software  is furnished to do so, subject to
the following condition:

Distribution of this code for  any  commercial purpose  is permissible
ONLY BY DIRECT ARRANGEMENT WITH THE COPYRIGHT OWNER.

The  above  copyright  notice  and  this permission  notice  shall  be
included in all copies or substantial portions of the Software.

THE  SOFTWARE IS  PROVIDED  "AS  IS", WITHOUT  WARRANTY  OF ANY  KIND,
EXPRESS OR  IMPLIED, INCLUDING  BUT NOT LIMITED  TO THE  WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT  SHALL THE AUTHORS OR COPYRIGHT HOLDERS  BE LIABLE FOR ANY
CLAIM, DAMAGES OR  OTHER LIABILITY, WHETHER IN AN  ACTION OF CONTRACT,
TORT  OR OTHERWISE, ARISING  FROM, OUT  OF OR  IN CONNECTION  WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

==============================================================================
*/

//
//   Project Name:        Kratos
//   Last Modified by:    $Author: nagel $
//   Date:                $Date: 2009-03-25 08:24:41 $
//   Revision:            $Revision: 1.18 $
//
//


#if !defined(KRATOS_VARIABLES_H_INCLUDED )
#define  KRATOS_VARIABLES_H_INCLUDED



// System includes
#include <string>
#include <iostream>

// External includes


// Project includes
#include "includes/define.h"
#include "containers/variable.h"
#include "containers/variable_component.h"
#include "containers/vector_component_adaptor.h"
#include "includes/kratos_components.h"
#include "includes/ublas_interface.h"
#include "containers/array_1d.h"
#include "containers/weak_pointer_vector.h"


namespace Kratos
{
KRATOS_DEFINE_VARIABLE(bool, IS_INACTIVE)
KRATOS_DEFINE_VARIABLE(int, OSS_SWITCH)
KRATOS_DEFINE_VARIABLE(double, DYNAMIC_TAU)
KRATOS_DEFINE_VARIABLE(double, ERASE_FLAG)

    KRATOS_DEFINE_VARIABLE(double, PARTITION_INDEX)
    KRATOS_DEFINE_VARIABLE(vector<int>, NEIGHBOURS_INDICES)
    KRATOS_DEFINE_VARIABLE(int, NL_ITERATION_NUMBER)
    KRATOS_DEFINE_VARIABLE(int, FRACTIONAL_STEP)
    KRATOS_DEFINE_VARIABLE(double, TIME)
    KRATOS_DEFINE_VARIABLE(int, TIME_STEPS)
    KRATOS_DEFINE_VARIABLE(double, START_TIME)
    KRATOS_DEFINE_VARIABLE(double, END_TIME)
    KRATOS_DEFINE_VARIABLE(double, DELTA_TIME)
    KRATOS_DEFINE_VARIABLE(double, TEMPERATURE)
    KRATOS_DEFINE_VARIABLE(double, TEMPERATURE_OLD_IT)
    KRATOS_DEFINE_VARIABLE(double, PRESSURE)
    KRATOS_DEFINE_VARIABLE(double, DENSITY)
    KRATOS_DEFINE_VARIABLE(double, VISCOSITY)
    KRATOS_DEFINE_VARIABLE(double, KINEMATIC_VISCOSITY)
    KRATOS_DEFINE_VARIABLE(double, DYNAMIC_VISCOSITY)
    KRATOS_DEFINE_VARIABLE(double, ERROR_RATIO)
    KRATOS_DEFINE_VARIABLE(double, DIVPROJ)
    KRATOS_DEFINE_VARIABLE(double, THAWONE)
    KRATOS_DEFINE_VARIABLE(double, THAWTWO)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(ANGULAR_ACCELERATION)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(ANGULAR_VELOCITY)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(ACCELERATION)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(VELOCITY)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DISPLACEMENT)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(ROTATION)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MOMENTUM)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(REACTION)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(BODY_FORCE)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(SEEPAGE_DRAG)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(NORMAL)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(FORCE)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MOMENT)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(FORCE_CM)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MOMENTUM_CM)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(ADVPROJ)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MASS)
    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(RHS)
    KRATOS_DEFINE_VARIABLE(double, RHS_WATER)
    KRATOS_DEFINE_VARIABLE(double, RHS_AIR)


KRATOS_DEFINE_VARIABLE(double, WEIGHT_FATHER_NODES)

KRATOS_DEFINE_VARIABLE(Matrix, INERTIA )

//for structural application TO BE REMOVED
KRATOS_DEFINE_VARIABLE(Vector, MATERIAL_PARAMETERS)
KRATOS_DEFINE_VARIABLE(bool, USE_DISTRIBUTED_PROPERTIES)
KRATOS_DEFINE_VARIABLE(Vector, INTERNAL_VARIABLES)
KRATOS_DEFINE_VARIABLE(int, WRINKLING_APPROACH )
KRATOS_DEFINE_VARIABLE(Matrix, GREEN_LAGRANGE_STRAIN_TENSOR)
KRATOS_DEFINE_VARIABLE(Matrix, PK2_STRESS_TENSOR )
KRATOS_DEFINE_VARIABLE(Matrix, CAUCHY_STRESS_TENSOR )
KRATOS_DEFINE_VARIABLE(Matrix, AUXILIARY_MATRIX_1 )
KRATOS_DEFINE_VARIABLE(double, YOUNG_MODULUS )
KRATOS_DEFINE_VARIABLE(double, POISSON_RATIO )
KRATOS_DEFINE_VARIABLE(double, MIU )
KRATOS_DEFINE_VARIABLE(double, LAMBDA )
KRATOS_DEFINE_VARIABLE(double, THICKNESS )
KRATOS_DEFINE_VARIABLE(double, NEGATIVE_FACE_PRESSURE )
KRATOS_DEFINE_VARIABLE(double, POSITIVE_FACE_PRESSURE )
KRATOS_DEFINE_VARIABLE(double, INTERNAL_FRICTION_ANGLE)
    KRATOS_DEFINE_VARIABLE(double, PERMEABILITY_28_DAYS)
    KRATOS_DEFINE_VARIABLE(double, PERMEABILITY_1_DAY)
    KRATOS_DEFINE_VARIABLE(double, PERMEABILITY_TRANSITION)


    

//CONTACT_LINK_MASTER is defined in condition.h
// 	KRATOS_DEFINE_VARIABLE( Condition::Pointer, CONTACT_LINK_MASTER )
//CONTACT_LINK_SLAVE is defined in condition.h
// 	KRATOS_DEFINE_VARIABLE( Condition::Pointer, CONTACT_LINK_SLAVE )

KRATOS_DEFINE_VARIABLE( double, PRESSURE_DT )
KRATOS_DEFINE_VARIABLE(double, DP_EPSILON )
KRATOS_DEFINE_VARIABLE(Vector, INSITU_STRESS )
KRATOS_DEFINE_VARIABLE(double, DP_ALPHA1 )
KRATOS_DEFINE_VARIABLE(double, DP_K )
KRATOS_DEFINE_VARIABLE(int, CALCULATE_INSITU_STRESS )
KRATOS_DEFINE_VARIABLE(Vector, PENALTY )
KRATOS_DEFINE_VARIABLE(Vector, PENALTY_T )
KRATOS_DEFINE_VARIABLE(double, FRICTION_COEFFICIENT )
KRATOS_DEFINE_VARIABLE(Vector, LAMBDAS )
KRATOS_DEFINE_VARIABLE(Matrix, LAMBDAS_T )
KRATOS_DEFINE_VARIABLE(Vector, GAPS )
KRATOS_DEFINE_VARIABLE(Vector, DELTA_LAMBDAS )
KRATOS_DEFINE_VARIABLE(Matrix, DELTA_LAMBDAS_T )
KRATOS_DEFINE_VARIABLE(int, CONTACT_SLAVE_INTEGRATION_POINT_INDEX )
KRATOS_DEFINE_VARIABLE( Matrix, CONTACT_LINK_M )
KRATOS_DEFINE_VARIABLE( int, CONTACT_DOUBLE_CHECK )
KRATOS_DEFINE_VARIABLE( int, IS_CONTACT_MASTER )
KRATOS_DEFINE_VARIABLE( int, IS_CONTACT_SLAVE )
KRATOS_DEFINE_VARIABLE( Vector, STICK )
KRATOS_DEFINE_VARIABLE( int, FIRST_TIME_STEP )
KRATOS_DEFINE_VARIABLE( int, QUASI_STATIC_ANALYSIS )
KRATOS_DEFINE_VARIABLE( Vector, NORMAL_STRESS )
KRATOS_DEFINE_VARIABLE( Vector, TANGENTIAL_STRESS )
KRATOS_DEFINE_VARIABLE( double, NORMAL_CONTACT_STRESS )
KRATOS_DEFINE_VARIABLE( double, TANGENTIAL_CONTACT_STRESS )
KRATOS_DEFINE_VARIABLE( double, CONTACT_STICK )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE )
KRATOS_DEFINE_VARIABLE( double, REACTION_WATER_PRESSURE )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE_DT )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE_ACCELERATION )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE_NULL )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE_NULL_DT )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE_NULL_ACCELERATION )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE_EINS )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE_EINS_DT )
KRATOS_DEFINE_VARIABLE( double, WATER_PRESSURE_EINS_ACCELERATION )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE )
KRATOS_DEFINE_VARIABLE( double, REACTION_AIR_PRESSURE )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE_DT )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE_ACCELERATION )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE_NULL )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE_NULL_DT )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE_NULL_ACCELERATION )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE_EINS )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE_EINS_DT )
KRATOS_DEFINE_VARIABLE( double, AIR_PRESSURE_EINS_ACCELERATION )
KRATOS_DEFINE_VARIABLE( double, SUCTION )
KRATOS_DEFINE_VARIABLE( double, YIELD_STRESS )

KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DISPLACEMENT_OLD)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DISPLACEMENT_DT)
// 	KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(ACCELERATION)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DISPLACEMENT_NULL)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DISPLACEMENT_NULL_DT)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(ACCELERATION_NULL)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DISPLACEMENT_EINS)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DISPLACEMENT_EINS_DT)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(ACCELERATION_EINS)
KRATOS_DEFINE_VARIABLE( Matrix, ELASTIC_LEFT_CAUCHY_GREEN_OLD )
KRATOS_DEFINE_VARIABLE(int, ACTIVATION_LEVEL)
KRATOS_DEFINE_VARIABLE(double, FLAG_VARIABLE )
KRATOS_DEFINE_VARIABLE(double, DISTANCE )
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( LAGRANGE_DISPLACEMENT )
KRATOS_DEFINE_VARIABLE( double, LAGRANGE_AIR_PRESSURE )
KRATOS_DEFINE_VARIABLE( double, LAGRANGE_WATER_PRESSURE )
KRATOS_DEFINE_VARIABLE( double, LAGRANGE_TEMPERATURE )

//for ALE appliation TO BE REMOVED
KRATOS_DEFINE_VARIABLE(double, IS_INLET )
KRATOS_DEFINE_VARIABLE(double, IS_LAGRANGIAN_INLET )
KRATOS_DEFINE_VARIABLE(double, IS_INTERFACE )
KRATOS_DEFINE_VARIABLE(double, IS_VISITED )
KRATOS_DEFINE_VARIABLE(double, IS_EROSIONABLE)

//for electric_application
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL )
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL_DT )
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL_DT2 )
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL_NULL )
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL_EINS )
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL_NULL_DT )
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL_EINS_DT )
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL_NULL_DT2 )
KRATOS_DEFINE_VARIABLE(double, ELECTRIC_POTENTIAL_EINS_DT2 )
KRATOS_DEFINE_VARIABLE(double, LAGRANGE_ELECTRIC_POTENTIAL )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION_DT )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION_DT2 )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION_NULL )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION_EINS )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION_NULL_DT )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION_EINS_DT )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION_NULL_DT2 )
KRATOS_DEFINE_VARIABLE(double, CONCENTRATION_EINS_DT2 )
KRATOS_DEFINE_VARIABLE(double, LAGRANGE_CONCENTRATION )

//for PFEM application TO BE REMOVED
KRATOS_DEFINE_VARIABLE(double,  NODAL_AREA)
KRATOS_DEFINE_VARIABLE(double,  NODAL_H)
KRATOS_DEFINE_VARIABLE(double,  IS_STRUCTURE)
KRATOS_DEFINE_VARIABLE(double,  IS_POROUS)
KRATOS_DEFINE_VARIABLE(double,  IS_WATER)
KRATOS_DEFINE_VARIABLE(double,  IS_FLUID)
KRATOS_DEFINE_VARIABLE(double,  IS_BOUNDARY)
KRATOS_DEFINE_VARIABLE(double,  IS_FREE_SURFACE)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(NORMAL_TO_WALL)
KRATOS_DEFINE_VARIABLE(double,  IS_WATER_ELEMENT)

KRATOS_DEFINE_VARIABLE(double, BULK_MODULUS )
KRATOS_DEFINE_VARIABLE(double, SATURATION )
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( GRAVITY )
KRATOS_DEFINE_VARIABLE(double, DENSITY_WATER )
KRATOS_DEFINE_VARIABLE(double, VISCOSITY_WATER)
KRATOS_DEFINE_VARIABLE(double, DENSITY_AIR )
KRATOS_DEFINE_VARIABLE(double, VISCOSITY_AIR)
KRATOS_DEFINE_VARIABLE(double, POROSITY )
KRATOS_DEFINE_VARIABLE(double, DIAMETER )
KRATOS_DEFINE_VARIABLE(double, LIN_DARCY_COEF )
KRATOS_DEFINE_VARIABLE(double, NONLIN_DARCY_COEF )
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(STRUCTURE_VELOCITY)

KRATOS_DEFINE_VARIABLE(double, AIR_ENTRY_VALUE )
KRATOS_DEFINE_VARIABLE(double, FIRST_SATURATION_PARAM )
KRATOS_DEFINE_VARIABLE(double, SECOND_SATURATION_PARAM )
KRATOS_DEFINE_VARIABLE(double, PERMEABILITY_WATER )
KRATOS_DEFINE_VARIABLE(double, PERMEABILITY_AIR )
KRATOS_DEFINE_VARIABLE(double, BULK_AIR )
KRATOS_DEFINE_VARIABLE(int, SCALE )
KRATOS_DEFINE_VARIABLE(double, C_SMAGORINSKY )
KRATOS_DEFINE_VARIABLE(double, MOLECULAR_VISCOSITY )
KRATOS_DEFINE_VARIABLE(double, TURBULENT_VISCOSITY )

// Used in convection_diffusion and FluidDynamics
KRATOS_DEFINE_VARIABLE(double,  TEMP_CONV_PROJ)
KRATOS_DEFINE_VARIABLE(double,  CONVECTION_COEFFICIENT)


KRATOS_DEFINE_VARIABLE(double,AIR_SOUND_VELOCITY)
KRATOS_DEFINE_VARIABLE(double,WATER_SOUND_VELOCITY)
KRATOS_DEFINE_VARIABLE(double,SOUND_VELOCITY)

KRATOS_DEFINE_VARIABLE( double, MU )
KRATOS_DEFINE_VARIABLE(double, EFFECTIVE_VISCOSITY)
KRATOS_DEFINE_VARIABLE( double, EQ_STRAIN_RATE )
KRATOS_DEFINE_VARIABLE(double, TAU )
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( FACE_LOAD )
KRATOS_DEFINE_VARIABLE( int, IS_JACK_LINK )

//for xfem application
KRATOS_DEFINE_VARIABLE(double, CRACK_OPENING)
KRATOS_DEFINE_VARIABLE(double, CRACK_TRANSLATION)

KRATOS_DEFINE_VARIABLE( double , SUCTION )

// for mengmeng application
//       KRATOS_DEFINE_VARIABLE( double, TEMPERATURE_NULL )
//       KRATOS_DEFINE_VARIABLE( double, TEMPERATURE_EINS )
//       KRATOS_DEFINE_VARIABLE( double, SURFACE_FLOW_HEAT )
//       KRATOS_DEFINE_VARIABLE( double, SURFACE_FLOW_WATER )
//       KRATOS_DEFINE_VARIABLE( double, ICE_VOLUME_FRACTION )
//       KRATOS_DEFINE_VARIABLE( double, ICE_VOLUME_FRACTION_NULL )
//       KRATOS_DEFINE_VARIABLE( double, ICE_VOLUME_FRACTION_EINS )

KRATOS_DEFINE_VARIABLE(double, ARRHENIUS )
KRATOS_DEFINE_VARIABLE(double, ARRHENIUSAUX )
KRATOS_DEFINE_VARIABLE(double, ARRHENIUSAUX_ )
KRATOS_DEFINE_VARIABLE(double, PRESSUREAUX)
KRATOS_DEFINE_VARIABLE(double, NODAL_MAUX)
KRATOS_DEFINE_VARIABLE(double, NODAL_PAUX)
KRATOS_DEFINE_VARIABLE(double, FACE_HEAT_FLUX)
KRATOS_DEFINE_VARIABLE(double, HEAT_FLUX)
KRATOS_DEFINE_VARIABLE(double, TC )
KRATOS_DEFINE_VARIABLE(double, IS_BURN )
KRATOS_DEFINE_VARIABLE(double, CONDUCTIVITY)
KRATOS_DEFINE_VARIABLE(double, SPECIFIC_HEAT)
KRATOS_DEFINE_VARIABLE(double, IS_DRIPPING )
KRATOS_DEFINE_VARIABLE(double,  IS_PERMANENT)
KRATOS_DEFINE_VARIABLE(double, MATERIAL_VARIABLE)
KRATOS_DEFINE_VARIABLE(double, IS_WALL )
KRATOS_DEFINE_VARIABLE(double, FUEL)
KRATOS_DEFINE_VARIABLE(double, YF)
KRATOS_DEFINE_VARIABLE(double, YO)
KRATOS_DEFINE_VARIABLE(double, YI)
KRATOS_DEFINE_VARIABLE(double, M)
KRATOS_DEFINE_VARIABLE(double, Y1)
KRATOS_DEFINE_VARIABLE(double, Y2)
KRATOS_DEFINE_VARIABLE(double, YP)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_1)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_2)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_3)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_4)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_5)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_6)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_7)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_8)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_9)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_10)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_11)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_12)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_13)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_14)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_15)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_16)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_17)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_18)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_19)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_20)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_21)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_22)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_23)
KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY_24)
KRATOS_DEFINE_VARIABLE(double,EMISSIVITY)
KRATOS_DEFINE_VARIABLE(double,ENTHALPY)
KRATOS_DEFINE_VARIABLE(double,MIXTURE_FRACTION)
KRATOS_DEFINE_VARIABLE(double,rhoD)
KRATOS_DEFINE_VARIABLE(double,Yfuel)
KRATOS_DEFINE_VARIABLE(double,Yox)
KRATOS_DEFINE_VARIABLE(double,Ypr)
KRATOS_DEFINE_VARIABLE(double,Hfuel)
KRATOS_DEFINE_VARIABLE(double,Hpr)
KRATOS_DEFINE_VARIABLE(double,Hpr1)
KRATOS_DEFINE_VARIABLE(double,Hox)
KRATOS_DEFINE_VARIABLE(double, xi)
KRATOS_DEFINE_VARIABLE(double, a)
KRATOS_DEFINE_VARIABLE(double, b)
KRATOS_DEFINE_VARIABLE(double,YCH4)
KRATOS_DEFINE_VARIABLE(double,YO2)
KRATOS_DEFINE_VARIABLE(double,YCO2)
KRATOS_DEFINE_VARIABLE(double,YH2O)
KRATOS_DEFINE_VARIABLE(double,YN2)


KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(xi_c)
KRATOS_DEFINE_VARIABLE(double,INCIDENT_RADIATION_FUNCTION)

KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY1)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY2)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY3)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY4)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY5)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY6)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY7)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY8)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY9)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY10)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY11)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY12)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY13)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY14)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY15)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY16)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY17)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY18)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY19)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY20)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY21)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY22)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY23)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(MESH_VELOCITY24)



KRATOS_DEFINE_VARIABLE(double,ABSORPTION_COEFFICIENT)
KRATOS_DEFINE_VARIABLE(double,STEFAN_BOLTZMANN_CONSTANT)
//KRATOS_DEFINE_VARIABLE(double,RADIATIVE_INTENSITY)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DIRECTION)
KRATOS_DEFINE_VARIABLE(double, NODAL_SWITCH)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(Y)

KRATOS_DEFINE_VARIABLE(double, SWITCH_TEMPERATURE)


//for incompressible fluid application
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(FRACT_VEL)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(PRESS_PROJ)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(CONV_PROJ)
KRATOS_DEFINE_VARIABLE( double, NODAL_MASS)
KRATOS_DEFINE_VARIABLE( double,  AUX_INDEX)
KRATOS_DEFINE_VARIABLE( double,  EXTERNAL_PRESSURE)
KRATOS_DEFINE_VARIABLE( double, PRESSURE_OLD_IT )
KRATOS_DEFINE_VARIABLE( Vector, BDF_COEFFICIENTS )

//for level set application
KRATOS_DEFINE_VARIABLE(int, REFINEMENT_LEVEL)
KRATOS_DEFINE_VARIABLE(double,  IS_DIVIDED)
KRATOS_DEFINE_VARIABLE(bool, IS_DUPLICATED)
KRATOS_DEFINE_VARIABLE(bool, SPLIT_NODAL)
KRATOS_DEFINE_VARIABLE(bool, SPLIT_ELEMENT)
KRATOS_DEFINE_VARIABLE(double,  MIN_DT)
KRATOS_DEFINE_VARIABLE(double,  MAX_DT)

KRATOS_DEFINE_VARIABLE(double,  VEL_ART_VISC)
KRATOS_DEFINE_VARIABLE(double,  PR_ART_VISC)
KRATOS_DEFINE_VARIABLE(double, INTERNAL_ENERGY )

//for DEM Application
KRATOS_DEFINE_VARIABLE(std::size_t,  NUMBER_OF_NEIGHBOURS)
KRATOS_DEFINE_VARIABLE(double,  RADIUS)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_MASS)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_INERTIA)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_DENSITY)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_STATIC_FRICTION_COEF)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_DYNAMIC_FRICTION_COEF)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_STIFFNESS)
KRATOS_DEFINE_VARIABLE(double,  VISCO_DAMP_COEFF)
KRATOS_DEFINE_VARIABLE(double,  RESTITUTION_COEFF)        
KRATOS_DEFINE_VARIABLE(int, PARTICLE_MATERIAL)
KRATOS_DEFINE_VARIABLE(double, PARTICLE_COHESION)
KRATOS_DEFINE_VARIABLE(int, PARTICLE_CONTINUUM)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_TENSION)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_FRICTION)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_LOCAL_DAMP_RATIO)
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_FAILURE_ID)
KRATOS_DEFINE_VARIABLE(double,  SEARCH_RADIUS_EXTENSION)
KRATOS_DEFINE_VARIABLE( bool, DELTA_OPTION )
KRATOS_DEFINE_VARIABLE( bool,CONTINUUM_OPTION )
KRATOS_DEFINE_VARIABLE(int, CASE_OPTION)
KRATOS_DEFINE_VARIABLE(int, BOUNDING_BOX_OPTION)
KRATOS_DEFINE_VARIABLE(int, ROTATION_OPTION)
KRATOS_DEFINE_VARIABLE(int, ROTATION_SPRING_OPTION)
KRATOS_DEFINE_VARIABLE( int, FORCE_CALCULATION_TYPE)
KRATOS_DEFINE_VARIABLE( int, DAMP_TYPE )
KRATOS_DEFINE_VARIABLE( double, GROUP_ID )

KRATOS_DEFINE_VARIABLE( int, GLOBAL_VARIABLES_OPTION )
KRATOS_DEFINE_VARIABLE( double, GLOBAL_KN )
KRATOS_DEFINE_VARIABLE( double, GLOBAL_KT )
KRATOS_DEFINE_VARIABLE( double, GLOBAL_KR )
KRATOS_DEFINE_VARIABLE( double, GLOBAL_RN )
KRATOS_DEFINE_VARIABLE( double, GLOBAL_RT )
KRATOS_DEFINE_VARIABLE( double, GLOBAL_RR )
KRATOS_DEFINE_VARIABLE( double, GLOBAL_FRI_ANG )


KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DELTA_DISPLACEMENT)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(DELTA_VELOCITY)        
        
typedef vector<array_1d<double,3> > VectorArray3Double;

KRATOS_DEFINE_VARIABLE( Vector, PARTICLE_CONTACT_DELTA )
KRATOS_DEFINE_VARIABLE( Vector, PARTICLE_INITIAL_DELTA )
// KRATOS_DEFINE_VARIABLE( vector<int>, PARTICLE_CONTACT_FAILURE_ID )
KRATOS_DEFINE_VARIABLE( Vector, PARTICLE_CONTACT_FAILURE_ID ) 
KRATOS_DEFINE_VARIABLE( VectorArray3Double, PARTICLE_CONTACT_FORCES )
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(APPLIED_FORCE)

//dummy variables:   
KRATOS_DEFINE_VARIABLE(double,  DUMMY_FORCES)
KRATOS_DEFINE_VARIABLE(int,  DUMMY_SWITCH)


// varibles for DEM and DEM-FEM

KRATOS_DEFINE_VARIABLE(double,  DEM_DELTA_TIME);

KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(AUX_VEL)

KRATOS_DEFINE_VARIABLE(Vector,     PARTICLE_BLOCK_CONTACT_FAILURE_ID)
KRATOS_DEFINE_VARIABLE(Vector,     PARTICLE_BLOCK_CONTACT_FORCE)
KRATOS_DEFINE_VARIABLE(Vector,     PARTICLE_BLOCK_IF_INITIAL_CONTACT)
//KRATOS_DEFINE_VARIABLE(WeakPointerVector<Element >,     NEIGHBOUR_PARTICLE_BLOCK_ELEMENTS)

KRATOS_DEFINE_VARIABLE(Vector,     PARTICLE_ROTATE_SPRING_FAILURE_TYPE)

typedef vector<array_1d<double,3> > VectorArray3Double;
KRATOS_DEFINE_VARIABLE( VectorArray3Double, PARTICLE_ROTATE_SPRING_MOMENT )

KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( PARTICLE_MOMENT );
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( PARTICLE_ROTATION_ANGLE );
KRATOS_DEFINE_VARIABLE(double,  PARTICLE_MOMENT_OF_INERTIA);

KRATOS_DEFINE_VARIABLE(Vector,     INITIAL_AXES_TRACKING)
KRATOS_DEFINE_VARIABLE(int,     plot_OPTIONS)



// for Vulcan application
KRATOS_DEFINE_VARIABLE(double,  LAST_AIR)
KRATOS_DEFINE_VARIABLE(double,  PRESSURES)
KRATOS_DEFINE_VARIABLE(double,  TEMPERATURES)
KRATOS_DEFINE_VARIABLE(double,  MATERIAL)
KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(VELOCITIES)
KRATOS_DEFINE_VARIABLE(double,  SOLID_FRACTION)
KRATOS_DEFINE_VARIABLE(double,  SOLID_FRACTION_RATE)
KRATOS_DEFINE_VARIABLE(double,  LATENT_HEAT)
KRATOS_DEFINE_VARIABLE(double,  SOLID_TEMPERATURE );
KRATOS_DEFINE_VARIABLE(double,  FLUID_TEMPERATURE ); 
KRATOS_DEFINE_VARIABLE(double,  AMBIENT_TEMPERATURE ); 

}  // namespace Kratos.
#endif // KRATOS_VARIABLES_H_INCLUDED  defined 
