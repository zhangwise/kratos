from KratosMultiphysics import *
from KratosMultiphysics.PFEM2Application import *
#from KratosMultiphysics.ConvectionDiffusionApplication import *
from KratosMultiphysics.ExternalSolversApplication import *
#from KratosMultiphysics.OpenCLApplication import *
#from KratosMultiphysics.GPUSolversApplication import *

from math import sqrt
import time as timer
#dir(pure_diffusion_application)

def AddVariables(model_part):
    model_part.AddNodalSolutionStepVariable(PRESSURE);
    model_part.AddNodalSolutionStepVariable(DISTANCE);
    model_part.AddNodalSolutionStepVariable(VELOCITY);
    model_part.AddNodalSolutionStepVariable(FRACT_VEL);
    model_part.AddNodalSolutionStepVariable(G_VALUE);
    model_part.AddNodalSolutionStepVariable(TEMPERATURE);
    model_part.AddNodalSolutionStepVariable(PRESS_PROJ);
    model_part.AddNodalSolutionStepVariable(PRESS_PROJ_NO_RO);
    model_part.AddNodalSolutionStepVariable(YP);

    model_part.AddNodalSolutionStepVariable(RHS);
    model_part.AddNodalSolutionStepVariable(MESH_VELOCITY);
    model_part.AddNodalSolutionStepVariable(ACCELERATION);
    model_part.AddNodalSolutionStepVariable(NORMAL);	
    #model_part.AddNodalSolutionStepVariable(DENSITY);	

    model_part.AddNodalSolutionStepVariable(DELTA_VELOCITY) 
    model_part.AddNodalSolutionStepVariable(MEAN_SIZE) 
    model_part.AddNodalSolutionStepVariable(NODAL_AREA) 
    model_part.AddNodalSolutionStepVariable(NODAL_MASS) 
    model_part.AddNodalSolutionStepVariable(MASS)
    model_part.AddNodalSolutionStepVariable(FORCE)
    model_part.AddNodalSolutionStepVariable(TAU)
    model_part.AddNodalSolutionStepVariable(TEMPERATURE)



def AddDofs(model_part):
    for node in model_part.Nodes:
        node.AddDof(PRESSURE);
        node.AddDof(VELOCITY_X);
        node.AddDof(VELOCITY_Y);
        node.AddDof(VELOCITY_Z);
        node.AddDof(DISTANCE);
        node.AddDof(TEMPERATURE);


    print "DoFs for the Poisson solver added correctly"

class PFEM2Solver:
    #######################################################################
    #def __init__(self,model_part,linea_model_part,domain_size):
    def __init__(self,model_part,domain_size):
        self.model_part = model_part
        
        self.time_scheme = ResidualBasedIncrementalUpdateStaticScheme()

        #definition of the solvers
	gmres_size = 50
	tol = 1e-5
	verbosity = 1
	pDiagPrecond = DiagonalPreconditioner()
	#self.monolitic_linear_solver= GPUBICGSTABSolverWithDiagonalPreconditioner(tol, 5000)
	#self.monolitic_linear_solver= ViennaCLSolver(tol,3000,OpenCLPrecision.Double,OpenCLSolverType.CG,OpenCLPreconditionerType.AMG_DAMPED_JACOBI) 
	#self.monolitic_linear_solver = BICGSTABSolver(1e-5, 1000,pDiagPrecond) # SkylineLUFactorizationSolver() 
	#self.monolitic_linear_solver = BICGSTABSolver(1e-5, 1000,pDiagPrecond) # SkylineLUFactorizationSolver() 
	self.monolitic_linear_solver =  AMGCLSolver(AMGCLSmoother.ILU0,AMGCLIterativeSolverType.CG,tol,3000,verbosity,gmres_size)      #BICGSTABSolver(1e-7, 5000) # SkylineLUFactorizationSolver() 
	
	#self.viscosity_linear_solver = AMGCLSolver(AMGCLSmoother.DAMPED_JACOBI,AMGCLIterativeSolverType.CG,tol,200,verbosity,gmres_size)      #BICGSTABSolver(1e-7, 5000) # SkylineLUFactorizationSolver() #
	#self.pressure_linear_solver = DeflatedCGSolver(1e-5, 3000, True,1000)
	#self.viscosity_linear_solver = DeflatedCGSolver(1e-6, 3000, True,1000)
	self.temperature_linear_solver =  BICGSTABSolver(1e-4, 5000,pDiagPrecond) #
	#self.temperature_linear_solver =  AMGCLSolver(AMGCLSmoother.DAMPED_JACOBI,AMGCLIterativeSolverType.CG,tol,200,verbosity,gmres_size)      #BICGSTABSolver(1e-7, 5000) # SkylineLUFactorizationSolver() #
        #self.pressure_linear_solver =  SkylineLUFactorizationSolver()  #we set the type of solver that we want 
        self.conv_criteria = DisplacementCriteria(1e-9,1e-15)  #tolerance for the solver 
        
        self.domain_size = domain_size
        number_of_avg_elems = 10
        number_of_avg_nodes = 10
        self.neighbour_search = FindNodalNeighboursProcess(model_part,number_of_avg_elems,number_of_avg_nodes)
        (self.neighbour_search).Execute()
	self.neighbour_elements_search= FindElementalNeighboursProcess(model_part,domain_size,number_of_avg_elems)
	(self.neighbour_elements_search).Execute()
        ##calculate normals
        self.normal_tools = BodyNormalCalculationUtils()
        
        
    #######################################################################
    #######################################################################
    def Initialize(self):
        #creating the solution strategy
        CalculateReactionFlag = False
        ReformDofSetAtEachStep = False	
        MoveMeshFlag = False
        pDiagPrecond = DiagonalPreconditioner()
        #build the edge data structure
	#if self.domain_size==2:
	#	self.matrix_container = MatrixContainer2D()
	#else: 
	#	self.matrix_container = MatrixContainer3D()
	#maximum_number_of_particles= 10*self.domain_size
	maximum_number_of_particles= 8*self.domain_size

	self.ExplicitStrategy=PFEM2_Explicit_Strategy(self.model_part,self.domain_size, MoveMeshFlag)

	self.VariableUtils = VariableUtils()
	
	if self.domain_size==2:
		self.moveparticles = MoveParticleUtilityDiffFluidOnly2D(self.model_part,maximum_number_of_particles)
	else:
		self.moveparticles = MoveParticleUtilityDiffFluidOnly3D(self.model_part,maximum_number_of_particles)

	print "self.domain_size = ", self.domain_size
	if self.domain_size==2:
		self.calculatewatervolume = CalculateWaterFraction2D(self.model_part)
	else:	
		self.calculatewatervolume = CalculateWaterFraction3D(self.model_part)
	self.moveparticles.MountBinDiff()
        #self.matrix_container.ConstructCSRVector(self.model_part)
        #self.matrix_container.BuildCSRData(self.model_part)
	self.water_volume=0.0  #we initialize it at zero
	self.water_initial_volume=0.0 #we initialize it at zero
	self.water_initial_volume_flag=True #we initialize it at zero
	self.mass_correction_factor=0.0
        #creating the solution strategy
        #CalculateReactionFlag = False
        #ReformDofSetAtEachStep = False
        #MoveMeshFlag = True
        #import strategy_python
        #self.solver = strategy_python.SolvingStrategyPython(self.model_part,self.time_scheme,self.poisson_linear_solver,self.conv_criteria,CalculateReactionFlag,ReformDofSetAtEachStep,MoveMeshFlag)

        ##constructing the solver
        #if self.domain_size==2:
        #   self.solver = DifussionSolver2D(self.matrix_container,self.model_part)
        #else:
        #   self.solver = DifussionSolver3D(self.matrix_container,self.model_part)
        #print "ln90"      
        #self.solver.Initialize(h,radius)
        #print "ln91"

        

	self.normal_tools.CalculateBodyNormals(self.model_part,self.domain_size);  
	condition_number=1
	'''
	if self.domain_size==2:
		self.addBC = AddFixedVelocityCondition2D(self.model_part)
	else:
		self.addBC = AddFixedVelocityCondition3D(self.model_part)

	(self.addBC).AddThem()
	'''	
	import strategy_python #implicit solver

	self.monolitic_solver = strategy_python.SolvingStrategyPython(self.model_part,self.time_scheme,self.monolitic_linear_solver,self.conv_criteria,CalculateReactionFlag,ReformDofSetAtEachStep,MoveMeshFlag)
	self.temperature_solver = strategy_python.SolvingStrategyPython(self.model_part,self.time_scheme,self.temperature_linear_solver,self.conv_criteria,CalculateReactionFlag,ReformDofSetAtEachStep,MoveMeshFlag)
	#pDiagPrecond = DiagonalPreconditioner()
	self.linear_solver =  BICGSTABSolver(1e-7, 5000,pDiagPrecond)
	#(self.moveparticles).ReplaceParticlesVelocityAndDistance();
	self.calculateinitialdrag=0.0
	self.streamlineintegration=0.0
	self.accelerateparticles=0.0
	self.navierstokes=0.0
	self.lagrangiantoeulerian=0.0
	self.reseed=0.0
	self.prereseed=0.0
	self.erasing=0.0
	self.total=0.0
	self.nodaltasks=0.0
	self.thermal=0.0
	self.implicitviscosity=0.0
        
      
                 
    #######################################################################   
    def Solve(self):
		combustion_problem=False;
		


		add_gravity=False #in the monolitic solver we do not add the gravity, it is added directly in the implicit monolitic system
		#add_gravity=True #in the monolitic solver we do not add the gravity, it is added directly in the implicit monolitic system

		temperature_implicit_calculation=False;
		viscosity_streamline_integrate=False; #True means explicit integration! False means we will have to solve the fractional velocity system implicetely later, once information has been passed to mesh
		#pressure_gradient_integrate=False; #we use the pressure of the previous step. not reccomended for 2 fluid flows. REMOVED FROM THE CODE	
		calculate_viscous_contribution_after_everything=False;		
		#implicit_velocity_correction=False;	# as expected this can not be active the implicit correction is done:
		#if (calculate_viscous_contribution_after_everything):
		#	implicit_velocity_correction=False;
		if combustion_problem:
			temperature_implicit_calculation=True;
		t1 = timer.time()

		#calculating RHS by viscous forces using information of the previous time step:	
		#self.CalculateExplicitViscosityContribution();
		t2 = timer.time()
		self.calculateinitialdrag = self.calculateinitialdrag + t2-t1

		#in order to define a reasonable number of substeps we calculate a mean courant in each element
		(self.moveparticles).CalculateVelOverElemSize();
		t2a = timer.time()

		#streamline integration:
		(self.moveparticles).MoveParticlesDiff(viscosity_streamline_integrate,add_gravity);	
		t3 = timer.time()
		self.streamlineintegration = self.streamlineintegration + t3-t2a
		t3a = timer.time()

		#Reseeding using streamlines in inverse way in case there are too few particles. Not very accurate since particles follow streamlines, no matter if it's water or air.
		#(for 1 fluid should be accurate though
		pre_minimum_number_of_particles=3#self.domain_size;
		(self.moveparticles).PreReseed(viscosity_streamline_integrate,add_gravity,pre_minimum_number_of_particles);
		t4 = timer.time()
		self.reseed = self.reseed + t4-t3a
		self.prereseed = self.prereseed + t4-t3a


		(self.moveparticles).TransferLagrangianToEulerian();

		t5 = timer.time()
		self.lagrangiantoeulerian = self.lagrangiantoeulerian + t5-t4


		(self.moveparticles).FlagSplittedElementsAndTheirNodes();

		t6 = timer.time()

		t7=timer.time()

		(self.VariableUtils).CopyVectorVar(MESH_VELOCITY,VELOCITY,self.model_part.Nodes)
		
		full_reset=False;
		
		#implicit everything
		full_reset=True;
		(self.moveparticles).ResetBoundaryConditions(full_reset) 

		(self.monolitic_solver).Solve() #implicit resolution of the system. 
		self.CalculatePressureProjection() #for the next timestep

		full_reset=True;
		(self.moveparticles).ResetBoundaryConditions(full_reset) 

		(self.moveparticles).CalculateDeltaVelocity();		
		t11 = timer.time()
		self.navierstokes = self.navierstokes + t11-t6
		#transfering the information to the mesh:
		modify_particle_pressure=False
		(self.moveparticles).AccelerateParticlesWithoutMovingUsingDeltaVelocity(add_gravity,modify_particle_pressure);
		t12 = timer.time()
		self.accelerateparticles = self.accelerateparticles + t12-t11

		#reseeding in elements that have few particles to avoid having problems in next iterations:
		post_minimum_number_of_particles=self.domain_size*2;
		self.water_volume = (self.calculatewatervolume).Calculate()
		if (self.water_initial_volume_flag): 
			print "calculated water volume for the first time"
			self.water_initial_volume=self.water_volume
			self.water_initial_volume_flag=False
		print self.water_volume
		water_fraction= self.water_volume/(self.water_initial_volume+1e-9)
		self.mass_correction_factor = (1.0 - water_fraction) * 100.0 * 0.25
		#if self.mass_correction_factor>0.5:
		#	 self.mass_correction_factor
		print "mass correction factor: ", self.mass_correction_factor
		print "current mass loss is : " , (1.0 - water_fraction) * 100.0 , " % "
		(self.moveparticles).PostReseed(post_minimum_number_of_particles,self.mass_correction_factor);		
		t13 = timer.time()
		self.reseed=self.reseed+ t13-t12

		self.total = self.total + t13-t1 
		
		if True:
			print "----------TIMES----------"
			print "self.calculateinitialdrag  " , self.calculateinitialdrag , "in % = ",  100.0*(self.calculateinitialdrag)/(self.total)
			print "self.streamlineintegration " ,  self.streamlineintegration , "in % = ", 100.0*(self.streamlineintegration)/(self.total)
			print "self.accelerateparticles " ,  self.accelerateparticles , "in % = ", 100.0*(self.accelerateparticles)/(self.total)
			print "self.navierstokes " ,  self.navierstokes , "in % = ", 100.0*(self.navierstokes)/(self.total)
			print "self.nodaltasks ", self.nodaltasks , (self.nodaltasks)/(self.total)
			print "self.lagrangiantoeulerian " ,  self.lagrangiantoeulerian , "in % = ", 100.0*(self.lagrangiantoeulerian)/(self.total)
			print "self.reseed " ,  self.reseed , "in % = ", 100.0*(self.reseed)/(self.total)
			print "self.prereseed " ,  self.prereseed , "in % = ", 100.0*(self.prereseed)/(self.total)
			print "TOTAL ----- " ,  self.total
			print "THIS TIME STEP = " , t13-t1 


    #######################################################################   
    def CalculatePressureProjection(self):
		self.model_part.ProcessInfo.SetValue(FRACTIONAL_STEP, 3) #explicit contribution by viscosity is defined as fract step = 0
		(self.ExplicitStrategy).InitializeSolutionStep(self.model_part.ProcessInfo);
		(self.ExplicitStrategy).AssembleLoop(self.model_part.ProcessInfo);
		self.model_part.ProcessInfo.SetValue(FRACTIONAL_STEP, 10)
		(self.ExplicitStrategy).FinalizeSolutionStep(self.model_part.ProcessInfo);


    #######################################################################   
    def CalculateExplicitViscosityContribution(self):
		self.model_part.ProcessInfo.SetValue(FRACTIONAL_STEP, 0) #explicit contribution by viscosity is defined as fract step = 0
		(self.ExplicitStrategy).InitializeSolutionStep(self.model_part.ProcessInfo);
		(self.ExplicitStrategy).AssembleLoop(self.model_part.ProcessInfo);
		(self.ExplicitStrategy).FinalizeSolutionStep(self.model_part.ProcessInfo);

    #######################################################################   

    def CalculateExplicitPressureViscousCorrection(self):
		self.model_part.ProcessInfo.SetValue(FRACTIONAL_STEP, 6) #explicit contribution by viscosity is defined as fract step = 0
		(self.ExplicitStrategy).InitializeSolutionStep(self.model_part.ProcessInfo);
		(self.ExplicitStrategy).AssembleLoop(self.model_part.ProcessInfo);
		(self.ExplicitStrategy).FinalizeSolutionStep(self.model_part.ProcessInfo);

    ####################################################################### 

    #######################################################################   

    def CalculateMassMatrix(self):
		self.model_part.ProcessInfo.SetValue(FRACTIONAL_STEP, 7) #explicit contribution by viscosity is defined as fract step = 0
		(self.ExplicitStrategy).InitializeSolutionStep(self.model_part.ProcessInfo);
		(self.ExplicitStrategy).AssembleLoop(self.model_part.ProcessInfo);
		#(self.ExplicitStrategy).FinalizeSolutionStep(self.model_part.ProcessInfo);

    ####################################################################### 

    def SetEchoLevel(self,level):
        (self.solver).SetEchoLevel(level)
