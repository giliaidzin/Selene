#ifndef SE_GRAPHICS_H
#define SE_GRAPHICS_H

#include "Selene/Types/seVector2.h"
#include "Selene/Types/seVector3.h"
#include "Selene/Types/seColor.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

namespace Selene
{
	class CCamera;
	class CTexture;

	class CGraphics
	{
	public:
		enum EZTestFunc
		{
			ZTF_NEVER = GL_NEVER,		// Never passes.
			ZTF_LESS = GL_LESS,			// Passes if the incoming z value is less than the stored z value. This is the default value.
			ZTF_LEQUAL = GL_LEQUAL,		// Passes if the incoming z value is less than or equal to the stored z value.
			ZTF_EQUAL = GL_EQUAL,		// Passes if the incoming z value is equal to the stored z value.
			ZTF_GREATER = GL_GREATER,	// Passes if the incoming z value is greater than the stored z value.
			ZTF_NOTEQUAL = GL_NOTEQUAL,	// Passes if the incoming z value is not equal to the stored z value.
			ZTF_GEQUAL = GL_GEQUAL,		// Passes if the incoming z value is greater than or equal to the stored z value.
			ZTF_ALWAYS = GL_ALWAYS		// Always passes.
		};
		enum EAlphaTestFunc
		{
			ATF_NEVER = GL_NEVER,		// Never passes.
			ATF_LESS = GL_LESS,			// Passes if the incoming alpha value is less than the reference value.
			ATF_EQUAL = GL_EQUAL,		// Passes if the incoming alpha value is equal to the reference value.
			ATF_LEQUAL = GL_LEQUAL,		// Passes if the incoming alpha value is less than or equal to the reference value.
			ATF_GREATER = GL_GREATER,	// Passes if the incoming alpha value is greater than the reference value.
			ATF_NOTEQUAL = GL_NOTEQUAL,	// Passes if the incoming alpha value is not equal to the reference value.
			ATF_GEQUAL = GL_GEQUAL,		// Passes if the incoming alpha value is greater than or equal to the reference value.
			ATF_ALWAYS = GL_ALWAYS		// Always passes. This is the default.
		};
		enum ESrcBlendMode
		{
			SBM_ZERO = GL_ZERO,
			SBM_ONE = GL_ONE,
			SBM_DST_COLOR = GL_DST_COLOR,
			SBM_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
			SBM_SRC_ALPHA = GL_SRC_ALPHA,
			SBM_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
			SBM_DST_ALPHA = GL_DST_ALPHA,
			SBM_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
			SBM_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE
		};
		enum EDstBlendMode
		{
			DBM_ZERO = GL_ZERO,
			DBM_ONE = GL_ONE,
			DBM_SRC_COLOR = GL_SRC_COLOR,
			DBM_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
			DBM_SRC_ALPHA = GL_SRC_ALPHA,
			DBM_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
			DBM_DST_ALPHA = GL_DST_ALPHA,
			DBM_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA
		};
		enum EBackfaceDirection
		{
			BD_CLOCKWISE = GL_CCW,			// gl values are for front face
			BD_COUNTER_CLOCKWISE = GL_CW	// hence the reverse
		};
		enum EPrimitiveMode
		{
			PM_POINTS = GL_POINTS,
			PM_LINES = GL_LINES,
			PM_LINE_STRIP = GL_LINE_STRIP,
			PM_LINE_LOOP = GL_LINE_LOOP,
			PM_TRIANGLES = GL_TRIANGLES,
			PM_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
			PM_TRIANGLE_FAN = GL_TRIANGLE_FAN,
			PM_QUADS = GL_QUADS,
			PM_QUAD_STRIP = GL_QUAD_STRIP,
			PM_POLYGON = GL_POLYGON
		};

	public:
		struct SVertex
		{
			Vector2 m_TexCoords;
			Vector3 m_Coords;
			Color m_Color;
		};

	public:
		CGraphics();
		~CGraphics();

		bool Init();

		void SetActiveCamera(CCamera* pCamera);
		CCamera* GetActiveCamera() const;

		void PrepareView(int width, int height);
		void StartFrame();
		void EndFrame();

		void EnableZTest();
		void EnableZWrite();
		void EnableAlphaTest();
		void EnableAlphaBlend();
		void EnableBackfaceCulling();

		void DisableZTest();
		void DisableZWrite();
		void DisableAlphaTest();
		void DisableAlphaBlend();
		void DisableBackfaceCulling();

		void SetZTestFunc(EZTestFunc func);
		void SetAlphaTestFunc(EAlphaTestFunc func, float ref);
		void SetAlphaBlendMode(ESrcBlendMode srcMode, EDstBlendMode dstMode);
		void SetBackfaceDirection(EBackfaceDirection dir);

		void SetPrimitiveMode(EPrimitiveMode mode);
		void SetTexture(CTexture* pTex);

		void StartPrimitives();
		void EndPrimitives();

		void Draw(SVertex* buffer, int vertexCount);

	private:
		CCamera* m_pActiveCamera;
		EPrimitiveMode m_PrimitiveMode;
		CTexture* m_pTexture;
		HGLRC m_RC;
		HDC m_DC;
	};
}

#endif // SE_GRAPHICS_H
