//-------------------------------------------------------------------------------------------+
// �X�v���C�g(2D)�p�t���O�����g�V�F�[�_
//-------------------------------------------------------------------------------------------+

// Request GLSL 3.3
#version 330

// ���_�V�F�[�_�[����̓���
in vec2 FragTexCoords;       // �e�N�X�`�����W

// �J���[�o�b�t�@�ւ̏o��
out vec4 outColor;

// uniform
uniform sampler2D uTexture;  // �e�N�X�`���T���v�����O

void main()
{
	// �e�N�X�`������J���[���T���v�����O
	outColor = texture(uTexture,FragTexCoords);
}