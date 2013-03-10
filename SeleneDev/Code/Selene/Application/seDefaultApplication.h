// Selene default application
#ifndef SE_DEFAULT_APPLICATION_H
#define SE_DEFAULT_APPLICATION_H

#include "seApplication.h"

namespace Selene
{
	class CDefaultApplication : public CApplication
	{
	public:
		CDefaultApplication();
		virtual ~CDefaultApplication();

		virtual void ParseCommandLine(int iArgC, char* astrArgV[]);
		virtual void Init();
		virtual void Terminate();

		virtual void Update(float fDeltaTime);
		virtual void Render(float fDeltaTime);

		virtual bool ShouldQuit();

	private:
		bool m_bShouldQuit;
	};

} // namespace Selene

#endif // SE_DEFAULT_APPLICATION_H
