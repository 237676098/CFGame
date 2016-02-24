

cbuffer cbPerFrame
{

};

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldViewProj;
	float4x4 gWorldInvTranspose;				//��������ת�������������ת�þ�������ת����������
	float4x4 gTexTransform;
	//Material gMaterial;
};

Texture2D gDiffuseMap;

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 9;

	AddressU = wrap;
	AddressV = wrap;

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
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);				//�������
	//vout.NormalW = mul(vin.NormalL, (float3x3)gWorldInvTranspose);		//��������ϵ�ķ�����
	//vout.Tex = vin.Tex;

	vout.NormalW = float3(1.0f, 0.0f,0.0f);
	vout.Tex = float2(1.0f, 0.0f);
	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	//float texColor = gDiffuseMap.Sample(samAnisotropic, pin.Tex);

	//return texColor;
	return float4(1.0f,1.0f,0.0f,1.0f);
}

technique11 Test
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}