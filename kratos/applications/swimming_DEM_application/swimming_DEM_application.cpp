//   
//   Project Name:        Kratos       
//   Last Modified by:    $Author:  $
//   Date:                $Date:  $
//   Revision:            $Revision: 1.3 $
//
// 



// System includes


// External includes 


// Project includes
#include "includes/define.h"


#include "includes/variables.h"
#include "swimming_DEM_application.h"
#include "geometries/point_3d.h"
#include "geometries/line_3d_2.h"

namespace Kratos
{


        KRATOS_CREATE_3D_VARIABLE_WITH_COMPONENTS( BUOYANCY )

	KratosSwimmingDEMApplication::KratosSwimmingDEMApplication()  
	{}
        
	void KratosSwimmingDEMApplication::Register()
	{
		// calling base class register to register Kratos components
		KratosApplication::Register();
		std::cout << "Initializing KratosSwimmingDEMApplication... " << std::endl;


                KRATOS_REGISTER_3D_VARIABLE_WITH_COMPONENTS( BUOYANCY )

	  //  KRATOS_REGISTER_VARIABLE ( EXPORT_NEIGHBOUR_LIST )

		/* Define In Global variables.cpp
		  */



		
				               
	Serializer::Register( "VariablesList", mVariablesList );
	
        }

}  // namespace Kratos.


