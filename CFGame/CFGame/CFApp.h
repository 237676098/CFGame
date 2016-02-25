#pragma once
#include "D3DApp.h"
#include "TestEffect.h"
#include "Cube.h"
#include "Camera.h"

class CFApp : public D3DApp
{
public:
	CFApp(HINSTANCE instance);
	~CFApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);


private:
	TestEffect* mEffectTest;
	Cube* mCube;
	Camera mCam;
	POINT mLastMousePos;
	DirectionalLight mDirLights[3];
};
