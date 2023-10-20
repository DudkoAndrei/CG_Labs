#include "rgb.hpp"

RGB::RGB(uint8_t r, uint8_t g, uint8_t b)
  : r_(r), g_(g), b_(b) {}

uint8_t RGB::GetR() const {
  return r_;
}

void RGB::SetR(uint8_t r) {
  r_ = r;
}

uint8_t RGB::GetG() const {
  return g_;
}

void RGB::SetG(uint8_t g) {
  g_ = g;
}

uint8_t RGB::GetB() const {
  return b_;
}

void RGB::SetB(uint8_t b) {
  b_ = b;
}
