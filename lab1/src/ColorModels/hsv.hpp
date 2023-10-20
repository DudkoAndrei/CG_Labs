#pragma once

#include <cstdint>

class HSV {
 public:
  HSV() = default;
  HSV(double h, double s, double v);

  double GetH() const;
  void SetH(double h);

  double GetS() const;
  void SetS(double s);

  double GetV() const;
  void SetV(double v);

 private:
  double h_;
  double s_;
  double v_;
};
