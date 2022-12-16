//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : 
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	PARTICLE_BUFFER		(10)		// パーティクル最大数
#define	MAX_PARTICLE		(200)		// パーティクル最大個数

enum
{  //テクスチャーの種類
	EFFECT_BOM,
	EFFECT_KEMURI,
	EFFECT_KEMURI2,
	EFFECT_LIGHT,
	EFFECT_REFLECTION,
	EFFECT_MAX,
};

enum
{  //テクスチャーの種類
	MOVE_PATTERN_UP,
	MOVE_PATTERN_UP_SMALL,
	MOVE_PATTERN_UPLEFT,
	MOVE_PATTERN_MAX,
};


//*****************************************************************************
// 構造体定義
//*****************************************************************************
class SPRITE_ANIMATION
{
private:
	int			m_patternAnim;	// アニメーションパターンナンバー
	int		    m_uwnum;		// テクスチャの表示する部分の幅
	float		m_countAnim;	// アニメーションカウント
	float		m_tw;			// 表示するテクスチャの幅
	float		m_th;			// 表示するテクスチャの高さ
	float		m_tx;			// 表示するテクスチャの位置
	float		m_ty;			// 表示するテクスチャの位置
	BOOL		m_use;			// 使用しているかどうか

public:

	SPRITE_ANIMATION() {
	
		m_patternAnim = 0;
		m_uwnum = 0;
		m_countAnim = 0.0f;
		m_tw = 0.0f;
		m_th = 0.0f;
		m_tx = 0.0f;
		m_ty = 0.0f;
		m_use = FALSE;
	};

	~SPRITE_ANIMATION() {};

	void Init() {
		m_patternAnim = 0;
		m_uwnum = 0;
		m_countAnim = 0.0f;
		m_tw = 0.0f;
		m_th = 0.0f;
		m_tx = 0.0f;
		m_ty = 0.0f;
		m_use = FALSE;
	}

	void Update(int time);   
	XMFLOAT2 GetTexPos(void) { return XMFLOAT2{ m_tx,m_ty }; }   // テクスチャー座標の取得
	XMFLOAT2 GetTexWidth(void) { return XMFLOAT2{ m_tw,m_th }; }   // テクスチャー座標の取得
	void SetUse(BOOL flag) {  m_use = flag; };  
	BOOL GetUse(void) { return m_use; }
};

class PARTICLE
{
private:
	XMFLOAT3		m_posBase;		// 発生位置
	XMFLOAT3		m_pos;			// 位置
	XMFLOAT3		m_rot;			// 回転
	XMFLOAT3		m_scale;		// スケール
	XMFLOAT3		m_move;			// 移動量
	MATERIAL		m_material;		// マテリアル
	float			m_fSizeX;		// 幅
	float			m_fSizeY;		// 高さ
	int				m_nLife;		// 寿命
	BOOL			m_bUse;			// 使用しているかどうか
	BOOL			m_bSwich;		// ON,OFF
	int			    m_nTexno;		// テクスチャーナンバー
	int			    m_Pattern;		// パターンナンバー
	int				m_nextAnime;	// 次のアニメーションに行くまでの時間

public:

	SPRITE_ANIMATION SpriteAnim;

	PARTICLE();
	~PARTICLE() {};

	void AddPos(XMFLOAT3 move) { 
		m_pos.x += move.x;
		m_pos.y += move.y;
		m_pos.z += move.z;
	};


	XMFLOAT3 GetPos(void)  { return m_pos; };		    // パーティクルの座標の取得
	XMFLOAT3 GetMove(void) { return m_move; };		    // パーティクルの移動量の取得
	BOOL	 GetUse(void)  { return m_bUse; };		    // パーティクルの使用情報の取得
	BOOL	 GetSwich(void) { return m_bSwich; };		// パーティクルバッファのON OFF
	int		 GetAnimeTime(void) { return m_nextAnime; }
	void	 SetPosBase(XMFLOAT3 pos) { m_posBase = pos; };
	void	 SetPos(XMFLOAT3 pos)	  { m_pos = pos; };
	void	 SetSize(float size)      { m_fSizeX = size; m_fSizeY = size;};
	void	 SetUse(BOOL flag)        { m_bUse = flag; };
	void	 SetSwich(BOOL flag)      { m_bSwich = flag; };
	void	 SetTexno(int no)         { m_nTexno = no; };
	void	 SetPattern(int pattern)         { m_Pattern = pattern; };
	void	 SetParticle(/*XMFLOAT3 pos,*/ XMFLOAT3 move, XMFLOAT4 col, float fSizeX, float fSizeY, int nLife);
	void	 SetAnimeTime(int time)   { m_nextAnime = time; };

	void Update(void);       // 更新処理
	void Draw(void);         // 描画処理

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

void CallParticle(XMFLOAT3 pos, float size, int num, int texID, int pattern);

