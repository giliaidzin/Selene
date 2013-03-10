#ifndef SE_VIRTUAL_FILE_H
#define SE_VIRTUAL_FILE_H

#include "Selene/Utils/seStdIncludes.h"

namespace Selene
{
	class CVirtualFile
	{
	public:
		enum ESeekOrigin
		{
			SO_CURRENT = SEEK_CUR,
			SO_END = SEEK_END,
			SO_START = SEEK_SET
		};

	public:
		CVirtualFile(FILE* pf);
		CVirtualFile(void* tableEntry);
		~CVirtualFile();

		int GetSize() const;

		bool Seek(int offset, ESeekOrigin origin);
		int Tell() const;

		bool Eof() const;

		int Read(void* buffer, int elementSize, int elementCount);

		int ReadI();
		unsigned int ReadUI();
		float ReadF();
		double ReadD();
		bool ReadB();
		char ReadC();
		unsigned char ReadUC();

	private:
		FILE* m_pFile;
		int m_FileSize;
		int m_CurrentPos;
	};
}

#endif // SE_VIRTUAL_FILE_H
