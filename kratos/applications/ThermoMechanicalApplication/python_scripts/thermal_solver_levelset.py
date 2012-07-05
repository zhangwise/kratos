#importing the Kratos Library
from KratosMultiphysics import *
from KratosMultiphysics.ThermoMechanicalApplication import *
from KratosMultiphysics.IncompressibleFluidApplication import *

# Check that KratosMultiphysics was imported in the main script
CheckForPreviousImport()

def AddVariables(model_part,settings):
    model_part.AddNodalSolutionStepVariable(VELOCITY);
    model_part.AddNodalSolutionStepVariable(DISPLACEMENT);
    model_part.AddNodalSolutionStepVariable(NODAL_AREA);    
    model_part.AddNodalSolutionStepVariable(settings.GetMeshVelocityVariable());   
    model_part.AddNodalSolutionStepVariable(settings.GetUnknownVariable());    
    model_part.AddNodalSolutionStepVariable(SPECIFIC_HEAT);
    model_part.AddNodalSolutionStepVariable(settings.GetVolumeSourceVariable());
    model_part.AddNodalSolutionStepVariable(settings.GetDensityVariable());
    model_part.AddNodalSolutionStepVariable(settings.GetDiffusionVariable());
    model_part.AddNodalSolutionStepVariable(settings.GetSurfaceSourceVariable());
    #model_part.AddNodalSolutionStepVariable(CONVECTION_COEFFICIENT);
    model_part.AddNodalSolutionStepVariable(NORMAL);
    model_part.AddNodalSolutionStepVariable(IS_BOUNDARY);    
    model_part.AddNodalSolutionStepVariable(settings.GetTransferCoefficientVariable());        
    #model_part.AddNodalSolutionStepVariable(HTC);    
    
    print "variables for the THERMAL_SOLVER added correctly"
        
def AddDofs(model_part,settings):
    print "KKKKKKKKKKKKKKKKKKK............................................................nnnnnnnnnnnnnnnnnnnnnnn"
    for node in model_part.Nodes:
	    node.AddDof(settings.GetUnknownVariable());
        
    print "dofs for the THERMAL_SOLVER added correctly"

class Solver:
    #######################################################################
    def __init__(self,model_part,domain_size,my_settings,):

        self.model_part = model_part

        self.time_scheme = ResidualBasedIncrementalUpdateStaticScheme()       
        self.settings = my_settings
        self.domain_size = domain_size
        #definition of the solvers
        #self.linear_solver =  SkylineLUFactorizationSolver()
##        self.linear_solver =SuperLUSolver()
##        self.linear_solver = MKLPardisoSolver()

        pPrecond = DiagonalPreconditioner()
##        pPrecond = ILU0Preconditioner()
        #self.linear_solver =  BICGSTABSolver(1e-6, 5000,pPrecond)
        self.linear_solver = BICGSTABSolver(1e-6, 5000)

        self.dynamic_tau = 0.0

        self.echo_level = 0
        self.CalculateReactionFlag = False
        self.ReformDofSetAtEachStep = True
        self.CalculateNormDxFlag = True
        self.MoveMeshFlag = False
    
        self.neigh_finder = FindNodalNeighboursProcess(self.model_part,9,18)
        if (self.domain_size == 2):
           self.elem_neighbor_finder = FindElementalNeighboursProcess(self.model_part, 2, 20)
        else:
           self.elem_neighbor_finder = FindElementalNeighboursProcess(self.model_part, 3, 20)	  
           
        self.Nmax = len(model_part.Properties)
        self.contact_matix = Matrix()
        
        ##calculate normals
        self.normal_tools = BodyNormalCalculationUtils()
        
        #material settings
        self.rho_mat = 100.0
        self.rho_empty = 1.0
        
        self.specific_heat_mat = 1006.0
        self.specific_heat_empty = 1.0   
        
        self.conductivity_mat = 0.024
        self.conductivity_empty = 1.0          
    #######################################################################
    def Initialize(self):

        if (self.domain_size == 2):
             self.duplicate_and_create_conditions = DuplicateInterfaceNodesCreateConditionsProcess(self.model_part,"HeatContact2D", self.Nmax, self.contact_matix )        
        else:
             print "duplicate_and_create_conditions is not implemented for 3D"        
	     
        #(self.neigh_finder).ClearNeighbours();
        #(self.neigh_finder).Execute();
        
        #(self.elem_neighbor_finder).ClearNeighbours()
        #(self.elem_neighbor_finder).Execute() 
        print "INSIDE INITIALIZE"           
 	(self.model_part.ProcessInfo).SetValue(CONVECTION_DIFFUSION_SETTINGS,self.settings)    
 	
        self.solver = ResidualBasedLinearStrategy(self.model_part,self.time_scheme,self.linear_solver,self.CalculateReactionFlag, self.ReformDofSetAtEachStep,self.CalculateNormDxFlag,self.MoveMeshFlag)   
        (self.solver).SetEchoLevel(self.echo_level)
        #(self.solver).SetBuilderAndSolver(ResidualBasedEliminationBuilderAndSolverDeactivation(self.linear_solver))

        self.model_part.ProcessInfo.SetValue(DYNAMIC_TAU, self.dynamic_tau);

        if (self.domain_size == 2):
            self.normal_tools.CalculateBodyNormals(self.model_part,2);        
        else:
            self.normal_tools.CalculateBodyNormals(self.model_part,3);     	  
##        print "Initialization monolithic solver finished"
    #######################################################################   
    def ApplyFluidProperties(self):
        #apply density
        for node in self.model_part.Nodes:
            dist = node.GetSolutionStepValue(DISTANCE)
            if(dist < 0):
                node.SetSolutionStepValue(self.settings.GetDensityVariable(),0,self.rho_mat)
                node.SetSolutionStepValue(self.settings.GetDiffusionVariable(),0,self.conductivity_mat)
                node.SetSolutionStepValue(SPECIFIC_HEAT,0,self.specific_heat_mat)               
                #node.SetSolutionStepValue(TEMPERATURE,0,melting_temp)                   
            else:
                node.SetSolutionStepValue(self.settings.GetDensityVariable(),0,self.rho_empty)
                node.SetSolutionStepValue(self.settings.GetDiffusionVariable(),0,self.conductivity_empty)
                node.SetSolutionStepValue(SPECIFIC_HEAT,0,self.specific_heat_empty)              

    #######################################################################   
    def Solve(self):        
        print "*****************entering solve?????????????"
        (self.model_part.ProcessInfo).SetValue(CONVECTION_DIFFUSION_SETTINGS,self.settings)    
        #self.ApplyFluidProperties()
        (self.solver).Solve()
##        print "solving step monolithic solver finished"
       

    #######################################################################   
    def SetEchoLevel(self,level):
        (self.solver).SetEchoLevel(level)
    
    ########################################################################

        




