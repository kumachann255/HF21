#define SIZE 100
#define TIME_STEP 0.01
#define DENSITY_COEF 0.01
#define VISCOSITY_COEFF 0.01

#define ID(i,j,k) (i)+(j)*(SIZE+2)+(k)*(SIZE+2)*(SIZE+2)

SamplerState g_samLinear : register(s1);

//
struct Buff
{
	float f;
	float f0;
};

//
Texture3D<float4> g_rD : register(t0);
RWTexture3D<float4> g_wD : register(u0);

Texture3D<float4> g_rV : register(t1);
RWTexture3D<float4> g_wV : register(u1);

Texture3D<float4> g_rV_s : register(t2);
RWTexture3D<float4> g_wV_s : register(u2);

Texture3D<float4> g_rV_bs : register(t3);
RWTexture3D<float4> g_wV_bs : register(u3);

RWStructuredBuffer<Buff> g_Prs : register(u3);
RWStructuredBuffer<Buff> g_Div : register(u4);
RWTexture3D<float4> g_D_Tex3D : register(u5);

//
cbuffer global
{
	float4 g_DensitySphere;
	float4 g_DensitySource;
	float4 g_VelocitySphere;
	float4 g_VelocitySource;
	float4 g_Vorticity;
}

//
//
//
[numthreads(1,1,1)]
void AddSource( uint3 id : SV_DispatchThreadID ,uint3 gid : SV_GroupID )
{
	float3 center=g_DensitySphere.xyz;
	int radius=g_DensitySphere.w;
	
	for(int i=-radius;i<radius;i++)
	{
		for(int j=-radius;j<radius;j++)
		{
			for(int k=-radius;k<radius;k++)
			{
				float3 p=float3(i,j,k);								
				float l=dot(p,p);
				float rate=exp(-l/radius*radius)*500;
				float3 pos=center+p;
				g_wD[uint3(pos.x,pos.y,pos.z)]=g_rD[uint3(pos.x,pos.y,pos.z)]+g_DensitySource*rate;
				g_wV[uint3(pos.x,pos.y,pos.z)]=g_rV[uint3(pos.x,pos.y,pos.z)]+g_VelocitySource*rate;
			}
		}		
	}
}
//
//
//
[numthreads(10,10,10)]
void AdvectDensity( uint3 id : SV_DispatchThreadID ,uint3 gid : SV_GroupID )
{
	uint i = id.x+1;
	uint j = id.y+1;
	uint k = id.z+1;

	float3 uv=id+1;
	uv.x-=g_rV[uint3(i,j,k)].x*TIME_STEP;
	uv.y-=g_rV[uint3(i,j,k)].y*TIME_STEP;
	uv.z-=g_rV[uint3(i,j,k)].z*TIME_STEP;

	uv=(uv+0.5)/(SIZE+2);
	
	g_wD[uint3(i,j,k)]=g_rD.SampleLevel(g_samLinear,uv,0);

	//テクスチャーに書き込む
	g_D_Tex3D[uint3(id.x,id.y,id.z)]=g_rD[uint3(i,j,k)];	
}
//
//
//
[numthreads(10,10,10)]
void Project1(uint3 id : SV_DispatchThreadID, uint3 gid : SV_GroupID)
{
	uint i = id.x+1;
	uint j = id.y+1;
	uint k = id.z+1;
	g_Prs[ID(i,j,k)].f=0;
	g_Div[ID(i,j,k)].f = (g_rV[uint3(i+1,j,k)].x -g_rV[uint3(i-1,j,k)].x)/2+
		(g_rV[uint3(i,j+1,k)].y - g_rV[uint3(i,j-1,k)].y)/2+
		(g_rV[uint3(i,j,k+1)].z - g_rV[uint3(i,j,k-1)].z)/2;
}
//
//
//
[numthreads(10,10,10)]
void Project2(uint3 id : SV_DispatchThreadID, uint3 gid : SV_GroupID)
{
	uint i = id.x+1;
	uint j = id.y+1;
	uint k = id.z+1;

	g_Prs[ID(i,j,k)].f=(g_Prs[ID(i-1,j,k)].f+g_Prs[ID(i+1,j,k)].f+
		g_Prs[ID(i,j-1,k)].f+g_Prs[ID(i,j+1,k)].f+
		g_Prs[ID(i,j,k-1)].f+g_Prs[ID(i,j,k+1)].f-g_Div[ID(i,j,k)].f)/6;
}
//
//
//
[numthreads(10,10,10)]
void Project3( uint3 id : SV_DispatchThreadID ,uint3 gid : SV_GroupID )
{
	uint i = id.x+1;
	uint j = id.y+1;
	uint k = id.z+1;

	float x=g_rV[uint3(i,j,k)].x-(g_Prs[ID(i+1,j,k)].f-g_Prs[ID(i-1,j,k)].f)/2;
	float y=g_rV[uint3(i,j,k)].y-(g_Prs[ID(i,j+1,k)].f-g_Prs[ID(i,j-1,k)].f)/2;
	float z=g_rV[uint3(i,j,k)].z-(g_Prs[ID(i,j,k+1)].f-g_Prs[ID(i,j,k-1)].f)/2;

	g_wV[uint3(i,j,k)]=float4(x,y,z,0);
}
//
//
//
[numthreads(10,10,10)]
void Project4(uint3 id : SV_DispatchThreadID, uint3 gid : SV_GroupID)
{

}
//
//
//
[numthreads(10,10,10)]
void AdvectVelocity( uint3 id : SV_DispatchThreadID ,uint3 gid : SV_GroupID )
{
	uint i = id.x+1;
	uint j = id.y+1;
	uint k = id.z+1;

	float3 uv=id+1;
	uv.x-=g_rV[uint3(i,j,k)].x*TIME_STEP;
	uv.y-=g_rV[uint3(i,j,k)].y*TIME_STEP;
	uv.z-=g_rV[uint3(i,j,k)].z*TIME_STEP;

	uv=(uv+0.5)/(SIZE+2);
	
	g_wV_s[uint3(i,j,k)]=g_rV.SampleLevel(g_samLinear,uv,0);
}
//
//
//
[numthreads(10,10,10)]
void AdvectBack( uint3 id : SV_DispatchThreadID ,uint3 gid : SV_GroupID )
{
	uint i = id.x+1;
	uint j = id.y+1;
	uint k = id.z+1;

	float3 uv=id+1;
	uv.x+=g_rV[uint3(i,j,k)].x*TIME_STEP;
	uv.y+=g_rV[uint3(i,j,k)].y*TIME_STEP;
	uv.z+=g_rV[uint3(i,j,k)].z*TIME_STEP;

	uv=(uv+0.5)/(SIZE+2);
	
	g_wV_bs[uint3(i,j,k)]=g_rV_s.SampleLevel(g_samLinear,uv,0);
}
//
//
//
[numthreads(10,10,10)]
void MacCormackScheme( uint3 id : SV_DispatchThreadID ,uint3 gid : SV_GroupID )
{
	uint i = id.x+1;
	uint j = id.y+1;
	uint k = id.z+1;

	float4 New=g_rV_s[uint3(i,j,k)]+0.5*(g_rV[uint3(i,j,k)]-g_rV_bs[uint3(i,j,k)]);
	//破綻防止リミッター
	float4 Max=0,Min=0;
	float4 v1=g_rV_s[uint3(i,j,k)];
	float4 v2=g_rV_s[uint3(i+1,j,k)];
	float4 v3=g_rV_s[uint3(i,j+1,k)];
	float4 v4=g_rV_s[uint3(i,j,k+1)];
	float4 v5=g_rV_s[uint3(i-1,j,k)];
	float4 v6=g_rV_s[uint3(i,j-1,k)];
	float4 v7=g_rV_s[uint3(i,j,k-1)];
	float4 v8=g_rV_s[uint3(i+1,j+1,k+1)];

	Max=max(max(max(max(max(max(max(v1,v2),v3),v4),v5),v6),v7),v8);
	Min=min(min(min(min(min(min(min(v1,v2),v3),v4),v5),v6),v7),v8);

	g_wV[uint3(i,j,k)]=max(min(New,Max),Min);
}
//
//
//
[numthreads(10,10,1)]
void Boundary1(uint3 id : SV_DispatchThreadID, uint3 gid : SV_GroupID)
{
	uint i = id.x+1;
	uint j = id.y+1;
	uint k = id.z+1;

	g_wV[uint3(0,i,j)]=float4(-g_rV[uint3(1,i,j)].x,g_rV[uint3(0,i,j)].y,g_rV[uint3(0,i,j)].z,0);
	g_wV[uint3(SIZE,i,j)]=float4(-g_rV[uint3(SIZE-1,i,j)].x,g_rV[uint3(0,i,j)].y,g_rV[uint3(0,i,j)].z,0);

	g_wV[uint3(i,0,j)]=float4(g_rV[uint3(i,0,j)].x,-g_rV[uint3(i,1,j)].y,g_rV[uint3(i,0,j)].z,0);
	g_wV[uint3(i,SIZE,j)]=float4(g_rV[uint3(i,SIZE,j)].x,-g_rV[uint3(i,SIZE-1,j)].y,g_rV[uint3(i,SIZE,j)].z,0);

	g_wV[uint3(i,j,0)]=float4(g_rV[uint3(i,j,0)].x,g_rV[uint3(i,j,0)].y,-g_rV[uint3(i,j,1)].z,0);
	g_wV[uint3(i,j,SIZE)]=float4(g_rV[uint3(i,j,SIZE)].x,g_rV[uint3(i,j,SIZE)].y,-g_rV[uint3(i,j,SIZE-1)].z,0);
}
//
//
//
[numthreads(10,1,1)]
void Boundary2(uint3 id : SV_DispatchThreadID, uint3 gid : SV_GroupID)
{
	//本来は12本のエッジについても判断が必要だが、すでにかなりのコード量なので割愛する
	
	//本来は８つのコーナーについても判断が必要だが、すでにかなりのコード量なので割愛する
}
