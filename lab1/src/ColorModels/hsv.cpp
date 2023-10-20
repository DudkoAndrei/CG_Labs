#include "hsv.hpp"

HSV::HSV(double h, double s, double v)
  : h_(h), s_(s), v_(v) {}

double HSV::GetH() const {
  return h_;
}

void HSV::SetH(double h) {
  h_ = h;
}

double HSV::GetS() const {
  return s_;
}

void HSV::SetS(double s) {
  s_ = s;
}

double HSV::GetV() const {
  return v_;
}

void HSV::SetV(double v) {
  v_ = v;
}
