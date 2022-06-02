//-------------------------------------------------------------------------------------------+
// �X�v���C�g(2D)�p���_�V�F�[�_
//-------------------------------------------------------------------------------------------+

// Request GLSL 3.3
#version 330

// �A�g���r���[�g (�o�b�t�@��AttribPointer�Ŏw�肵���f�[�^)
layout(location = 0) in vec3 inPosition;  // ���_���W
layout(location = 1) in vec3 inNormal;    // �@��
layout(location = 2) in vec2 inTexCoord;  // �e�N�X�`�����W(UV)

// Uniform�w��q
uniform mat4 uWorldTransform;   // ���[���h�ϊ��s��
uniform mat4 uViewProj;         // �r���[ * �v���W�F�N�V�����̍����s��

// �t���O�����g�V�F�[�_�ւ̏o��
out vec2 fragTexCoord;

void main()
{
	// ���_���W��gl_Position�p��vec4�^�֕ϊ�
	vec4 pos = vec4(inPosition, 1.0);
	// �N���b�v��ԂɃ��[���h���W��ϊ�
	gl_Position = pos * uWorldTransform * uViewProj;

	// �e�N�X�`�����W���t���O�����g�֏o��
	fragTexCoord = inTexCoord;
}