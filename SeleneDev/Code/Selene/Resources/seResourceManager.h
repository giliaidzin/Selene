#ifndef SE_RESOURCE_MANAGER_H
#define SE_RESOURCE_MANAGER_H

#include "Selene/Utils/seStdIncludes.h"

#include "Selene/3rdParty/FreeType/include/ft2build.h"
#include FT_FREETYPE_H

namespace Selene
{
	class CResourceManager
	{
	public:
		CResourceManager();
		~CResourceManager();

		FT_Library GetFontLibrary() const;

	private:
		FT_Library m_FontLibrary;
	};
}

#endif // SE_RESOURCE_MANAGER_H
