#pragma once

#include "d3dUtil.h"
//�����

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
	//��ͼ�����������������ϵ��Ԫ��(�������������λ��)
	XMFLOAT3 mPosition;
	XMFLOAT3 mRight;
	XMFLOAT3 mUp;
	XMFLOAT3 mLook;

	//������ͷ��(������Ҫ������Ⱦ���Ǹ����ͷ��ķ�Χ)
	float mNearZ;			
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	//��������Ԫ�ؼ������ͼ�����ͶӰ����
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProj;
};
