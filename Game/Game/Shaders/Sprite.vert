//-------------------------------------------------------------------------------------------+
// 頂点シェーダー
//-------------------------------------------------------------------------------------------+

// Request GLSL 3.3
#version 330

// Declaration of Uniforms variables
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// attribute
in vec3 inPosition;

void main()
{
	// Convert position to homogeneous coordinates
	vec4 pos = vec4(inPosition, 1.0);
	
	// Transform to position world space, then clip space
	gl_Position = pos * uWorldTransform * uViewProj;
}