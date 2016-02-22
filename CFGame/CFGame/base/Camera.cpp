#include "Camera.h"

Camera::Camera()
	:mPosition(0.0f,0.0f,0.0f),
	mRight(1.0f,0.0f,0.0f),
	mUp(0.0f, 1.0f, 0.0f),
	mLook(0.0f,0.0f,1.0f)
{
	SetLens(0.25f * MathHelper::Pi, 1.0f, 1.0f, 1000.0f);
}


Camera::~Camera()
{
}


void Camera::SetLens(float fov, float aspect, float nearz, float farz)
{
	mFovY = fov;
	mAspect = aspect;
	mNearZ = nearz;
	mFarZ = farz;

	mNearWindowHeight = 2.0f * mNearZ * tanf(0.5f*mFovY);
	mFarWindowHeight = 2.0f * mFarZ * tanf(0.5f*mFovY);

	XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
	XMStoreFloat4x4(&mProj, P);
}

