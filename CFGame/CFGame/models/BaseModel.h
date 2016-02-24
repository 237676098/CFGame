#pragma once
#include "d3dUtil.h"
#include "BaseEffect.h"
#include "Camera.h"

class BaseModel
{
public:
	BaseModel();
	~BaseModel();

protected:
	virtual void Init(ID3D11Device* device);
	virtual void Draw(ID3D11DeviceContext* context, BaseEffect* effect,Camera* Camera) = 0;

};