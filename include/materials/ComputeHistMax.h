#pragma once

#include "Material.h"

class ComputeHistMax : public Material
{
public:
  ComputeHistMax(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

private:

  /// member variable to hold the historical maximum local equivalent plastic strain
  MaterialProperty<Real> & _H;
  /// memeber variable to hold the current value
  const MaterialProperty<Real> & _curr_value;
  /// property names of phase transition (effective_plastic_strain or maximal_principle_stress)
  const std::string & _property_name;
};