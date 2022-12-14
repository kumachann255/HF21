//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "debugproc.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM			(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM			(150.0f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM			(-500.0f)		// カメラの初期位置(Z座標)

#define	FULL_POS_Y_CAM		(7.0f)			// カメラの初期位置(Y座標)
#define	FULL_POS_Z_CAM		(-130.0f)		// カメラの初期位置(Z座標)

#define	SLOT_POS_Y_CAM		(2.0f)			// カメラの初期位置(Y座標)
#define	SLOT_POS_Z_CAM		(-25.0f)		// カメラの初期位置(Z座標)

#define	IVENT_POS_X_CAM		(20.0f)			// カメラの初期位置(X座標)
#define	IVENT_POS_Y_CAM		(30.0f)			// カメラの初期位置(Y座標)
#define	IVENT_POS_Z_CAM		(-100.0f)		// カメラの初期位置(Z座標)


#define	VIEW_ANGLE		(XMConvertToRadians(45.0f))						// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_ASPECT_HARF ((float)L_SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_ASPECT_IVENT ((float)RU_SCREEN_WIDTH / (float)RU_SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_ASPECT_SLOT ((float)RD_SCREEN_WIDTH / (float)RD_SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(2.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(XM_PI * 0.01f)								// カメラの回転量
#define	VALUE_ROTATE_CAMERA_EVENT	(XM_PI * 0.0011f)								// カメラの回転量

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAMERA			g_Camera;		// カメラデータ
static CAMERA			g_CameraEvent;	// イベント時のカメラデータ

static int				g_ViewPortType = TYPE_FULL_SCREEN;

//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = { POS_X_CAM, POS_Y_CAM, POS_Z_CAM };
	g_Camera.at  = { 0.0f, 0.0f, 0.0f };
	g_Camera.up  = { 0.0f, 1.0f, 0.0f };
	g_Camera.rot = { 0.0f, 0.0f, 0.0f };

	g_CameraEvent.pos = { POS_X_CAM, POS_Y_CAM, POS_Z_CAM };
	g_CameraEvent.at = { 0.0f, 0.0f, 0.0f };
	g_CameraEvent.up = { 0.0f, 1.0f, 0.0f };
	g_CameraEvent.rot = { 0.0f, 0.0f, 0.0f };

	// 視点と注視点の距離を計算
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);
	
	// ビューポートタイプの初期化
	g_ViewPortType = TYPE_FULL_SCREEN;
}


//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{

#ifdef _DEBUG

	if (GetKeyboardPress(DIK_Z))
	{// 視点旋回「左」
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > XM_PI)
		{
			g_Camera.rot.y -= XM_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_C))
	{// 視点旋回「右」
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -XM_PI)
		{
			g_Camera.rot.y += XM_PI * 2.0f;
		}

		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_Y))
	{// 視点移動「上」
		g_Camera.pos.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_N))
	{// 視点移動「下」
		g_Camera.pos.y -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_Q))
	{// 注視点旋回「左」
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -XM_PI)
		{
			g_Camera.rot.y += XM_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_E))
	{// 注視点旋回「右」
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > XM_PI)
		{
			g_Camera.rot.y -= XM_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_T))
	{// 注視点移動「上」
		g_Camera.at.y += VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_B))
	{// 注視点移動「下」
		g_Camera.at.y -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_U))
	{// 近づく
		g_Camera.len -= VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (GetKeyboardPress(DIK_M))
	{// 離れる
		g_Camera.len += VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	// カメラを初期に戻す
	if (GetKeyboardPress(DIK_R))
	{
		//UninitCamera();
		//InitCamera();
	}

#endif

	// イベント画面は常に回転している
	{
		g_CameraEvent.rot.y += VALUE_ROTATE_CAMERA_EVENT;
		if (g_CameraEvent.rot.y > XM_PI)
		{
			g_CameraEvent.rot.y -= XM_PI * 2.0f;
		}

		g_CameraEvent.pos.x = g_CameraEvent.at.x - sinf(g_CameraEvent.rot.y) * g_CameraEvent.len;
		g_CameraEvent.pos.z = g_CameraEvent.at.z - cosf(g_CameraEvent.rot.y) * g_CameraEvent.len;
	}


#ifdef _DEBUG	// デバッグ情報を表示する
	//PrintDebugProc("Camera:ZC QE TB YN UM R\n");
#endif
}


//=============================================================================
// カメラの更新
//=============================================================================
void SetCamera(void) 
{
	// ビューマトリックス設定

	if (g_ViewPortType == TYPE_RIGHT_HALF_SCREEN)
	{
		XMMATRIX mtxView;
		mtxView = XMMatrixLookAtLH(XMLoadFloat3(&g_CameraEvent.pos), XMLoadFloat3(&g_CameraEvent.at), XMLoadFloat3(&g_CameraEvent.up));
		SetViewMatrix(&mtxView);
		XMStoreFloat4x4(&g_Camera.mtxView, mtxView);

		XMMATRIX mtxInvView;
		mtxInvView = XMMatrixInverse(nullptr, mtxView);
		XMStoreFloat4x4(&g_Camera.mtxInvView, mtxInvView);
	}
	else
	{
		XMMATRIX mtxView;
		mtxView = XMMatrixLookAtLH(XMLoadFloat3(&g_Camera.pos), XMLoadFloat3(&g_Camera.at), XMLoadFloat3(&g_Camera.up));
		SetViewMatrix(&mtxView);
		XMStoreFloat4x4(&g_Camera.mtxView, mtxView);

		XMMATRIX mtxInvView;
		mtxInvView = XMMatrixInverse(nullptr, mtxView);
		XMStoreFloat4x4(&g_Camera.mtxInvView, mtxInvView);
	}


	// プロジェクションマトリックス設定
	XMMATRIX mtxProjection;
	mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE / 3, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z);

	switch (g_ViewPortType)
	{
	case TYPE_LEFT_HALF_SCREEN:
		mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT_HARF, VIEW_NEAR_Z, VIEW_FAR_Z);

		break;

	case TYPE_DOWN_RIGHT_HALF_SCREEN:
		mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT_HARF, VIEW_NEAR_Z, VIEW_FAR_Z);

		break;

	case TYPE_RIGHT_HALF_SCREEN:
		mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT_IVENT, VIEW_NEAR_Z, VIEW_FAR_Z);

		break;

	default:

		break;
	}
	//if(g_ViewPortType == TYPE_LEFT_HALF_SCREEN) mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT_HARF, VIEW_NEAR_Z, VIEW_FAR_Z);
	//else if (g_ViewPortType == TYPE_DOWN_RIGHT_HALF_SCREEN ) mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT_HARF, VIEW_NEAR_Z, VIEW_FAR_Z);
	//else if (g_ViewPortType == TYPE_RIGHT_HALF_SCREEN) mtxProjection = XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT_IVENT, VIEW_NEAR_Z, VIEW_FAR_Z);
	SetProjectionMatrix(&mtxProjection);
	XMStoreFloat4x4(&g_Camera.mtxProjection, mtxProjection);

	SetShaderCamera(g_Camera.pos);
}


//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}

//=============================================================================
// イベント時のカメラの取得
//=============================================================================
CAMERA *GetCameraEvent(void)
{
	return &g_CameraEvent;
}

//=============================================================================
// ビューポートの設定
//=============================================================================
void SetViewPort(int type)
{
	ID3D11DeviceContext *g_ImmediateContext = GetDeviceContext();
	D3D11_VIEWPORT vp;

	g_ViewPortType = type;

	// ビューポート設定
	switch (g_ViewPortType)
	{
	case TYPE_FULL_SCREEN:
		vp.Width = (FLOAT)SCREEN_WIDTH;
		vp.Height = (FLOAT)SCREEN_HEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_LEFT_HALF_SCREEN:
		vp.Width = (FLOAT)L_SCREEN_WIDTH;
		vp.Height = (FLOAT)SCREEN_HEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_RIGHT_HALF_SCREEN:
		vp.Width = (FLOAT)RU_SCREEN_WIDTH;
		vp.Height = (FLOAT)RU_SCREEN_HEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = (FLOAT)L_SCREEN_WIDTH;
		vp.TopLeftY = 0;
		break;

	case TYPE_UP_HALF_SCREEN:
		vp.Width = (FLOAT)SCREEN_WIDTH;
		vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		break;

	case TYPE_DOWN_HALF_SCREEN:
		vp.Width = (FLOAT)SCREEN_WIDTH;
		vp.Height = (FLOAT)SCREEN_HEIGHT / 2;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = (FLOAT)SCREEN_HEIGHT / 2;
		break;

	case TYPE_DOWN_RIGHT_HALF_SCREEN:
		vp.Width = (FLOAT)RD_SCREEN_WIDTH;
		vp.Height = (FLOAT)RD_SCREEN_HEIGHT;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = (FLOAT)L_SCREEN_WIDTH;
		vp.TopLeftY = (FLOAT)RU_SCREEN_HEIGHT;
		break;
	}
	g_ImmediateContext->RSSetViewports(1, &vp);

}


int GetViewPortType(void)
{
	return g_ViewPortType;
}


// カメラの視点と注視点をセット
void SetCameraAT(XMFLOAT3 pos)
{
	// カメラの注視点をプレイヤーの座標にしてみる
	g_Camera.at = g_CameraEvent.at =  pos;

	float vx, vz;

	switch (g_ViewPortType)
	{
	case TYPE_DOWN_RIGHT_HALF_SCREEN:
		g_Camera.pos = { POS_X_CAM, SLOT_POS_Y_CAM, SLOT_POS_Z_CAM };
		g_Camera.at.y = 1.0f;
		vx = g_Camera.pos.x - g_Camera.at.x;
		vz = g_Camera.pos.z - g_Camera.at.z;
		g_Camera.len = sqrtf(vx * vx + vz * vz);

		// カメラの視点をカメラのY軸回転に対応させている
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;

		break;

	case TYPE_RIGHT_HALF_SCREEN:
		//g_Camera.pos = { POS_X_CAM, POS_Y_CAM, POS_Z_CAM };
		g_CameraEvent.pos = { IVENT_POS_X_CAM, IVENT_POS_Y_CAM, IVENT_POS_Z_CAM };
		vx = g_CameraEvent.pos.x - g_CameraEvent.at.x;
		vz = g_CameraEvent.pos.z - g_CameraEvent.at.z;
		g_CameraEvent.len = sqrtf(vx * vx + vz * vz);

		// カメラの視点をカメラのY軸回転に対応させている
		g_CameraEvent.pos.x = g_CameraEvent.at.x - sinf(g_CameraEvent.rot.y) * g_CameraEvent.len;
		g_CameraEvent.pos.z = g_CameraEvent.at.z - cosf(g_CameraEvent.rot.y) * g_CameraEvent.len;

		break;

	case TYPE_FULL_SCREEN:
		g_Camera.pos = { POS_X_CAM, FULL_POS_Y_CAM, FULL_POS_Z_CAM };
		g_Camera.at.y = FULL_POS_Y_CAM;

		vx = g_Camera.pos.x - g_Camera.at.x;
		vz = g_Camera.pos.z - g_Camera.at.z;
		g_Camera.len = sqrtf(vx * vx + vz * vz);

		// カメラの視点をカメラのY軸回転に対応させている
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;

		break;

	default:
		g_Camera.pos = { POS_X_CAM, POS_Y_CAM, POS_Z_CAM };
		vx = g_Camera.pos.x - g_Camera.at.x;
		vz = g_Camera.pos.z - g_Camera.at.z;
		g_Camera.len = sqrtf(vx * vx + vz * vz);

		// カメラの視点をカメラのY軸回転に対応させている
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;

		break;
	}

	//if (g_ViewPortType == TYPE_DOWN_RIGHT_HALF_SCREEN)
	//{
	//	float vx, vz;
	//	g_Camera.pos = { POS_X_CAM, SLOT_POS_Y_CAM, SLOT_POS_Z_CAM };
	//	vx = g_Camera.pos.x - g_Camera.at.x;
	//	vz = g_Camera.pos.z - g_Camera.at.z;
	//	g_Camera.len = sqrtf(vx * vx + vz * vz);
	//}
	//else if(g_ViewPortType == TYPE_RIGHT_HALF_SCREEN)
	//{
	//	float vx, vz;
	//	//g_Camera.pos = { POS_X_CAM, POS_Y_CAM, POS_Z_CAM };
	//	g_Camera.pos = { IVENT_POS_X_CAM, IVENT_POS_Y_CAM, IVENT_POS_Z_CAM };
	//	vx = g_Camera.pos.x - g_Camera.at.x;
	//	vz = g_Camera.pos.z - g_Camera.at.z;
	//	g_Camera.len = sqrtf(vx * vx + vz * vz);
	//}
	//else
	//{
	//	float vx, vz;
	//	g_Camera.pos = { POS_X_CAM, POS_Y_CAM, POS_Z_CAM };
	//	vx = g_Camera.pos.x - g_Camera.at.x;
	//	vz = g_Camera.pos.z - g_Camera.at.z;
	//	g_Camera.len = sqrtf(vx * vx + vz * vz);
	//}



}
