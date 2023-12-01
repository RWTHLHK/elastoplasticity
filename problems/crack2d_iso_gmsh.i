[Mesh]
  type = FileMesh
  file = crack.msh
[]

[GlobalParams]
  displacements = 'disp_x disp_y'
[]

[Modules/TensorMechanics/Master]
  [./block1]
    strain = FINITE
    add_variables = true
    generate_output = 'stress_yy strain_yy vonmises_stress max_principal_stress effective_plastic_strain'
  [../]
[]

[Materials]
  [./fplastic]
    type = FiniteStrainPlasticMaterial
    block = all
    yield_stress='0. 445. 0.05 610. 0.1 680. 0.38 810. 0.95 920. 2. 950.'
  [../]
  [./elasticity_tensor]
    type = ComputeElasticityTensor
    block = all
    C_ijkl = '2.827e5 1.21e5 1.21e5 2.827e5 1.21e5 2.827e5 0.808e5 0.808e5 0.808e5'
    fill_method = symmetric9
  [../]
[]

[BCs]
  [yfix]
    type = DirichletBC
    variable = disp_y
    boundary = bottom
    value = 0
  []
  [ydisp]
    type = FunctionDirichletBC
    variable = disp_y
    boundary = top
    function = '0.0005*t'
  []
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  dt = 0.25
  end_time = 40
  dtmin = 1e-10
  solve_type = 'PJFNK'

  petsc_options = '-snes_ksp_ew'
  petsc_options_iname = '-pc_type -sub_pc_type -pc_asm_overlap -ksp_gmres_restart'
  petsc_options_value = 'asm lu 1 101'
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
  [./ave_max_pstress_top]
    type = SideAverageValue
    variable = max_principal_stress
    boundary = top
  [../]
  [./ave_estrain_top]
    type = SideAverageValue
    variable = effective_plastic_strain
    boundary = top
  [../]
[]

[Outputs]
  exodus = true
  perf_graph = true
  csv = true
  print_linear_residuals = false
[]
