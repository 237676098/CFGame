#pragma once

#include "d3dUtil.h"
//相机类

class Camera
{
public:
	Camera();
	~Camera();

	XMVECTOR GetPositionXM() const;
	XMFLOAT3 GetPosition() const;
	void SetPosition(const XMFLOAT3 &pos);
	void SetPosition(float x,float y,float z);

	XMVECTOR GetRightXM() const;
	XMFLOAT3 GetRight() const;
	XMVECTOR GetUpXM() const;
	XMFLOAT3 GetUp() const;
	XMVECTOR GetLookXM() const;
	XMFLOAT3 GetLook() const;

	float GetNearZ() const;
	float GetFarZ() const;
	float GetAspect() const;
	float GetFovY() const;
	float GetFovX() const;

	// Get near and far plane dimensions in view space coordinates.
	float GetNearWindowWidth()const;
	float GetNearWindowHeight()const;
	float GetFarWindowWidth()const;
	float GetFarWindowHeight()const;

	void SetLens(float fovY, float aspect, float zn, float zf);

	void LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp);
	void LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& worldUp);

	XMMATRIX View() const;
	XMMATRIX Proj() const;
	XMMATRIX ViewProj() const;

	void UpdateViewMatrix();

	void Strafe(float d);
	void Walk(float d);
	void Pitch(float angle);
	void RotateY(float angle);

private:
	//视图坐标相对于世界坐标系的元素(决定了摄像机的位置)
	XMFLOAT3 mPosition;
	XMFLOAT3 mRight;
	XMFLOAT3 mUp;
	XMFLOAT3 mLook;

	//缓存半截头体(决定了要进行渲染的那个半截头体的范围)
	float mNearZ;			
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	//根据上述元素计算出视图矩阵和投影矩阵
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
};
