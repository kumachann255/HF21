//=============================================================================
//
// サウンド処理 [sound.cpp]
//
//=============================================================================
#include "sound.h"

//*****************************************************************************
// パラメータ構造体定義
//*****************************************************************************
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDPARAM;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイス
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

// 各音素材のパラメータ
SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{ (char*)"data/BGM/sample000.wav", -1 },	// BGM0
	{ (char*)"data/BGM/bgm_maoudamashii_neorock73.wav", -1 },	// BGM1
	{ (char*)"data/BGM/sample001.wav", -1 },	// BGM2
	{ (char*)"data/SE/bomb000.wav", 0 },		// 弾発射音
	{ (char*)"data/SE/defend000.wav", 0 },		// 弾発射音
	{ (char*)"data/SE/defend001.wav", 0 },		// 弾発射音
	{ (char*)"data/SE/hit000.wav", 0 },			// 弾発射音
	{ (char*)"data/SE/laser000.wav", 0 },		// 弾発射音
	{ (char*)"data/SE/lockon000.wav", 0 },		// 弾発射音
	{ (char*)"data/SE/shot000.wav", 0 },		// 弾発射音
	{ (char*)"data/SE/shot001.wav", 0 },		// ヒット音

	{ (char*)"data/BGM/BGM_title.wav", -1 },	// タイトル
	{ (char*)"data/SE/se_title_start.wav", 0 },	// タイトルゲームスタート音
	{ (char*)"data/SE/se_title_quit.wav", 0 },	// タイトルゲーム終了音
	{ (char*)"data/SE/se_title_rot.wav", 0 },	// タイトルゲーム終了音


	{ (char*)"data/BGM/BGM_tutorial.wav", -1 },	// チュートリアル
	{ (char*)"data/BGM/BGM_stage01.wav", -1 },	// ステージ01

	{ (char*)"data/SE/se_modeSelect_trance.wav", 0 },	// モードセレクト時のカーソル移動
	{ (char*)"data/SE/se_modeSelect_enter.wav", 0 },	// モードセレクト時の決定
	{ (char*)"data/SE/se_tutorial_telop.wav", 0 },		// チュートリアルのテロップ音

	{ (char*)"data/SE/se_slot_button_01.wav", 0 },	// スロットを止める
	{ (char*)"data/SE/se_drumStart1.wav", 0 },		// スロットを動かす
	{ (char*)"data/SE/se_drumStart0.wav", 0 },		// スロットを動かす
	{ (char*)"data/SE/se_crow_cry_01.wav", 0 },		// カラースの鳴き声
	{ (char*)"data/SE/se_crow_flap_04.wav", 0 },	// カラース発射
	{ (char*)"data/SE/se_gomiPop_0.wav", 0 },		// クエスト出現
	{ (char*)"data/SE/se_gomiPop_1.wav", 0 },		// クエスト出現
	{ (char*)"data/SE/se_lamp_clear.wav", 0 },		// クエスト達成
	{ (char*)"data/SE/se_quest_clear.wav", 0 },		// クエスト達成
	{ (char*)"data/SE/se_map_change.wav", 0 },		// マップ変化

	{ (char*)"data/SE/se_bom0.wav", 0 },			// 爆破
	{ (char*)"data/SE/se_bom1.wav", 0 },			// 爆破
	{ (char*)"data/SE/se_bom2.wav", 0 },			// 爆破
	{ (char*)"data/SE/se_bom4.wav", 0 },			// 爆破

	{ (char*)"data/SE/se_countDown.wav", 0 },		// カウントダウン
	{ (char*)"data/SE/se_timer.wav", 0 },			// カチカチ音
	{ (char*)"data/SE/se_timer_speedup.wav", 0 },	// カチカチ音

	{ (char*)"data/SE/se_crow_25s.wav", 0 },		// カラスの鳴き声
	{ (char*)"data/SE/se_crow_x1.wav", 0 },			// カラスの鳴き声
	{ (char*)"data/SE/se_crow_x3.wav", 0 },			// カラスの鳴き声

	{ (char*)"data/SE/se_mens_hihi.wav", 0 },		// 男性の声
	{ (char*)"data/SE/se_mens_ou.wav", 0 },			// 男性の声
	{ (char*)"data/SE/se_mens_yei.wav", 0 },		// 男性の声
	{ (char*)"data/SE/se_women_ou.wav", 0 },		// 女性の声
	{ (char*)"data/SE/se_women_kya.wav", 0 },		// 女性の声

	{ (char*)"data/SE/se_slot_stop.wav", 0 },		// スロットの止める音
	{ (char*)"data/SE/se_bonusStop.wav", 0 },		// スロットの止める音

	{ (char*)"data/SE/se_chance.wav", 0 },			// チャンス音
	{ (char*)"data/SE/se_pkieeen.wav", 0 },			// ぴきーーん！
	{ (char*)"data/SE/se_Roulette_high.wav", 0 },	// ちゃーーーじ！
	{ (char*)"data/SE/se_hit.wav", 0 },				// 当たり音

	{ (char*)"data/SE/se_spotlight.wav", 0 },		// スポットライト
	{ (char*)"data/SE/se_syakin.wav", 0 },			// シャキーン！
	{ (char*)"data/SE/se_zyan.wav", 0 },			// ジャン！
	{ (char*)"data/SE/se_shock.wav", 0 },			// ガーン！
	{ (char*)"data/SE/se_doom.wav", 0 },			// ドーン！
	{ (char*)"data/SE/se_gong.wav", 0 },			// カン！！

	{ (char*)"data/SE/se_training_false.wav", 0 },	// 筋トレ失敗
	{ (char*)"data/SE/se_training_hart.wav", -1 },	// 筋トレドキドキ
	{ (char*)"data/SE/se_transition.wav", 0 },		// ブオン
	{ (char*)"data/SE/se_wing_x1.wav", 0 },			// 羽ばたき1回
	{ (char*)"data/SE/se_wing_x6.wav", 0 },			// 羽ばたき6回
													
	{ (char*)"data/SE/se_title_bu.wav", 0 },		// 開幕ブザー
};

//=============================================================================
// 初期化処理
//=============================================================================
BOOL InitSound(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return FALSE;
	}
	
	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return FALSE;
	}

	// サウンドデータの初期化
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return FALSE;
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return FALSE;
		}
	
		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return FALSE;
		}
	
		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return FALSE;
		}
	
		// ソースボイスの生成
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aParam[nCntSound].nCntLoop;

		// オーディオバッファの登録
		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	// 各音源の音量調節
	SetSourceVolume(SOUND_LABEL_SE_se_slot_button_01, 0.5f);
	SetSourceVolume(SOUND_LABEL_SE_se_slot_stop, 0.5f);

	SetSourceVolume(SOUND_LABEL_BGM_tutorial, 0.5f);
	SetSourceVolume(SOUND_LABEL_BGM_stage01, 0.5f);

	return TRUE;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSound(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// セグメント再生(再生中なら停止)
//=============================================================================
void PlaySound(int label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aParam[label].nCntLoop;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice[label]->Start(0);

}

//=============================================================================
// セグメント停止(ラベル指定)
//=============================================================================
void StopSound(int label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止(全て)
//=============================================================================
void StopSound(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

// ソースボイスの音量調整(0.0f ~ 1.0fで調整)
void SetSourceVolume(int label, float volume)
{
	g_apSourceVoice[label]->SetVolume(volume);
	return;
}
