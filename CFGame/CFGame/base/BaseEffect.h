#pragma once
#include "d3dUtil.h"
class BaseEffect
{
public:
	BaseEffect(ID3D11Device* device, LPCWCHAR filename);
	virtual ~BaseEffect();

private:
	ID3DX11Effect* mFX;
	ID3DX11EffectTechnique* mTech;
};