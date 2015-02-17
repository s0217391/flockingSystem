// The code for the OpenGL window. Responsible for drawing the cloth and the environment objects.
// this is very much based on Jon Macey's demos

#include "GLWindow.h"
#include <iostream>
#include <ngl/Vec3.h>
#include <ngl/Quaternion.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Util.h>
#include <ngl/Material.h>



//----------------------------------------------------------------------------------------------------------------------
GLWindow::GLWindow(const QGLFormat _format, QWidget *_parent)
  : QGLWidget( _format, _parent ), c_increment(0.1f), c_zoom(1.0f)  {}



// This virtual function is called once before the first call to paintGL() or resizeGL(),
// and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.
void GLWindow::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);			   // Grey Background becaue I'm unoriginal
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  // as re-size is not explicitly called we need to do this.
  glViewport(0,0,width(),height());

  //CAMERA ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Now we will create a basic Camera from the graphics library
  // First create Values for the camera position
  ngl::Vec3 from(10,10,10);
  ngl::Vec3 to(0,0,0);
  ngl::Vec3 up(0,1,0);
  // now load to our new camera
  m_cam= new ngl::Camera(from,to,up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_cam->setShape(45,(float)720.0/576.0,0.1,350);

  // PUT IN SHADERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Get the NGL shader lib.
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  // set this as the active shader
  shader->use("nglColourShader");
  // set the colour to white
  shader->setShaderParam4f("Colour",1.0f,1.0f,1.0f,1.0f);

  glViewport(0,0,width(),height());

  startTimer(10); // ########################################################## timing!!!

  //INIT VAO for triangles

  // FLOCKING
  m_flocker.createNewFlock(); // one flock (flock zero)
  m_agentNumber = 100;
  for(int i = 0; i < m_agentNumber; ++i)
  {
    m_flocker.addAgentToFlock(0);
  }

  m_positions.resize(m_agentNumber);
  m_velocities.resize(m_agentNumber);

  // first create the VAO
  m_vao = ngl::VertexArrayObject::createVOA(GL_POINTS);
  // to use this it must be bound
  m_vao->bind();
  // now copy the data
  m_vao->setData(m_positions.size()*sizeof(ngl::Vec3),m_positions[0].m_x);
  // now we need to tell OpenGL the  size and layout of the data
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);

  // now tell OpenGL how many elements we have
  m_vao->setNumIndices(m_positions.size());
  // always best to unbind after use
  m_vao->unbind();

}


// load the matrices to the shader for drawing
void GLWindow::loadMatricesToClothShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;

  // m_transform is never used for the cloth.
  MV  = m_mouseGlobalTX * m_cam->getViewMatrix();
  MVP = MV * m_cam->getProjectionMatrix() ;

  normalMatrix = MV;
  normalMatrix.inverse();

  //shader->setUniform("MV",MV);
  shader->setUniform("MVP",MVP);
  //shader->setUniform("normalMatrix",normalMatrix);
}


//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
void GLWindow::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX(m_spinXFace);
  rotY.rotateY(m_spinYFace);
  // multiply the rotations
  m_mouseGlobalTX=rotY*rotX;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  loadMatricesToClothShader();

  m_vao->bind();
  m_vao->draw(); // draw
  m_vao->unbind();
}

// Update the points of the cloth
void GLWindow::updatePoints()
{
  // get the next agent state right here //////////////////////////////////////////////////////////////////////////////////////////////////////
  m_flocker.updateSystem();
  m_flocker.getAgentStates(m_positions, m_velocities);

  // to use this it must be bound
  m_vao->bind();
  // now copy the data
  m_vao->setNumIndices(m_positions.size());
  m_vao->updateData(0, m_positions.size()*sizeof(ngl::Vec3),m_positions[0].m_x);

  // always best to unbind after use
  m_vao->unbind();
}

void GLWindow::mouseMoveEvent (QMouseEvent * _event)
{
  // note the method buttons() is the button state when event was called
  // this is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
  if(m_rotate && _event->buttons() == Qt::LeftButton)
  {
    int diffx=_event->x()-m_origX;
    int diffy=_event->y()-m_origY;
    m_spinXFace += (float) 0.5f * diffy;
    m_spinYFace += (float) 0.5f * diffx;
    m_origX = _event->x();
    m_origY = _event->y();

  }
  // right mouse translate code
  else if(m_translate && _event->buttons() == Qt::RightButton)
  {
    int diffX = (int)(_event->x() - m_origXPos);
    int diffY = (int)(_event->y() - m_origYPos);
    m_origXPos=_event->x();
    m_origYPos=_event->y();
    m_modelPos.m_x += c_increment * diffX;
    m_modelPos.m_y -= c_increment * diffY;

  }
}


//----------------------------------------------------------------------------------------------------------------------
void GLWindow::mousePressEvent ( QMouseEvent * _event)
{
  // this method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if(_event->button() == Qt::LeftButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate =true;
  }
  // right mouse translate mode
  else if(_event->button() == Qt::RightButton)
  {
    m_origXPos = _event->x();
    m_origYPos = _event->y();
    m_translate=true;
  }

}

//----------------------------------------------------------------------------------------------------------------------
void GLWindow::mouseReleaseEvent ( QMouseEvent * _event )
{
  // this event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::LeftButton)
  {
    m_rotate=false;
  }
  // right mouse translate mode
  if (_event->button() == Qt::RightButton)
  {
    m_translate=false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void GLWindow::wheelEvent(QWheelEvent *_event)
{

  // check the diff of the wheel position (0 means no change)
  if(_event->delta() > 0)
  {
    m_modelPos.m_z+= c_zoom;
  }
  else if(_event->delta() <0 )
  {
    m_modelPos.m_z-= c_zoom;
  }
}


void GLWindow::timerEvent(QTimerEvent *_event)
{
  updatePoints();
  updateGL();
}



GLWindow::~GLWindow()
{
  ngl::NGLInit *init = ngl::NGLInit::instance();
  init->NGLQuit();
}

