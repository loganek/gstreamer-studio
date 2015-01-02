/*
 * IGui.h
 *
 *  Created on: Dec 23, 2014
 *      Author: mkolny
 */

#ifndef IGUI_H_
#define IGUI_H_

#include "controller.h"

#include <memory>

namespace GstreamerStudio {
namespace Core {

class IGui
{
public:
  virtual ~IGui(){}
  virtual void set_controller (std::shared_ptr<Controller> controller) = 0;
  virtual void current_model_changed (const std::string& path) = 0;
};

}
}

#endif /* IGUI_H_ */
