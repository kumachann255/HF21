//=============================================================================
//
// タイトル画面処理 [Title.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UI.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_MAX					(23)				// テクスチャの数

enum
{
	CHOICE = 0,
	GAME_START = 1,
	EXIT = 2,
};


// これがタイトルマネージャの役割。関数で命令を出す。関数の引数を柔軟にポインタで切り替え
class Title : public Scene
{
private:
	bool m_DebugSwich = true;	// デバッグモード切り替え用SW
	int m_DebugNum = 0;			// デバッグ用変数
	int m_modeSw = CHOICE;		// titleMode切り替え用

public:
	Title(God * god);
	~Title();
	void Init();
	void Update();
	void Draw();
	void NextScene();

	/* 背景部品群操作関数 */


	// モード切り替え関数
	/* 列挙子をセット */
	int SetMode(int mode);

	// 画像非表示用関数
	/* 引数はBOOL型 */
	void SetBOOL(BOOL *use);

	// シーン遷移先を選ぶ関数
	/* 第一引数ExitPosX、第二引数GameStartPosX、第三引数ChoicePosX */
	void Choice(float *posExitx, float *posGameX, float *posChoiceX);

	// 第一引数のアドレスの回転角に任意の回転量をセットする関数
	/* 第一引数回転対象アドレス、第二引数回転量 */
	void Rot(float *RotZ, float valueRot);

	// 第一引数のアドレスの回転角に任意の回転量をセットし、徐々に加速させる関数
	/* 第一引数回転対象アドレス、第二引数回転量 */
	void RotAccel(float *RotZ, float valueRot);

	// オブジェクト上下関数
	/* 第一引数対象bool、第二引数対象アドレスYPos、第三引数移動量 */
	void UpDown(bool *udFlug, float *posY, float addY);

	// オブジェクトトランジション関数
	/* 第一引数対象アドレスXPos、第二引数移動量、第三引数時間減算用変数 */
	void Transition(float *posX, float moveValue, float timeSub);

	// 任意の方角へ一定の時間を満たしたら回転しながら射出する関数
	// 第一引数のアドレスの回転角に任意の回転量をセットする関数
	void RotRocket(float *posX, float *posY, float addX, float addY, float *RotZ, float valueRot, int time);

	// バイブレーション関数（引数の値が小さいほど高速にバイブレーション）
	/* 第一引数バイブレーション頻度の整数、第二引数回転対象のアドレス */
	void Swaying(int i, float *RotZ);



	/* デバッグ機構 */



	// デバッグ対象切り替え
	int ChangeNum(int *Num);

	// デバッグ内容表示
	void DebugPrint(float posX, float posY, float w, float h);

	// 対象位置の変更
	void PosCustom(float *posX, float *posY);

	// 対象サイズの変更
	void SizeCustom(float *width, float *height);
};

// こいつらが操作対象の部品に当たる
struct s_Title
{
	bool		g_UD_Change;// UpDown用関数スイッチ
	BOOL		g_Use;		// TRUE:使っている  FALSE:未使用
	XMFLOAT3	g_Pos;		// ポリゴンの座標
	XMFLOAT3	g_Rot;		// ポリゴンの回転
	float		g_w, g_h;	// 幅と高さ
	int			g_TexNo;	// テクスチャ番号
};

// こいつらが操作対象の部品に当たる
struct s_OpenEgg
{
	BOOL		g_Use;		// TRUE:使っている  FALSE:未使用
	XMFLOAT3	g_Pos;		// ポリゴンの座標
	XMFLOAT3	g_Rot;		// ポリゴンの回転
	float		g_w, g_h;	// 幅と高さ
	int			g_TexNo;	// テクスチャ番号
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

