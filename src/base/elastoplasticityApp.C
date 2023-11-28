#include "elastoplasticityApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
elastoplasticityApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

elastoplasticityApp::elastoplasticityApp(InputParameters parameters) : MooseApp(parameters)
{
  elastoplasticityApp::registerAll(_factory, _action_factory, _syntax);
}

elastoplasticityApp::~elastoplasticityApp() {}

void 
elastoplasticityApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAllObjects<elastoplasticityApp>(f, af, s);
  Registry::registerObjectsTo(f, {"elastoplasticityApp"});
  Registry::registerActionsTo(af, {"elastoplasticityApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
elastoplasticityApp::registerApps()
{
  registerApp(elastoplasticityApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
elastoplasticityApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  elastoplasticityApp::registerAll(f, af, s);
}
extern "C" void
elastoplasticityApp__registerApps()
{
  elastoplasticityApp::registerApps();
}
