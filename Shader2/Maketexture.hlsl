

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
	float4 LocalPos : POSITION;
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


	output.LocalPos=Pos;

	return output;
}

//
//�s�N�Z���V�F�[�_�[
//
float4 PS( VS_OUTPUT input ) : SV_Target
{
	float4 ret = input.LocalPos;
	ret.y = 1 - ret.y;
	return ret;
}