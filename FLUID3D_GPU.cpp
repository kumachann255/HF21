#include "FLUID3D_GPU.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "model.h"


ID3D11UnorderedAccessView* g_ppUAV_NULL[1]={NULL};
ID3D11ShaderResourceView* g_ppSRV_NULL[1]={NULL};

FLUID3D_GPU::~FLUID3D_GPU()
{

}

void FLUID3D_GPU::Clear(ID3D11Device* pDevice)
{

	D3D11_BUFFER_DESC bdesc;
	D3D11_UNORDERED_ACCESS_VIEW_DESC udesc;

	m_pDevice = pDevice;

	//3Dテクスチャー
	CreateEmpty3DTexture(SIZE + 2, m_pDevice, &m_D_Tex.pTex3D, &m_D_Tex.pSRV);
	for (int i = 0; i < 2; i++) CreateEmpty3DTexture(SIZE + 2, m_pDevice, &m_D[i].pTex3D, &m_D[i].pSRV);
	for (int i = 0; i < 2; i++) CreateEmpty3DTexture(SIZE + 2, m_pDevice, &m_V[i].pTex3D, &m_V[i].pSRV);
	CreateEmpty3DTexture(SIZE + 2, m_pDevice, &m_V_s.pTex3D, &m_V_s.pSRV);
	CreateEmpty3DTexture(SIZE + 2, m_pDevice, &m_V_bs.pTex3D, &m_V_bs.pSRV);

	//ストラクチャードバッファ
	ZeroMemory(&bdesc, sizeof(bdesc));
	bdesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	bdesc.ByteWidth = sizeof(SBUFFER_ELEMENT)*(SIZE + 2)*(SIZE + 2)*(SIZE + 2);
	bdesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bdesc.StructureByteStride = sizeof(SBUFFER_ELEMENT);
	m_pDevice->CreateBuffer(&bdesc, NULL, &m_Prs.pStredBuf);
	m_pDevice->CreateBuffer(&bdesc, NULL, &m_Div.pStredBuf);

	//UAV
	ZeroMemory(&udesc, sizeof(udesc));
	udesc.Format = DXGI_FORMAT_UNKNOWN;
	udesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	udesc.Texture2D.MipSlice = 0;
	udesc.Buffer.NumElements = (SIZE + 2)*(SIZE + 2)*(SIZE + 2);
	m_pDevice->CreateUnorderedAccessView(m_Prs.pStredBuf, &udesc, &m_Prs.pUAV);
	m_pDevice->CreateUnorderedAccessView(m_Div.pStredBuf, &udesc, &m_Div.pUAV);

	//UAV (3Dテクスチャーの)
	ZeroMemory(&udesc, sizeof(udesc));
	udesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	udesc.Texture3D.FirstWSlice = 0;
	udesc.Texture3D.WSize = SIZE;
	udesc.Texture3D.MipSlice = 0;
	udesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;

	m_pDevice->CreateUnorderedAccessView(m_D_Tex.pTex3D, &udesc, &m_D_Tex.pUAV);
	for (int i = 0; i < 2; i++) m_pDevice->CreateUnorderedAccessView(m_D[i].pTex3D, &udesc, &m_D[i].pUAV);
	for (int i = 0; i < 2; i++) m_pDevice->CreateUnorderedAccessView(m_V[i].pTex3D, &udesc, &m_V[i].pUAV);
	m_pDevice->CreateUnorderedAccessView(m_V_s.pTex3D, &udesc, &m_V_s.pUAV);
	m_pDevice->CreateUnorderedAccessView(m_V_bs.pTex3D, &udesc, &m_V_bs.pUAV);

}

//
//
//hlslファイルを読み込みシェーダーを作成する
HRESULT FLUID3D_GPU::MakeShader(ID3D11Device* pDevice,LPSTR szFileName,LPSTR szFuncName,LPSTR szProfileName,void** ppShader,ID3DBlob** ppBlob)
{
	ID3DBlob *pErrors=NULL;
	if(FAILED(D3DX11CompileFromFileA(szFileName,NULL,NULL,szFuncName,szProfileName,D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,0,NULL,ppBlob,&pErrors,NULL)))
	{
		char*p =(char*) pErrors->GetBufferPointer();
		MessageBoxA(0,p,0,MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	char szProfile[3]={0};
	memcpy(szProfile,szProfileName,2);
	if(strcmp(szProfile,"vs")==0)//Vertex Shader
	{
		if(FAILED(pDevice->CreateVertexShader((*ppBlob)->GetBufferPointer(),(*ppBlob)->GetBufferSize(),NULL,(ID3D11VertexShader**)ppShader))) return E_FAIL;
	}
	if(strcmp(szProfile,"ps")==0)//Pixel Shader
	{
		if(FAILED(pDevice->CreatePixelShader((*ppBlob)->GetBufferPointer(),(*ppBlob)->GetBufferSize(),NULL,(ID3D11PixelShader**)ppShader))) return E_FAIL;
	}
	if(strcmp(szProfile,"gs")==0)//Geometry Shader
	{
		if(FAILED(pDevice->CreateGeometryShader((*ppBlob)->GetBufferPointer(),(*ppBlob)->GetBufferSize(),NULL,(ID3D11GeometryShader**)ppShader))) return E_FAIL;
	}
	if(strcmp(szProfile,"hs")==0)//Hull Shader
	{
		if(FAILED(pDevice->CreateHullShader((*ppBlob)->GetBufferPointer(),(*ppBlob)->GetBufferSize(),NULL,(ID3D11HullShader**)ppShader))) return E_FAIL;
	}
	if(strcmp(szProfile,"ds")==0)//Domain Shader
	{
		if(FAILED(pDevice->CreateDomainShader((*ppBlob)->GetBufferPointer(),(*ppBlob)->GetBufferSize(),NULL,(ID3D11DomainShader**)ppShader))) return E_FAIL;
	}
	if(strcmp(szProfile,"cs")==0)//Compute Shader
	{
		if(FAILED(pDevice->CreateComputeShader((*ppBlob)->GetBufferPointer(),(*ppBlob)->GetBufferSize(),NULL,(ID3D11ComputeShader**)ppShader))) return E_FAIL;
	}
	return S_OK;
}
//
//
//
HRESULT FLUID3D_GPU::CreateEmpty3DTexture(int Size,ID3D11Device* pDevice,ID3D11Texture3D** ppTexture,ID3D11ShaderResourceView** ppSRV)
{
	D3D11_TEXTURE3D_DESC descTex;
	ZeroMemory(&descTex, sizeof(descTex));
	descTex.Height=Size;
	descTex.Width=Size;
	descTex.Depth=Size;
	descTex.MipLevels=1;
	descTex.Format=DXGI_FORMAT_R16G16B16A16_FLOAT;
	descTex.Usage=D3D11_USAGE_DEFAULT;
	descTex.BindFlags= D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;

	pDevice->CreateTexture3D(&descTex,NULL,ppTexture);
	pDevice->CreateShaderResourceView(*ppTexture,NULL,ppSRV);

	return S_OK;
}
//
//
//
void FLUID3D_GPU::Init(ID3D11Device* pDevice,ID3D11DeviceContext* pContext,DWORD Width,DWORD Height,
					   ID3D11RenderTargetView* pBackRTV,ID3D11DepthStencilView* pBackDSV)
{
	D3D11_RENDER_TARGET_VIEW_DESC rdesc;
	D3D11_TEXTURE2D_DESC desc;
	D3D11_SHADER_RESOURCE_VIEW_DESC sdesc;
	D3D11_BUFFER_DESC bdesc;
	D3D11_SUBRESOURCE_DATA InitData;
	D3D11_UNORDERED_ACCESS_VIEW_DESC udesc;

	m_pDevice=pDevice;
	m_pDeviceContext=pContext;

	m_BackBuffer.pRTV=pBackRTV;
	m_BackBuffer.pDSV=pBackDSV;

	//3Dテクスチャー
	CreateEmpty3DTexture(SIZE+2,m_pDevice,&m_D_Tex.pTex3D,&m_D_Tex.pSRV);
	for(int i=0;i<2;i++) CreateEmpty3DTexture(SIZE+2,m_pDevice,&m_D[i].pTex3D,&m_D[i].pSRV);
	for(int i=0;i<2;i++) CreateEmpty3DTexture(SIZE+2,m_pDevice,&m_V[i].pTex3D,&m_V[i].pSRV);
	CreateEmpty3DTexture(SIZE+2,m_pDevice,&m_V_s.pTex3D,&m_V_s.pSRV);
	CreateEmpty3DTexture(SIZE+2,m_pDevice,&m_V_bs.pTex3D,&m_V_bs.pSRV);

	//ストラクチャードバッファ
	ZeroMemory(&bdesc,sizeof(bdesc));
	bdesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	bdesc.ByteWidth = sizeof(SBUFFER_ELEMENT)*(SIZE+2)*(SIZE+2)*(SIZE+2);
	bdesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bdesc.StructureByteStride = sizeof(SBUFFER_ELEMENT);
	m_pDevice->CreateBuffer(&bdesc, NULL, &m_Prs.pStredBuf);
	m_pDevice->CreateBuffer(&bdesc, NULL, &m_Div.pStredBuf);

	//UAV
	ZeroMemory(&udesc,sizeof(udesc));
	udesc.Format = DXGI_FORMAT_UNKNOWN;
	udesc.ViewDimension=D3D11_UAV_DIMENSION_BUFFER;
	udesc.Texture2D.MipSlice=0;
	udesc.Buffer.NumElements = (SIZE+2)*(SIZE+2)*(SIZE+2);
	m_pDevice->CreateUnorderedAccessView(m_Prs.pStredBuf, &udesc, &m_Prs.pUAV);
	m_pDevice->CreateUnorderedAccessView(m_Div.pStredBuf, &udesc, &m_Div.pUAV);

	//UAV (3Dテクスチャーの)
	ZeroMemory(&udesc,sizeof(udesc));
	udesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	udesc.Texture3D.FirstWSlice=0;
	udesc.Texture3D.WSize=SIZE;
	udesc.Texture3D.MipSlice=0;
	udesc.ViewDimension=D3D11_UAV_DIMENSION_TEXTURE3D;

	m_pDevice->CreateUnorderedAccessView(m_D_Tex.pTex3D, &udesc,&m_D_Tex.pUAV);
	for(int i=0;i<2;i++) m_pDevice->CreateUnorderedAccessView(m_D[i].pTex3D, &udesc,&m_D[i].pUAV);
	for(int i=0;i<2;i++) m_pDevice->CreateUnorderedAccessView(m_V[i].pTex3D, &udesc,&m_V[i].pUAV);
	m_pDevice->CreateUnorderedAccessView(m_V_s.pTex3D, &udesc,&m_V_s.pUAV);
	m_pDevice->CreateUnorderedAccessView(m_V_bs.pTex3D, &udesc,&m_V_bs.pUAV);

	//Shader読み込み
	ID3DBlob *pCompiledShader=NULL;
	MakeShader(m_pDevice, "Shader2/Solver.hlsl","AddSource","cs_5_0",(void**)&m_AddSourceShader.pComputeShader,&pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl","AdvectDensity","cs_5_0",(void**)&m_AdvectDensityShader.pComputeShader,&pCompiledShader);	
	MakeShader(m_pDevice, "Shader2/Solver.hlsl","Project1","cs_5_0",(void**)&m_Project1Shader.pComputeShader,&pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl","Project2","cs_5_0",(void**)&m_Project2Shader.pComputeShader,&pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl", "Project3", "cs_5_0", (void**)&m_Project3Shader.pComputeShader, &pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl", "Project4", "cs_5_0", (void**)&m_Project4Shader.pComputeShader, &pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl", "AdvectVelocity", "cs_5_0", (void**)&m_AdvectVelocityShader.pComputeShader, &pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl", "AdvectBack", "cs_5_0", (void**)&m_AdvectBackShader.pComputeShader, &pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl", "MacCormackScheme", "cs_5_0", (void**)&m_MacCormackShader.pComputeShader, &pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl", "Boundary1", "cs_5_0", (void**)&m_Boundary1Shader.pComputeShader, &pCompiledShader);
	MakeShader(m_pDevice, "Shader2/Solver.hlsl", "Boundary2", "cs_5_0", (void**)&m_Boundary2Shader.pComputeShader, &pCompiledShader);
		
	//コンスタントバッファー作成	
	bdesc.BindFlags= D3D11_BIND_CONSTANT_BUFFER;
	bdesc.ByteWidth= sizeof(CS_CBUFFER);
	bdesc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	bdesc.MiscFlags=0;
	bdesc.StructureByteStride=0;
	bdesc.Usage=D3D11_USAGE_DYNAMIC;
	m_pDevice->CreateBuffer(&bdesc,NULL,&m_pConstantBuffer);

	//バッファ用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc,sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	m_pDevice->CreateSamplerState( &SamDesc, &m_pSamLinear);

	//テクスチャーのレンダーターゲット関連作成
	{
		ZeroMemory(&desc,sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = Width;
		desc.Height = Height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags=D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		m_pDevice->CreateTexture2D(&desc,NULL,&m_TextureA.pTex2D);
		m_pDevice->CreateTexture2D(&desc, NULL, &m_TextureB.pTex2D);
		//そのテクスチャーに対しレンダーターゲットビュー(RTV)を作成	
		ZeroMemory(&rdesc,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		rdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		rdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rdesc.Texture2DArray.MipSlice=0;
		m_pDevice->CreateRenderTargetView(m_TextureA.pTex2D,&rdesc,&m_TextureA.pRTV);
		m_pDevice->CreateRenderTargetView(m_TextureB.pTex2D, &rdesc, &m_TextureB.pRTV);
		//そのテクスチャーに対しシェーダーリソースビュー(SRV)を作成		
		ZeroMemory(&sdesc,sizeof(sdesc));
		sdesc.Format =DXGI_FORMAT_R8G8B8A8_UNORM;
		sdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sdesc.Texture2D.MipLevels = 1;
		m_pDevice->CreateShaderResourceView(m_TextureA.pTex2D,&sdesc,&m_TextureA.pSRV);
		m_pDevice->CreateShaderResourceView(m_TextureB.pTex2D, &sdesc, &m_TextureB.pSRV);
		//そのテクスチャーのレンダーターゲット化に伴うデプスステンシルテクスチャー作成
		desc.Width = Width;
		desc.Height = Height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_D32_FLOAT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		m_pDevice->CreateTexture2D(&desc,NULL,&m_TextureA.pDSTex2D);	
		m_pDevice->CreateTexture2D(&desc, NULL, &m_TextureB.pDSTex2D);
		//そのDSVを作成
		m_pDevice->CreateDepthStencilView(m_TextureA.pDSTex2D,NULL,&m_TextureA.pDSV);
		m_pDevice->CreateDepthStencilView(m_TextureB.pDSTex2D, NULL, &m_TextureB.pDSV);
	}
	//テクスチャー用サンプラー作成
	ZeroMemory(&SamDesc,sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	SamDesc.BorderColor[0]=0;SamDesc.BorderColor[1]=0;SamDesc.BorderColor[2]=0;SamDesc.BorderColor[3]=0;
	m_pDevice->CreateSamplerState( &SamDesc, &m_pSampleLinear);

	//3Dテクスチャーをファイルから読み込む
	CreateEmpty3DTexture(100,m_pDevice,&m_pTexture3D,&m_pTexture3D_SRV);

	//画面ポリゴン関連の各種オブジェクト作成
	
	//シェーダ読み込み 
	ID3DBlob *pErrors=NULL;

	if(FAILED(MakeShader(m_pDevice,"Shader2/VolumeRender.hlsl","VS","vs_5_0",(void**)&m_ScreenPoly.pVertexShader,&pCompiledShader))) return;
	
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};
	UINT numElements=sizeof(layout)/sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if( FAILED( m_pDevice->CreateInputLayout(layout,numElements,pCompiledShader->GetBufferPointer(),pCompiledShader->GetBufferSize(),&m_ScreenPoly.pVertexLayout)))
	{
		return;
	}
	SAFE_RELEASE(pCompiledShader);

	if(FAILED(MakeShader(m_pDevice,"Shader2/VolumeRender.hlsl","PS","ps_5_0",(void**)&m_ScreenPoly.pPixelShader,&pCompiledShader))) return;	
	SAFE_RELEASE(pCompiledShader);

	//コンスタントバッファー作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth= sizeof(CBUFFER_F);
	cb.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags	=0;
	cb.StructureByteStride=0;
	cb.Usage=D3D11_USAGE_DYNAMIC;

	m_pDevice->CreateBuffer( &cb,NULL,&m_ScreenPoly.pCBuffer);


	//頂点バッファ作成
	VERTEX_F VertexData[]=
	{
		XMFLOAT3(-1,-1,0),
		XMFLOAT3(-1,1,0),
		XMFLOAT3(1,-1,0),
		XMFLOAT3(1,1,0)
	};
	
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.ByteWidth = sizeof(VERTEX_F)*4;
	bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bdesc.CPUAccessFlags = 0;
	bdesc.MiscFlags = 0;
	InitData.pSysMem = VertexData;
	if(FAILED(m_pDevice->CreateBuffer(&bdesc,&InitData,&m_ScreenPoly.pVBuffer)))
	{
		return;
	}

	//キューブ関連の各種オブジェクトの作成

	//シェーダ読み込み
	if(FAILED(MakeShader(m_pDevice,"Shader2/Maketexture.hlsl","VS","vs_5_0",(void**)&m_Cube.pVertexShader,&pCompiledShader))) return;
	
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout2[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	};
	numElements=sizeof(layout2)/sizeof(layout2[0]);
	//頂点インプットレイアウトを作成
	if( FAILED( m_pDevice->CreateInputLayout(layout2,numElements,pCompiledShader->GetBufferPointer(),pCompiledShader->GetBufferSize(),&m_Cube.pVertexLayout)))
	{
		return;
	}
	SAFE_RELEASE(pCompiledShader);

	if(FAILED(MakeShader(m_pDevice,"Shader2/Maketexture.hlsl","PS","ps_5_0",(void**)&m_Cube.pPixelShader,&pCompiledShader))) return;	
	SAFE_RELEASE(pCompiledShader);

	//コンスタントバッファー作成
	cb.BindFlags= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth= sizeof(CBUFFER_F);
	cb.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags	=0;
	cb.StructureByteStride=0;
	cb.Usage=D3D11_USAGE_DYNAMIC;

	if( FAILED(m_pDevice->CreateBuffer(&cb,NULL,&m_Cube.pCBuffer)))
	{
		return;
	}
	//頂点バッファ作成
	VERTEX_F VertexData2[]=
	{
		XMFLOAT3(-0.5,-0.5,0.5),
		XMFLOAT3(-0.5,-0.5,-0.5),
		XMFLOAT3(-0.5,0.5,0.5),
		XMFLOAT3(-0.5,0.5,-0.5),
		XMFLOAT3(0.5,-0.5,0.5),
		XMFLOAT3(0.5,-0.5,-0.5),
		XMFLOAT3(0.5,0.5,0.5),
		XMFLOAT3(0.5,0.5,-0.5),
	};
	for(int i=0;i<8;i++)
	{
		VertexData2[i].Pos.x+=0.5;
		VertexData2[i].Pos.y+=0.5;
		VertexData2[i].Pos.z+=0.5;
	}
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.ByteWidth = sizeof(VERTEX_F)*8;
	bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bdesc.CPUAccessFlags = 0;
	bdesc.MiscFlags = 0;
	InitData.pSysMem = VertexData2;
	if(FAILED(m_pDevice->CreateBuffer(&bdesc,&InitData,&m_Cube.pVBuffer)))
		return;

	//インデックスバッファを作成
	int IndexData[]=
	{
		2,1,0,
		2,3,1,
		1,4,0,
		1,5,4,
		3,5,1,
		3,7,5,
		3,2,6,
		7,3,6,
		2,0,4,
		6,2,4,
		5,6,4,
		7,6,5
	};
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.ByteWidth=sizeof(int)*12*3;
	bdesc.BindFlags=D3D11_BIND_INDEX_BUFFER;
	bdesc.CPUAccessFlags=0;
	bdesc.MiscFlags=0;
	InitData.pSysMem=IndexData;
	InitData.SysMemPitch=0;
	InitData.SysMemSlicePitch=0;
	if( FAILED(m_pDevice->CreateBuffer(&bdesc,&InitData,&m_Cube.pIBuffer)))
		return;

	//アルファブレンド用ブレンドステート作成
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable =false;
	bd.AlphaToCoverageEnable=false;
	bd.RenderTarget[0].BlendEnable=true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	m_pDevice->CreateBlendState(&bd, &m_pBlendState);
}

//
//
//
void FLUID3D_GPU::AddDensitySource(XMFLOAT4& Sphere, XMFLOAT4& Value)
{

	if (!m_bUse) return;

	m_Add=true;
	m_Source.DensitySphere=Sphere;

	Value.x *= TIME_STEP;
	Value.y *= TIME_STEP;
	Value.z *= TIME_STEP;

	m_Source.DensitySource=Value;
}
//
//
//
void FLUID3D_GPU::AddVelocitySource(XMFLOAT4& Pos, XMFLOAT4& Value)
{
	if (!m_bUse) return;

	m_Add=true;
	m_Source.VelocitySphere=Pos;

	Value.x *= TIME_STEP;
	Value.y *= TIME_STEP;
	Value.z *= TIME_STEP;

	m_Source.VelocitySource=Value;
}
//
//
//
void FLUID3D_GPU::Unbind()
{
	ID3D11UnorderedAccessView* ppUAV_NULL[1]={NULL};
	ID3D11ShaderResourceView* ppSRV_NULL[1]={NULL};
	for(int i=0;i<8;i++)
	{
		m_pDeviceContext->CSSetUnorderedAccessViews(i,1,ppUAV_NULL,0);
		m_pDeviceContext->CSSetShaderResources(i,1,ppSRV_NULL);
	}
}

//
//
//
void FLUID3D_GPU::Solve()
{

	if (!m_bUse) return;

	//速度ソルバー
	
	//Swap
	Swap(m_V[0],m_V[1]);

	//Project
	m_pDeviceContext->CSSetUnorderedAccessViews(4, 1, &m_Div.pUAV, 0);
	m_pDeviceContext->CSSetUnorderedAccessViews(3, 1, &m_Prs.pUAV, 0);
	m_pDeviceContext->CSSetShaderResources(1,1,&m_V[0].pSRV);
	m_pDeviceContext->CSSetShader(m_Project1Shader.pComputeShader,NULL,0);
	m_pDeviceContext->Dispatch(10,10,10);
	Unbind();

	//project2
	m_pDeviceContext->CSSetUnorderedAccessViews(3, 1, &m_Prs.pUAV, 0);
	m_pDeviceContext->CSSetUnorderedAccessViews(4, 1, &m_Div.pUAV, 0);
	m_pDeviceContext->CSSetShader(m_Project2Shader.pComputeShader, NULL, 0);
	for (int i = 0; i < 5;i++)  m_pDeviceContext->Dispatch(10,10,10);
	Unbind();

	//project3
	m_pDeviceContext->CSSetShaderResources(1,1,&m_V[0].pSRV);
	m_pDeviceContext->CSSetUnorderedAccessViews(1,1,&m_V[1].pUAV,0);
	m_pDeviceContext->CSSetUnorderedAccessViews(3, 1, &m_Prs.pUAV, 0);
	m_pDeviceContext->CSSetShader(m_Project3Shader.pComputeShader, NULL, 0);
	m_pDeviceContext->Dispatch(10,10,10);
	Unbind();

	//Swap
	Swap(m_V[0],m_V[1]);

	//boundary
	m_pDeviceContext->CSSetShaderResources(1,1,&m_V[0].pSRV);
	m_pDeviceContext->CSSetUnorderedAccessViews(1,1,&m_V[1].pUAV,0);
	m_pDeviceContext->CSSetUnorderedAccessViews(3, 1, &m_Prs.pUAV, 0);
	m_pDeviceContext->CSSetShader(m_Boundary1Shader.pComputeShader, NULL, 0);
	m_pDeviceContext->Dispatch(10,10,1);
	Unbind();
	
	//Advect
	m_pDeviceContext->CSSetShaderResources(1,1,&m_V[0].pSRV);
	m_pDeviceContext->CSSetUnorderedAccessViews(2,1,&m_V_s.pUAV,0);
	m_pDeviceContext->CSSetShader(m_AdvectVelocityShader.pComputeShader, NULL, 0);
	m_pDeviceContext->Dispatch(10,10,10);
	Unbind();

	//Advect Back
	m_pDeviceContext->CSSetShaderResources(1,1, &m_V[0].pSRV);
	m_pDeviceContext->CSSetShaderResources(2,1, &m_V_s.pSRV);
	m_pDeviceContext->CSSetUnorderedAccessViews(3, 1, &m_V_bs.pUAV, 0);
	m_pDeviceContext->CSSetShader(m_AdvectBackShader.pComputeShader, NULL, 0);
	m_pDeviceContext->Dispatch(10,10,10);
	Unbind();

	//MacCormack
	m_pDeviceContext->CSSetShaderResources(1,1, &m_V[0].pSRV);
	m_pDeviceContext->CSSetUnorderedAccessViews(1, 1, &m_V[1].pUAV, 0);
	m_pDeviceContext->CSSetShaderResources(2,1, &m_V_s.pSRV);
	m_pDeviceContext->CSSetShaderResources(3,1, &m_V_bs.pSRV);
	m_pDeviceContext->CSSetShader(m_MacCormackShader.pComputeShader, NULL, 0);
	m_pDeviceContext->Dispatch(10,10,10);
	Unbind();

	//密度ソルバー

	//Advect
	m_pDeviceContext->CSSetShaderResources(1,1,&m_V[0].pSRV);
	m_pDeviceContext->CSSetUnorderedAccessViews(5, 1, &m_D_Tex.pUAV, 0);	
	m_pDeviceContext->CSSetShaderResources(0,1,&m_D[0].pSRV);
	m_pDeviceContext->CSSetUnorderedAccessViews(0,1,&m_D[1].pUAV,0);
	Swap(m_D[0],m_D[1]);
	m_pDeviceContext->CSSetShader(m_AdvectDensityShader.pComputeShader, NULL, 0);
	m_pDeviceContext->Dispatch(10,10,10);
	Unbind();

	
	//密度、速度を注入
	if(m_Add)
	{
	
		D3D11_MAPPED_SUBRESOURCE pData;
		m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&m_Source), sizeof(m_Source));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
		m_pDeviceContext->CSSetShaderResources(0,1,&m_D[1].pSRV);
		m_pDeviceContext->CSSetUnorderedAccessViews(0,1,&m_D[0].pUAV,0);
		m_pDeviceContext->CSSetShaderResources(1,1,&m_V[0].pSRV);
		m_pDeviceContext->CSSetUnorderedAccessViews(1,1,&m_V[1].pUAV,0);

		m_pDeviceContext->CSSetShader(m_AddSourceShader.pComputeShader, NULL, 0);
		m_pDeviceContext->CSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pDeviceContext->Dispatch(1, 1, 1);
		Unbind();
	}
	
	m_pDeviceContext->CSSetShader(NULL,NULL,0);

	ZeroMemory(&m_Source,sizeof(m_Source));
	m_Add=false;
}

//
//
//
void FLUID3D_GPU::DrawFluid(void)
{

	if (!m_bUse) return;

	float ClearColor[4] = { 0.0f,0.0f,0.0f,1.0f };//クリア色作成　RGBAの順
	UINT stride = sizeof(VERTEX_F);
	UINT offset = 0;

	XMMATRIX mtxScl, mtxRot,mtxTranslate, mtxWorld;

	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	// スケールを反映
	mtxScl = XMMatrixScaling(m_scl.x, m_scl.y, m_scl.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);


	//1パス
	{
		//レンダーターゲットをテクスチャーAに変更
		m_pDeviceContext->OMSetRenderTargets(1, &m_TextureA.pRTV, m_TextureA.pDSV);
		m_pDeviceContext->ClearRenderTargetView(m_TextureA.pRTV, ClearColor);//画面クリア
		m_pDeviceContext->ClearDepthStencilView(m_TextureA.pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//深度バッファクリア

		// ビューポート設定
		SetViewPort(TYPE_FULL_SCREEN);
		SetCamera();

		//フロントフェイスのみレンダリングするようにカリングモードをセット
		SetCullingMode(CULL_MODE_BACK);

		//使用するシェーダーのセット	
		m_pDeviceContext->VSSetShader(m_Cube.pVertexShader, NULL, 0);
		m_pDeviceContext->PSSetShader(m_Cube.pPixelShader, NULL, 0);
		
		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		//シェーダーのコンスタントバッファーに各種データを渡す
		Send_WVPCbuffer();

		DrawBox();
	}

	//2パス
	{
		//レンダーターゲットをテクスチャーBに変更
		m_pDeviceContext->OMSetRenderTargets(1,&m_TextureB.pRTV,m_TextureB.pDSV);
		m_pDeviceContext->ClearRenderTargetView(m_TextureB.pRTV,ClearColor);//画面クリア
		m_pDeviceContext->ClearDepthStencilView(m_TextureB.pDSV,D3D11_CLEAR_DEPTH,1.0f,0);//深度バッファクリア

		//バックフェイスのみレンダリングするようにカリングモードをセット
		SetCullingMode(CULL_MODE_FRONT);

		DrawBox();
	}

	//3パス
	{
		//レンダーターゲットをバックバッファーに戻す
		m_pDeviceContext->OMSetRenderTargets(1,&m_BackBuffer.pRTV,m_BackBuffer.pDSV);

		SetCullingMode(CULL_MODE_BACK);
		m_pDeviceContext->PSSetSamplers(0,1,&m_pSampleLinear);

		//使用するシェーダーのセット	
		m_pDeviceContext->VSSetShader(m_ScreenPoly.pVertexShader,NULL,0);
		m_pDeviceContext->PSSetShader(m_ScreenPoly.pPixelShader,NULL,0);

		//パス１とパス２で作成したテクスチャー2枚をシェーダーにセット
		m_pDeviceContext->PSSetShaderResources(0,1,&m_TextureA.pSRV);
		m_pDeviceContext->PSSetShaderResources(1,1,&m_TextureB.pSRV);
		//3Dテクスチャーをシェーダーにセット		
		m_pDeviceContext->PSSetShaderResources(2, 1, &m_D_Tex.pSRV);

		DrawBox();

	}
}


//=============================================================================
// 描画処理
//=============================================================================
void FLUID3D_GPU::DrawBox(void)
{

	UINT stride = sizeof(VERTEX_F);
	UINT offset = 0;

	//頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout(m_Cube.pVertexLayout);
	//プリミティブ・トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//頂点バッファをセット
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_Cube.pVBuffer, &stride, &offset);
	//インデックスバッファをセット
	m_pDeviceContext->IASetIndexBuffer(m_Cube.pIBuffer, DXGI_FORMAT_R32_UINT, 0);
	//レンダリング
	m_pDeviceContext->DrawIndexed(12 * 3, 0, 0);


}
