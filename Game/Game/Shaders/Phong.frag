// Request GLSL 3.3
#version 330

// ���_�V�F�[�_�[����̓���
// �t���O�����g�ւ̏o��
in vec2 fragTexCoord;   // �e�N�X�`�����W
in vec3 fragNormal;     // ���[���h�X�y�[�X��̖@��
in vec3 fragWorldPos;   // ���[���h�X�y�[�X��̍��W

// Uniform�w��q
uniform sampler2D uMeshTexture;  // �e�N�X�`���T���v�����O
// ���C�e�B���O�p�ϐ�
uniform vec3 uCameraPos;         // �J�����ʒu�i���[���h��ԁj
uniform float uSpecPower;        // �|���S���\�ʂ̃X�y�L�����[���x
uniform vec3 uAmbientLight;      // �A���r�G���g���C�g�F

// �o�̓J���[�i�o�̓s�N�Z���J���[�j
out Vec4 outColor;

// �e�N�X�`���T���v�����O�p�\����
struct DirectionelLight
{
    vec3 mDirection;     // ���C�g����
    vec3 mDiffuseColor;  // �f�B�t���[�Y�F
    vec3 mSpecColor;     // �X�y�L�����[�F
}