#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>

#include "ColorModels/cmyk.hpp"
#include "ColorModels/hsv.hpp"
#include "ColorModels/rgb.hpp"
#include "ValueSelectorWidget/value_selector_widget.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

 private:
  enum class ModelChanged {
    kRGB,
    kHSV,
    kCMYK
  };

  void PlaceWidgets();
  void ConnectWidgets();
  void UpdateColor(ModelChanged model_changed);
  void UpdateRGB();
  void UpdateHSV();
  void UpdateCMYK();

  CMYK cmyk_;
  HSV hsv_;
  RGB rgb_;

  QWidget* widget_;
  QGridLayout* layout_;

  QPushButton* button_;

  QLabel* rgb_label_;
  ValueSelectorWidget* r_selector_;
  ValueSelectorWidget* g_selector_;
  ValueSelectorWidget* b_selector_;

  QLabel* hsv_label_;
  ValueSelectorWidget* h_selector_;
  ValueSelectorWidget* s_selector_;
  ValueSelectorWidget* v_selector_;

  QLabel* cmyk_label_;
  ValueSelectorWidget* c_selector_;
  ValueSelectorWidget* m_selector_;
  ValueSelectorWidget* y_selector_;
  ValueSelectorWidget* k_selector_;

  QWidget* color_;
};
