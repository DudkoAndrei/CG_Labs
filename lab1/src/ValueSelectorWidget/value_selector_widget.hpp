#pragma once

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>

class ValueSelectorWidget : public QWidget {
  Q_OBJECT

 public:
  ValueSelectorWidget(QWidget* parent, QString name, int min, int max);

 signals:
  void valueChanged(int value);

 public slots:
  void setValue(int value);

 private:
  void Connect();

  int min_;
  int max_;
  int value_;
  QString name_;

  QLabel* label_;
  QSlider* slider_;
  QSpinBox* spin_box_;

  QHBoxLayout* layout_;
};

