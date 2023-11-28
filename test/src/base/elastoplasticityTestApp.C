//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "elastoplasticityTestApp.h"
#include "elastoplasticityApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
elastoplasticityTestApp::validParams()
{
  InputParameters params = elastoplasticityApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

elastoplasticityTestApp::elastoplasticityTestApp(InputParameters parameters) : MooseApp(parameters)
{
  elastoplasticityTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

elastoplasticityTestApp::~elastoplasticityTestApp() {}

void
elastoplasticityTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  elastoplasticityApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"elastoplasticityTestApp"});
    Registry::registerActionsTo(af, {"elastoplasticityTestApp"});
  }
}

void
elastoplasticityTestApp::registerApps()
{
  registerApp(elastoplasticityApp);
  registerApp(elastoplasticityTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
elastoplasticityTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  elastoplasticityTestApp::registerAll(f, af, s);
}
extern "C" void
elastoplasticityTestApp__registerApps()
{
  elastoplasticityTestApp::registerApps();
}
