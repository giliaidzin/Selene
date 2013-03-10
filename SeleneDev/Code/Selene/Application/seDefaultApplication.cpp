// Selene default application
#include "Selene/Application/seDefaultApplication.h"
#include "Selene/Application/seSupervisor.h"

#include "Selene/Utils/seUtils.h"
#include "Selene/Types/seVector2.h"


Selene::CDefaultApplication::CDefaultApplication()
{
	m_bShouldQuit = false;
}

Selene::CDefaultApplication::~CDefaultApplication()
{
}

void Selene::CDefaultApplication::ParseCommandLine(int iArgC, char* astrArgV[])
{
}

void Selene::CDefaultApplication::Init()
{
}

void Selene::CDefaultApplication::Terminate()
{
}

void Selene::CDefaultApplication::Update(float fDeltaTime)
{
	//m_bShouldQuit = elfKeyboard_IsKeyPressed(ElfKey_Escape);
}

void Selene::CDefaultApplication::Render(float fDeltaTime)
{
	Vector2 vSize(200.0f, 200.0f);
	Vector2 vPos(400.0f, 300.0f);

	float afCoords[8] = 
	{
		-vSize.x * 0.5f, -vSize.y * 0.5f,
		vSize.x * 0.5f, -vSize.y * 0.5f,
		vSize.x * 0.5f, vSize.y * 0.5f,
		-vSize.x * 0.5f, vSize.y * 0.5f,
	};

//	elfQuads_begin();
//	// format - argb
//	elfQuads_setColour(0xffff4080);
////	elfQuads_setTextureRectangle(0.0f, 0.0f, 1.0f, 1.0f);
////	elfQuads_drawRectangleCentered(m_fPosX, m_fPosY, m_fSizeWidth, m_fSizeHeight);
//	//elfQuads_drawRectangle(fStartX, fStartY, fEndX, fEndY);
//	elfQuads_drawShapeOffset(vPos.x, vPos.y, afCoords);
//	elfQuads_end();
}

bool Selene::CDefaultApplication::ShouldQuit()
{
	return m_bShouldQuit;
}
