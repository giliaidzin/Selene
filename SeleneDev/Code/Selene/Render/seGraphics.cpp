#include "Selene/Render/seGraphics.h"
#include "Selene/Render/seCamera.h"

#include "Selene/Resources/seTexture.h"

#include "Selene/Utils/seUtils.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

Selene::CGraphics::CGraphics()
:m_pActiveCamera(NULL)
,m_PrimitiveMode(PM_TRIANGLES)
,m_pTexture(NULL)
,m_RC(NULL)
,m_DC(NULL)
{

}

Selene::CGraphics::~CGraphics()
{
}

bool Selene::CGraphics::Init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);

	return true;
}

void Selene::CGraphics::SetActiveCamera(CCamera* pCamera)
{
	m_pActiveCamera = pCamera;
}

Selene::CCamera* Selene::CGraphics::GetActiveCamera() const
{
	return m_pActiveCamera;
}

void Selene::CGraphics::PrepareView(int width, int height)
{
	float aspectRatio = 1.0f;
	if (height == 0)
	{
		aspectRatio = (float) width;
	}
	else
	{
		aspectRatio = (float) width / (float) height;
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (m_pActiveCamera != NULL)
	{
		m_pActiveCamera->SetAspectRatio(aspectRatio);
		//m_pActiveCamera->
		gluPerspective(m_pActiveCamera->GetFov(),
					   m_pActiveCamera->GetAspectRatio(),
					   m_pActiveCamera->GetNearPlane(),
					   m_pActiveCamera->GetFarPlane());
	}
	else
	{
		//gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
		//gluOrtho2D(-3.0, 3.0, -3.0, 3.0);
		double scale = 3.0;
		//glOrtho(-1.0 * aspectRatio * scale,
		//		1.0 * aspectRatio * scale,
		//		-1.0 * scale,
		//		1.0 * scale,
		//		-1.0 * scale,
		//		1.0 * scale);
		glFrustum(-1.0 * aspectRatio * scale,
				  1.0 * aspectRatio * scale,
				  -1.0 * scale,
				  1.0 * scale,
				  1.0 * scale,
				  100.0 * scale);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (m_pActiveCamera != NULL)
	{
		glLoadMatrixf(&m_pActiveCamera->GetViewMatrix().m[0][0]);
	}
}

void Selene::CGraphics::StartFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (m_pActiveCamera != NULL)
	{
		glLoadMatrixf(&m_pActiveCamera->GetViewMatrix().m[0][0]);
	}
}

void Selene::CGraphics::EndFrame()
{
	glFlush();
	glFinish();
}

void Selene::CGraphics::EnableZTest()
{
	glEnable(GL_DEPTH_TEST);
}

void Selene::CGraphics::EnableZWrite()
{
	glEnable(GL_DEPTH_WRITEMASK);
}

void Selene::CGraphics::EnableAlphaTest()
{
	glEnable(GL_ALPHA_TEST);
}

void Selene::CGraphics::EnableAlphaBlend()
{
	glEnable(GL_BLEND);
}

void Selene::CGraphics::EnableBackfaceCulling()
{
	glEnable(GL_CULL_FACE);
}

void Selene::CGraphics::DisableZTest()
{
	glDisable(GL_DEPTH_TEST);
}

void Selene::CGraphics::DisableZWrite()
{
	glDisable(GL_DEPTH_WRITEMASK);
}

void Selene::CGraphics::DisableAlphaTest()
{
	glDisable(GL_ALPHA_TEST);
}

void Selene::CGraphics::DisableAlphaBlend()
{
	glDisable(GL_BLEND);
}

void Selene::CGraphics::DisableBackfaceCulling()
{
	glDisable(GL_CULL_FACE);
}

void Selene::CGraphics::SetZTestFunc(EZTestFunc func)
{
	glDepthFunc(func);
}

void Selene::CGraphics::SetAlphaTestFunc(EAlphaTestFunc func, float ref)
{
	glAlphaFunc(func, ref);
}

void Selene::CGraphics::SetAlphaBlendMode(ESrcBlendMode srcMode, EDstBlendMode dstMode)
{
	glBlendFunc(srcMode, dstMode);
}

void Selene::CGraphics::SetBackfaceDirection(EBackfaceDirection dir)
{
	glFrontFace(dir);
}

void Selene::CGraphics::SetPrimitiveMode(EPrimitiveMode mode)
{
	m_PrimitiveMode = mode;
}

void Selene::CGraphics::SetTexture(CTexture* pTex)
{
	m_pTexture = pTex;
}

void Selene::CGraphics::StartPrimitives()
{
	if (m_pTexture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->GetTextureID());
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
	glBegin(m_PrimitiveMode);
}

void Selene::CGraphics::EndPrimitives()
{
	glEnd();
}

void Selene::CGraphics::Draw(SVertex* buffer, int vertexCount)
{
	ASSERT(buffer != NULL, "Vertex buffer is null!");
	for (int i = 0; i < vertexCount; i++)
	{
		Color c(buffer[i].m_Color);
		Vector2 uv(buffer[i].m_TexCoords);
		Vector3 v(buffer[i].m_Coords);
		glColor4f(c.m_R, c.m_G, c.m_B, c.m_A);
		glTexCoord2f(uv.x, uv.y);
		glVertex3f(v.m_X, v.m_Y, v.m_Z);
	}
}
