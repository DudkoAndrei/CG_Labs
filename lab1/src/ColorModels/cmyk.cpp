#include "cmyk.hpp"

CMYK::CMYK(double c, double m, double y, double k)
  : c_(c), m_(m), y_(y), k_(k) {}

double CMYK::GetC() const {
  return c_;
}

void CMYK::SetC(double c) {
  c_ = c;
}

double CMYK::GetM() const {
  return m_;
}

void CMYK::SetM(double m) {
  m_ = m;
}

double CMYK::GetY() const {
  return y_;
}

void CMYK::SetY(double y) {
  y_ = y;
}

double CMYK::GetK() const {
  return k_;
}

void CMYK::SetK(double k) {
  k_ = k;
}
