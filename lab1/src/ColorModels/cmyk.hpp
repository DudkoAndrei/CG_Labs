#pragma once

#include <cstdint>

class CMYK {
 public:
  CMYK() = default;
  CMYK(double c, double m, double y, double k);

  double GetC() const;
  void SetC(double c);

  double GetM() const;
  void SetM(double m);

  double GetY() const;
  void SetY(double y);

  double GetK() const;
  void SetK(double k);

 private:
  double c_;
  double m_;
  double y_;
  double k_;
};
