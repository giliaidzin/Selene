#include <math.h>

#include "Src/Game/sdGame.h"
#include "Src/Game/sdTestNode.h"
#include "Src/Game/sdFpsNode.h"
#include "Src/Game/sdHudNode.h"

#include "Selene/3rdParty/FreeType/include/ft2build.h"
#include FT_FREETYPE_H

#include "Selene/Render/seGraphics.h"
#include "Selene/Render/seCamera.h"

#include "Selene/Application/seSupervisor.h"

#include "Selene/Resources/seTexture.h"
#include "Selene/Resources/seFont.h"
#include "Selene/Resources/seResourceManager.h"
#include "Selene/Resources/seVirtualFileSystem.h"

#include "Selene/Utils/seUtils.h"


SeleneDev::CGame::CGame()
{
	m_pTestNode = NULL;
	m_pFpsNode = NULL;
	m_pHudNode = NULL;
	m_ElapsedTime = 0.0f;
}

SeleneDev::CGame::~CGame()
{
}

void SeleneDev::CGame::Init()
{
	Selene::CVirtualFileSystem* pVfs = GetSupervisor()->GetVFS();
	Selene::CGraphics* pGraphics = GetSupervisor()->GetGraphics();
	Selene::CResourceManager* pResMan = GetSupervisor()->GetResMan();

	Selene::CVirtualFile* pFile = pVfs->Open("/Data/Moon.sir");
	Selene::CTexture* pMoonTex = new Selene::CTexture("MoonTex");
	pMoonTex->SetFile(pFile);
	pMoonTex->Load();
	pVfs->Close(pFile);

	pFile = pVfs->Open("/Data/Squares.sir");
	Selene::CTexture* pSquaresTex = new Selene::CTexture("SquaresTex");
	pSquaresTex->SetFile(pFile);
	pSquaresTex->Load();
	pVfs->Close(pFile);

	pFile = pVfs->Open("/Data/Dials.sir");
	Selene::CTexture* pDialTex = new Selene::CTexture("DialTex");
	pDialTex->SetFile(pFile);
	pDialTex->Load();
	pVfs->Close(pFile);

	//pFile = pVfs->Open("/Data/arial.ttf");
	//pFile = pVfs->Open("/Data/cour.ttf");
	//pFile = pVfs->Open("/Data/MyriadPro-Regular.otf");
	pFile = pVfs->Open("/Data/msmincho.ttc");

	Selene::CFont* pFont = new Selene::CFont("TestFont");
	pFont->SetFile(pFile);
	pFont->SetFontLibrary(pResMan->GetFontLibrary());
	pFont->Load();
	pVfs->Close(pFile);

	//STextureData boxTexData;
	//boxTexData.m_Width = 256;
	//boxTexData.m_Height = 256;
	//boxTexData.m_pData = NULL;
	//boxTexData.m_pData = new unsigned char[boxTexData.m_Width * boxTexData.m_Height * 4];
	//const float kPi = 3.14159265358979323846f;
	//for (int i=0; i<boxTexData.m_Width; i++)
	//{
	//	for (int j=0; j<boxTexData.m_Height; j++)
	//	{
	//		float periodCount = 2.0f;
	//		float phase = sinf(periodCount * 2.0f * kPi * (float) i/(float) boxTexData.m_Width);
	//		float amplitude = 32.0f;
	//		float boundary = amplitude * phase + boxTexData.m_Height * 0.5f;
	//		boxTexData.m_pData[i * boxTexData.m_Width * 4 + j * 4 + 0] = (float) j < boundary ? 32 : 255;
	//		boxTexData.m_pData[i * boxTexData.m_Width * 4 + j * 4 + 1] = 128;
	//		boxTexData.m_pData[i * boxTexData.m_Width * 4 + j * 4 + 2] = 128;
	//		boxTexData.m_pData[i * boxTexData.m_Width * 4 + j * 4 + 3] = 255;
	//	}
	//}
	//glGenTextures(1, &boxTextureID);
	//glBindTexture(GL_TEXTURE_2D, boxTextureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3,
	//			 boxTexData.m_Width, boxTexData.m_Height,
	//			 0, GL_RGBA, GL_UNSIGNED_BYTE,
	//			 boxTexData.m_pData);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//SAFE_DELETE(boxTexData.m_pData);

	m_pTestNode = new CTestNode(pGraphics, pMoonTex, pMoonTex, pSquaresTex, pFont);
	GetSupervisor()->GetGameRoot()->AddChild(m_pTestNode);

	m_pFpsNode = new CFpsNode(pGraphics, pDialTex);
	GetSupervisor()->GetGameRoot()->AddChild(m_pFpsNode);

	m_pHudNode = new CHudNode(pGraphics, pDialTex, pFont);
	GetSupervisor()->GetGameRoot()->AddChild(m_pHudNode);

	//pGraphics->GetActiveCamera()->SetPos(Selene::Vector3(1.0f, 2.0, 5.0f));
	pGraphics->GetActiveCamera()->SetPos(Selene::Vector3(13.0f, 5.0, 4.0f));
	pGraphics->GetActiveCamera()->SetLookAt(Selene::Vector3(-1.5f, 1.0f, -5.0f));
	//pGraphics->GetActiveCamera()->SetUp(Selene::Vector3(0.0f, 1.0, 0.0f));

	pGraphics->EnableAlphaBlend();

	m_ElapsedTime = 0.0f;
}

void SeleneDev::CGame::Terminate()
{
	SAFE_DELETE(m_pHudNode);
	SAFE_DELETE(m_pFpsNode);
	SAFE_DELETE(m_pTestNode);
}

void SeleneDev::CGame::Reset()
{
	m_ElapsedTime = 0.0f;
}

void SeleneDev::CGame::Tick(float deltaTime)
{
	Selene::CVirtualFileSystem* pVfs = GetSupervisor()->GetVFS();
	Selene::CGraphics* pGraphics = GetSupervisor()->GetGraphics();

	// test
	//
	m_ElapsedTime += deltaTime;
	float period = 8.0f;
	float phaseTime = fmodf(m_ElapsedTime, period);
	float phase = phaseTime / period;
	float radius = 10.0f;
	float pi = 3.141592f;
	Selene::Vector3 camPos(13.0f, 10.0, 4.0f);
	Selene::Vector3 lookAt(-1.5f, 1.0f, -5.0f);
	Selene::Vector3 camUp(0.0f, 1.0f, 0.0f);
	camPos.m_X = cosf(pi * 2.0f * phase) * radius + lookAt.m_X;
	camPos.m_Z = sinf(pi * 2.0f * phase) * radius + lookAt.m_Z;
	//pGraphics->GetActiveCamera()->Look(camPos, lookAt, camUp);

	m_pTestNode->Update(deltaTime);
	m_pFpsNode->Update(deltaTime);
	m_pHudNode->Update(deltaTime);
}

bool SeleneDev::CGame::Finished()
{
	return false;
}
