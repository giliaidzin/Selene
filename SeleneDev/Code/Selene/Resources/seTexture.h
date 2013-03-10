#ifndef SE_TEXTURE_H
#define SE_TEXTURE_H

#include "Selene/Resources/seResource.h"

namespace Selene
{
	class CVirtualFile;

	class CTexture : CResource
	{
	public:
		CTexture(const char* name);
		~CTexture();

		bool Load();
		bool Unload();
		bool IsLoaded() const;

		int GetWidth() const;
		int GetHeight() const;

		unsigned int GetTextureID() const;
		void SetFile(CVirtualFile* pFile);
		void SetMemoryData(void* pData);

	private:
		CVirtualFile* m_pFile;
		bool m_Loaded;
		unsigned int m_TextureID;
		int m_Width;
		int m_Height;
	};
}

#endif // SE_TEXTURE_H
