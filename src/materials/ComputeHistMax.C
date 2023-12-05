#include "ComputeHistMax.h"

registerMooseObject("elastoplasticityApp", ComputeHistMax);

InputParameters
ComputeHistMax::validParams()
{
  InputParameters params = Material::validParams();
  params.addParam<MaterialPropertyName>("property_name",
                                        "property name of phase transition");
  return params;
}

ComputeHistMax::ComputeHistMax(const InputParameters & parameters)
 : Material(parameters),
 _property_name(getParam<MaterialPropertyName>("property_name")),
 _curr_value(getMaterialPropertyByName<Real>(_property_name)),
_H(declareProperty<Real>("hist"))
{}

void
ComputeHistMax::initQpStatefulProperties()
{
  _H[_qp] = 0.0;
}

void
ComputeHistMax::computeQpProperties()
{
  ///find maximum critical value
  if (_H[_qp] < _curr_value[_qp])
  {
    _H[_qp] = _curr_value[_qp];
  }
}


