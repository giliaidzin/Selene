#include "Selene/Resources/seFont.h"
#include "Selene/Resources/seResourceTypes.h"
#include "Selene/Resources/seVirtualFile.h"

#include "Selene/Utils/seUtils.h"

#include "Selene/3rdParty/FreeType/include/ft2build.h"
#include FT_FREETYPE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

Selene::CFont::CFont(const char *name)
:CResource(name, TYPE_FONT)
,m_pFile(NULL)
,m_Loaded(false)
,m_FontLibrary(NULL)
,m_TextureID(0)
,m_CharData(NULL)
,m_SymbolCount(0)
{
}

Selene::CFont::~CFont()
{
}

bool Selene::CFont::Load()
{
	if (m_Loaded || m_pFile == NULL || m_FontLibrary == NULL)
	{
		return false;
	}

	int dataSize = m_pFile->GetSize();
	unsigned char* pData = new unsigned char[dataSize];
	m_pFile->Read(pData, dataSize, 1);

	FT_Face face;

	FT_Error error = FT_New_Memory_Face(m_FontLibrary, pData, dataSize, 0, &face);
	if (error != 0)
	{
		//...
	}

	long fontSize = 60;
	unsigned int dpi = 96;
	error = FT_Set_Char_Size(face, 0, fontSize << 6, 0, dpi);
	if (error != 0)
	{
		//...
	}

	m_SymbolCount = 128;
	m_CharData = new SCharData[m_SymbolCount];
	int* sortedIndices = new int[m_SymbolCount];
	for (int i = 0; i < m_SymbolCount; i++)
	{
		//unsigned long charCode = 0x3043;
		//unsigned long charCode = 0x61; // a
		unsigned long charCode = i;
		if (i < 32)
		{
			charCode = i + 0x3042;
		}

		sortedIndices[i] = i;
		m_CharData[i].m_CharCode = charCode;
		if (!FillCharData(m_CharData[i], face))
		{
			//...
		}
	}

	// sort (bubble)
	for (int i = 0; i < m_SymbolCount; i++)
	{
		int maxGlyphIndex = i;
		for (int j = i; j < m_SymbolCount; j++)
		{
			//bool maxIsHorizontal = charData[maxGlyphIndex].m_Width > charData[maxGlyphIndex].m_Height;
			//bool currentIsHorizontal = charData[sortedIndices[j]].m_Width > charData[sortedIndices[j]].m_Height;
			//if (!maxIsHorizontal && currentIsHorizontal)
			//{
			//	maxGlyphIndex = j;
			//}
			//else if (maxIsHorizontal && currentIsHorizontal)
			//{
				if (m_CharData[maxGlyphIndex].m_Width < m_CharData[sortedIndices[j]].m_Width)
				{
					maxGlyphIndex = j;
				}
				//else if (m_CharData[maxGlyphIndex].m_Width == m_CharData[sortedIndices[j]].m_Width &&
				//		 m_CharData[maxGlyphIndex].m_Height < m_CharData[sortedIndices[j]].m_Height)
				//{
				//	maxGlyphIndex = j;
				//}
			//}
			//else if (!maxIsHorizontal && !currentIsHorizontal)
			//{
			//	if (charData[maxGlyphIndex].m_Height < charData[sortedIndices[j]].m_Height)
			//	{
			//		maxGlyphIndex = j;
			//	}
			//	else if (charData[maxGlyphIndex].m_Height == charData[sortedIndices[j]].m_Height &&
			//			 charData[maxGlyphIndex].m_Width < charData[sortedIndices[j]].m_Width)
			//	{
			//		maxGlyphIndex = j;
			//	}
			//}
		}
		int temp = sortedIndices[i];
		sortedIndices[i] = sortedIndices[maxGlyphIndex];
		sortedIndices[maxGlyphIndex] = temp;
	}

	// tree
	struct SNode
	{
		SNode* m_pChild[2];
		SRect m_Rect;
		int m_CharIndex;

		SNode()
		{
			m_pChild[0] = NULL;
			m_pChild[1] = NULL;
			m_CharIndex = -1;
		}

		void Clear()
		{
			if (m_pChild[0] != NULL)
			{
				m_pChild[0]->Clear();
				SAFE_DELETE(m_pChild[0]);
			}
			if (m_pChild[1] != NULL)
			{
				m_pChild[1]->Clear();
				SAFE_DELETE(m_pChild[1]);
			}
		}

		SNode* Insert(const SCharData& data)
		{
			if (m_pChild[0] != NULL && m_pChild[1] != NULL)
			{
				// try inserting into first child
				SNode* pNewNode = m_pChild[0]->Insert(data);
				if (pNewNode != NULL)
				{
					return pNewNode;
				}

				// no room, insert into second
				return m_pChild[1]->Insert(data);
			}
			else
			{
				// if there's already a glyph here, return
				if (m_CharIndex >= 0)
				{
					return NULL;
				}

				int width = m_Rect.m_Right - m_Rect.m_Left;
				int height = m_Rect.m_Bottom - m_Rect.m_Top;
				// if we're too small, return
				if (data.m_Width > width ||
					data.m_Height > height)
				{
					return NULL;
				}

				// if we're just right, accept
				if (data.m_Width == width &&
					data.m_Height == height)
				{
					return this;
				}

				// otherwise, gotta split this node and create some kids
				m_pChild[0] = new SNode();
				m_pChild[1] = new SNode();

				// decide which way to split
				int dw = width - data.m_Width;
				int dh = height - data.m_Height;

				if (dw > dh)
				{
					m_pChild[0]->m_Rect = SRect(m_Rect.m_Left, m_Rect.m_Left + data.m_Width,
												m_Rect.m_Top, m_Rect.m_Bottom);
					m_pChild[1]->m_Rect = SRect(m_Rect.m_Left + data.m_Width + 1, m_Rect.m_Right,
												m_Rect.m_Top, m_Rect.m_Bottom);
				}
				else
				{
					m_pChild[0]->m_Rect = SRect(m_Rect.m_Left, m_Rect.m_Right,
												m_Rect.m_Top, m_Rect.m_Top + data.m_Height);
					m_pChild[1]->m_Rect = SRect(m_Rect.m_Left, m_Rect.m_Right,
												m_Rect.m_Top + data.m_Height + 1, m_Rect.m_Bottom);
				}

				// insert into first child we created
				return m_pChild[0]->Insert(data);
			}
			return NULL;
		}
	};

	int atlasWidth = 1024;
	int atlasHeight = 1024;
	unsigned char* atlasData = new unsigned char[atlasWidth * atlasHeight * 2];
	memset(atlasData, 128, atlasWidth * atlasHeight * 2);

	SNode* pRoot = new SNode();
	pRoot->m_Rect.m_Left = 0;
	pRoot->m_Rect.m_Right = atlasWidth - 1;
	pRoot->m_Rect.m_Top = 0;
	pRoot->m_Rect.m_Bottom = atlasHeight - 1;

	for (int i = 0; i < m_SymbolCount; i++)
	{
		//int placeX = i % 16;
		//int placeY = i / 16;
		SCharData& data = m_CharData[sortedIndices[i]];
		SNode* pNode = pRoot->Insert(data);
		if (pNode != NULL)
		{
			data.m_StartX = pNode->m_Rect.m_Left;
			data.m_StartY = pNode->m_Rect.m_Top;
			//int placeIndex = placeY * 64 * atlasWidth * 2 + placeX * 64 * 2;
			int placeIndex = pNode->m_Rect.m_Top * atlasWidth * 2 + pNode->m_Rect.m_Left * 2;
			for (int k = 0; k < data.m_Height; k++)
			{
				for (int l = 0; l < data.m_Width; l++)
				{
					int atlasIndexL = placeIndex + k * atlasWidth * 2 + l * 2 + 0;
					int atlasIndexA = placeIndex + k * atlasWidth * 2 + l * 2 + 1;
					int charIndexL = k * data.m_Width * 2 + l * 2 + 0;
					int charIndexA = k * data.m_Width * 2 + l * 2 + 1;
					atlasData[atlasIndexL] = data.m_pData[charIndexL];
					atlasData[atlasIndexA] = data.m_pData[charIndexA];
				}
			}
			pNode->m_CharIndex = sortedIndices[i];
		}
	}

	pRoot->Clear();
	SAFE_DELETE(pRoot);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
				 atlasWidth, atlasHeight,
				 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
				 atlasData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SAFE_DELETE_ARRAY(atlasData);

	SAFE_DELETE_ARRAY(sortedIndices);

	SAFE_DELETE(pData);

	error = FT_Done_Face(face);
	if (error != 0)
	{
		//...
	}

	SAFE_DELETE(pData);

	m_Loaded = true;

	return m_Loaded;
}

bool Selene::CFont::Unload()
{
	if (m_Loaded)
	{
		for (int i = 0; i < m_SymbolCount; i++)
		{
			SAFE_DELETE(m_CharData[i].m_pData);
		}
		SAFE_DELETE_ARRAY(m_CharData);
		glDeleteTextures(1, &m_TextureID);
		m_TextureID = 0;
	}
	m_Loaded = false;
	return !m_Loaded;
}

bool Selene::CFont::IsLoaded() const
{
	return m_Loaded;
}

void Selene::CFont::SetFontLibrary(FT_Library library)
{
	m_FontLibrary = library;
}

void Selene::CFont::SetFile(CVirtualFile* pFile)
{
	m_pFile = pFile;
}

void Selene::CFont::SetMemoryData(void* pData)
{
}

unsigned int Selene::CFont::GetTextureID() const
{
	return m_TextureID;
}

const Selene::CFont::SCharData& Selene::CFont::GetCharData(int index) const
{
	return m_CharData[index];
}

bool Selene::CFont::FillCharData(SCharData& data, FT_Face face)
{
	unsigned int glyphIndex = FT_Get_Char_Index(face, data.m_CharCode);
	FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
	if (error != 0)
	{
		//...
		return false;
	}

	FT_GlyphSlot glyph = face->glyph;
	error = FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);
	if (error != 0)
	{
		//...
		return false;
	}

	// do something with bitmap
	const FT_Bitmap& bitmap = glyph->bitmap;
	int width = bitmap.width; // NextP2(bitmap.width);
	int height = bitmap.rows; // NextP2(bitmap.rows);
	data.m_pData = new unsigned char[width * height * 2];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			bool inBitmap = i < bitmap.width && j < bitmap.rows;
			data.m_pData[j * width * 2 + i * 2 + 0] = inBitmap ? 255 : 0;
			data.m_pData[j * width * 2 + i * 2 + 1] = inBitmap ? bitmap.buffer[j * bitmap.width + i] : 0;
		}
	}
	data.m_Width = width;
	data.m_Height = height;
	data.m_AdvanceX = glyph->advance.x >> 6;
	data.m_AdvanceY = glyph->advance.y >> 6;
	return true;
}

int Selene::CFont::NextP2(int value) const
{
	int result = 2;
	while (result < value)
	{
		result <<= 1;
	}
	return result;
}
