#ifndef SD_FPS_NODE_H
#define SD_FPS_NODE_H

#include "Selene/Render/seSceneNode.h"
#include "Selene/Types/seVector2.h"
#include "Selene/Types/seVector3.h"

namespace Selene
{
	class CGraphics;
	class CTexture;
}

namespace SeleneDev
{

	class CFpsNode : public Selene::CSceneNode
	{
	public:
		CFpsNode(Selene::CGraphics* pGraphics,
				 Selene::CTexture* pDialTex);
		virtual ~CFpsNode();

		virtual void Render();

		void Update(float deltaTime);

	private:
		struct SFpsSample
		{
			float m_Fps;
			float m_TimeStamp;
		};

	private:
		float m_HandAngle;
		Selene::CGraphics* m_pGraphics;
		Selene::CTexture* m_pDialTex;
		Selene::Vector3 m_DialPos;
		Selene::Vector2 m_DialSize;
		float m_ElapsedTime;
		float m_CheckTime;
		static const int k_SampleCount = 100;
		SFpsSample m_Samples[k_SampleCount];
	};

} // namespace SeleneDev

#endif // SD_FPS_NODE_H
