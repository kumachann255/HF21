//�O���[�o��

Texture2D g_texA: register(t0);
Texture2D g_texB: register(t1);
Texture3D g_tex3D: register(t2);
SamplerState g_samLinear : register(s0);

// �}�g���N�X�o�b�t�@
cbuffer WorldBuffer : register(b0)
{
	matrix World;
}

cbuffer ViewBuffer : register(b1)
{
	matrix View;
}

cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}


//�\����
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 CPos : POSITION;
	float2 TexCoord : TEXCOORD0;
};

//
//�o�[�e�b�N�X�V�F�[�_�[
//
VS_OUTPUT VS( float4 Pos : POSITION,
		     float2 TexCoord : TEXCOORD0)

{

	VS_OUTPUT output = (VS_OUTPUT)0;

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
	output.Pos = mul(Pos, wvp);
	output.TexCoord = TexCoord;

	output.CPos=output.Pos;

	return output;
}

//
//�s�N�Z���V�F�[�_�[
//
float4 PS( VS_OUTPUT input ) : SV_Target
{
	const int Loops = 2;
	const float Stride = 1.0f / Loops;
	//���_���W����e�N�X�`���[���W���쐬
	float2 Tex=input.CPos.xy/=input.CPos.w;
    Tex.x=0.5f*Tex.x+0.5f;
    Tex.y=-0.5f*Tex.y+0.5f;


	float3 Front=g_texA.Sample(g_samLinear,Tex).xyz;
    float3 Back=g_texB.Sample(g_samLinear,Tex).xyz;

	float3 Dir=normalize(Back-Front);	
	
	float4 TotalColor=float4(0,0,0,0);
    float4 Texel3D=float4(0,0,0,0);
 
    float3 Step=Stride*Dir;

	float Max = 0;
	for(int i=0;i<Loops;i++)
    {
		Texel3D=g_tex3D.Sample(g_samLinear,Front);
		Front+=Step;
		Max = max(Max, Texel3D.r);
	}

	float4 RedBlack = float4(-1, -2, -3, 0);
	float4 White = float4(0.5, 0.2, 1.0, 2);
	TotalColor = saturate(lerp(RedBlack, White, Max));
	return TotalColor;
}