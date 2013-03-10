#ifndef SE_CAMERA_H
#define SE_CAMERA_H

#include "Selene/Types/seVector3.h"
#include "Selene/Types/seMatrix4.h"

namespace Selene
{

	class CCamera
	{
	public:
		CCamera();
		~CCamera();

		bool Init();

		void SetPos(const Vector3& pos);
		void SetLookAt(const Vector3& lookAt);
		void SetUp(const Vector3& up);
		void SetFov(float fov);
		void SetAspectRatio(float aspectRatio);
		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);

		Vector3 GetPos() const;
		Vector3 GetLookAt() const;
		Vector3 GetUp() const;
		float GetFov() const;
		float GetAspectRatio() const;
		float GetNearPlane() const;
		float GetFarPlane() const;

		Matrix4 GetViewMatrix() const;

		Vector3 GetLookDir() const;
		Vector3 GetRightDir() const;
		Vector3 GetUpDir() const;

		void Look(const Vector3& pos, const Vector3& lookAt, const Vector3& up);

	private:
		void CalcMatrices();

	private:
		Matrix4 m_ViewMatrix;
		Vector3 m_Pos;
		Vector3 m_LookAt;
		Vector3 m_Up;
		Vector3 m_LookDir;
		Vector3 m_RightDir;
		Vector3 m_UpDir;
		float m_Fov;
		float m_AspectRatio;
		float m_NearPlane;
		float m_FarPlane;

	};
}

#endif // SE_CAMERA_H
