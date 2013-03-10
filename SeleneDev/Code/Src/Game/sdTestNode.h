#ifndef SD_TEST_NODE_H
#define SD_TEST_NODE_H

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

	class CTestNode : public Selene::CSceneNode
	{
	public:
		CTestNode(Selene::CGraphics* pGraphics,
				  Selene::CTexture* pBoxTex,
				  Selene::CTexture* pMoonTex,
				  Selene::CTexture* pSquaresTex,
				  Selene::CFont* pFont);
		virtual ~CTestNode();

		virtual void Render();

		void Update(float deltaTime);

	private:
		float m_TriangleAngle;
		float m_QuadAngle;
		Selene::CGraphics* m_pGraphics;
		Selene::CTexture* m_pBoxTex;
		Selene::CTexture* m_pMoonTex;
		Selene::CTexture* m_pSquaresTex;
		Selene::CFont* m_pFont;
		Selene::Vector3 m_MoonPos;
		Selene::Vector3 m_BoxPos;
		Selene::Vector3 m_SquaresPos;
	};

} // namespace SeleneDev

#endif // SD_TEST_NODE_H
