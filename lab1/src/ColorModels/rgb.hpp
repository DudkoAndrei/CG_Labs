#pragma once

#include <cstdint>

class RGB {
 public:
  RGB() = default;
  RGB(uint8_t r, uint8_t g, uint8_t b);

  uint8_t GetR() const;
  void SetR(uint8_t r);

  uint8_t GetG() const;
  void SetG(uint8_t g);

  uint8_t GetB() const;
  void SetB(uint8_t b);

 private:
  uint8_t r_ = 0;
  uint8_t g_ = 0;
  uint8_t b_ = 0;
};
