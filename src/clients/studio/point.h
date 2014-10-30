/*
 * point.h
 *
 *  Created on: Oct 29, 2014
 *      Author: loganek
 */

#ifndef POINT_H_
#define POINT_H_

namespace GstreamerStudio {
namespace Clients {

// todo I'm almost sure, in goocanvas library is a similar class...
template<typename T>
struct Point
{
  T x;
  T y;

  Point () : x (T()), y (T()) {}

  Point (const T& x, const T& y)
  {
    update (x, y);
  }

  void update (const T& x, const T& y)
  {
    this->x = x;
    this->y = y;
  }
};

}
}

#endif /* POINT_H_ */
