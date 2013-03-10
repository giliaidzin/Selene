#include "Src/Game/sdFpsNode.h"

#include "Selene/Render/seGraphics.h"
#include "Selene/Render/seCamera.h"

#include "Selene/Types/seVector2.h"
#include "Selene/Types/seVector3.h"
#include "Selene/Types/seMatrix4.h"

#include "Selene/Utils/seUtils.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>


SeleneDev::CFpsNode::CFpsNode(Selene::CGraphics* pGraphics,
							  Selene::CTexture* pDialTex)
:m_HandAngle(0.0f)
,m_pGraphics(pGraphics)
,m_pDialTex(pDialTex)
,m_DialPos(-1.5f, 8.0f, -5.0f)
,m_DialSize(3.0f, 3.0f)
,m_ElapsedTime(0.0f)
,m_CheckTime(1.0f)
{
	for (int i=0; i<k_SampleCount; i++)
	{
		m_Samples[i].m_Fps = 0.0f;
		m_Samples[i].m_TimeStamp = -1.0f;
	}
}

SeleneDev::CFpsNode::~CFpsNode()
{
}

void SeleneDev::CFpsNode::Render()
{
	Selene::CGraphics::SVertex dialVertices[4];
	Selene::Color dialColor(1.0f, 1.0f, 1.0f, 1.0f);

	Selene::CCamera* pCam = m_pGraphics->GetActiveCamera();
	Selene::Vector3 camLookDir = pCam->GetLookDir();
	Selene::Vector3 camRightDir = pCam->GetRightDir();
	Selene::Vector3 camUpDir = pCam->GetUpDir();

	dialVertices[0].m_Color = dialColor;
	dialVertices[0].m_TexCoords = Selene::Vector2(0.0f, 0.0f);
	dialVertices[0].m_Coords = -camRightDir * m_DialSize.x * 0.5f + camUpDir * m_DialSize.y * 0.5f;
	dialVertices[0].m_Coords += m_DialPos;

	dialVertices[1].m_Color = dialColor;
	dialVertices[1].m_TexCoords = Selene::Vector2(1.0f, 0.0f);
	dialVertices[1].m_Coords = camRightDir * m_DialSize.x * 0.5f + camUpDir * m_DialSize.y * 0.5f;
	dialVertices[1].m_Coords += m_DialPos;

	dialVertices[2].m_Color = dialColor;
	dialVertices[2].m_TexCoords = Selene::Vector2(1.0f, 1.0f);
	dialVertices[2].m_Coords = camRightDir * m_DialSize.x * 0.5f - camUpDir * m_DialSize.y * 0.5f;
	dialVertices[2].m_Coords += m_DialPos;

	dialVertices[3].m_Color = dialColor;
	dialVertices[3].m_TexCoords = Selene::Vector2(0.0f, 1.0f);
	dialVertices[3].m_Coords = -camRightDir * m_DialSize.x * 0.5f - camUpDir * m_DialSize.y * 0.5f;
	dialVertices[3].m_Coords += m_DialPos;

	// coordinate axes
	Selene::CGraphics::SVertex handVertices[2];

	handVertices[0].m_Color = Selene::Color(0.0f, 0.0f, 1.0f, 1.0f);
	handVertices[0].m_Coords = m_DialPos;
	handVertices[1].m_Color = Selene::Color(0.0f, 0.0f, 1.0f, 1.0f);
	handVertices[1].m_Coords = camUpDir * m_DialSize.y * 0.4f;

	m_pGraphics->EnableAlphaBlend();
	m_pGraphics->SetAlphaBlendMode(Selene::CGraphics::SBM_SRC_ALPHA,
								   Selene::CGraphics::DBM_ONE_MINUS_DST_ALPHA);
	m_pGraphics->DisableZTest();
	m_pGraphics->DisableZWrite();

	m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_QUADS);
	m_pGraphics->SetTexture(m_pDialTex);
	m_pGraphics->StartPrimitives();
	m_pGraphics->Draw(dialVertices, 4);
	m_pGraphics->EndPrimitives();


	//// object rotation test
	//Selene::Vector3 rightDir(1.0f, 0.0f, 0.0f);
	//Selene::Vector3 upDir(0.0f, 1.0f, 0.0f);
	//Selene::Vector3 forwardDir(0.0f, 0.0f, 1.0f);

	//handVertices[0].m_Coords *= rotationMatrix;
	//handVertices[1].m_Coords *= rotationMatrix;

	/*/
	Selene::CCamera* pCamera = m_pGraphics->GetActiveCamera();
	float dist = 3.0f;
	xLineVertices[1].m_Coords = pCamera->GetRightDir() * dist;
	yLineVertices[1].m_Coords = pCamera->GetUpDir() * dist;
	zLineVertices[1].m_Coords = pCamera->GetLookDir() * dist;
	//*/

	Selene::Matrix4 rotationMatrix;
	rotationMatrix.RotateOnAxis(m_HandAngle, -camLookDir);
	//float pi = 3.141592f;
	//rotationMatrix.RotateOnAxis(pi * 0.75f, -camLookDir);

	handVertices[1].m_Coords *= rotationMatrix;
	handVertices[1].m_Coords += m_DialPos;

	m_pGraphics->DisableAlphaBlend();

	m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_LINES);
	m_pGraphics->SetTexture(NULL);
	m_pGraphics->StartPrimitives();
	m_pGraphics->Draw(handVertices, 2);
	m_pGraphics->EndPrimitives();

	CSceneNode::Render();
}

void SeleneDev::CFpsNode::Update(float deltaTime)
{
	if (deltaTime < 0.00001f)
	{
		return;
	}

	float pi = 3.141592f;
	float fps = 1.0f / deltaTime;
	m_ElapsedTime += deltaTime;

	float oldestTimeStamp = m_ElapsedTime;
	int oldestIndex = 0;
	for (int i=0; i<k_SampleCount; i++)
	{
		if (m_Samples[i].m_TimeStamp + m_CheckTime < m_ElapsedTime)
		{
			m_Samples[i].m_Fps = 0.0f;
			m_Samples[i].m_TimeStamp = -1.0f;
		}
		if (m_Samples[i].m_TimeStamp > 0.0f)
		{
			if (m_Samples[i].m_TimeStamp < oldestTimeStamp)
			{
				oldestTimeStamp = m_Samples[i].m_TimeStamp;
				oldestIndex = i;
			}
		}
	}
	bool sampleRecorded = false;
	for (int i=0; i<k_SampleCount; i++)
	{
		if (m_Samples[i].m_TimeStamp < 0.0f)
		{
			m_Samples[i].m_TimeStamp = m_ElapsedTime;
			m_Samples[i].m_Fps = fps;
			sampleRecorded = true;
			break;
		}
	}
	if (!sampleRecorded)
	{
		m_Samples[oldestIndex].m_TimeStamp = m_ElapsedTime;
		m_Samples[oldestIndex].m_Fps = fps;
	}

	float sampleSum = 0.0f;
	int sampleCount = 0;
	for (int i=0; i<k_SampleCount; i++)
	{
		if (m_Samples[i].m_TimeStamp > 0.0f)
		{
			sampleSum += m_Samples[i].m_Fps;
			sampleCount++;
		}
	}

	float averageFps = fps;
	if (sampleCount > 0)
	{
		averageFps = sampleSum / (float) sampleCount;
	}

	float maxFps = 100.0f;
	m_HandAngle = 2.0f * pi * averageFps / maxFps;
}
