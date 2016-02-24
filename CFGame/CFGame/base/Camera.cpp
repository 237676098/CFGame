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

XMVECTOR Camera::GetPositionXM() const
{
	return XMLoadFloat3(&mPosition);
}

XMFLOAT3 Camera::GetPosition() const
{
	return mPosition;
}

void Camera::SetPosition(float x, float y, float z)
{
	mPosition = XMFLOAT3(x, y, z);
}

void Camera::SetPosition(const XMFLOAT3 &pos)
{
	mPosition = pos;
}

XMVECTOR Camera::GetRightXM() const
{
	return XMLoadFloat3(&mRight);
}

XMFLOAT3 Camera::GetRight() const
{
	return mRight;
}

XMVECTOR Camera::GetUpXM()const
{
	return XMLoadFloat3(&mUp);
}

XMFLOAT3 Camera::GetUp() const
{
	return mUp;
}

XMVECTOR Camera::GetLookXM() const
{
	return XMLoadFloat3(&mLook);
}

XMFLOAT3 Camera::GetLook() const
{
	return mLook;
}

float Camera::GetNearZ()const
{
	return mNearZ;
}

float Camera::GetFarZ()const
{
	return mFarZ;
}

float Camera::GetAspect()const
{
	return mAspect;
}

float Camera::GetFovY()const
{
	return mFovY;
}

float Camera::GetFovX()const
{
	float halfWidth = 0.5f*GetNearWindowWidth();
	return 2.0f*atan(halfWidth / mNearZ);
}

float Camera::GetNearWindowWidth()const
{
	return mAspect * mNearWindowHeight;
}

float Camera::GetNearWindowHeight()const
{
	return mNearWindowHeight;
}

float Camera::GetFarWindowWidth()const
{
	return mAspect * mFarWindowHeight;
}

float Camera::GetFarWindowHeight()const
{
	return mFarWindowHeight;
}

void Camera::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
{
	XMVECTOR L = XMVector4Normalize(XMVectorSubtract(target, pos));
	XMVECTOR R = XMVector4Normalize(XMVector3Cross(L, worldUp));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&mPosition, pos);
	XMStoreFloat3(&mLook, L);
	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
}

void Camera::LookAt(const XMFLOAT3 &pos, const XMFLOAT3 &target, const XMFLOAT3 &up)
{
	XMVECTOR P = XMLoadFloat3(&pos);
	XMVECTOR T = XMLoadFloat3(&target);
	XMVECTOR U = XMLoadFloat3(&up);

	LookAt(P, T, U);
}


void Camera::UpdateViewMatrix()
{
	//此处省略了对三个方向向量的规格化

	float x = -XMVectorGetX(XMVector3Dot(XMLoadFloat3(&mPosition), XMLoadFloat3(&mRight)));
	float y = -XMVectorGetX(XMVector3Dot(XMLoadFloat3(&mPosition), XMLoadFloat3(&mUp)));
	float z = -XMVectorGetX(XMVector3Dot(XMLoadFloat3(&mPosition), XMLoadFloat3(&mLook)));
	
	mView(0, 0) = mRight.x;
	mView(1, 0) = mRight.y;
	mView(2, 0) = mRight.z;
	mView(3, 0) = x;

	mView(0, 1) = mUp.x;
	mView(1, 1) = mUp.y;
	mView(2, 1) = mUp.z;
	mView(3, 1) = y;

	mView(0, 1) = mLook.x;
	mView(1, 1) = mLook.y;
	mView(2, 1) = mLook.z;
	mView(3, 1) = z;

	mView(0, 1) = 0;
	mView(1, 1) = 0;
	mView(2, 1) = 0;
	mView(3, 1) = 1;
}

XMMATRIX Camera::View() const
{
	return XMLoadFloat4x4(&mView);
}

XMMATRIX Camera::Proj() const
{
	return XMLoadFloat4x4(&mProj);
}

XMMATRIX Camera::ViewProj() const
{
	return XMMatrixMultiply(View(),Proj());
}

// mPosition += d*mRight
void Camera::Strafe(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&mRight);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s,r,p));
}

// mPosition += d*mLook
void Camera::Walk(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat3(&mLook);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, l, p));
}

// Rotate up and look vector about the right vector.
void Camera::Pitch(float angle)
{
	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&mRight),angle);

	XMStoreFloat3(&mUp, XMVector2TransformNormal(XMLoadFloat3(&mUp),R));
	XMStoreFloat3(&mLook, XMVector2TransformNormal(XMLoadFloat3(&mLook), R));
}

// Rotate the basis vectors about the world y-axis.
void Camera::RotateY(float angle)
{
	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&mUp), angle);

	XMStoreFloat3(&mRight, XMVector2TransformNormal(XMLoadFloat3(&mRight), R));
	XMStoreFloat3(&mLook, XMVector2TransformNormal(XMLoadFloat3(&mLook), R));
}

