#include "CFApp.h"


CFApp::CFApp(HINSTANCE instance) :D3DApp(instance), mEffectTest(NULL)
{
	//mCam.SetPosition(0.0f, 0.0f, -200.0f);
	XMFLOAT3 pos = XMFLOAT3(0.0f, 0.0f, -200.0f);
	XMFLOAT3 target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	mCam.LookAt(pos, target, up);
}

CFApp::~CFApp()
{
	delete mEffectTest;
	delete mCube;
}


bool CFApp::Init()
{
	if (!D3DApp::Init())
	{
		return false;
	}

	mEffectTest = new TestEffect(md3dDevice, L"fx/Basic.fx");
	
	//初始化立方体
	mCube = new Cube();
	mCube->Init(md3dDevice);


	return true;
}

void CFApp::UpdateScene(float dt)
{
	//
	// Control the camera.
	//
	if (GetAsyncKeyState('W') & 0x8000)
		mCam.Walk(100.0f*dt);

	if (GetAsyncKeyState('S') & 0x8000)
		mCam.Walk(-100.0f*dt);

	if (GetAsyncKeyState('A') & 0x8000)
		mCam.Strafe(-100.0f*dt);

	if (GetAsyncKeyState('D') & 0x8000)
		mCam.Strafe(100.0f*dt);
}

void CFApp::DrawScene()
{

	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Silver));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	mCam.UpdateViewMatrix();

	mCube->Draw(md3dImmediateContext, mEffectTest,&mCam);
	HR(mSwapChain->Present(0, 0));
}

void CFApp::OnResize()
{
	D3DApp::OnResize();
	mCam.SetLens(0.5 * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
}

void CFApp::OnMouseDown(WPARAM btnState, int x, int y)
{

}

void CFApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void CFApp::OnMouseMove(WPARAM btnState, int x, int y)
{

}
