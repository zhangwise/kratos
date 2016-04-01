//    |  /           | 
//    ' /   __| _` | __|  _ \   __| 
//    . \  |   (   | |   (   |\__ \.
//   _|\_\_|  \__,_|\__|\___/ ____/ 
//                   Multi-Physics  
//
//  License:		 BSD License 
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Riccardo Rossi
//












// This define must be HERE
#define DKRATOS_EXPORT_INTERFACE_2 1

// System includes
#include <string>
#include <iostream>
#include <vector>

// External includes

// Project includes
#include "includes/define.h"
#include "includes/dem_variables.h"
#include "includes/kernel.h"
#include "includes/node.h"
// #include "includes/element.h"
// #include "includes/condition.h"
// #include "includes/constitutive_law.h"
// #include "includes/geometrical_object.h"

// #include "geometries/line_2d.h"
// #include "geometries/line_2d_2.h"
// #include "geometries/line_2d_3.h"
// #include "geometries/line_3d_2.h"
// #include "geometries/line_3d_3.h"
// #include "geometries/point.h"
// #include "geometries/point_2d.h"
// #include "geometries/point_3d.h"
// #include "geometries/sphere_3d_1.h"
// #include "geometries/triangle_2d_3.h"
// #include "geometries/triangle_2d_6.h"
// #include "geometries/triangle_3d_3.h"
// #include "geometries/triangle_3d_6.h"
// #include "geometries/quadrilateral_2d_4.h"
// #include "geometries/quadrilateral_2d_8.h"
// #include "geometries/quadrilateral_2d_9.h"
// #include "geometries/quadrilateral_3d_4.h"
// #include "geometries/quadrilateral_3d_8.h"
// #include "geometries/quadrilateral_3d_9.h"
// #include "geometries/tetrahedra_3d_4.h"
// #include "geometries/tetrahedra_3d_10.h"
// #include "geometries/prism_3d_6.h"
// #include "geometries/prism_3d_15.h"
// #include "geometries/hexahedra_3d_8.h"
// #include "geometries/hexahedra_3d_20.h"
// #include "geometries/hexahedra_3d_27.h"

// #include "python/add_dem_variables_to_python.h"

// #include "includes/convection_diffusion_settings.h"
// #include "includes/radiation_settings.h"

#include "includes/kratos_flags.h"

namespace Kratos
{
    
  //KRATOS_CREATE_VARIABLE( double, MOULD_AVERAGE_TEMPERATURE ) 
    KRATOS_CREATE_VARIABLE( int, PARTICLE_MATERIAL )              
    KRATOS_CREATE_VARIABLE( double, PARTICLE_MASS )
    KRATOS_CREATE_VARIABLE( double, RADIUS )
    KRATOS_CREATE_VARIABLE( double, SEARCH_TOLERANCE )
    KRATOS_CREATE_VARIABLE( double, AMPLIFIED_CONTINUUM_SEARCH_RADIUS_EXTENSION )
    KRATOS_CREATE_VARIABLE( double, DEM_DELTA_TIME )
    KRATOS_CREATE_VARIABLE( int, FIXED_MESH_OPTION )
    KRATOS_CREATE_VARIABLE( int, PARTITION_MASK )             
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( DAMP_FORCES )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( AUX_VEL )
    KRATOS_CREATE_VARIABLE( Vector, NEIGHBOURS_IDS_DOUBLE )
    KRATOS_CREATE_VARIABLE( Vector, PARTICLE_ROTATE_SPRING_FAILURE_TYPE )
    KRATOS_CREATE_VARIABLE( vector<int>, OLD_NEIGHBOURS_IDS )
    KRATOS_CREATE_VARIABLE( vector<int>, INI_NEIGHBOURS_IDS )
    KRATOS_CREATE_VARIABLE( vector<int>, CONTINUUM_INI_NEIGHBOURS_IDS )
    KRATOS_CREATE_VARIABLE( vector<int>, NEIGHBOURS_IDS )
    KRATOS_CREATE_VARIABLE( vector<int>, PARTICLE_INITIAL_FAILURE_ID )
    KRATOS_CREATE_VARIABLE( vector<int>, CONTINUUM_PARTICLE_INITIAL_FAILURE_ID )              
    KRATOS_CREATE_VARIABLE( std::string, ELEMENT_TYPE)   
    KRATOS_CREATE_VARIABLE( VectorArray3Double, PARTICLE_ROTATE_SPRING_MOMENT )
    KRATOS_CREATE_VARIABLE( int, COUPLING_TYPE)
    KRATOS_CREATE_VARIABLE( int, NON_NEWTONIAN_OPTION )
    KRATOS_CREATE_VARIABLE( int, MANUALLY_IMPOSED_DRAG_LAW_OPTION )
    KRATOS_CREATE_VARIABLE( int, DRAG_MODIFIER_TYPE )
    KRATOS_CREATE_VARIABLE( int, BUOYANCY_FORCE_TYPE )
    KRATOS_CREATE_VARIABLE( int, DRAG_FORCE_TYPE )
    KRATOS_CREATE_VARIABLE( int, VIRTUAL_MASS_FORCE_TYPE )
    KRATOS_CREATE_VARIABLE( int, LIFT_FORCE_TYPE )
    KRATOS_CREATE_VARIABLE( int, MAGNUS_FORCE_TYPE )  
    KRATOS_CREATE_VARIABLE( int, HYDRO_TORQUE_TYPE )
    KRATOS_CREATE_VARIABLE( int, FLUID_MODEL_TYPE )
    KRATOS_CREATE_VARIABLE( int, DRAG_POROSITY_CORRECTION_TYPE )
    KRATOS_CREATE_VARIABLE( double, POWER_LAW_TOLERANCE )
    KRATOS_CREATE_VARIABLE( double, PARTICLE_SPHERICITY )
    KRATOS_CREATE_VARIABLE( double, INIT_DRAG_FORCE )
    KRATOS_CREATE_VARIABLE( double, DRAG_LAW_SLOPE )
    KRATOS_CREATE_VARIABLE( double, SOLID_FRACTION )
    KRATOS_CREATE_VARIABLE( double, SOLID_FRACTION_RATE )
    KRATOS_CREATE_VARIABLE( double, FLUID_FRACTION )
    KRATOS_CREATE_VARIABLE( double, FLUID_FRACTION_RATE )
    KRATOS_CREATE_VARIABLE( double, PHASE_FRACTION )
    KRATOS_CREATE_VARIABLE( double, PHASE_FRACTION_RATE )
    KRATOS_CREATE_VARIABLE( double, SOLID_FRACTION_PROJECTED )
    KRATOS_CREATE_VARIABLE( double, FLUID_FRACTION_PROJECTED )
    KRATOS_CREATE_VARIABLE( double, FLUID_DENSITY_PROJECTED )
    KRATOS_CREATE_VARIABLE( double, FLUID_VISCOSITY_PROJECTED )
    KRATOS_CREATE_VARIABLE( double, REYNOLDS_NUMBER )
    KRATOS_CREATE_VARIABLE( double, DRAG_COEFFICIENT )
    KRATOS_CREATE_VARIABLE( double, SHEAR_RATE_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( HYDRODYNAMIC_FORCE )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( HYDRODYNAMIC_MOMENT )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( FLUID_VEL_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( FLUID_VEL_LAPL_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( FLUID_VEL_LAPL_RATE_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( FLUID_ACCEL_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( FLUID_VORTICITY_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( HYDRODYNAMIC_REACTION )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( DRAG_REACTION )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( LIFT_FORCE )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( VIRTUAL_MASS_FORCE )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( BUOYANCY )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( PRESSURE_GRADIENT )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( PRESSURE_GRAD_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( SOLID_FRACTION_GRADIENT )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( SOLID_FRACTION_GRADIENT_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( FLUID_FRACTION_GRADIENT )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( FLUID_FRACTION_GRADIENT_PROJECTED )
    KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( PHASE_FRACTION_GRADIENT )

  void KratosApplication::RegisterDEMVariables()
  {
        
    //--------------- DEM Application -------------------//
      KRATOS_REGISTER_VARIABLE( PARTICLE_MASS )
      KRATOS_REGISTER_VARIABLE( RADIUS )
      KRATOS_REGISTER_VARIABLE( SEARCH_TOLERANCE )
      KRATOS_REGISTER_VARIABLE( PARTICLE_MATERIAL )
      KRATOS_REGISTER_VARIABLE( AMPLIFIED_CONTINUUM_SEARCH_RADIUS_EXTENSION )
      KRATOS_REGISTER_VARIABLE( DEM_DELTA_TIME )
      KRATOS_REGISTER_VARIABLE( FIXED_MESH_OPTION )
      KRATOS_REGISTER_VARIABLE( PARTITION_MASK )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( DAMP_FORCES )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( AUX_VEL )
      KRATOS_REGISTER_VARIABLE( NEIGHBOURS_IDS_DOUBLE )
      KRATOS_REGISTER_VARIABLE( PARTICLE_ROTATE_SPRING_FAILURE_TYPE )
      KRATOS_REGISTER_VARIABLE( OLD_NEIGHBOURS_IDS )
      KRATOS_REGISTER_VARIABLE( INI_NEIGHBOURS_IDS )
      KRATOS_REGISTER_VARIABLE( CONTINUUM_INI_NEIGHBOURS_IDS )
      KRATOS_REGISTER_VARIABLE( NEIGHBOURS_IDS )
      KRATOS_REGISTER_VARIABLE( PARTICLE_INITIAL_FAILURE_ID )
      KRATOS_REGISTER_VARIABLE( CONTINUUM_PARTICLE_INITIAL_FAILURE_ID )                
      KRATOS_REGISTER_VARIABLE( ELEMENT_TYPE )  
      KRATOS_REGISTER_VARIABLE( PARTICLE_ROTATE_SPRING_MOMENT )              
      
              
      // Swimming DEM Application BEGINNING
      KRATOS_REGISTER_VARIABLE( COUPLING_TYPE)
      KRATOS_REGISTER_VARIABLE( NON_NEWTONIAN_OPTION )
      KRATOS_REGISTER_VARIABLE( MANUALLY_IMPOSED_DRAG_LAW_OPTION )
      KRATOS_REGISTER_VARIABLE( DRAG_MODIFIER_TYPE )
      KRATOS_REGISTER_VARIABLE( BUOYANCY_FORCE_TYPE )
      KRATOS_REGISTER_VARIABLE( DRAG_FORCE_TYPE )
      KRATOS_REGISTER_VARIABLE( VIRTUAL_MASS_FORCE_TYPE )
      KRATOS_REGISTER_VARIABLE( LIFT_FORCE_TYPE )
      KRATOS_REGISTER_VARIABLE( MAGNUS_FORCE_TYPE )
      KRATOS_REGISTER_VARIABLE( HYDRO_TORQUE_TYPE )
      KRATOS_REGISTER_VARIABLE( FLUID_MODEL_TYPE )
      KRATOS_REGISTER_VARIABLE( DRAG_POROSITY_CORRECTION_TYPE )
      KRATOS_REGISTER_VARIABLE( POWER_LAW_TOLERANCE )
      KRATOS_REGISTER_VARIABLE( PARTICLE_SPHERICITY )
      KRATOS_REGISTER_VARIABLE( INIT_DRAG_FORCE )
      KRATOS_REGISTER_VARIABLE( DRAG_LAW_SLOPE )
      KRATOS_REGISTER_VARIABLE( SOLID_FRACTION )
      KRATOS_REGISTER_VARIABLE( SOLID_FRACTION_RATE )
      KRATOS_REGISTER_VARIABLE( FLUID_FRACTION )
      KRATOS_REGISTER_VARIABLE( FLUID_FRACTION_RATE )
      KRATOS_REGISTER_VARIABLE( PHASE_FRACTION )
      KRATOS_REGISTER_VARIABLE( PHASE_FRACTION_RATE )
      KRATOS_REGISTER_VARIABLE( SOLID_FRACTION_PROJECTED )
      KRATOS_REGISTER_VARIABLE( FLUID_FRACTION_PROJECTED )
      KRATOS_REGISTER_VARIABLE( FLUID_DENSITY_PROJECTED )
      KRATOS_REGISTER_VARIABLE( FLUID_VISCOSITY_PROJECTED )
      KRATOS_REGISTER_VARIABLE( REYNOLDS_NUMBER )
      KRATOS_REGISTER_VARIABLE( DRAG_COEFFICIENT )
      KRATOS_REGISTER_VARIABLE( SHEAR_RATE_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( HYDRODYNAMIC_FORCE )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( HYDRODYNAMIC_MOMENT )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( FLUID_VEL_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( FLUID_VEL_LAPL_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( FLUID_VEL_LAPL_RATE_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( FLUID_ACCEL_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( FLUID_VORTICITY_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( HYDRODYNAMIC_REACTION )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( DRAG_REACTION )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( LIFT_FORCE )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( VIRTUAL_MASS_FORCE )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( BUOYANCY )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( PRESSURE_GRADIENT )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( PRESSURE_GRAD_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( SOLID_FRACTION_GRADIENT )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( SOLID_FRACTION_GRADIENT_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( FLUID_FRACTION_GRADIENT )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( FLUID_FRACTION_GRADIENT_PROJECTED )
      KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( PHASE_FRACTION_GRADIENT )
              
      
      // Swimming DEM Application END

  }


}  // namespace Kratos.

// This define must be HERE
#undef DKRATOS_EXPORT_INTERFACE_2



