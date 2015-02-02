/*
 * This class represents the user interface for the cloth sim application.
 */

#ifndef _CLOTHUI_H_
#define _CLOTHUI_H_

#include "boost/shared_ptr.hpp"
#include "QMainWindow"

#include "GLWindow.h"

namespace Ui {
class MainWindow;
}

class ClothUi: public QMainWindow
{
  Q_OBJECT

public:
  //constructor
  explicit ClothUi(QWidget *parent = 0);
  ~ClothUi();

private:
	//The interface
	Ui::MainWindow *m_ui;
	// The OpenGL window, which will be part of the interface
    GLWindow *m_gl;




private slots :

};

#endif // CLOTHUI_H
