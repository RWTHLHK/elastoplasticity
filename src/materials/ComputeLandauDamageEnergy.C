#include "ComputeLandauDamageEnergy.h"

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
 _transition_property_name(getParam<MaterialPropertyName>("transition_property_name"))
 _transition_value(getMaterialPropertyByName<Real>(_transition_property_name)),


{}

void
ComputeLandauDamageEnergy::initQpStatefulProperties()
{
  _H[_qp] = 0.0;
}


