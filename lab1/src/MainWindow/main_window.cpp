#include "main_window.hpp"

#include "ColorModels/converter.hpp"

#include <QColorDialog>

MainWindow::MainWindow()
    : widget_(new QWidget(this)), layout_(new QGridLayout(widget_)),
      button_(new QPushButton("Select Color", widget_)),
      rgb_label_(new QLabel("RGB", widget_)),
      r_selector_(new ValueSelectorWidget(this, "R", 0, 255)),
      g_selector_(new ValueSelectorWidget(this, "G", 0, 255)),
      b_selector_(new ValueSelectorWidget(this, "B", 0, 255)),
      hsv_label_(new QLabel("HSV", widget_)),
      h_selector_(new ValueSelectorWidget(this, "H", 0, 359)),
      s_selector_(new ValueSelectorWidget(this, "S", 0, 100)),
      v_selector_(new ValueSelectorWidget(this, "V", 0, 100)),
      cmyk_label_(new QLabel("CMYK", widget_)),
      c_selector_(new ValueSelectorWidget(this, "C", 0, 100)),
      m_selector_(new ValueSelectorWidget(this, "M", 0, 100)),
      y_selector_(new ValueSelectorWidget(this, "Y", 0, 100)),
      k_selector_(new ValueSelectorWidget(this, "K", 0, 100)),
      color_(new QWidget(this)) {
  color_->setAutoFillBackground(true);
  hsv_ = ToHSV(rgb_);
  cmyk_ = ToCMYK(rgb_);
  UpdateColor(ModelChanged::kRGB);

  PlaceWidgets();
  ConnectWidgets();

  setCentralWidget(widget_);
}

void MainWindow::PlaceWidgets() {
  layout_->addWidget(button_, 0, 3);
  layout_->addWidget(rgb_label_, 0, 0);
  layout_->addWidget(hsv_label_, 0, 1);
  layout_->addWidget(cmyk_label_, 0, 2);
  layout_->addWidget(r_selector_, 1, 0);
  layout_->addWidget(g_selector_, 2, 0);
  layout_->addWidget(b_selector_, 3, 0);
  layout_->addWidget(h_selector_, 1, 1);
  layout_->addWidget(s_selector_, 2, 1);
  layout_->addWidget(v_selector_, 3, 1);
  layout_->addWidget(c_selector_, 1, 2);
  layout_->addWidget(m_selector_, 2, 2);
  layout_->addWidget(y_selector_, 3, 2);
  layout_->addWidget(k_selector_, 4, 2);
  layout_->addWidget(color_, 1, 3, 4, 1);

  widget_->setLayout(layout_);
}

void MainWindow::ConnectWidgets() {
  connect(button_, &QPushButton::clicked, [&]() {
    auto current = QColor(rgb_.GetR(), rgb_.GetG(), rgb_.GetB());

    auto temp = QColorDialog::getColor(
        current, this, "Select Color",
        {QColorDialog::ColorDialogOption::DontUseNativeDialog});

    rgb_.SetR(temp.red());
    rgb_.SetG(temp.green());
    rgb_.SetB(temp.blue());

    UpdateColor(ModelChanged::kRGB);
  });

  connect(r_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    rgb_.SetR(value);
    UpdateColor(ModelChanged::kRGB);
  });
  connect(g_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    rgb_.SetG(value);
    UpdateColor(ModelChanged::kRGB);
  });
  connect(b_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    rgb_.SetB(value);
    UpdateColor(ModelChanged::kRGB);
  });

  connect(h_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    hsv_.SetH(value);
    UpdateColor(ModelChanged::kHSV);
  });
  connect(s_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    hsv_.SetS(value / 100.0);
    UpdateColor(ModelChanged::kHSV);
  });
  connect(v_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    hsv_.SetV(value / 100.0);
    UpdateColor(ModelChanged::kHSV);
  });

  connect(c_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    cmyk_.SetC(value / 100.0);
    UpdateColor(ModelChanged::kCMYK);
  });
  connect(m_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    cmyk_.SetM(value / 100.0);
    UpdateColor(ModelChanged::kCMYK);
  });
  connect(y_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    cmyk_.SetY(value / 100.0);
    UpdateColor(ModelChanged::kCMYK);
  });
  connect(k_selector_, &ValueSelectorWidget::valueChanged, [&](int value) {
    cmyk_.SetK(value / 100.0);
    UpdateColor(ModelChanged::kCMYK);
  });
}

void MainWindow::UpdateColor(MainWindow::ModelChanged model_changed) {
  QColor color;

  this->blockSignals(true);
  switch (model_changed) {
  case ModelChanged::kRGB: {
    color.setRgb(rgb_.GetR(), rgb_.GetG(), rgb_.GetB());

    hsv_ = ToHSV(rgb_);
    cmyk_ = ToCMYK(rgb_);
    break;
  }
  case ModelChanged::kHSV: {
    color.setHsvF(hsv_.GetH() / 360.0, hsv_.GetS(), hsv_.GetV());

    rgb_ = ToRGB(hsv_);
    cmyk_ = ToCMYK(hsv_);
    break;
  }
  case ModelChanged::kCMYK: {
    color.setCmykF(cmyk_.GetC(), cmyk_.GetM(), cmyk_.GetY(), cmyk_.GetK());

    rgb_ = ToRGB(cmyk_);
    hsv_ = ToHSV(cmyk_);
    break;
  }
  }

  auto palette = QPalette();
  palette.setColor(QPalette::Window, color);
  color_->setPalette(palette);

  UpdateRGB();
  UpdateCMYK();
  UpdateHSV();

  this->blockSignals(false);
}

void MainWindow::UpdateRGB() {
  r_selector_->setValue(rgb_.GetR());
  g_selector_->setValue(rgb_.GetG());
  b_selector_->setValue(rgb_.GetB());
}

void MainWindow::UpdateHSV() {
  h_selector_->setValue(hsv_.GetH());
  s_selector_->setValue(std::lround(hsv_.GetS() * 100.0));
  v_selector_->setValue(std::lround(hsv_.GetV() * 100.0));
}

void MainWindow::UpdateCMYK() {
  c_selector_->setValue(std::lround(cmyk_.GetC() * 100.0));
  m_selector_->setValue(std::lround(cmyk_.GetM() * 100.0));
  y_selector_->setValue(std::lround(cmyk_.GetY() * 100.0));
  k_selector_->setValue(std::lround(cmyk_.GetK() * 100.0));
}
