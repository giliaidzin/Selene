#include "Selene/Resources/seResource.h"

Selene::CResource::CResource(const char* name, int type)
:m_Name(name)
,m_Type(type)
{
}

Selene::CResource::~CResource()
{
}

bool Selene::CResource::Load()
{
	return true;
}

bool Selene::CResource::Unload()
{
	return true;
}

bool Selene::CResource::IsLoaded() const
{
	return true;
}
