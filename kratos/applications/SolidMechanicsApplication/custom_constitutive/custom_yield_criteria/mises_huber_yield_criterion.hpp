//
//   Project Name:        KratosSolidMechanicsApplication $
//   Last modified by:    $Author:            JMCarbonell $
//   Date:                $Date:                July 2013 $
//   Revision:            $Revision:                  0.0 $
//
//

#if !defined(KRATOS_MISES_HUBER_YIELD_CRITERION_H_INCLUDED )
#define  KRATOS_MISES_HUBER_YIELD_CRITERION_H_INCLUDED



// System includes

// External includes

// Project includes
#include "custom_constitutive/custom_yield_criteria/yield_criterion.hpp"

namespace Kratos
{
///@addtogroup ApplicationNameApplication
///@{

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

/// Short class definition.
/** Detail class definition.
*/
class MisesHuberYieldCriterion
	: public YieldCriterion
{
    public:
        ///@name Type Definitions
        ///@{

        /// Pointer definition of MisesHuberYieldCriterion
        KRATOS_CLASS_POINTER_DEFINITION(MisesHuberYieldCriterion);

        ///@}
        ///@name Life Cycle
        ///@{

        /// Default constructor.
        MisesHuberYieldCriterion();

        /// Copy constructor.
        MisesHuberYieldCriterion(MisesHuberYieldCriterion const& rOther);

        /// Assignment operator.
        MisesHuberYieldCriterion& operator=(MisesHuberYieldCriterion const& rOther);


        /// Destructor.
        virtual ~MisesHuberYieldCriterion();


        ///@}
        ///@name Operators
        ///@{


        ///@}
        ///@name Operations
        ///@{

        double& CalculateYieldCondition(double & rStateFunction, double& rNormStress, double& rAlpha);

        double& CalculateYieldCondition(double & rStateFunction, Matrix& rStressMatrix, double& rAlpha);

        ///@}
        ///@name Access
        ///@{
        

        ///@}
        ///@name Inquiry
        ///@{


        ///@}
        ///@name Input and output
        ///@{

        /// Turn back information as a string.
        virtual std::string Info() const;

        /// Print information about this object.
        virtual void PrintInfo(std::ostream& rOStream) const;

        /// Print object's data.
        virtual void PrintData(std::ostream& rOStream) const;


        ///@}
        ///@name Friends
        ///@{


        ///@}

    protected:
        ///@name Protected static Member Variables
        ///@{


        ///@}
        ///@name Protected member Variables
        ///@{
	
	
        ///@}
        ///@name Protected Operators
        ///@{


        ///@}
        ///@name Protected Operations
        ///@{


        ///@}
        ///@name Protected  Access
        ///@{


        ///@}
        ///@name Protected Inquiry
        ///@{


        ///@}
        ///@name Protected LifeCycle
        ///@{


        ///@}

    private:
        ///@name Static Member Variables
        ///@{


        ///@}
        ///@name Member Variables
        ///@{


        ///@}
        ///@name Private Operators
        ///@{


        ///@}
        ///@name Private Operations
        ///@{


        ///@}
        ///@name Private  Access
        ///@{

	
	///@}
	///@name Serialization
	///@{
	friend class Serializer;

	// A private default constructor necessary for serialization

	virtual void save(Serializer& rSerializer) const;

	virtual void load(Serializer& rSerializer);

        ///@}
        ///@name Private Inquiry
        ///@{


        ///@}
        ///@name Un accessible methods
        ///@{

        ///@}

    }; // Class MisesHuberYieldCriterion

    ///@}

    ///@name Type Definitions
    ///@{


    ///@}
    ///@name Input and output
    ///@{


    /// input stream function
    inline std::istream& operator >> (std::istream& rIStream,
                                      MisesHuberYieldCriterion& rThis);

    /// output stream function
    inline std::ostream& operator << (std::ostream& rOStream,
                                      const MisesHuberYieldCriterion& rThis)
    {
        rThis.PrintInfo(rOStream);
        rOStream << std::endl;
        rThis.PrintData(rOStream);

        return rOStream;
    }
    ///@}

    ///@} addtogroup block

}  // namespace Kratos.

#endif // KRATOS_MISES_HUBER_YIELD_CRITERION_H_INCLUDED  defined 


