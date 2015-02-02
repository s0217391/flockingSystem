// Implementation of the UI functions

#include "ClothUi.h"
#include "ui_ClothUi.h"
#include <QApplication>
#include <set>
#include <string>

// Constructor - links the ui to the code
ClothUi::ClothUi(QWidget *parent) :QMainWindow(parent),  m_ui(new Ui::MainWindow)
{
  // set up th eUI
  m_ui->setupUi(this);

  // create an openGL format and pass to the new GLWidget
  QGLFormat format;
  format.setVersion(3,2);
  format.setProfile( QGLFormat::CoreProfile);

  m_gl = new  GLWindow(format,this);
  //add gl to the ui
  m_ui->Sim_grid->addWidget(m_gl,0,0,12,1);
}

//dtor
ClothUi::~ClothUi()
{
  delete m_ui;
}
