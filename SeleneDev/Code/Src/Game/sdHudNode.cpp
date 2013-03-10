#include "Src/Game/sdHudNode.h"

#include "Selene/Render/seGraphics.h"
#include "Selene/Render/seCamera.h"

#include "Selene/Types/seVector2.h"
#include "Selene/Types/seVector3.h"
#include "Selene/Types/seMatrix4.h"

#include "Selene/Utils/seUtils.h"

// for hack
#include "Selene/Resources/seFont.h"
// end hack

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>


SeleneDev::CHudNode::CHudNode(Selene::CGraphics* pGraphics,
							  Selene::CTexture* pTex,
							  Selene::CFont* pFont)
:m_pGraphics(pGraphics)
,m_pTex(pTex)
,m_pFont(pFont)
,m_Pos(-1.5f, -5.0f, -5.0f)
,m_Size(25.0f, 25.0f)
,m_ElapsedTime(0.0f)
,m_Fps(0.0f)
{
}

SeleneDev::CHudNode::~CHudNode()
{
}

void SeleneDev::CHudNode::Render()
{
	Selene::CGraphics::SVertex vertices[4];
	Selene::Color color(1.0f, 1.0f, 1.0f, 1.0f);

	Selene::CCamera* pCam = m_pGraphics->GetActiveCamera();
	Selene::Vector3 camLookDir = pCam->GetLookDir();
	Selene::Vector3 camRightDir = pCam->GetRightDir();
	Selene::Vector3 camUpDir = pCam->GetUpDir();

	vertices[0].m_Color = color;
	vertices[0].m_TexCoords = Selene::Vector2(0.0f, 0.0f);
	vertices[0].m_Coords = -camRightDir * m_Size.x * 0.5f + camUpDir * m_Size.y * 0.5f;
	vertices[0].m_Coords += m_Pos;

	vertices[1].m_Color = color;
	vertices[1].m_TexCoords = Selene::Vector2(1.0f, 0.0f);
	vertices[1].m_Coords = camRightDir * m_Size.x * 0.5f + camUpDir * m_Size.y * 0.5f;
	vertices[1].m_Coords += m_Pos;

	vertices[2].m_Color = color;
	vertices[2].m_TexCoords = Selene::Vector2(1.0f, 1.0f);
	vertices[2].m_Coords = camRightDir * m_Size.x * 0.5f - camUpDir * m_Size.y * 0.5f;
	vertices[2].m_Coords += m_Pos;

	vertices[3].m_Color = color;
	vertices[3].m_TexCoords = Selene::Vector2(0.0f, 1.0f);
	vertices[3].m_Coords = -camRightDir * m_Size.x * 0.5f - camUpDir * m_Size.y * 0.5f;
	vertices[3].m_Coords += m_Pos;


	m_pGraphics->EnableAlphaBlend();
	m_pGraphics->SetAlphaBlendMode(Selene::CGraphics::SBM_SRC_ALPHA,
								   Selene::CGraphics::DBM_ONE_MINUS_DST_ALPHA);
	m_pGraphics->DisableZTest();
	m_pGraphics->DisableZWrite();

	m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_QUADS);
	m_pGraphics->SetTexture(m_pTex);
	// hack
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_pFont->GetTextureID());
	glBegin(Selene::CGraphics::PM_QUADS);
	// end hack
	//m_pGraphics->StartPrimitives();
	m_pGraphics->Draw(vertices, 4);
	m_pGraphics->EndPrimitives();

	// sample text
	const char* sampleText = "Some text and numbers: 34921!";
	const int kBufferLength = 128;
	char buffer[kBufferLength];
	memset(buffer, 0, kBufferLength);
	sprintf(buffer, "%s Fps: %7.2f", sampleText, m_Fps);
	int length = strlen(buffer);

	m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_QUADS);
	m_pGraphics->SetTexture(m_pTex);
	// hack
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_pFont->GetTextureID());
	glBegin(Selene::CGraphics::PM_QUADS);
	// end hack
	//m_pGraphics->StartPrimitives();
	Selene::Vector3 textPos(-23.5f, 15.0f, 12.0f);
	Selene::Vector3 step(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < length; i++)
	{
		const Selene::CFont::SCharData& charData = m_pFont->GetCharData(buffer[i]);

		Selene::Vector2 vCharSize(charData.m_Width / (float) 1024 * m_Size.x,
								  charData.m_Height / (float) 1024 * m_Size.y);
		float startU = charData.m_StartX / (float) 1024;
		float startV = charData.m_StartY / (float) 1024;
		float endU = (charData.m_StartX + charData.m_Width) / (float) 1024;
		float endV = (charData.m_StartY + charData.m_Height) / (float) 1024;

		vertices[0].m_TexCoords = Selene::Vector2(startU, startV);
		vertices[0].m_Coords = -camRightDir * vCharSize.x * 0.5f + camUpDir * vCharSize.y * 0.5f;
		vertices[0].m_Coords += textPos;

		vertices[1].m_TexCoords = Selene::Vector2(endU, startV);
		vertices[1].m_Coords = camRightDir * vCharSize.x * 0.5f + camUpDir * vCharSize.y * 0.5f;
		vertices[1].m_Coords += textPos;

		vertices[2].m_TexCoords = Selene::Vector2(endU, endV);
		vertices[2].m_Coords = camRightDir * vCharSize.x * 0.5f - camUpDir * vCharSize.y * 0.5f;
		vertices[2].m_Coords += textPos;

		vertices[3].m_TexCoords = Selene::Vector2(startU, endV);
		vertices[3].m_Coords = -camRightDir * vCharSize.x * 0.5f - camUpDir * vCharSize.y * 0.5f;
		vertices[3].m_Coords += textPos;

		step.m_X = charData.m_AdvanceX / (float) 1024 * m_Size.x;
		step.m_Y = charData.m_AdvanceY / (float) 1024 * m_Size.y;
		textPos += camRightDir * step.m_X - camUpDir * step.m_Y;

		m_pGraphics->Draw(vertices, 4);
	}
	m_pGraphics->EndPrimitives();

	CSceneNode::Render();
}

void SeleneDev::CHudNode::Update(float deltaTime)
{
	if (deltaTime < 0.00001f)
	{
		return;
	}

	//float pi = 3.141592f;
	m_Fps = 1.0f / deltaTime;
	m_ElapsedTime += deltaTime;
}
