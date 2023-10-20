#include <QApplication>

#include "MainWindow/main_window.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  QCoreApplication::setApplicationName("Color Converter");

  MainWindow window;
  window.show();

  return QApplication::exec();
}
