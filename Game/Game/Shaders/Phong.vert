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
out vec2 fragTexCoord;          // �e�N�X�`�����W
out vec3 fragNormal;            // ���[���h�X�y�[�X��̖@��
out vec3 fragWorldPos;          // ���[���h�X�y�[�X��̍��W

void main()
{
    // vec4�^�ɒ��_���W��ϊ�
    vec4 pos = vec4(inPosition,1.0);
    // ���_�������[���h�X�y�[�X�ɕϊ�
    pos = pos * uWorldTransform;
    // �t���O�����g�o�͂ɃZ�b�g
    fragWorldPos = pos.xyz;
    // �N���b�v��ԂɃ��[���h��̒��_���W��ϊ�
    gl_Position = pos * uViewProj;

    // �@���������[���h�X�y�[�X�ɕϊ��iw = 0�j
    fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

    // �e�N�X�`�����W���t���O�����g�V�F�[�_�֏o��
    fragTexCoord = inTexCoord;
    
}