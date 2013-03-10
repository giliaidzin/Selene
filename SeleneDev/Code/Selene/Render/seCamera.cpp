#include "Selene/Render/seCamera.h"

#include "Selene/Utils/seUtils.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

Selene::CCamera::CCamera()
:m_Pos(0.0f, 0.0f, 0.0f)
,m_LookAt(0.0f, 0.0f, -1.0f)
,m_Up(0.0f, 1.0f, 0.0f)
,m_LookDir(0.0f, 0.0f, -1.0f)
,m_RightDir(-1.0f, 0.0f, 0.0f)
,m_UpDir(0.0f, 1.0f, 0.0f)
,m_Fov(45.0f)
,m_AspectRatio(1.0f)
,m_NearPlane(1.0f)
,m_FarPlane(100.0f)
{
}

Selene::CCamera::~CCamera()
{
}

bool Selene::CCamera::Init()
{
	return true;
}

void Selene::CCamera::SetPos(const Vector3& pos)
{
	m_Pos = pos;
	CalcMatrices();
}

void Selene::CCamera::SetLookAt(const Vector3& lookAt)
{
	m_LookAt = lookAt;
	CalcMatrices();
}

void Selene::CCamera::SetUp(const Vector3& up)
{
	m_Up = up;
	CalcMatrices();
}

void Selene::CCamera::Look(const Vector3& pos, const Vector3& lookAt, const Vector3& up)
{
	m_Pos = pos;
	m_LookAt = lookAt;
	m_Up = up;
	CalcMatrices();
}

void Selene::CCamera::SetFov(float fov)
{
	m_Fov = fov;
}

void Selene::CCamera::SetAspectRatio(float aspectRatio)
{
	m_AspectRatio = aspectRatio;
}

void Selene::CCamera::SetNearPlane(float nearPlane)
{
	m_NearPlane = nearPlane;
}

void Selene::CCamera::SetFarPlane(float farPlane)
{
	m_FarPlane = farPlane;
}

Selene::Vector3 Selene::CCamera::GetPos() const
{
	return m_Pos;
}

Selene::Vector3 Selene::CCamera::GetLookAt() const
{
	return m_LookAt;
}

Selene::Vector3 Selene::CCamera::GetUp() const
{
	return m_Up;
}

float Selene::CCamera::GetFov() const
{
	return m_Fov;
}

float Selene::CCamera::GetAspectRatio() const
{
	return m_AspectRatio;
}

float Selene::CCamera::GetNearPlane() const
{
	return m_NearPlane;
}

float Selene::CCamera::GetFarPlane() const
{
	return m_FarPlane;
}

Selene::Matrix4 Selene::CCamera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

Selene::Vector3 Selene::CCamera::GetLookDir() const
{
	return m_LookDir;
}

Selene::Vector3 Selene::CCamera::GetRightDir() const
{
	return m_RightDir;
}

Selene::Vector3 Selene::CCamera::GetUpDir() const
{
	return m_UpDir;
}

void Selene::CCamera::CalcMatrices()
{
	m_LookDir = m_LookAt - m_Pos;
	m_LookDir *= -1.0f;
	m_LookDir.Normalize();
	m_RightDir = m_Up.Cross(m_LookDir);
	//m_RightDir *= -1.0f;
	m_RightDir.Normalize();
	m_UpDir = m_LookDir.Cross(m_RightDir);
	//m_UpDir *= -1.0f;
	m_UpDir.Normalize();

	Matrix4 rotationMatrix;
	//rotationMatrix.m[0][0] = m_RightDir.m_X;
	//rotationMatrix.m[0][1] = m_RightDir.m_Y;
	//rotationMatrix.m[0][2] = m_RightDir.m_Z;
	//rotationMatrix.m[0][3] = 0.0f;

	//rotationMatrix.m[1][0] = m_UpDir.m_X;
	//rotationMatrix.m[1][1] = m_UpDir.m_Y;
	//rotationMatrix.m[1][2] = m_UpDir.m_Z;
	//rotationMatrix.m[1][3] = 0.0f;

	//rotationMatrix.m[2][0] = m_LookDir.m_X;
	//rotationMatrix.m[2][1] = m_LookDir.m_Y;
	//rotationMatrix.m[2][2] = m_LookDir.m_Z;
	//rotationMatrix.m[2][3] = 0.0f;

	//rotationMatrix.m[3][0] = 0.0f;
	//rotationMatrix.m[3][1] = 0.0f;
	//rotationMatrix.m[3][2] = 0.0f;
	//rotationMatrix.m[3][3] = 1.0f;

	//rotationMatrix.Transpose();

	rotationMatrix.m[0][0] = m_RightDir.m_X;
	rotationMatrix.m[0][1] = m_UpDir.m_X;
	rotationMatrix.m[0][2] = m_LookDir.m_X;
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = m_RightDir.m_Y;
	rotationMatrix.m[1][1] = m_UpDir.m_Y;
	rotationMatrix.m[1][2] = m_LookDir.m_Y;
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = m_RightDir.m_Z;
	rotationMatrix.m[2][1] = m_UpDir.m_Z;
	rotationMatrix.m[2][2] = m_LookDir.m_Z;
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	Matrix4 translationMatrix;
	translationMatrix.m[0][0] = 1.0f;
	translationMatrix.m[0][1] = 0.0f;
	translationMatrix.m[0][2] = 0.0f;
	translationMatrix.m[0][3] = 0.0f;

	translationMatrix.m[1][0] = 0.0f;
	translationMatrix.m[1][1] = 1.0f;
	translationMatrix.m[1][2] = 0.0f;
	translationMatrix.m[1][3] = 0.0f;

	translationMatrix.m[2][0] = 0.0f;
	translationMatrix.m[2][1] = 0.0f;
	translationMatrix.m[2][2] = 1.0f;
	translationMatrix.m[2][3] = 0.0f;

	translationMatrix.m[3][0] = -m_Pos.m_X;
	translationMatrix.m[3][1] = -m_Pos.m_Y;
	translationMatrix.m[3][2] = -m_Pos.m_Z;
	translationMatrix.m[3][3] = 1.0f;

	//translationMatrix.Transpose();

	//rotationMatrix = Matrix4();
	//translationMatrix = Matrix4();
	m_ViewMatrix = translationMatrix * rotationMatrix;
	//m_ViewMatrix = rotationMatrix * translationMatrix;
	//m_ViewMatrix.Transpose();
}
