#include "Selene/Resources/seResourceManager.h"

Selene::CResourceManager::CResourceManager()
{
	FT_Error error = FT_Init_FreeType(&m_FontLibrary);
	if (error != 0)
	{
		//... an error occurred during library initialization ...
	}
}

Selene::CResourceManager::~CResourceManager()
{
	FT_Error error = FT_Done_FreeType(m_FontLibrary);
	if (error != 0)
	{
		//... an error occurred during library initialization ...
	}
}

FT_Library Selene::CResourceManager::GetFontLibrary() const
{
	return m_FontLibrary;
}
