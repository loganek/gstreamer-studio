/*
 * iselectableobserver.h
 *
 *  Created on: Jan 2, 2015
 *      Author: loganek
 */

#ifndef ISELECTABLEOBSERVER_H_
#define ISELECTABLEOBSERVER_H_

#include "core/IObservable.h"

#include <gstreamermm.h>

namespace GstreamerStudio {
namespace Clients {

class ISelectableObserver
{
public:
  virtual ~ISelectableObserver () {}
  virtual void selection_changed (Core::IObservable<ISelectableObserver>* sender, const Glib::RefPtr<Gst::Object>& selected) {}
};

}
}

#endif /* ISELECTABLEOBSERVER_H_ */
