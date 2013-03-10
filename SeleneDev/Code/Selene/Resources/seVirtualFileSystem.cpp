#include "Selene/Resources/seVirtualFileSystem.h"
#include "Selene/Resources/seVirtualFile.h"

#include "Selene/Utils/seUtils.h"

Selene::CVirtualFileSystem::CVirtualFileSystem()
:m_kErrorBufferSize(1024)
,m_Error("")
{
	//m_Error = new char[m_kErrorBufferSize];
}

Selene::CVirtualFileSystem::~CVirtualFileSystem()
{
	//SAFE_DELETE(m_Error);
}

bool Selene::CVirtualFileSystem::MountDir(const char* mountPoint, const char* path)
{
	//std::map<const char*, SMountData*, string_less>::iterator it = m_Mounts.find(mountPoint);
	std::map<std::string, SMountData*>::iterator it = m_Mounts.find(mountPoint);
	if (it != m_Mounts.end())
	{
		//strcpy(m_Error, "Mount point already used!");
		m_Error = "Mount point already used!";
		return false;
	}
	//int mountPointLength = strlen(mountPoint);
	//int pathLength = strlen(path);
	//SMountData* pData = new SMountData;
	//pData->m_Type = MT_DIR;
	//pData->m_MountPoint = new char[mountPointLength + 1];
	//memset(pData->m_MountPoint, 0, mountPointLength + 1);
	//strncpy(pData->m_MountPoint, mountPoint, mountPointLength);
	//pData->m_Path = new char[pathLength + 1];
	//memset(pData->m_Path, 0, pathLength + 1);
	//strncpy(pData->m_Path, path, pathLength);

	SMountData* pData = new SMountData;
	pData->m_Type = MT_DIR;
	pData->m_MountPoint = mountPoint;
	pData->m_Path = path;

	m_Mounts[pData->m_MountPoint] = pData;

	m_Error = "";
	return true;
}

bool Selene::CVirtualFileSystem::MountFile(const char* mountPoint, const char* path)
{
	m_Error = "";
	return true;
}

bool Selene::CVirtualFileSystem::Unmount(const char* mountPoint)
{
	m_Error = "";
	return true;
}

bool Selene::CVirtualFileSystem::IsMounted(const char* mountPoint) const
{
	return m_Mounts.find(mountPoint) != NULL;
}

Selene::CVirtualFile* Selene::CVirtualFileSystem::Open(const char* filePath)
{
	if (filePath == NULL)
	{
		m_Error = "File path is null!";
		return NULL;
	}
	int filePathLength = strlen(filePath);
	if (filePathLength <= 3 || filePath[0] != '/')
	{
		m_Error = "File path does not contain mount point!";
		return NULL;
	}
	const int kBufferSize = 1024;
	ASSERT(filePathLength < kBufferSize, "Buffer too small!");
	char mountPoint[kBufferSize];
	memset(mountPoint, 0, kBufferSize);
	int fileNameIndex = 0;
	for (int i = 1; i < filePathLength; i++)
	{
		if (filePath[i] == '/')
		{
			fileNameIndex = i;
			break;
		}
		mountPoint[i - 1] = filePath[i];
	}
	SMountData* pMount = m_Mounts[mountPoint];
	if (pMount == NULL)
	{
		return NULL;
	}

	char fileName[kBufferSize];
	memset(fileName, 0, kBufferSize);
	strcpy(fileName, filePath + fileNameIndex);

	CVirtualFile* pFile = NULL;

	if (pMount->m_Type == MT_DIR)
	{
		char fullPath[kBufferSize];
		memset(fullPath, 0, kBufferSize);
		const int pathLength = pMount->m_Path.length();
		strcpy(fullPath, pMount->m_Path.c_str());
		strcpy(fullPath + pathLength, fileName);
		FILE* pf = fopen(fullPath, "rb");
		if (pf != NULL)
		{
			pFile = new CVirtualFile(pf);
		}
		else
		{
			m_Error = "File not found!";
		}
	}
	else if (pMount->m_Type == MT_FILE)
	{
		m_Error = "Mount type \"MT_FILE\" not implemented yet!";
	}
	else
	{
		m_Error = "Unknown mount type!";
	}

	m_Error = "";
	return pFile;
}

bool Selene::CVirtualFileSystem::Close(CVirtualFile* pFile)
{
	return true;
}

const char* Selene::CVirtualFileSystem::GetError() const
{
	return m_Error.c_str();
}
