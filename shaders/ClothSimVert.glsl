#version 330 core
#pragma optionNV(fastmath on)
#pragma optionNV(fastprecision on)
#pragma optionNV(ifcvt none)
#pragma optionNV(inline all)
#pragma optionNV(strict on)
#pragma optionNV(unroll all)
/// @brief flag to indicate if model has unit normals if not normalize
uniform bool Normalize;


/// @brief the vertex passed in
layout(location =0) in vec3 inVert;
/// @brief the normal passed in
layout(location =1) in vec3 inNormal;

// material colour
uniform vec4 diffuseColour;

uniform vec4 lightIntensity;

// direction of the lights used for shading
out vec3 lightDir;
// vertex position
out vec3 vPosition;
/// @brief the current fragment normal for the vert being processed
out vec3 fragmentNormal;

// model view matrix calculated in the App
uniform mat4 MV;
// model view projection calculated in the app
uniform mat4 MVP;
// normal matrix calculated in the app
uniform mat3 normalMatrix;

void main()
{
 // calculate the fragments surface normal
 fragmentNormal = (normalMatrix*inNormal);


 if (Normalize == true)
 {
  fragmentNormal = normalize(fragmentNormal);
 }
 // calculate the vertex position
 gl_Position = MVP*vec4(inVert,1.0);

 // Get vertex position in eye coordinates
 // Transform the vertex to eye co-ordinates for frag shader
 /// @brief the vertex in eye co-ordinates  homogeneous
 vec4 eyeCord=MV*vec4(inVert,1);

 vPosition = eyeCord.xyz / eyeCord.w;;

 float dist;
 lightDir=vec3(-1 * eyeCord.xyz); //light position is assumed to be in view coordinates, and at the eye position.
 dist = length(lightDir);
 lightDir /= dist;
}







