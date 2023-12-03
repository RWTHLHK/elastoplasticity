#pragma once

#include "Material.h"

class ComputeLandauDamageEnergy : public Material
{
public:
  ComputeLandauDamageEnergyl(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

private:
  /// member variable to hold the local free energy density
  MaterialProperty<Real> & _f_loc;
  ///member variable to hold equivalent plastic strain or maximum principla stress
  const MaterialProperty<Real> & _transition_value;
  /// member variable to hold the historical maximum local equivalent plastic strain
  MaterialProperty<Real> & _H;
  /// Coupled order parameter defining the crack
  const VariableValue & _d;
  /// deviation parameter from critical transition value
  const MaterialProperty<Real> & _alpha;
  /// critical transition plastic strain or stress
  const MaterialProperty<Real> & _critical_transition_value;
  /// property names of phase transition (effective_plastic_strain or maximal_principle_stress)
  const std::string & _transition_property_name;
};