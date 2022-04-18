//-------------------------------------------------------------------------------------------+
// フラグメントシェーダー
//-------------------------------------------------------------------------------------------+

// Request GLSL 3.3
#version 330

// This corresponds to the output color to the color buffer
out vec4 outColor;

void main()
{
	gl_Position = vec4(inPosition,1.0);
}