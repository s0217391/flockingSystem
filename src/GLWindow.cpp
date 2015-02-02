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
  ngl::Vec3 from(0,0,30);
  ngl::Vec3 to(0,0,0);
  ngl::Vec3 up(0,1,0);
  // now load to our new camera
  m_cam= new ngl::Camera(from,to,up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_cam->setShape(45,(float)720.0/576.0,0.05,350);


  // PUT IN SHADERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Get the NGL shader lib.
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  // we are creating a shader called ClothSimShader
  shader->createShaderProgram("ObjectShader");
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader("ObjectVertex",ngl::VERTEX);
  shader->attachShader("ObjectFragment",ngl::FRAGMENT);
  // attach the source
  shader->loadShaderSource("ObjectVertex","shaders/ObjectVert.glsl");
  shader->loadShaderSource("ObjectFragment","shaders/ObjectFrag.glsl");
  // compile the shaders
  shader->compileShader("ObjectVertex");
  shader->compileShader("ObjectFragment");
  // add them to the program
  shader->attachShaderToProgram("ObjectShader","ObjectVertex");
  shader->attachShaderToProgram("ObjectShader","ObjectFragment");

  // now we have associated this data we can link the shader
  shader->linkProgramObject("ObjectShader");

  // we are creating a shader called ClothSimShader
  shader->createShaderProgram("ClothSimShader");
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader("ClothSimVertex",ngl::VERTEX);
  shader->attachShader("ClothSimFragment",ngl::FRAGMENT);
  // attach the source
  shader->loadShaderSource("ClothSimVertex","shaders/ClothSimVert.glsl");
  shader->loadShaderSource("ClothSimFragment","shaders/ClothSimFrag.glsl");
  // compile the shaders
  shader->compileShader("ClothSimVertex");
  shader->compileShader("ClothSimFragment");
  // add them to the program
  shader->attachShaderToProgram("ClothSimShader","ClothSimVertex");
  shader->attachShaderToProgram("ClothSimShader","ClothSimFragment");

  shader->bindAttribute("ClothSimShader", 0, "inVert");
  shader->bindAttribute("ClothSimShader", 1, "inNormal");

  // now we have associated this data we can link the shader
  shader->linkProgramObject("ClothSimShader");
  // and make it active ready to load values
  (*shader)["ClothSimShader"]->use();

  // SHADER END ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //SET Materials
  //m_clothMaterialColour; //ClothShader only does diffuse - color is changeable by user - will be set automatically

  m_objectMaterial.setAmbient(ngl::Colour(0.4, 0.4, 0.4, 1.0));
  m_objectMaterial.setDiffuse(ngl::Colour(1, 1, 0.8, 1.0));
  m_objectMaterial.setSpecular(ngl::Colour(0.5, 0.5, 0.5, 1.0)); // Let's do some specular here :)
  m_objectMaterial.setSpecularExponent(300);

  // light as the shader calculations are done in eye space
  // Light coming from the camera: I didn't bother setting up a position for the light: I use (0, 0, 0) when using the light position,
  // which is, in view coordinates, the position of the eye.
  m_light = new ngl::Light(ngl::Vec3(0, 0, 0),ngl::Colour(1,1,1,1),ngl::POINTLIGHT); //Specified in world coordinates

  (*shader)["ObjectShader"]->use();
  m_light->loadToShader("light");


  glViewport(0,0,width(),height());
  // Start in wireframe mode
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  startTimer(1); // ########################################################## timing!!!

  //INIT VAO for triangles
  std::vector<ngl::Vec3> points, normals;
  // first create the VAO
  m_vao = ngl::VertexArrayObject::createVOA(GL_TRIANGLES);
  // to use this it must be bound
  m_vao->bind();
  // now copy the data
  m_vao->setData(points.size()*sizeof(ngl::Vec3),points[0].m_x);
  // now we need to tell OpenGL the  size and layout of the data
  m_vao->setVertexAttributePointer(0,3,GL_FLOAT,0,0);

  // now copy the data
  m_vao->setData(normals.size()*sizeof(ngl::Vec3),normals[0].m_x);
  // now we need to tell OpenGL the  size and layout of the data
  m_vao->setVertexAttributePointer(1,3,GL_FLOAT,0,0);

  // now tell OpenGL how many elements we have
  m_vao->setNumIndices(points.size());
  // always best to unbind after use
  m_vao->unbind();

}


// load the matrices to the shader for drawing
void GLWindow::loadMatricesToClothShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  //switch to cloth shader
  (*shader)["ClothSimShader"]->use();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;


  // m_transform is never used for the cloth.

  MV= m_mouseGlobalTX*m_cam->getViewMatrix();
  MVP= MV * m_cam->getProjectionMatrix() ;

  normalMatrix = MV;
  normalMatrix.inverse();

  shader->setUniform("MV",MV);
  shader->setUniform("MVP",MVP);
  shader->setUniform("normalMatrix",normalMatrix);
  //rather than using light and material, these suffice for the cloth.
  shader->setUniform("lightIntensity", ngl::Colour(1, 1, 1, 1));
  shader->setUniform("diffuseColour", m_clothMaterialColour);
}

// load the matrices to the shader for drawing the objects
void GLWindow::loadMatricesToObjectShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  //switch to object shader
  (*shader)["ObjectShader"]->use();


  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;

  MV = m_transform.getMatrix() * m_mouseGlobalTX*m_cam->getViewMatrix();
  MVP= MV * m_cam->getProjectionMatrix();

  normalMatrix = MV;
  normalMatrix.inverse();

  shader->setUniform("MV",MV);
  shader->setUniform("MVP",MVP);
  shader->setUniform("normalMatrix",normalMatrix);
  shader->setRegisteredUniform("viewerPos",m_cam->getEye().toVec3());
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

  std::vector<ngl::Vec3> points, normals;

  // to use this it must be bound
  m_vao->bind();
  // now copy the data
  m_vao->setNumIndices(points.size());
  m_vao->updateData(0, points.size()*sizeof(ngl::Vec3),points[0].m_x);
  m_vao->updateData(1, normals.size()*sizeof(ngl::Vec3),normals[0].m_x);

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
  if(m_run)
  {
    updatePoints();
  }
  updateGL();
}



GLWindow::~GLWindow()
{
  ngl::NGLInit *init = ngl::NGLInit::instance();
  init->NGLQuit();
}

