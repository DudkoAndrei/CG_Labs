#include "converter.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>

CMYK ToCMYK(const RGB& rgb) {
  double r = rgb.GetR() / 255.0;
  double g = rgb.GetG() / 255.0;
  double b = rgb.GetB() / 255.0;

  double k = 1.0 - std::max({r, g, b});
  double c = (1.0 - r - k) / (1.0 - k);
  double m = (1.0 - g - k) / (1.0 - k);
  double y = (1.0 - b - k) / (1.0 - k);

  return {c, m, y, k};
}

CMYK ToCMYK(const HSV& hsv) {
  return ToCMYK(ToRGB(hsv));
}

HSV ToHSV(const CMYK& cmyk) {
  return ToHSV(ToRGB(cmyk));
}

HSV ToHSV(const RGB& rgb) {
  double r = rgb.GetR() / 255.0;
  double g = rgb.GetG() / 255.0;
  double b = rgb.GetB() / 255.0;

  auto [c_min, c_max] = std::minmax({r, g, b});
  double delta = c_max - c_min;

  double h;

  if (delta <= 1e-9) {
    h = 0;
  } else if (c_max == r) {
    h = 60.0 * ((g - b) / delta);
  } else if (c_max == g) {
    h = 60.0 * ((b - r) / delta + 2);
  } else {
    h = 60.0 * ((r - g) / delta + 4);
  }

  double s;

  if (c_max <= 1e-9) {
    s = 0;
  } else {
    s = delta / c_max;
  }

  return {h, s, c_max};
}

RGB ToRGB(const CMYK& cmyk) {
  uint8_t r = std::lround(255.0 * (1.0 - cmyk.GetC()) * (1.0 - cmyk.GetK()));
  uint8_t g = std::lround(255.0 * (1.0 - cmyk.GetM()) * (1.0 - cmyk.GetK()));
  uint8_t b = std::lround(255.0 * (1.0 - cmyk.GetY()) * (1.0 - cmyk.GetK()));

  return {r, g, b};
}

RGB ToRGB(const HSV& hsv) {
  double h_mod2 = hsv.GetH() / 60.0;
  while (h_mod2 > 2.0) {
    h_mod2 -= 2.0;
  }

  double c = hsv.GetV() * hsv.GetS();
  double x = c * (1.0 - (h_mod2 - 1.0));
  double m = hsv.GetV() - c;

  double r;
  double g;
  double b;

  if (hsv.GetH() < 60.0) {
    r = c;
    g = x;
    b = 0;
  } else if (hsv.GetH() < 120.0) {
    r = x;
    g = c;
    b = 0;
  } else if (hsv.GetH() < 180.0) {
    r = 0;
    g = c;
    b = x;
  } else if (hsv.GetH() < 240.0) {
    r = 0;
    g = x;
    b = c;
  } else if (hsv.GetH() < 300.0) {
    r = x;
    g = 0;
    b = c;
  } else {
    r = c;
    g = 0;
    b = x;
  }

  uint8_t r_int = std::lround((r + m) * 255.0);
  uint8_t g_int = std::lround((g + m) * 255.0);
  uint8_t b_int = std::lround((b + m) * 255.0);

  return {r_int, g_int, b_int};
}
