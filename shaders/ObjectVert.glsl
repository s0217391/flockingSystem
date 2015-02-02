#version 330 core
/// @brief flag to indicate if model has unit normals if not normalize
uniform bool Normalize;

// the eye position of the camera
uniform vec3 viewerPos;

/// @brief the vertex passed in
layout (location =0)in vec3 inVert;
/// @brief the normal passed in
layout (location =2) in vec3 inNormal;
/// @brief the in uv
layout (location =1) in vec2 inUV;

struct Lights
{
	vec4 ambient;
	vec4 diffuse;
  vec4 specular;
};
// array of lights
uniform Lights light;


// model view matrix calculated in the App
uniform mat4 MV;
// model view projection calculated in the app
uniform mat4 MVP;
// normal matrix calculated in the app
uniform mat3 normalMatrix;


// direction of the lights used for shading
out vec3 lightDir;
// out the blinn half vector
out vec3 halfVector;


/// @brief the current fragment normal for the vert being processed
out vec3 fragmentNormal;



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

 // Transform the vertex to eye co-ordinates for frag shader
 /// @brief the vertex in eye co-ordinates  homogeneous
 vec4 eyeCord=MV*vec4(inVert,1);


 float dist;
 lightDir=vec3(-1 * eyeCord.xyz);
 dist = length(lightDir);
 lightDir/= dist;
 halfVector = normalize(lightDir);
}



