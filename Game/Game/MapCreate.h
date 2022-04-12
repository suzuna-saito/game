#pragma once

/*
�}�b�v���쐬����N���X
*/
class MapCreate
{
public:
	// �R���X�g���N�^
	MapCreate();
	// �f�X�g���N�^
	~MapCreate();

	/// <summary>
	/// json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
	/// </summary>
	/// <returns>true : �t�@�C�����J���� , false : �t�@�C�����J���Ȃ�����</returns>
	bool OpenFile();

	// @@@
	// ���𐶐�����
	void CreateGround();

private:
	/// <summary>
	/// �f�[�^�̓ǂݍ��ݏ���
	/// </summary>
	/// <param name="_mapData">�f�[�^</param>
	/// <param name="_fileName">�t�@�C����</param>
	/// <param name="_layerName">���C���[��</param>
	/// <returns>true : �ǂݍ��݊��� , false : �ǂݍ��ݎ��s</returns>
	bool ReadTiledJson(vector<vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	/// <summary>
	/// �S�Ă�layer����Y��layer�̓Y�����𒲂ׂ�
	/// </summary>
	/// <param name="_layer">layer�S��</param>
	/// <param name="_layerName">�Y�����C���[��</param>
	/// <returns>-1 : �Ȃ�����</returns>
	int FindLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, string& _layerName);

	// @@@
	// �}�b�v�f�[�^
	vector<vector<int>> mMapDate;

	// �}�b�v�f�[�^�T�C�Y(x,y)
	Vector2 mMapSize;
	// �I�u�W�F�N�g���Ƃ̋���(x,y,z)
	Vector3 mObjDistance;

	// �X�P�[��
	const float MScale;
};

