
#if !defined(KRATOS_PFEM_FLUID_DYNAMIC_APPLICATION_VARIABLES_H_INCLUDED )
#define  KRATOS_PFEM_FLUID_DYNAMIC_APPLICATION_VARIABLES_H_INCLUDED

// System includes

// External includes


// Project includes
#include "includes/define.h"
#include "includes/kratos_application.h"
#include "includes/variables.h"
#include "includes/node.h"

namespace Kratos
{
	KRATOS_DEFINE_VARIABLE(double,TAUONE)
	KRATOS_DEFINE_VARIABLE(double,TAUTWO)

	KRATOS_DEFINE_VARIABLE(double,SUBSCALE_PRESSURE)

	KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(SUBSCALE_VELOCITY)
	KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS(VORTICITY)
}

#endif	/* KRATOS_PFEM_FLUID_DYNAMIC_APPLICATION_VARIABLES_H_INCLUDED */

