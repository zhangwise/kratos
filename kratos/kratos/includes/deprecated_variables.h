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
//   Last Modified by:    $Author: JMCarbonell $
//   Date:                $Date:          2014 $
//   Revision:            $Revision:      1.20 $
//   Note:  IT HAS TO BE CLEANED AND SIMPLIFIED
//


#if !defined(KRATOS_DEPRECATED_VARIABLES_H_INCLUDED )
#define  KRATOS_DEPRECATED_VARIABLES_H_INCLUDED



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
#include "containers/periodic_variables_container.h"
#include "includes/kratos_export_dll.h"

#undef KRATOS_DEFINE_VARIABLE
#undef KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS
#define KRATOS_DEFINE_VARIABLE KRATOS_DEFINE_VARIABLE_DLL
#define KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS_DLL

namespace Kratos
{

    //Define Variables by type:

    //bools

    //for Structural application:
    KRATOS_DEFINE_VARIABLE( bool, IS_INACTIVE )

    //for Level Set application:
    KRATOS_DEFINE_VARIABLE( bool, IS_DUPLICATED )
    KRATOS_DEFINE_VARIABLE( bool, SPLIT_ELEMENT )
    KRATOS_DEFINE_VARIABLE( bool, SPLIT_NODAL )

    KRATOS_DEFINE_VARIABLE( int, IS_CONTACT_MASTER )
    KRATOS_DEFINE_VARIABLE( int, IS_CONTACT_SLAVE )

    //for PFEM fluids application:
    KRATOS_DEFINE_VARIABLE( int, IS_JACK_LINK )
    KRATOS_DEFINE_VARIABLE( int, IMPOSED_PRESSURE )
    KRATOS_DEFINE_VARIABLE( int, IMPOSED_VELOCITY_X )
    KRATOS_DEFINE_VARIABLE( int, IMPOSED_VELOCITY_Y )
    KRATOS_DEFINE_VARIABLE( int, IMPOSED_VELOCITY_Z )
    KRATOS_DEFINE_VARIABLE( int, IMPOSED_ANGULAR_VELOCITY_X )
    KRATOS_DEFINE_VARIABLE( int, IMPOSED_ANGULAR_VELOCITY_Y )
    KRATOS_DEFINE_VARIABLE( int, IMPOSED_ANGULAR_VELOCITY_Z )
    
    // For the DEM Application:
    KRATOS_DEFINE_VARIABLE(double, IMPOSED_VELOCITY_X_VALUE)
    KRATOS_DEFINE_VARIABLE(double, IMPOSED_VELOCITY_Y_VALUE)
    KRATOS_DEFINE_VARIABLE(double, IMPOSED_VELOCITY_Z_VALUE)
    KRATOS_DEFINE_VARIABLE(double, IMPOSED_ANGULAR_VELOCITY_X_VALUE)
    KRATOS_DEFINE_VARIABLE(double, IMPOSED_ANGULAR_VELOCITY_Y_VALUE)
    KRATOS_DEFINE_VARIABLE(double, IMPOSED_ANGULAR_VELOCITY_Z_VALUE)        

    KRATOS_DEFINE_VARIABLE( double, IS_INLET )
    KRATOS_DEFINE_VARIABLE ( double, IS_INTERFACE )
    KRATOS_DEFINE_VARIABLE ( double, IS_VISITED )
    KRATOS_DEFINE_VARIABLE ( double,IS_EROSIONABLE )

    KRATOS_DEFINE_VARIABLE( double, IS_STRUCTURE )
    KRATOS_DEFINE_VARIABLE( double, IS_POROUS )
    KRATOS_DEFINE_VARIABLE( double, IS_WATER )
    KRATOS_DEFINE_VARIABLE( double, IS_FLUID )
    KRATOS_DEFINE_VARIABLE( double, IS_BOUNDARY )
    KRATOS_DEFINE_VARIABLE( double, IS_FREE_SURFACE )
    KRATOS_DEFINE_VARIABLE( double, IS_AIR_EXIT )
    KRATOS_DEFINE_VARIABLE( double, IS_LAGRANGIAN_INLET )
    KRATOS_DEFINE_VARIABLE( double, IS_WATER_ELEMENT )


    KRATOS_DEFINE_VARIABLE( double, IS_BURN )
    KRATOS_DEFINE_VARIABLE( double, IS_DRIPPING )
    KRATOS_DEFINE_VARIABLE( double, IS_PERMANENT )
    KRATOS_DEFINE_VARIABLE( double, IS_WALL )

    KRATOS_DEFINE_VARIABLE( double, Ypr ) //var name does not follow standard
    KRATOS_DEFINE_VARIABLE( double, Yox )
    KRATOS_DEFINE_VARIABLE( double, Yfuel )
    KRATOS_DEFINE_VARIABLE( double, Hfuel )
    KRATOS_DEFINE_VARIABLE( double, Hpr )
    KRATOS_DEFINE_VARIABLE( double, Hpr1 )
    KRATOS_DEFINE_VARIABLE( double, Hox )

    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_1 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_2 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_3 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_4 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_5 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_6 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_7 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_8 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_9 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_10 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_11 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_12 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_13 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_14 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_15 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_16 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_17 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_18 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_19 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_20 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_21 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_22 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_23 )
    KRATOS_DEFINE_VARIABLE( double, RADIATIVE_INTENSITY_24 )

    KRATOS_DEFINE_VARIABLE( double, rhoD )
    KRATOS_DEFINE_VARIABLE( double, xi )
    KRATOS_DEFINE_VARIABLE( double, a )
    KRATOS_DEFINE_VARIABLE( double, b )


    KRATOS_DEFINE_VARIABLE( double, IS_SLIP )

    //for Level Set application:
    KRATOS_DEFINE_VARIABLE( double, IS_DIVIDED )

    KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS( xi_c )

    
    
    
    
    

}  // namespace Kratos.



// Resotre the default defines
#undef KRATOS_DEFINE_VARIABLE
#undef KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS
#define KRATOS_DEFINE_VARIABLE KRATOS_DEFINE_VARIABLE_NO_DLL
#define KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS KRATOS_DEFINE_3D_VARIABLE_WITH_COMPONENTS_NO_DLL

#endif // KRATOS_DEPRECATED_VARIABLES_H_INCLUDED  defined 