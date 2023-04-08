#include "rectangle.h"
#include <fstream>
#include <iostream>

using namespace std;

ostream &Rectangle::write(ostream &out) const {
  out << "      <rect ";
  out << "x=\"" << x << "\" ";
  out << "y=\"" << y << "\" ";
  out << "width=\"" << width << "\" ";
  out << "height=\"" << height << "\" ";
  out << "fill=\"" << color << "\" ";
  out << " />" << endl;
  return out;
}

// operator>> equivalent to read the object contents
istream &Rectangle::read(istream &inf) {
  inf >> x >> y >> width >> height >> color;
  return inf;
}