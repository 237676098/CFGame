#include "LightHelper.fx"

cbuffer cbPerFrame
{
	DirectionalLight gDirLights[3];
	float3 gEyePosW;
};

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldViewProj;
	float4x4 gWorldInvTranspose;				//世界坐标转换矩阵的逆矩阵的转置矩阵（用来转换法向量）
	float4x4 gTexTransform;
	Material gMaterial;
};

Texture2D gDiffuseMap;

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 9;

	AddressU = wrap;
	AddressV = wrap;

};


RasterizerState NoCull
{
	CullMode = None;
};

struct VertexIn
{
	float3 PosL		:	POSITION;
	float3 NormalL	:	NORMAL;
	float2 Tex		:	TEXCOORD;
};

struct VertexOut
{
	float4 PosH		:	SV_POSITION;
	float3 PosW		:	POSITION;
	float3 NormalW	:	NORMAL;
	float2 Tex      :   TEXCOORD;
};


VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	vout.PosW = mul(float4(vin.PosL, 1.0f), gWorld).xyz;						//世界坐标
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);					//齐次坐标
	//vout.NormalW = mul(float4(vin.PosL, 0.0f), gWorldInvTranspose).xyz			//顶点法向量从本地坐标转换到世界坐标

	vout.NormalW = mul(vin.NormalL, (float3x3)gWorldInvTranspose);				//世界坐标系的法向量
	vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;			//纹理坐标转换
	
	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	//初始颜色
	float4 texColor = gDiffuseMap.Sample(samAnisotropic,pin.Tex);
	//顶点法向量规格化
	pin.NormalW = normalize(pin.NormalW);
	//点到眼的向量 高光模型计算的时候要使用到
	float3 toEye = gEyePosW - pin.PosW;
	float distToEye = length(toEye);
	toEye /= distToEye;



	float4 litColor = texColor;
	//计算三束直射光的光照
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	[unroll]
	for (int i = 0; i < 3; ++i)
	{
		float4 A, D, S;
		ComputeDirectionalLight(gMaterial, gDirLights[i], pin.NormalW, toEye, A, D, S);
		ambient += A;
		diffuse += D;
		spec	+= S;
	}

	litColor = texColor * (ambient + diffuse) + spec;
	litColor.a = gMaterial.Diffuse.a * texColor.a;
	return texColor;
}

technique11 Test
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
		SetRasterizerState(NoCull);
	}
}