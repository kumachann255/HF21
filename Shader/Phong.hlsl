

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マトリクスバッファ
cbuffer WorldBuffer : register( b0 )
{
	matrix World;
}

cbuffer ViewBuffer : register( b1 )
{
	matrix View;
}

cbuffer ProjectionBuffer : register( b2 )
{
	matrix Projection;
}

// マテリアルバッファ
struct MATERIAL
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	int			noTexSampling;
	float		Dummy[2];//16byte境界用

};

cbuffer MaterialBuffer : register( b3 )
{
	MATERIAL	Material;
}

// ライト用バッファ
struct LIGHT
{
	float4		Direction[5];
	float4		Position[5];
	float4		Diffuse[5];
	float4		Ambient[5];
	float4		Attenuation[5];
	int4		Flags[5];
	int			Enable;
	int			Dummy[3];//16byte境界用
};

cbuffer LightBuffer : register( b4 )
{
	LIGHT		Light;
}


cbuffer CameraBuffer : register(b5)
{
	float4 CameraPos;
}



//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D		g_Texture  : register(t0);
SamplerState	g_SamplerState  : register(s0);

//=============================================================================
// 頂点シェーダ
//=============================================================================
void VertexShaderPolygon( in  float4 inPosition			: POSITION0,
						  in  float4 inNormal			: NORMAL0,
						  in  float4 inDiffuse			: COLOR0,
						  in  float2 inTexCoord			: TEXCOORD0,

						  out float4 outPosition		: SV_POSITION,
						  out float4 outNormal			: NORMAL0,
						  out float2 outTexCoord		: TEXCOORD0,
						  out float4 outDiffuse			: COLOR0,
						  out float4 outWorldPos		: POSITION0,

						  out float4 outLightTexCoord	: TEXCOORD1,
						  out float4 outLighViewPos		: TEXCOORD2
						  )

{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	outPosition = mul(inPosition, wvp);

	outNormal = normalize(mul(float4(inNormal.xyz, 0.0f), World));

	outTexCoord = inTexCoord;

	outWorldPos = mul(inPosition, World);

	outDiffuse = inDiffuse;

}


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void PixelShaderPolygon( in  float4 inPosition		: SV_POSITION,
						 in  float4 inNormal		: NORMAL0,
						 in  float2 inTexCoord		: TEXCOORD0,
						 in  float4 inDiffuse		: COLOR0,
						 in  float4 inWorldPos      : POSITION0,

						 in  float4 inLightTexCoord	: TEXCOORD1,
						 in  float4 inLighViewPos	: TEXCOORD2,

						 out float4 outDiffuse		: SV_Target )
{
	float4 color;

	if (Material.noTexSampling == 0)
	{
		color = g_Texture.Sample(g_SamplerState, inTexCoord);

		color *= inDiffuse;
	}
	else
	{
		color = inDiffuse;
	}

	if (Light.Enable == 0)
	{
		color = color * Material.Diffuse;
	}
	else
	{
		float4 tempColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 outColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

		for (int i = 0; i < 5; i++)
		{
			float3 lightDir;
			float light;

			if (Light.Flags[i].y == 1)
			{
				if (Light.Flags[i].x == 1)
				{
					lightDir = normalize(Light.Direction[i].xyz);
					light = dot(lightDir, inNormal.xyz);

					light =light * 0.5f ;
					tempColor = color * Material.Diffuse * light * Light.Diffuse[i];


					// ライト方向ベクトルを法線ベクトルに
					float3 LightDir = normalize(Light.Position[i].xyz - inWorldPos.xyz);

					// ライト方向と法線の内積
					// saturateは０〜１でクランプ
					float4 NL = saturate(dot(inNormal.xyz , LightDir));

					// 反射ベクトル
					float3 Reflect = normalize(2 * NL * inNormal.xyz - LightDir);

					float3 EyePos = normalize(CameraPos.xyz - inWorldPos);

					// 絞りでハイライト調整
					float4 Specular = pow(saturate(dot(Reflect, EyePos)), 8);

					tempColor += color * Material.Diffuse + Specular;

					//tempColor += color * Material.Diffuse * NL + Specular ;



				}
				else if (Light.Flags[i].x == 2)
				{
					lightDir = normalize(Light.Position[i].xyz - inWorldPos.xyz);
					light = dot(lightDir, inNormal.xyz);

					tempColor = color * Material.Diffuse * light * Light.Diffuse[i];

					float distance = length(inWorldPos - Light.Position[i]);

					float att = saturate((Light.Attenuation[i].x - distance) / Light.Attenuation[i].x);
					tempColor *= att;
				}
				else
				{
					tempColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
				}

				outColor += tempColor;
			}
		}

		color = outColor;
		color.a = inDiffuse.a * Material.Diffuse.a;
	}

	outDiffuse = color;
}


