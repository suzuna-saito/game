// Request GLSL 3.3
#version 330

// �e�N�X�`���T���v�����O�p�\����
struct DirectionelLight
{
    vec3 mDirection;     // ���C�g����
    vec3 mDiffuseColor;  // �f�B�t���[�Y�F
    vec3 mSpecColor;     // �X�y�L�����[�F
}

// ���_�V�F�[�_�[����̓���
// �t���O�����g�ւ̏o��
in vec2 fragTexCoord;   // �e�N�X�`�����W
in vec3 fragNormal;     // ���[���h�X�y�[�X��̖@��
in vec3 fragWorldPos;   // ���[���h�X�y�[�X��̍��W

// Uniform�w��q
uniform sampler2D uMeshTexture;      // �e�N�X�`���T���v�����O
// ���C�e�B���O�p�ϐ�
uniform vec3 uCameraPos;             // �J�����ʒu�i���[���h��ԁj
uniform float uSpecPower;            // �|���S���\�ʂ̃X�y�L�����[���x
uniform vec3 uAmbientLight;          // �A���r�G���g���C�g�F

uniform DirectionalLight uDirLight;  // �f�B���N�V���i�����C�g

// �o�̓J���[�i�o�̓s�N�Z���J���[�j
out Vec4 outColor;

void main()
{
    // �@���ƃx�N�g��
    vec3 N = normalize(fragNormal);                 // �|���S���\�ʂ̖@���i�t���O�����g�V�F�[�_�[��ŕ�Ԃ���Ă���j
    vec3 L = normalize(-uDirLight.mDirection);      // �|���S���\�ʂ��烉�C�g�����ւ̃x�N�g��
    vec3 V = normalize(uCameraPos - fragWorldPos);  // �|���S���\�ʂ���J���������ւ̃x�N�g��
    vec3 R = normalize(reflect(-L,N));              // -L �x�N�g����@�� N �ɑ΂��Ĕ��˃x�N�g��R�����߂�

    // �t�H�����ˌv�Z
    vec3 Phong = uAmbientLight;
    float NdotL = dot(N,L);      // dot = ����
    
    vec3 Diffuse = uDirLight.mDiffuseColor * max(NdotL,0.0f);
    vec3 Specular = uDirLight.mSpecColor * pow(max(0.0,dot(R,V)),uSpecPower);
    phong += Diffuse + Specular;

    // �ŏI�J���[���o�́ialpha = 1�j
    outColor = texture(uMeshTexture,fragTexCoord) * vec4(Phong,1.0f);
}