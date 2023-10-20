#pragma once

#include "cmyk.hpp"
#include "hsv.hpp"
#include "rgb.hpp"

CMYK ToCMYK(const RGB& rgb);
CMYK ToCMYK(const HSV& hsv);

HSV ToHSV(const CMYK& cmyk);
HSV ToHSV(const RGB& rgb);

RGB ToRGB(const CMYK& cmyk);
RGB ToRGB(const HSV& hsv);
