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
	float4x4 gWorldInvTranspose;				//��������ת�������������ת�þ�������ת����������
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

	vout.PosW = mul(float4(vin.PosL, 1.0f), gWorld).xyz;						//��������
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);					//�������
	//vout.NormalW = mul(float4(vin.PosL, 0.0f), gWorldInvTranspose).xyz			//���㷨�����ӱ�������ת������������

	vout.NormalW = mul(vin.NormalL, (float3x3)gWorldInvTranspose);				//��������ϵ�ķ�����
	vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;			//��������ת��
	
	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	//��ʼ��ɫ
	float4 texColor = gDiffuseMap.Sample(samAnisotropic,pin.Tex);
	//���㷨�������
	pin.NormalW = normalize(pin.NormalW);
	//�㵽�۵����� �߹�ģ�ͼ����ʱ��Ҫʹ�õ�
	float3 toEye = gEyePosW - pin.PosW;
	float distToEye = length(toEye);
	toEye /= distToEye;



	float4 litColor = texColor;
	//��������ֱ���Ĺ���
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