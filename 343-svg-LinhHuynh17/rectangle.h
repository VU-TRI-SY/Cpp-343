/**
 * SVG Circle
 **/
//comment
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Rectangle : public SVG {

public:
  // operator<< equivalent to write the object out
  ostream &write(ostream &out) const override;

  // operator>> equivalent to read the object contents
  istream &read(istream &inf) override;

private:
  // coordinates for rectangle's top-left corner
  int x{0}, y{0};

  // size of the rectangle
  int width{0}, height{0};

  // color of rectangle
  string color{"black"};
};

#endif
