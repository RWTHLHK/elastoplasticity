#include "ComputeLandauDamageEnergy.h"

registerMooseObject("elastoplasticityApp", ComputeLandauDamageEnergy);

InputParameters
ComputeLandauDamageEnergy::validParams()
{
  InputParameters params = Material::validParams();
  params.addRequiredCoupledVar("d", "Name of damage variable");

  params.addRequiredParam<Real>("alpha",
                                        "deviation parameter from critical transition value");
  params.addRequiredParam<Real>("critical_transition_value",
                                        "critical transition plastic strain or stress");
  params.addParam<MaterialPropertyName>("transition_property_name",
                                        "property name of phase transition");
  return params;
}

ComputeLandauDamageEnergy::ComputeLandauDamageEnergy(const InputParameters & parameters)
 : Material(parameters),
 _f_loc(declareProperty<Real>("landau_damage_energy")),
 _transition_property_name(getParam<MaterialPropertyName>("transition_property_name")),
 _transition_value(getMaterialPropertyByName<Real>(_transition_property_name)),
_H(declareProperty<Real>("hist")),
_alpha(getParam<Real>("alpha")),
_critical_transition_value(getParam<Real>("critical_transition_value")),
_d(coupledValue("d"))
{}

void
ComputeLandauDamageEnergy::initQpStatefulProperties()
{
  _H[_qp] = 0.0;
}

void
ComputeLandauDamageEnergy::computeQpProperties()
{
  ///find maximum critical value
  if (_H[_qp] < _transition_value[_qp])
  {
    _H[_qp] = _transition_value[_qp];
  }
  _f_loc[_qp] = _alpha / 2.0 * (_H[_qp] - _critical_transition_value) * (std::pow(1 - _d[_qp], 2) - std::pow(1 - _d[_qp], 4) / 2);
}


