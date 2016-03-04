import KratosMultiphysics 
import KratosMultiphysics.FluidDynamicsApplication 

def Factory(settings, Model):
    if(type(settings) != KratosMultiphysics.Parameters):
        raise Exception("expected input shall be a Parameters object, encapsulating a json string")
    return ApplySlipProcess(Model, settings["Parameters"])

##all the processes python processes should be derived from "python_process"
class ApplySlipProcess(KratosMultiphysics.ApplyConstantVectorValueProcess):
    def __init__(self, Model, Parameters ):
        self.model_part = Model[Parameters["model_part_name"].GetString()]
        self.avoid_recomputing_normals = Parameters["avoid_recomputing_normals"].GetBool()

        #compute the normal on the nodes of interest - note that the model part employed here is supposed to
        #only have slip "conditions"
        NormalCalculationUtils().CalculateOnSimplex(self.model_part, self.domain_size)
        
        #mark the nodes and conditions with the appropriate slip flag
        #TODO: a flag shall be used here!!!!!
        for cond in self.model_part.Conditions: #TODO: this may well not be needed!
            cond.SetValue(IS_STRUCTURE,1.0)
            
        #TODO: use a flag!!!
        KratosMultiphysics.VariableUtils().SetScalarVar(IS_STRUCTURE,1.0, self.model_part.Nodes)
        
    def InitializeSolutionStep(self):
        #recompute the normals
        if self.avoid_recomputing_normals == False:
            NormalCalculationUtils().CalculateOnSimplex(self.model_part, self.domain_size)