#include "CFApp.h"


CFApp::CFApp(HINSTANCE instance) :D3DApp(instance), mEffectTest(NULL)
{
	mMainWndCaption = L"CFGame";

	mClientWidth = 800;
	mClientHeight = 600;
	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	//mCam.SetPosition(0.0f, 0.0f, -200.0f);
	XMFLOAT3 pos = XMFLOAT3(0.0f, 0.0f, -200.0f);
	XMFLOAT3 target = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	mCam.LookAt(pos, target, up);


	//初始化三束直射光
	mDirLights[0].Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLights[0].Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLights[0].Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mDirLights[0].Direction = XMFLOAT3(0.57735f, -0.57735f, 0.57735f);

	mDirLights[1].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[1].Diffuse = XMFLOAT4(0.20f, 0.20f, 0.20f, 1.0f);
	mDirLights[1].Specular = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
	mDirLights[1].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);

	mDirLights[2].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[2].Diffuse = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLights[2].Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[2].Direction = XMFLOAT3(0.0f, -0.707f, -0.707f);
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

	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Black));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	mCam.UpdateViewMatrix();

	mCube->Draw(md3dImmediateContext, mEffectTest,&mCam,mDirLights,mCam.GetPosition());
	HR(mSwapChain->Present(0, 0));
}

void CFApp::OnResize()
{
	D3DApp::OnResize();
	mCam.SetLens(0.5 * MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
}

void CFApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void CFApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void CFApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		mCam.Pitch(dy);
		mCam.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}
