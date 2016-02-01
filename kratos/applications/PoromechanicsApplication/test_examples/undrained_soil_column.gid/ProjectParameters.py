## General Data ---------------------------------------------------------------------------------------------------------------

domain_size = 2
NumberofThreads = 1
delta_time = 0.02
ending_time = 2
fic_stabilization = False


## Solver Data ----------------------------------------------------------------------------------------------------------------

class SolverSettings:
    analysis_type = "Quasi-Static"
    strategy_type = "Newton-Raphson"
    dofs_relative_tolerance = 1.0E-4
    residual_relative_tolerance = 1.0E-4
    max_iteration = 15
    linear_solver = "Direct"
    direct_solver = "Super_LU"
    iterative_solver = "AMGCL"
    compute_reactions = True


## Boundary Conditions Data ---------------------------------------------------------------------------------------------------

class ConditionsOptions:
    Imposed_Displacement = "Constant"
    Imposed_Pressure = "Constant"
    Imposed_PointLoad = "Constant"
    Imposed_LineLoad = "Constant"
    Imposed_SurfaceLoad = "Constant"
    Imposed_NormalLoad = "Constant"
    Imposed_TangentialLoad = "Constant"
    Imposed_NormalFluidFlux = "Constant"


## PostProcess Data -----------------------------------------------------------------------------------------------------------

nodal_results = ["DISPLACEMENT","WATER_PRESSURE","REACTION","REACTION_WATER_PRESSURE","NO_RESULT","LINE_LOAD","NO_RESULT","NO_RESULT","NO_RESULT","NO_RESULT"]
gauss_points_results=["NO_RESULT","CAUCHY_STRESS_TENSOR","NO_RESULT","FLUID_FLUX"]

class GidOutputConfiguration:
    GiDWriteMeshFlag = True
    GiDWriteConditionsFlag = False
    GiDPostFiles = "Single"
    GiDPostMode = "Binary"
    GiDWriteFrequency = 0.02


## Problem Data ---------------------------------------------------------------------------------------------------------------

problem_name = 'undrained_soil_column'
problem_path = '/path/to/kratos/applications/PoromechanicsApplication/test_examples/undrained_soil_column.gid'
