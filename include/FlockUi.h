/*
 * This class represents the user interface for the cloth sim application.
 */

#ifndef _FLOCKUI_H_
#define _FLOCKUI_H_

#include "boost/shared_ptr.hpp"
#include "QMainWindow"

#include "GLWindow.h"

namespace Ui {
class MainWindow;
}

class FlockUi: public QMainWindow
{
  Q_OBJECT

public:
  //constructor
  explicit FlockUi(QWidget *parent = 0);
  ~FlockUi();

private:
	//The interface
	Ui::MainWindow *m_ui;
	// The OpenGL window, which will be part of the interface
	GLWindow *m_gl;




private slots :

};

#endif // FLOCKUI_H
