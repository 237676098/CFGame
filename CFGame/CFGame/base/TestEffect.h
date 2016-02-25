#pragma once
#include "BaseEffect.h"

namespace Vertex
{
	struct TestVertex
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Tex;
	};
}

class TestEffect:public BaseEffect
{
public:
	
	static const D3D11_INPUT_ELEMENT_DESC TestInputLayoutDesc[3];

	TestEffect(ID3D11Device* device, LPCWCHAR filename);
	~TestEffect();

	ID3DX11EffectTechnique* getTestTech()				{ return mTestTech; }

	void SetWorldViewProj(CXMMATRIX M)                  { mWorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { mWorld->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { mWorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { mTexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { mEyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetDirLights(const DirectionalLight* lights)   { mDirLights->SetRawValue(lights, 0, 3 * sizeof(mDirLights)); }
	void SetMaterial(const Material& mat)               { mMat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { mDiffuseMap->SetResource(tex); }

	static ID3D11InputLayout* InputLayout;

private:
	ID3DX11EffectTechnique* mTestTech;

	ID3DX11EffectMatrixVariable* mWorldViewProj;
	ID3DX11EffectMatrixVariable* mWorld;
	ID3DX11EffectMatrixVariable* mWorldInvTranspose;
	ID3DX11EffectMatrixVariable* mTexTransform;
	ID3DX11EffectVectorVariable* mEyePosW;
	ID3DX11EffectVariable* mDirLights;
	ID3DX11EffectVariable* mMat;

	ID3DX11EffectShaderResourceVariable* mDiffuseMap;

};
