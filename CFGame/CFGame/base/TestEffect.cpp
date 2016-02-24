#include "TestEffect.h"

const D3D11_INPUT_ELEMENT_DESC TestEffect::TestInputLayoutDesc[3] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};


ID3D11InputLayout* TestEffect::InputLayout = 0;

TestEffect::TestEffect(ID3D11Device* device, LPCWCHAR filename) :BaseEffect(device,filename)
{
	mTestTech = mFX->GetTechniqueByName("Test");

	mWorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	mWorld = mFX->GetVariableByName("gWorld")->AsMatrix();
	mWorldInvTranspose = mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	mTexTransform = mFX->GetVariableByName("gTexTransform")->AsMatrix();
	//mEyePosW = mFX->GetVariableByName("gEyePosW")->AsVector();
	//mDirLights = mFX->GetVariableByName("gDirLights");
	//mMat = mFX->GetVariableByName("gMaterial");
	mDiffuseMap = mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	mTestTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(TestEffect::TestInputLayoutDesc, 3, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &TestEffect::InputLayout));
}

TestEffect::~TestEffect()
{
}
