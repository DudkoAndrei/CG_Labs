#include "value_selector_widget.hpp"

ValueSelectorWidget::ValueSelectorWidget(QWidget *parent, QString name, int min, int max)
  : QWidget(parent),
   min_(min),
   max_(max),
   value_(min),
   name_(std::move(name)),
   label_(new QLabel(name_, this)),
   slider_(new QSlider(Qt::Orientation::Horizontal, this)),
   spin_box_(new QSpinBox(this)),
   layout_(new QHBoxLayout(this)) {
  slider_->setTickInterval(1);
  slider_->setMinimum(min);
  slider_->setMaximum(max);

  spin_box_->setMinimum(min);
  spin_box_->setMaximum(max);

  layout_->addWidget(label_);
  layout_->addWidget(slider_);
  layout_->addWidget(spin_box_);

  setLayout(layout_);
  Connect();
}

void ValueSelectorWidget::Connect() {
  connect(slider_, &QSlider::valueChanged, [&](int value) {
    spin_box_->blockSignals(true);
    spin_box_->setValue(value);
    spin_box_->blockSignals(false);

    emit valueChanged(value);
  });

  connect(spin_box_, &QSpinBox::valueChanged, [&](int value) {
    slider_->blockSignals(true);
    slider_->setValue(value);
    slider_->blockSignals(false);

    emit valueChanged(value);
  });
}

void ValueSelectorWidget::setValue(int value) {
  this->blockSignals(true);
  spin_box_->setValue(value);
  slider_->setValue(value);
  this->blockSignals(false);
}
