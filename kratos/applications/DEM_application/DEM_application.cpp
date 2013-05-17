//   
//   Project Name:        Kratos       
//   Last Modified by:    $Author:  $
//   Date:                $Date:  $
//   Revision:            $Revision: 1.3 $
//

// System includes

// External includes 

// Project includes
#include "includes/define.h"
#include "includes/variables.h"
#include "DEM_application.h"
#include "geometries/point_3d.h"
#include "geometries/line_3d_2.h"

namespace Kratos
{

        // Options and flags
        KRATOS_CREATE_VARIABLE(int, NON_LINEAR_OPTION)
        KRATOS_CREATE_VARIABLE(int, ACTIVATE_SEARCH)
        KRATOS_CREATE_VARIABLE(int, CONTACT_MESH_OPTION)
        KRATOS_CREATE_VARIABLE(int, NEIGH_INITIALIZED)
        KRATOS_CREATE_VARIABLE(int, VIRTUAL_MASS_OPTION)
        KRATOS_CREATE_VARIABLE(int, UNIFORM_MATERIAL_OPTION)
        KRATOS_CREATE_VARIABLE(int, CRITICAL_TIME_OPTION)
        KRATOS_CREATE_VARIABLE(int, LIMIT_SURFACE_OPTION)
        KRATOS_CREATE_VARIABLE(int, SURFACE_FRICC)
        KRATOS_CREATE_VARIABLE(int, IF_BOUNDARY_ELEMENT)
        KRATOS_CREATE_VARIABLE(Vector, IF_BOUNDARY_FACE)
        KRATOS_CREATE_VARIABLE(int, SKIN_SPHERE)
        KRATOS_CREATE_VARIABLE(int, FAILURE_CRITERION_OPTION)
        KRATOS_CREATE_VARIABLE(int, CONCRETE_TEST_OPTION)
        KRATOS_CREATE_VARIABLE(int, plot_OPTIONS)

        // Export...
        KRATOS_CREATE_VARIABLE(double, EXPORT_ID)

        // Integers
        KRATOS_CREATE_VARIABLE(int, NUM_OF_NEIGH)
        KRATOS_CREATE_VARIABLE(int, TOTAL_CONTACTS)

        // Time related
        KRATOS_CREATE_VARIABLE(double, TIME_INCREASING_RATIO)
        KRATOS_CREATE_VARIABLE(double, FINAL_SIMULATION_TIME)
        KRATOS_CREATE_VARIABLE(double, INITIAL_PRESSURE_TIME)

	// Geometric Parameters
	KRATOS_CREATE_VARIABLE(double, LOCAL_CONTACT_AREA_HIGH)
	KRATOS_CREATE_VARIABLE(double, LOCAL_CONTACT_AREA_LOW)
	KRATOS_CREATE_VARIABLE(double, MEAN_CONTACT_AREA)
	KRATOS_CREATE_VARIABLE(double, REPRESENTATIVE_VOLUME)

	// Material parameters
	KRATOS_CREATE_VARIABLE(double, NODAL_MASS_COEFF)
	KRATOS_CREATE_VARIABLE(double, DEM_MAGIC_FACTOR)
	KRATOS_CREATE_VARIABLE(double, PARTICLE_MOMENT_OF_INERTIA)
	KRATOS_CREATE_VARIABLE(double, ROLLING_FRICTION)
	KRATOS_CREATE_VARIABLE(double, GENERAL_DENSITY)
	KRATOS_CREATE_VARIABLE(double, GENERAL_YOUNG_MODULUS)
	KRATOS_CREATE_VARIABLE(double, GENERAL_POISSON_RATIO)
	KRATOS_CREATE_VARIABLE(double, GENERAL_COHESION)
	KRATOS_CREATE_VARIABLE(double, GENERAL_ROLLING_FRICTION)
	KRATOS_CREATE_VARIABLE(double, GENERAL_STATIC_FRICTION)
	KRATOS_CREATE_VARIABLE(double, GENERAL_DYNAMIC_FRICTION)
	KRATOS_CREATE_VARIABLE(double, GENERAL_RESTITUTION_COEF)
	KRATOS_CREATE_VARIABLE(double, HISTORICAL_MIN_K)

	// CONTINUUM ONLY BEGIN

        // Skin
        KRATOS_CREATE_VARIABLE(double, PREDEFINED_SKIN)
        KRATOS_CREATE_VARIABLE(double, EXPORT_SKIN_SPHERE)

        // Continuum Constitutive Models
        KRATOS_CREATE_VARIABLE(double, NON_ELASTIC_STAGE)
        KRATOS_CREATE_VARIABLE(double, SLOPE_FRACTION_N1)
        KRATOS_CREATE_VARIABLE(double, SLOPE_FRACTION_N2)
        KRATOS_CREATE_VARIABLE(double, SLOPE_LIMIT_COEFF_C1)
        KRATOS_CREATE_VARIABLE(double, SLOPE_LIMIT_COEFF_C2)
        KRATOS_CREATE_VARIABLE(double, CONTACT_FAILURE)
        KRATOS_CREATE_VARIABLE(double, CONTACT_SIGMA)
        KRATOS_CREATE_VARIABLE(double, CONTACT_TAU)
        KRATOS_CREATE_VARIABLE(double, FAILURE_CRITERION_STATE)
        KRATOS_CREATE_VARIABLE(double, CONTACT_SIGMA_MAX)
        KRATOS_CREATE_VARIABLE(double, CONTACT_SIGMA_MIN)
        KRATOS_CREATE_VARIABLE(double, CONTACT_TAU_ZERO)
        KRATOS_CREATE_VARIABLE(double, CONTACT_INTERNAL_FRICC)
        KRATOS_CREATE_VARIABLE(double, LOW_POISSON_FORCE)
        KRATOS_CREATE_VARIABLE(double, HIGH_POISSON_FORCE)

        // Concrete test
        KRATOS_CREATE_VARIABLE(double, FIXED_VEL_TOP)
        KRATOS_CREATE_VARIABLE(double, FIXED_VEL_BOT)
        KRATOS_CREATE_VARIABLE(double, RADIAL_DISPLACEMENT)
        KRATOS_CREATE_VARIABLE(double, AREA_VERTICAL_TAPA)
        KRATOS_CREATE_VARIABLE(double, AREA_VERTICAL_CENTRE)

        // Tension
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_XX)
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_XY)
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_XZ)
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_YX)
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_YY)
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_YZ)
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_ZX)
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_ZY)
        KRATOS_CREATE_VARIABLE(double, DEM_STRESS_ZZ)

        // CONTINUUM ONLY END

        // Kinematics
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_ROTATION_ANGLE)
        KRATOS_CREATE_VARIABLE(double, ORIENTATION_REAL)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(ORIENTATION_IMAG)
        KRATOS_CREATE_VARIABLE(Vector, INITIAL_AXES_TRACKING)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(SURFACE_NORMAL_DIR)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(SURFACE_POINT_COOR)

        // Forces
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(DAMP_FORCES)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(BUOYANCY)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(TOTAL_FORCES)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_SURFACE_CONTACT_FORCES)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_MOMENT)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(MAX_ROTA_MOMENT)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(INITIAL_ROTA_MOMENT)
        KRATOS_CREATE_VARIABLE(Vector, PARTICLE_BLOCK_CONTACT_FORCE)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_SURFACE_ROTATE_SPRING_MOMENT)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(EXTERNAL_APPLIED_FORCE)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(LOCAL_CONTACT_FORCE_LOW)
        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS(LOCAL_CONTACT_FORCE_HIGH)

        // M:possible future blocks (no FEM) interaction
        KRATOS_CREATE_VARIABLE(Vector, PARTICLE_BLOCK_CONTACT_FAILURE_ID)
        KRATOS_CREATE_VARIABLE(Vector, PARTICLE_BLOCK_IF_INITIAL_CONTACT)
        KRATOS_CREATE_VARIABLE(WeakPointerVector<Element >, NEIGHBOUR_PARTICLE_BLOCK_ELEMENTS)

	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_1)
	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_2)
	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_3)
	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_4)
	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_5)
	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_6)
	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_7)
	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_8)
	KRATOS_CREATE_VARIABLE(int, INT_DUMMY_9)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_1)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_2)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_3)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_4)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_5)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_6)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_7)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_8)
	KRATOS_CREATE_VARIABLE(double, DOUBLE_DUMMY_9)

	KratosDEMApplication::KratosDEMApplication():
        mSphericParticle3D( 0, Element::GeometryType::Pointer( new Point3D<Node<3> >( Element::GeometryType::PointsArrayType( 1, Node<3>() ) ) ) ),
        mSphericContinuumParticle3D( 0, Element::GeometryType::Pointer( new Point3D<Node<3> >( Element::GeometryType::PointsArrayType( 1, Node<3>() ) ) ) ),
        mSphericSwimmingParticle3D( 0, Element::GeometryType::Pointer( new Point3D<Node<3> >( Element::GeometryType::PointsArrayType( 1, Node<3>() ) ) ) ),
        mDEM_FEM_Particle3D( 0, Element::GeometryType::Pointer( new Point3D<Node<3> >( Element::GeometryType::PointsArrayType( 1, Node<3>() ) ) ) ),
        mParticleContactElement( 0, Element::GeometryType::Pointer( new Line3D2<Node<3> >( Element::GeometryType::PointsArrayType( 2, Node<3>() ) ) ) )
                             
	{}
        
	void KratosDEMApplication::Register()
	{
	// Calling base class register to register Kratos components

	KratosApplication::Register();
	std::cout << "Initializing KratosDEMApplication... " << std::endl;

        // Options and flags
        KRATOS_REGISTER_VARIABLE(NON_LINEAR_OPTION)
        KRATOS_REGISTER_VARIABLE(ACTIVATE_SEARCH)
        KRATOS_REGISTER_VARIABLE(CONTACT_MESH_OPTION)
        KRATOS_REGISTER_VARIABLE(NEIGH_INITIALIZED)
        KRATOS_REGISTER_VARIABLE(VIRTUAL_MASS_OPTION)
        KRATOS_REGISTER_VARIABLE(UNIFORM_MATERIAL_OPTION)
        KRATOS_REGISTER_VARIABLE(CRITICAL_TIME_OPTION)
        KRATOS_REGISTER_VARIABLE(LIMIT_SURFACE_OPTION)
        KRATOS_REGISTER_VARIABLE(SURFACE_FRICC)
        KRATOS_REGISTER_VARIABLE(IF_BOUNDARY_ELEMENT)
        KRATOS_REGISTER_VARIABLE(IF_BOUNDARY_FACE)
        KRATOS_REGISTER_VARIABLE(SKIN_SPHERE)
        KRATOS_REGISTER_VARIABLE(FAILURE_CRITERION_OPTION)
        KRATOS_REGISTER_VARIABLE(CONCRETE_TEST_OPTION)
        KRATOS_REGISTER_VARIABLE(plot_OPTIONS)

        // Export...
        KRATOS_REGISTER_VARIABLE(EXPORT_ID)

        // Integers
        KRATOS_REGISTER_VARIABLE(NUM_OF_NEIGH)
        KRATOS_REGISTER_VARIABLE(TOTAL_CONTACTS)

        // Time related
        KRATOS_REGISTER_VARIABLE(TIME_INCREASING_RATIO)
        KRATOS_REGISTER_VARIABLE(FINAL_SIMULATION_TIME)
        KRATOS_REGISTER_VARIABLE(INITIAL_PRESSURE_TIME)

        // Geometric Parameters
        KRATOS_REGISTER_VARIABLE(LOCAL_CONTACT_AREA_HIGH)
        KRATOS_REGISTER_VARIABLE(LOCAL_CONTACT_AREA_LOW)
        KRATOS_REGISTER_VARIABLE(MEAN_CONTACT_AREA)
        KRATOS_REGISTER_VARIABLE(REPRESENTATIVE_VOLUME)

        // Material parameters
        KRATOS_REGISTER_VARIABLE(NODAL_MASS_COEFF)
        KRATOS_REGISTER_VARIABLE(DEM_MAGIC_FACTOR)
        KRATOS_REGISTER_VARIABLE(PARTICLE_MOMENT_OF_INERTIA)
        KRATOS_REGISTER_VARIABLE(ROLLING_FRICTION)
        KRATOS_REGISTER_VARIABLE(GENERAL_DENSITY)
        KRATOS_REGISTER_VARIABLE(GENERAL_YOUNG_MODULUS)
        KRATOS_REGISTER_VARIABLE(GENERAL_POISSON_RATIO)
        KRATOS_REGISTER_VARIABLE(GENERAL_COHESION)
        KRATOS_REGISTER_VARIABLE(GENERAL_ROLLING_FRICTION)
        KRATOS_REGISTER_VARIABLE(GENERAL_STATIC_FRICTION)
        KRATOS_REGISTER_VARIABLE(GENERAL_DYNAMIC_FRICTION)
        KRATOS_REGISTER_VARIABLE(GENERAL_RESTITUTION_COEF)
        KRATOS_REGISTER_VARIABLE(HISTORICAL_MIN_K)

        // CONTINUUM ONLY

        // Skin
        KRATOS_REGISTER_VARIABLE(PREDEFINED_SKIN)
        KRATOS_REGISTER_VARIABLE(EXPORT_SKIN_SPHERE)

        // Continuum Constitutive Models
        KRATOS_REGISTER_VARIABLE(NON_ELASTIC_STAGE)
        KRATOS_REGISTER_VARIABLE(SLOPE_FRACTION_N1)
        KRATOS_REGISTER_VARIABLE(SLOPE_FRACTION_N2)
        KRATOS_REGISTER_VARIABLE(SLOPE_LIMIT_COEFF_C1)
        KRATOS_REGISTER_VARIABLE(SLOPE_LIMIT_COEFF_C2)
        KRATOS_REGISTER_VARIABLE(CONTACT_FAILURE)
        KRATOS_REGISTER_VARIABLE(CONTACT_SIGMA)
        KRATOS_REGISTER_VARIABLE(CONTACT_TAU)
        KRATOS_REGISTER_VARIABLE(FAILURE_CRITERION_STATE)
        KRATOS_REGISTER_VARIABLE(CONTACT_SIGMA_MAX)
        KRATOS_REGISTER_VARIABLE(CONTACT_SIGMA_MIN)
        KRATOS_REGISTER_VARIABLE(CONTACT_TAU_ZERO)
        KRATOS_REGISTER_VARIABLE(CONTACT_INTERNAL_FRICC)
        KRATOS_REGISTER_VARIABLE(LOW_POISSON_FORCE)
        KRATOS_REGISTER_VARIABLE(HIGH_POISSON_FORCE)

        // Concrete test
        KRATOS_REGISTER_VARIABLE(FIXED_VEL_TOP)
        KRATOS_REGISTER_VARIABLE(FIXED_VEL_BOT)
        KRATOS_REGISTER_VARIABLE(RADIAL_DISPLACEMENT)
        KRATOS_REGISTER_VARIABLE(AREA_VERTICAL_TAPA)
        KRATOS_REGISTER_VARIABLE(AREA_VERTICAL_CENTRE)

        // Tension
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_XX)
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_XY)
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_XZ)
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_YX)
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_YY)
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_YZ)
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_ZX)
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_ZY)
        KRATOS_REGISTER_VARIABLE(DEM_STRESS_ZZ)

        // Kinematics
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_ROTATION_ANGLE)
        KRATOS_REGISTER_VARIABLE(ORIENTATION_REAL)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(ORIENTATION_IMAG)
        KRATOS_REGISTER_VARIABLE(INITIAL_AXES_TRACKING)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(SURFACE_NORMAL_DIR)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(SURFACE_POINT_COOR)

        // Forces
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(DAMP_FORCES)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(BUOYANCY)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(TOTAL_FORCES)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_SURFACE_CONTACT_FORCES)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_MOMENT)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(MAX_ROTA_MOMENT)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(INITIAL_ROTA_MOMENT)
        KRATOS_REGISTER_VARIABLE(PARTICLE_BLOCK_CONTACT_FORCE)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(PARTICLE_SURFACE_ROTATE_SPRING_MOMENT)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(EXTERNAL_APPLIED_FORCE)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(LOCAL_CONTACT_FORCE_LOW)
        KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS(LOCAL_CONTACT_FORCE_HIGH)

        // M:possible future blocks (no FEM) interaction
        KRATOS_REGISTER_VARIABLE(PARTICLE_BLOCK_CONTACT_FAILURE_ID)
        KRATOS_REGISTER_VARIABLE(PARTICLE_BLOCK_IF_INITIAL_CONTACT)

        KRATOS_REGISTER_VARIABLE(INT_DUMMY_1)
        KRATOS_REGISTER_VARIABLE(INT_DUMMY_2)
        KRATOS_REGISTER_VARIABLE(INT_DUMMY_3)
        KRATOS_REGISTER_VARIABLE(INT_DUMMY_4)
        KRATOS_REGISTER_VARIABLE(INT_DUMMY_5)
        KRATOS_REGISTER_VARIABLE(INT_DUMMY_6)
        KRATOS_REGISTER_VARIABLE(INT_DUMMY_7)
        KRATOS_REGISTER_VARIABLE(INT_DUMMY_8)
        KRATOS_REGISTER_VARIABLE(INT_DUMMY_9)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_1)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_2)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_3)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_4)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_5)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_6)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_7)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_8)
        KRATOS_REGISTER_VARIABLE(DOUBLE_DUMMY_9)

        // ELEMENTS
        KRATOS_REGISTER_ELEMENT("SphericParticle3D", mSphericParticle3D)
        KRATOS_REGISTER_ELEMENT("SphericContinuumParticle3D", mSphericContinuumParticle3D)
        KRATOS_REGISTER_ELEMENT("SphericSwimmingParticle3D", mSphericSwimmingParticle3D)
        KRATOS_REGISTER_ELEMENT("DEM_FEM_Particle3D", mDEM_FEM_Particle3D)
        KRATOS_REGISTER_ELEMENT("ParticleContactElement", mParticleContactElement)

       // SERIALIZER
       Serializer::Register( "VariablesList", mVariablesList );

       }

}  // namespace Kratos.


