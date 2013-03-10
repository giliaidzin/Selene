#include "Src/Game/sdTestNode.h"

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


SeleneDev::CTestNode::CTestNode(Selene::CGraphics* pGraphics,
								Selene::CTexture* pBoxTex,
								Selene::CTexture* pMoonTex,
								Selene::CTexture* pSquaresTex,
								Selene::CFont* pFont)
:m_TriangleAngle(0.0f)
,m_QuadAngle(0.0f)
,m_pGraphics(pGraphics)
,m_pBoxTex(pBoxTex)
,m_pMoonTex(pMoonTex)
,m_pSquaresTex(pSquaresTex)
,m_pFont(pFont)
,m_MoonPos(-1.5f, 0.0f, -5.0f)
,m_BoxPos(1.5f, 0.0f, -5.0f)
,m_SquaresPos(0.0f, -3.0f, -5.0f)
{
}

SeleneDev::CTestNode::~CTestNode()
{
}

void SeleneDev::CTestNode::Render()
{
	Selene::CGraphics::SVertex pyramidVertices[3];
	Selene::CGraphics::SVertex boxVertices[4];
	Selene::CGraphics::SVertex squaresVertices[12];

	Selene::Color pyramidColor(1.0f, 1.0f, 1.0f, 1.0f);
	Selene::Color boxColor(0.5f, 0.5f, 0.2f, 0.5f);
	Selene::Color squaresColor(1.0f, 1.0f, 1.0f, 0.5f);

	pyramidVertices[0].m_Color = pyramidColor;
	pyramidVertices[0].m_TexCoords = Selene::Vector2(0.0f, 0.0f);
	pyramidVertices[0].m_Coords = Selene::Vector3(0.0f, 1.0f, 0.0f);
	pyramidVertices[0].m_Coords += m_MoonPos;

	pyramidVertices[1].m_Color = pyramidColor;
	pyramidVertices[1].m_TexCoords = Selene::Vector2(0.0f, 1.0f);
	pyramidVertices[1].m_Coords = Selene::Vector3(-1.0f, -1.0f, 0.0f);
	pyramidVertices[1].m_Coords += m_MoonPos;

	pyramidVertices[2].m_Color = pyramidColor;
	pyramidVertices[2].m_TexCoords = Selene::Vector2(1.0f, 1.0f);
	pyramidVertices[2].m_Coords = Selene::Vector3(1.0f, -1.0f, 0.0f);
	pyramidVertices[2].m_Coords += m_MoonPos;


	boxVertices[0].m_Color = boxColor;
	boxVertices[0].m_TexCoords = Selene::Vector2(0.0f, 0.0f);
	boxVertices[0].m_Coords = Selene::Vector3(-1.0f, 1.0f, 0.0f);
	boxVertices[0].m_Coords += m_BoxPos;

	boxVertices[1].m_Color = boxColor;
	boxVertices[1].m_TexCoords = Selene::Vector2(1.0f, 0.0f);
	boxVertices[1].m_Coords = Selene::Vector3(1.0f, 1.0f, 0.0f);
	boxVertices[1].m_Coords += m_BoxPos;

	boxVertices[2].m_Color = boxColor;
	boxVertices[2].m_TexCoords = Selene::Vector2(1.0f, 1.0f);
	boxVertices[2].m_Coords = Selene::Vector3(1.0f, -1.0f, 0.0f);
	boxVertices[2].m_Coords += m_BoxPos;

	boxVertices[3].m_Color = boxColor;
	boxVertices[3].m_TexCoords = Selene::Vector2(0.0f, 1.0f);
	boxVertices[3].m_Coords = Selene::Vector3(-1.0f, -1.0f, 0.0f);
	boxVertices[3].m_Coords += m_BoxPos;

	Selene::Vector3 bottomOffset(0.0f, -0.5f, 0.0f);

	squaresVertices[0].m_Color = squaresColor;
	squaresVertices[0].m_TexCoords = Selene::Vector2(0.0f, 0.0f);
	squaresVertices[0].m_Coords = Selene::Vector3(-5.0f, 0.0f, 5.0f);
	squaresVertices[0].m_Coords += m_SquaresPos + bottomOffset;

	squaresVertices[1].m_Color = squaresColor;
	squaresVertices[1].m_TexCoords = Selene::Vector2(1.0f, 0.0f);
	squaresVertices[1].m_Coords = Selene::Vector3(5.0f, 0.0f, 5.0f);
	squaresVertices[1].m_Coords += m_SquaresPos + bottomOffset;

	squaresVertices[2].m_Color = squaresColor;
	squaresVertices[2].m_TexCoords = Selene::Vector2(1.0f, 1.0f);
	squaresVertices[2].m_Coords = Selene::Vector3(5.0f, 0.0f, -5.0f);
	squaresVertices[2].m_Coords += m_SquaresPos + bottomOffset;

	squaresVertices[3].m_Color = squaresColor;
	squaresVertices[3].m_TexCoords = Selene::Vector2(0.0f, 1.0f);
	squaresVertices[3].m_Coords = Selene::Vector3(-5.0f, 0.0f, -5.0f);
	squaresVertices[3].m_Coords += m_SquaresPos + bottomOffset;

	squaresVertices[4].m_Color = squaresColor;
	squaresVertices[4].m_TexCoords = Selene::Vector2(0.0f, 0.0f);
	squaresVertices[4].m_Coords = Selene::Vector3(-5.0f, 0.0f, -5.0f);
	squaresVertices[4].m_Coords += m_SquaresPos;

	squaresVertices[5].m_Color = squaresColor;
	squaresVertices[5].m_TexCoords = Selene::Vector2(1.0f, 0.0f);
	squaresVertices[5].m_Coords = Selene::Vector3(5.0f, 0.0f, -5.0f);
	squaresVertices[5].m_Coords += m_SquaresPos;

	squaresVertices[6].m_Color = squaresColor;
	squaresVertices[6].m_TexCoords = Selene::Vector2(1.0f, 1.0f);
	squaresVertices[6].m_Coords = Selene::Vector3(5.0f, 10.0f, -5.0f);
	squaresVertices[6].m_Coords += m_SquaresPos;

	squaresVertices[7].m_Color = squaresColor;
	squaresVertices[7].m_TexCoords = Selene::Vector2(0.0f, 1.0f);
	squaresVertices[7].m_Coords = Selene::Vector3(-5.0f, 10.0f, -5.0f);
	squaresVertices[7].m_Coords += m_SquaresPos;

	squaresVertices[8].m_Color = squaresColor;
	squaresVertices[8].m_TexCoords = Selene::Vector2(0.0f, 0.0f);
	squaresVertices[8].m_Coords = Selene::Vector3(-5.0f, 0.0f, -5.0f);
	squaresVertices[8].m_Coords += m_SquaresPos;

	squaresVertices[9].m_Color = squaresColor;
	squaresVertices[9].m_TexCoords = Selene::Vector2(1.0f, 0.0f);
	squaresVertices[9].m_Coords = Selene::Vector3(-5.0f, 10.0f, -5.0f);
	squaresVertices[9].m_Coords += m_SquaresPos;

	squaresVertices[10].m_Color = squaresColor;
	squaresVertices[10].m_TexCoords = Selene::Vector2(1.0f, 1.0f);
	squaresVertices[10].m_Coords = Selene::Vector3(-5.0f, 10.0f, 5.0f);
	squaresVertices[10].m_Coords += m_SquaresPos;

	squaresVertices[11].m_Color = squaresColor;
	squaresVertices[11].m_TexCoords = Selene::Vector2(0.0f, 1.0f);
	squaresVertices[11].m_Coords = Selene::Vector3(-5.0f, 0.0f, 5.0f);
	squaresVertices[11].m_Coords += m_SquaresPos;

	// coordinate axes
	Selene::CGraphics::SVertex xLineVertices[3];
	Selene::CGraphics::SVertex yLineVertices[2];
	Selene::CGraphics::SVertex zLineVertices[2];

	xLineVertices[0].m_Color = Selene::Color(1.0f, 0.0f, 0.0f, 1.0f);
	xLineVertices[0].m_Coords = Selene::Vector3(0.0f, 0.0f, 0.0f);
	xLineVertices[1].m_Color = Selene::Color(1.0f, 0.0f, 0.0f, 1.0f);
	xLineVertices[1].m_Coords = Selene::Vector3(5.0f, 0.0f, 0.0f);
	xLineVertices[2].m_Color = Selene::Color(1.0f, 0.0f, 0.0f, 1.0f);
	xLineVertices[2].m_Coords = Selene::Vector3(0.0f, 0.2f, 0.0f);


	yLineVertices[0].m_Color = Selene::Color(0.0f, 1.0f, 0.0f, 1.0f);
	yLineVertices[0].m_Coords = Selene::Vector3(0.0f, 0.0f, 0.0f);
	yLineVertices[1].m_Color = Selene::Color(0.0f, 1.0f, 0.0f, 1.0f);
	yLineVertices[1].m_Coords = Selene::Vector3(0.0f, 5.0f, 0.0f);

	zLineVertices[0].m_Color = Selene::Color(0.0f, 0.0f, 1.0f, 1.0f);
	zLineVertices[0].m_Coords = Selene::Vector3(0.0f, 0.0f, 0.0f);
	zLineVertices[1].m_Color = Selene::Color(0.0f, 0.0f, 1.0f, 1.0f);
	zLineVertices[1].m_Coords = Selene::Vector3(0.0f, 0.0f, 5.0f);


	//glLoadIdentity();
	//glTranslatef(-1.5f, 0.0f, 0.0f);
	//glRotatef(m_TriangleAngle, 0.0f, 1.0f, 0.0f);

	m_pGraphics->EnableAlphaBlend();
	m_pGraphics->SetAlphaBlendMode(Selene::CGraphics::SBM_SRC_ALPHA,
								   Selene::CGraphics::DBM_ONE_MINUS_SRC_ALPHA);

	m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_TRIANGLES);
	//m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_LINES);
	m_pGraphics->SetTexture(m_pBoxTex);
	m_pGraphics->StartPrimitives();
	m_pGraphics->Draw(pyramidVertices, 3);
	m_pGraphics->EndPrimitives();

	//glLoadIdentity();
	//glTranslatef(1.5f, 0.0f, 0.0f);
	//glRotatef(m_QuadAngle, 1.0f, 1.0f, 1.0f);

	m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_QUADS);
	//m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_LINES);
	m_pGraphics->SetTexture(m_pMoonTex);
	m_pGraphics->StartPrimitives();
	m_pGraphics->Draw(boxVertices, 4);
	m_pGraphics->EndPrimitives();

	m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_QUADS);
	m_pGraphics->SetTexture(m_pSquaresTex);
	// hack
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_pFont->GetTextureID());
	glBegin(Selene::CGraphics::PM_QUADS);
	// end hack
	//m_pGraphics->StartPrimitives();
	m_pGraphics->Draw(squaresVertices, 12);
	m_pGraphics->EndPrimitives();

	//m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_TRIANGLES);
	//m_pGraphics->SetTexture(NULL);
	//m_pGraphics->StartPrimitives();
	//m_pGraphics->Draw(xLineVertices, 3);
	//m_pGraphics->EndPrimitives();


	// object rotation test
	Selene::Vector3 rightDir(1.0f, 0.0f, 0.0f);
	Selene::Vector3 upDir(0.0f, 1.0f, 0.0f);
	Selene::Vector3 forwardDir(0.0f, 0.0f, 1.0f);

	Selene::Vector3 lookAt(0.0f, 0.0f, 1.0f);
	Selene::Vector3 pos(0.0f, 0.0f, 0.0f);
	Selene::Vector3 up(0.0f, 1.0f, 0.0f);

	//*
	lookAt = Selene::Vector3(0.0f, 0.0, 0.0f);
	pos = Selene::Vector3(3.0f, 0.0, 4.0f);
	up = Selene::Vector3(0.0f, 1.0, 0.0f);
	//*/

	forwardDir = lookAt - pos;
	forwardDir *= -1.0f;
	forwardDir.Normalize();
	rightDir = up.Cross(forwardDir);
	rightDir.Normalize();
	upDir = forwardDir.Cross(rightDir);
	upDir.Normalize();

	rightDir.Normalize();
	upDir.Normalize();
	forwardDir.Normalize();

	Selene::Matrix4 rotationMatrix;
	//rotationMatrix.m[0][0] = rightDir.m_X;
	//rotationMatrix.m[0][1] = rightDir.m_Y;
	//rotationMatrix.m[0][2] = rightDir.m_Z;
	//rotationMatrix.m[0][3] = 0.0f;

	//rotationMatrix.m[1][0] = upDir.m_X;
	//rotationMatrix.m[1][1] = upDir.m_Y;
	//rotationMatrix.m[1][2] = upDir.m_Z;
	//rotationMatrix.m[1][3] = 0.0f;

	//rotationMatrix.m[2][0] = forwardDir.m_X;
	//rotationMatrix.m[2][1] = forwardDir.m_Y;
	//rotationMatrix.m[2][2] = forwardDir.m_Z;
	//rotationMatrix.m[2][3] = 0.0f;

	//rotationMatrix.m[3][0] = 0.0f;
	//rotationMatrix.m[3][1] = 0.0f;
	//rotationMatrix.m[3][2] = 0.0f;
	//rotationMatrix.m[3][3] = 1.0f;

	rotationMatrix.m[0][0] = rightDir.m_X;
	rotationMatrix.m[0][1] = upDir.m_X;
	rotationMatrix.m[0][2] = forwardDir.m_X;
	rotationMatrix.m[0][3] = 0.0f;

	rotationMatrix.m[1][0] = rightDir.m_Y;
	rotationMatrix.m[1][1] = upDir.m_Y;
	rotationMatrix.m[1][2] = forwardDir.m_Y;
	rotationMatrix.m[1][3] = 0.0f;

	rotationMatrix.m[2][0] = rightDir.m_Z;
	rotationMatrix.m[2][1] = upDir.m_Z;
	rotationMatrix.m[2][2] = forwardDir.m_Z;
	rotationMatrix.m[2][3] = 0.0f;

	rotationMatrix.m[3][0] = 0.0f;
	rotationMatrix.m[3][1] = 0.0f;
	rotationMatrix.m[3][2] = 0.0f;
	rotationMatrix.m[3][3] = 1.0f;

	//rotationMatrix.Transpose();

	//*
	xLineVertices[0].m_Coords *= rotationMatrix;
	xLineVertices[1].m_Coords *= rotationMatrix;
	yLineVertices[0].m_Coords *= rotationMatrix;
	yLineVertices[1].m_Coords *= rotationMatrix;
	zLineVertices[0].m_Coords *= rotationMatrix;
	zLineVertices[1].m_Coords *= rotationMatrix;

	/*/
	Selene::CCamera* pCamera = m_pGraphics->GetActiveCamera();
	float dist = 3.0f;
	xLineVertices[1].m_Coords = pCamera->GetRightDir() * dist;
	yLineVertices[1].m_Coords = pCamera->GetUpDir() * dist;
	zLineVertices[1].m_Coords = pCamera->GetLookDir() * dist;
	//*/

	m_pGraphics->SetPrimitiveMode(Selene::CGraphics::PM_LINES);
	m_pGraphics->SetTexture(NULL);
	m_pGraphics->StartPrimitives();
	m_pGraphics->Draw(xLineVertices, 2);
	m_pGraphics->Draw(yLineVertices, 2);
	m_pGraphics->Draw(zLineVertices, 2);
	m_pGraphics->EndPrimitives();


	CSceneNode::Render();
}

void SeleneDev::CTestNode::Update(float deltaTime)
{
	m_TriangleAngle += 0.2f;
	m_QuadAngle += -0.15f;
}
