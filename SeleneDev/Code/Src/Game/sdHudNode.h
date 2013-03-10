#ifndef SD_HUD_NODE_H
#define SD_HUD_NODE_H

#include "Selene/Render/seSceneNode.h"
#include "Selene/Types/seVector2.h"
#include "Selene/Types/seVector3.h"

namespace Selene
{
	class CGraphics;
	class CTexture;
	class CFont;
}

namespace SeleneDev
{

	class CHudNode : public Selene::CSceneNode
	{
	public:
		CHudNode(Selene::CGraphics* pGraphics,
				 Selene::CTexture* pTex,
				 Selene::CFont* pFont);
		virtual ~CHudNode();

		virtual void Render();

		void Update(float deltaTime);

	private:
		Selene::CGraphics* m_pGraphics;
		Selene::CFont* m_pFont;
		Selene::CTexture* m_pTex;
		Selene::Vector3 m_Pos;
		Selene::Vector2 m_Size;
		float m_ElapsedTime;
		float m_Fps;
	};

} // namespace SeleneDev

#endif // SD_HUD_NODE_H
