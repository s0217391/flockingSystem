/****************************************************************************
basic OpenGL demo taken from the NCCA SimpleDrawing demo
****************************************************************************/

#include <QApplication>
#include <iostream>

#include "FlockUi.h"

#include "EcoSystem.h"

int main(int argc, char **argv)
{
  //*
  // make an instance of the QApplication
  QApplication a(argc, argv);
  // Create a new ClothUi
  FlockUi w;
  // show it
  w.show();
  // hand control over to Qt framework
  return a.exec();
}
