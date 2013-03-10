#ifndef SE_FONT_H
#define SE_FONT_H

#include "Selene/Resources/seResource.h"

#include "Selene/3rdParty/FreeType/include/ft2build.h"
#include FT_FREETYPE_H

namespace Selene
{
	class CVirtualFile;

	class CFont : CResource
	{
	public:
		CFont(const char* name);
		~CFont();

		bool Load();
		bool Unload();

		bool IsLoaded() const;

		void SetFontLibrary(FT_Library library);
		void SetFile(CVirtualFile* pFile);
		void SetMemoryData(void* pData);

		//
		unsigned int GetTextureID() const;

	//private:
	public:
		struct SRect
		{
			int m_Left;
			int m_Right;
			int m_Top;
			int m_Bottom;

			SRect()
				:m_Left(0)
				,m_Right(0)
				,m_Top(0)
				,m_Bottom(0)
			{
			}
			SRect(int left, int right, int top, int bottom)
				:m_Left(left)
				,m_Right(right)
				,m_Top(top)
				,m_Bottom(bottom)
			{
			}
		};
		struct SCharData
		{
			unsigned long m_CharCode;
			int m_Width;
			int m_Height;
			unsigned char* m_pData;
			int m_StartX;
			int m_StartY;
			int m_AdvanceX;
			int m_AdvanceY;
		};

		const SCharData& GetCharData(int index) const;

	private:
		bool FillCharData(SCharData& data, FT_Face face);
		int NextP2(int value) const;

	private:
		CVirtualFile* m_pFile;
		bool m_Loaded;
		FT_Library m_FontLibrary;
		//
		unsigned int m_TextureID;
		SCharData* m_CharData;
		int m_SymbolCount;
	};
}

#endif // SE_FONT_H
