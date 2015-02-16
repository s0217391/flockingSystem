/*
 *
 * GL Window widget, Heavily borrowing from Jon macey's demos.
 *
 * responsible for drawing the cloth and the environment objects.
 *
 * It uses two different shaders: a very simple diffuse for the cloth and one for the objects that is a bit more complicated.
 *
 */
#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_

#include "ngl/Camera.h"
#include "ngl/Colour.h"
#include "ngl/Light.h"
#include "ngl/Material.h"
#include "ngl/Text.h"
#include "ngl/Transformation.h"
#include "ngl/Vec3.h"
#include "ngl/VertexArrayObject.h"
#include "QEvent"
#include "QGLWidget"
#include "QResizeEvent"

#include "EcoSystem.h"

class GLWindow : public QGLWidget
{

public :
  // Constructor. takes a pointer to the simulation control to get the updates about the cloth
  GLWindow(const QGLFormat _format,QWidget *_parent);
  ~GLWindow();

  // play or pause the sim
  inline void setRunSim(bool _value) {m_run = _value;}



protected:

  //----------------------------------------------------------------------------------------------------------------------
  /// this is called when the window is created
  //----------------------------------------------------------------------------------------------------------------------
  void initializeGL();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is the main gl drawing routine which is called whenever the window needs to
  /// be re-drawn
  //----------------------------------------------------------------------------------------------------------------------
  void paintGL();




private :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseMoveEvent ( QMouseEvent * _event );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------

  void mousePressEvent ( QMouseEvent *_event );

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseReleaseEvent (QMouseEvent *_event);

  void wheelEvent(QWheelEvent *_event);
  void timerEvent(QTimerEvent *_event);

  // Function to update the points (and normals) of the cloth
  void updatePoints();


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to load the matrix values to the shader
  //----------------------------------------------------------------------------------------------------------------------
  void loadMatricesToClothShader();  // for the cloth shader
  void loadMatricesToObjectShader(); // for the object shader


  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the x rotation mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_spinXFace;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the y rotation mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_spinYFace;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the mouse button is pressed when dragging
  //----------------------------------------------------------------------------------------------------------------------
  bool m_rotate;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the Right mouse button is pressed when dragging
  //----------------------------------------------------------------------------------------------------------------------
  bool m_translate;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous x mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_origX;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous y mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_origY;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous x mouse value for Position changes
  //----------------------------------------------------------------------------------------------------------------------
  int m_origXPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous y mouse value for Position changes
  //----------------------------------------------------------------------------------------------------------------------
  int m_origYPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the global mouse transforms
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 m_mouseGlobalTX;
  //-----------------------------------------------
  /// @brief the model position for mouse movement
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_modelPos;

  // Camera and Light
  ngl::Camera * m_cam;
  ngl::Light * m_light; // Used for the object shader, not the cloth one.

  // Materials for the cloth and the objects
  ngl::Vec4 m_clothMaterialColour; // Just diffuse is enough for the cloth
  ngl::Material m_objectMaterial; // Used a material for the objects

  //a transform for drawing the sphere in the right place!
  ngl::Transformation m_transform;

  /// @brief VP matrix combination of view and project
  /// this is set once as static camera.
  ngl::Mat4 m_vp;
  /// @brief a vertex array object to contain the points
  ngl::VertexArrayObject *m_vao;

  // determines whether the opengl window is in
  bool m_run;

  // drawing mode bools
  bool m_drawClothWireframe, m_drawObjects, m_drawObjectsWireframe;


  // zoom and rotate variables
  const float c_increment;
  const float c_zoom;



  EcoSystem m_flocker;
  std::vector<ngl::Vec3> m_positions;
  std::vector<ngl::Vec3> m_velocities;
  int m_agentNumber;
};

#endif
