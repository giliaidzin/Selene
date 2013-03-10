#include "Selene/Resources/seVirtualFile.h"

#include "Selene/Utils/seUtils.h"


Selene::CVirtualFile::CVirtualFile(FILE* pf)
:m_pFile(pf)
,m_FileSize(0)
,m_CurrentPos(0)
{
	ASSERT(m_pFile != NULL, "FILE pointer is null!");
	fseek(m_pFile, 0, SEEK_END);
	m_FileSize = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_SET);
	m_CurrentPos = ftell(m_pFile);
}

Selene::CVirtualFile::CVirtualFile(void* tableEntry)
:m_pFile(NULL)
,m_FileSize(0)
,m_CurrentPos(0)
{
}

Selene::CVirtualFile::~CVirtualFile()
{
}

int Selene::CVirtualFile::GetSize() const
{
	return m_FileSize;
}

bool Selene::CVirtualFile::Seek(int offset, ESeekOrigin origin)
{
	int result = fseek(m_pFile, offset, origin);
	m_CurrentPos = Tell();
	return result == 0;
}

int Selene::CVirtualFile::Tell() const
{
	return ftell(m_pFile);
}

bool Selene::CVirtualFile::Eof() const
{
	return feof(m_pFile) != 0;
}

int Selene::CVirtualFile::Read(void* buffer, int elementSize, int elementCount)
{
	ASSERT(buffer != NULL, "Buffer is null!");
	int result = fread(buffer, elementSize, elementCount, m_pFile);
	return result;
}

int Selene::CVirtualFile::ReadI()
{
	int value = 0;
	int result = fread(&value, sizeof(int), 1, m_pFile);
	return value;
}

unsigned int Selene::CVirtualFile::ReadUI()
{
	unsigned int value = 0;
	int result = fread(&value, sizeof(unsigned int), 1, m_pFile);
	return value;
}

float Selene::CVirtualFile::ReadF()
{
	float value = 0.0f;
	int result = fread(&value, sizeof(float), 1, m_pFile);
	return value;
}

double Selene::CVirtualFile::ReadD()
{
	double value = 0.0;
	int result = fread(&value, sizeof(double), 1, m_pFile);
	return value;
}

bool Selene::CVirtualFile::ReadB()
{
	bool value = false;
	int result = fread(&value, sizeof(bool), 1, m_pFile);
	return value;
}

char Selene::CVirtualFile::ReadC()
{
	char value = 0;
	int result = fread(&value, sizeof(char), 1, m_pFile);
	return value;
}

unsigned char Selene::CVirtualFile::ReadUC()
{
	unsigned char value = 0;
	int result = fread(&value, sizeof(unsigned char), 1, m_pFile);
	return value;
}
