#include "Selene/Resources/seTexture.h"
#include "Selene/Resources/seResourceTypes.h"
#include "Selene/Resources/seVirtualFile.h"

#include "Selene/Utils/seUtils.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

Selene::CTexture::CTexture(const char *name)
:CResource(name, TYPE_TEXTURE)
,m_pFile(NULL)
,m_Loaded(false)
,m_TextureID(0)
,m_Width(0)
,m_Height(0)
{
}

Selene::CTexture::~CTexture()
{
}

bool Selene::CTexture::Load()
{
	if (m_Loaded || m_pFile == NULL)
	{
		return false;
	}

	m_Width = m_pFile->ReadI();
	m_Height = m_pFile->ReadI();
	int dataSize = m_Width * m_Height * 4;
	unsigned char* pData = new unsigned char[dataSize];
	m_pFile->Read(pData, dataSize, 1);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 m_Width, m_Height,
				 0, GL_RGBA, GL_UNSIGNED_BYTE,
				 pData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SAFE_DELETE(pData);

	m_Loaded = true;

	//FILE* pFile = fopen(m_FileName.c_str(), "rb");
	//if (pFile != NULL)
	//{
	//	fread(&m_Width, sizeof(int), 1, pFile);
	//	fread(&m_Height, sizeof(int), 1, pFile);
	//	int dataSize = m_Width * m_Height * 4;
	//	unsigned char* pData = new unsigned char[dataSize];
	//	fread(pData, dataSize, 1, pFile);
	//	fclose(pFile);

	//	glGenTextures(1, &m_TextureID);
	//	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	//	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	//				 m_Width, m_Height,
	//				 0, GL_RGBA, GL_UNSIGNED_BYTE,
	//				 pData);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	SAFE_DELETE(pData);

	//	m_Loaded = true;
	//}

	return m_Loaded;
}

bool Selene::CTexture::Unload()
{
	if (m_Loaded)
	{
		glDeleteTextures(1, &m_TextureID);
		m_TextureID = 0;
	}
	m_Loaded = false;
	return !m_Loaded;
}

bool Selene::CTexture::IsLoaded() const
{
	return m_Loaded;
}

int Selene::CTexture::GetWidth() const
{
	return m_Width;
}

int Selene::CTexture::GetHeight() const
{
	return m_Height;
}

unsigned int Selene::CTexture::GetTextureID() const
{
	return m_TextureID;
}

void Selene::CTexture::SetFile(CVirtualFile* pFile)
{
	m_pFile = pFile;
}
