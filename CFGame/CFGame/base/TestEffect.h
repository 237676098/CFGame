#pragma once
#include "BaseEffect.h"

class TestEffect:public BaseEffect
{
public:
	TestEffect(ID3D11Device* device, LPCWCHAR filename);
	~TestEffect();

	void SetWorldViewProj(CXMMATRIX M)                  { mWorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { mWorld->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { mWorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { mTexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	//void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	//void SetDirLights(const DirectionalLight* lights)   { DirLights->SetRawValue(lights, 0, 3 * sizeof(DirectionalLight)); }
	//void SetMaterial(const Material& mat)               { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetDiffuseMap(ID3D11ShaderResourceView* tex)   { DiffuseMap->SetResource(tex); }


private:
	ID3DX11EffectTechnique* TestTech;

	ID3DX11EffectMatrixVariable* mWorldViewProj;
	ID3DX11EffectMatrixVariable* mWorld;
	ID3DX11EffectMatrixVariable* mWorldInvTranspose;
	ID3DX11EffectMatrixVariable* mTexTransform;
	//ID3DX11EffectVectorVariable* EyePosW;
	//ID3DX11EffectVariable* DirLights;
	//ID3DX11EffectVariable* Mat;

	ID3DX11EffectShaderResourceVariable* DiffuseMap;

};
