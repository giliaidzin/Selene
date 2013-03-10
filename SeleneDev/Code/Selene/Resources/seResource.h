#ifndef SE_RESOURCE_H
#define SE_RESOURCE_H

#include "Selene/Utils/seStdIncludes.h"

namespace Selene
{
	class CResource
	{
	public:
		CResource(const char* name, int type);
		virtual ~CResource();

		inline const char* GetName() const;
		inline int GetType() const;

		virtual bool Load();
		virtual bool Unload();
		virtual bool IsLoaded() const;

	private:
		std::string m_Name;
		int m_Type;
	};

	// inline functions
	inline const char* CResource::GetName() const
	{
		return m_Name.c_str();
	}
	inline int CResource::GetType() const
	{
		return m_Type;
	}
}

#endif // SE_RESOURCE_H
