/*
 * controller.cpp
 *
 *  Created on: Dec 23, 2014
 *      Author: mkolny
 */

#include "controller.h"
#include "IGui.h"

using namespace GstreamerStudio::Core;

Controller::Controller(const std::string& model_name, int argc, char** argv)
: GstreamerController(model_name, argc, argv)
{
}
