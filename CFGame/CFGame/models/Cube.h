#pragma once
#include "BaseModel.h"
#include "LightHelper.h"

class Cube :public BaseModel
{
public:
	Cube();
	~Cube();

	void Init(ID3D11Device* device);

public:
	void Draw(ID3D11DeviceContext* context, BaseEffect* effect, Camera* Camera, DirectionalLight* lightArr, XMFLOAT3& eyePos);

private:
	ID3D11Buffer* mVB;			
	ID3D11Buffer* mIB;

	int mIndexCount;

	ID3D11ShaderResourceView* mTex;
	XMFLOAT4X4 mWorld;
	Material mMat;

	XMFLOAT4X4 mTexTran;

};