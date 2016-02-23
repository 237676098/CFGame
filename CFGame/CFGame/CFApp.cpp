#include "CFApp.h"


CFApp::CFApp(HINSTANCE instance) :D3DApp(instance), mEffectTest(NULL)
{

}

CFApp::~CFApp()
{
}


bool CFApp::Init()
{
	if (!D3DApp::Init())
	{
		return false;
	}

	mEffectTest = new TestEffect(md3dDevice, L"fx / Basic.fx");

	return true;
}

void CFApp::UpdateScene(float dt)
{

}

void CFApp::DrawScene()
{

}

void CFApp::OnResize()
{
	D3DApp::OnResize();
}

void CFApp::OnMouseDown(WPARAM btnState, int x, int y)
{

}

void CFApp::OnMouseUp(WPARAM btnState, int x, int y)
{

}

void CFApp::OnMouseMove(WPARAM btnState, int x, int y)
{

}