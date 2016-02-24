#pragma once
#include "d3dUtil.h"
class BaseEffect
{
public:
	BaseEffect(ID3D11Device* device, LPCWCHAR filename);
	virtual ~BaseEffect();

protected:
	ID3DX11Effect* mFX;
};