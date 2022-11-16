//=============================================================================
//
// タイトル画面処理 [Title.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "sprite.h"
#include "Title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(SCREEN_WIDTH)	// 背景サイズ
#define TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 

#define TEXTURE_WIDTH_LOGO			(480)			// ロゴサイズ
#define TEXTURE_HEIGHT_LOGO			(80)			// 

enum
{
	TITLE_TEX_BG,
	TITLE_TEX_MAX
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static char *g_TexturName[TEX_MAX] = {
	"data/TEXTURE/bg000.jpg",
	"data/TEXTURE/title_logo.png",
	"data/TEXTURE/effect000.jpg",
};


//=============================================================================
// コンストラクター
//=============================================================================
TitleUI::TitleUI()
{

	m_UIObject[TITLE_TEX_BG] = new UIObject;
	m_UIObject[TITLE_TEX_BG]->GetUITexData()->SetTextureName(g_TexturName[TITLE_TEX_BG]);
	m_UIObject[TITLE_TEX_BG]->GetUITexData()->Create();

	XMFLOAT3 pos = { TEXTURE_WIDTH / 2,TEXTURE_HEIGHT / 2,0.0f };
	m_UIObject[TITLE_TEX_BG]->SetPos(pos);
	m_UIObject[TITLE_TEX_BG]->SetWidth(TEXTURE_WIDTH);
	m_UIObject[TITLE_TEX_BG]->SetHeight(TEXTURE_HEIGHT);

}

//=============================================================================
// デストラクター
//=============================================================================
TitleUI::~TitleUI()
{
	delete m_UIObject[0];
}


//*****************************************************************************
//*****************************************************************************




//=============================================================================
// コンストラクター ※シーンのコンストラクターに渡してあげる
//=============================================================================
Title::Title(God *god) : Scene(god)
{
	m_TitleUI = new TitleUI;
}

//=============================================================================
// デストラクター
//=============================================================================
Title::~Title()
{
	delete m_TitleUI;
}

//=============================================================================
// 初期化処理
//=============================================================================
void Title::Init(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void Title::Update(void)
{

	// シーン切り替えチェック
	NextScene();
}

//=============================================================================
// 描画処理
//=============================================================================
void Title::Draw(void)
{
	// ビューポートの切り換え
	SetViewPort(TYPE_FULL_SCREEN);

	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, 
		m_TitleUI->GetUIObject()->GetUITexData()->GetpVertexBuffer(),
		&stride, &offset);

	// マトリクス設定
	SetWorldViewProjection2D();

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// タイトルの背景を描画
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1,
			m_TitleUI->GetUIObject()->GetUITexData()->GetTexture()
		);

		SetSprite(m_TitleUI->GetUIObject()->GetUITexData()->GetVertexBuffer(),
			m_TitleUI->GetUIObject()->GetPos().x,
			m_TitleUI->GetUIObject()->GetPos().y,
			m_TitleUI->GetUIObject()->GetWidth(),
			m_TitleUI->GetUIObject()->GetHeight(),
			0.0f, 0.0f, 1.0f, 1.0f);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		//SetSpriteColorRotation(m_UITexData->GetVertexBuffer(),
		//	GetPos().x, GetPos().y, GetWidth(), GetHeight(),
		//	0.0f, 0.0f, 1.0f, 1.0f,
		//	GetColor(), GetRot());

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}

//=============================================================================
// シーン遷移処理
//=============================================================================
void Title::NextScene(void)
{
	// フェードアウトを開始させる
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT);
	}

	// フェードアウトが終わったらシーンを切り替える
	if (GetFadeOut_EndFlag())
	{
		GetGod()->ChangeScene(STAGE_01ID);

	}

}
