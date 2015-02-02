/****************************************************************************
basic OpenGL demo taken from the NCCA SimpleDrawing demo
****************************************************************************/

#include <QApplication>
#include <iostream>

#include "ClothUi.h"
int main(int argc, char **argv)
{
  //*
  // make an instance of the QApplication
  QApplication a(argc, argv);
  // Create a new ClothUi
  ClothUi w;
  // show it
  w.show();
  // hand control over to Qt framework
  return a.exec();
}
