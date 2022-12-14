//=============================================================================
//
// ランプ管理 [Lamp.cpp]
// Author : 柏村大地
//
//=============================================================================
#include"Lamp.h"
#include "Roller.h"
#include "particle.h"
#include "sound.h"
#include "ParticleManager.h"
#include "Stage_01.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	LAMP_ROTATE_SPEED	(0.006f)	// 回転速度
#define	LAMP_SCL			(1.0f)		// 大きさ

#define LAMP_LIFE			(90)

//=============================================================================
// コンストラクター
//=============================================================================
Lamp::Lamp()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_lamp_red.obj");
	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { LAMP_SCL, LAMP_SCL, LAMP_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

}

//=============================================================================
// デストラクター
//=============================================================================
Lamp::~Lamp()
{
	if (m_prefab) {
		delete m_prefab; 
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void Lamp::Update(void)
{
	if (!this->GetIsUse()) return;

	static XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	rot.x += LAMP_ROTATE_SPEED;
	rot.y += LAMP_ROTATE_SPEED;
	rot.z += 0.00f;
	m_prefab->SetRot(rot);

	if (rot.x >= XM_2PI) {
		rot.x = 0.0f;
		rot.y = 0.0f;
		rot.z = 0.0f;
	}

	if (m_clear)
	{
		m_count++;
		if (m_count > LAMP_LIFE)
		{
			this->SetIsUse(FALSE);

			XMFLOAT3 pos = GetPos();
			GetParticlManager()->CallParticle(pos, 3.0f, 120, EFFECT_REFLECTION, MOVE_PATTERN_UP_SMALL,4);
			PlaySound(SOUND_LABEL_SE_se_lamp_clear);
		}
	}

}


//=============================================================================
// 描画処理
//=============================================================================
void Lamp::Draw(XMMATRIX WorldMatrix)
{

	// ワールドマトリクス生成
	XMMATRIX mtxWorld = GetWorldMatrix(m_prefab->GetPos(), m_prefab->GetRot(), m_prefab->GetScl());


	// プレハブ(ローカル座標)にワールドマトリクスをかける
	mtxWorld = XMMatrixMultiply(mtxWorld, WorldMatrix);

	// 座標を取り出す
	XMFLOAT3 pos = { mtxWorld.r[3].m128_f32[0],
					 mtxWorld.r[3].m128_f32[1],
					 mtxWorld.r[3].m128_f32[2] };

	SetPos(pos);

	if (!this->GetIsUse()) return;

	SetCullingMode(CULL_MODE_BACK);

	SetDepthEnable(TRUE);

	SetBlendState(BLEND_MODE_NONE);

	SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

	DrawModel(m_prefab->GetModel());

	SetBlendState(BLEND_MODE_ALPHABLEND);

}
