#pragma once

/*
マップを作成するクラス
*/
class MapCreate
{
public:
	// コンストラクタ
	MapCreate();
	// デストラクタ
	~MapCreate();

	/// <summary>
	/// jsonファイルをRapidJsonで読み込んでマップデータを各配列に格納する
	/// </summary>
	/// <returns>true : ファイルを開けた , false : ファイルが開けなかった</returns>
	bool OpenFile();

	// @@@
	// 床を生成する
	void CreateGround();

private:
	/// <summary>
	/// データの読み込み処理
	/// </summary>
	/// <param name="_mapData">データ</param>
	/// <param name="_fileName">ファイル名</param>
	/// <param name="_layerName">レイヤー名</param>
	/// <returns>true : 読み込み完了 , false : 読み込み失敗</returns>
	bool ReadTiledJson(vector<vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	/// <summary>
	/// 全てのlayerから該当layerの添え字を調べる
	/// </summary>
	/// <param name="_layer">layer全体</param>
	/// <param name="_layerName">該当レイヤー名</param>
	/// <returns>-1 : なかった</returns>
	int FindLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, string& _layerName);

	// @@@
	// マップデータ
	vector<vector<int>> mMapDate;

	// マップデータサイズ(x,y)
	Vector2 mMapSize;
	// オブジェクトごとの距離(x,y,z)
	Vector3 mObjDistance;

	// スケール
	const float MScale;
};

