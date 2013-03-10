#ifndef SE_VIRTUAL_FILE_SYSTEM_H
#define SE_VIRTUAL_FILE_SYSTEM_H

#include "Selene/Utils/seStdIncludes.h"

namespace Selene
{
	struct string_less
	{
		bool operator() (const char* lhs, const char* rhs) const
		{
			return strcmp(lhs, rhs) < 0;
		}
	};

	class CVirtualFile;

	class CVirtualFileSystem
	{
	public:
		CVirtualFileSystem();
		~CVirtualFileSystem();

		bool MountDir(const char* mountPoint, const char* path);
		bool MountFile(const char* mountPoint, const char* path);
		bool Unmount(const char* mountPoint);
		bool IsMounted(const char* mountPoint) const;

		CVirtualFile* Open(const char* filePath);
		bool Close(CVirtualFile* pFile);

		const char* GetError() const;

	private:
		enum EMountType
		{
			MT_DIR,
			MT_FILE
		};
		struct SMountData
		{
			std::string m_MountPoint;
			std::string m_Path;
			EMountType m_Type;
		};

	private:
		//std::map<const char*, SMountData*, string_less> m_Mounts;
		std::map<std::string, SMountData*> m_Mounts;
		const int m_kErrorBufferSize;
		std::string m_Error;
	};
}

#endif // SE_VIRTUAL_FILE_SYSTEM_H
