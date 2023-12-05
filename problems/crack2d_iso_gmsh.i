[Mesh]
  [./cube]
  type = GeneratedMeshGenerator
  dim = 3
  nx = 10
  ny = 10
  nz = 10
  [../]
[]

[GlobalParams]
  displacements = 'disp_x disp_y disp_z'
[]

[Modules/TensorMechanics/Master]
  [./block1]
    strain = FINITE
    add_variables = true
    generate_output = 'stress_yy strain_yy vonmises_stress max_principal_stress'
  [../]
[]

[Variables]
  [dm]   # damage variable
    order = FIRST
    family = MONOMIAL
  []
[]

[AuxVariables]
  [./hist_max]
    order = FIRST
    family = MONOMIAL
  [../]
  [./curr_value]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [d_dot]
    variable = dm
    type = TimeDerivative
  []
  [./ACInterface]
    type = ACInterface
    variable = dm
    mob_name = L
    kappa_name = kappa
  [../]
  [./AllenCahn]
    type = AllenCahn
    variable = dm
    mob_name = L
    f_name = f_loc
  [../]
[]

[AuxKernels]
  [./get_curr]
    type = MaterialRealAux
    property = effective_plastic_strain
    variable = curr_value
  [../]
  [./get_hist_max]
    type = ParsedAux
    variable = hist_max
    coupled_variables = 'curr_value hist_max'
    expression = 'max(hist_max,curr_value)'
  [../]
[]

[Functions]
  [./top_pull]
    type = ParsedFunction
    expression = t*(0.0625)
  [../]
[]

[Materials]
  [./isotropic_plasticity]
    type = IsotropicPlasticityStressUpdate
    yield_stress = 300.0
    hardening_constant = 500
    output_properties = effective_plastic_strain
    outputs = exodus
  [../]
  [./radial_return_stress]
    type = ComputeMultipleInelasticStress
    tangent_operator = elastic
    inelastic_models = 'isotropic_plasticity'
  [../]
  [./elasticity_tensor]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 2.1e5
    poissons_ratio = 0.3
  [../]
  [./constants]
    type = GenericConstantMaterial
    prop_names  = 'L   kappa'
    prop_values = '1.0 0.5'
  [../]
  [local_energy]
    # Defines the function for the local free energy density as given in the
    # problem, then converts units and adds scaling factor.
    type = DerivativeParsedMaterial
    block = 0
    f_name = f_loc
    coupled_variables = 'dm hist_max'
    constant_names = 'alpha   epsilon0'
    constant_expressions = '1.0 0.002'
    function = 'alpha / 2 * (hist_max - epsilon0) * (1 - dm)^2 + alpha * epsilon0 / 4 *(1-dm)^4'
  []
[]

[BCs]
  [./y_pull_function]
    type = FunctionDirichletBC
    variable = disp_y
    boundary = top
    function = top_pull
  [../]
  [./y_bot]
    type = DirichletBC
    variable = disp_y
    boundary = bottom
    value = 0.0
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'

  petsc_options = '-snes_ksp_ew'
  petsc_options_iname = '-pc_type -sub_pc_type -pc_asm_overlap -ksp_gmres_restart'
  petsc_options_value = 'asm lu 1 101'

  l_max_its = 50
  nl_max_its = 50
  nl_rel_tol = 1e-12
  nl_abs_tol = 1e-10
  l_tol = 1e-9

  start_time = 0.0
  end_time = 0.075
  dt = 0.00125
  dtmin = 0.0001
[]

[Postprocessors]
  [./ave_stress_yy_top]
    type = SideAverageValue
    variable = stress_yy
    boundary = top
  [../]
  [./ave_strain_yy_top]
    type = SideAverageValue
    variable = strain_yy
    boundary = top
  [../]
  [./av_max_pstress_top]
    type = SideAverageValue
    variable = max_principal_stress
    boundary = top
  [../]
  [./av_estrain_top]
    type = SideAverageMaterialProperty
    property = effective_plastic_strain
    boundary = top
  [../]
  [./av_damage_top]
    type = SideAverageValue
    variable = dm
    boundary = top
  [../]
[]

[Outputs]
  exodus = true
  perf_graph = true
  csv = true
  print_linear_residuals = false
[]
