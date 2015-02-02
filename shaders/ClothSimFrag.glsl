#version 330 core
#pragma optionNV(fastmath on)
#pragma optionNV(fastprecision on)
#pragma optionNV(ifcvt none)
#pragma optionNV(inline all)
#pragma optionNV(strict on)
#pragma optionNV(unroll all)

/// @brief[in] the vertex normal
in vec3 fragmentNormal;
// the light direction
in vec3 lightDir;
// our vertex position calculated in vert shader
in vec3 vPosition;

/// @brief our output fragment colour
layout (location =0) out vec4 fragColour;


// material colour
uniform vec4 diffuseColour;

//light intensity
uniform vec4 lightIntensity;


void main ()
{

  fragColour=vec4(0.0);
  vec3 N = normalize(fragmentNormal);
  vec3 L = normalize(lightDir);

  float attenuation;
  //Changed this to abs so both sides of the cloth are lit. /////////////////////////////////////////////////////////////////////////////////////
  float lambertTerm = abs(dot(N,L));
  vec4 diffuse=vec4(0);

  float d;            // distance from surface to light position
  vec3 VP;            // direction from surface to light position

  // Compute vector from surface to light position (assuming light position is at 0, 0, 0 in view coord.)
  VP = - vPosition;

  // Compute distance between surface and light position
  d = length (VP);

  diffuse+=diffuseColour*lightIntensity*lambertTerm;
  fragColour = diffuse;
}

