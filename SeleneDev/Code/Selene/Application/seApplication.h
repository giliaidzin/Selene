// Selene application interface
#ifndef SE_APPLICATION_H
#define SE_APPLICATION_H

#include "Selene/Utils/seStdIncludes.h"

namespace Selene
{
	class CAppConfig;
	class CSupervisor;
	class CVirtualFileSystem;
	class CGraphics;
	class IAppModule;

	class CApplication
	{
	public:
		CApplication();
		virtual ~CApplication();

		virtual void ParseCommandLine(int argc, char* argv[]);
		virtual void Init();
		virtual void Terminate();

		virtual void Loop();

		virtual bool ShouldQuit() const;

		int AddModule(const char* name, IAppModule* pModule);

		bool AddToLoop(int moduleID);
		bool AddToLoop(const char* moduleName);

		CAppConfig* GetAppConfig() const;
		CSupervisor* GetSupervisor() const;
		CVirtualFileSystem* GetVFS() const;
		CGraphics* GetGraphics() const;

	private:
		CAppConfig* m_pAppConfig;
		CSupervisor* m_pSupervisor;
		CVirtualFileSystem* m_pVFS;
		CGraphics* m_pGraphics;
		std::vector<IAppModule*> m_Modules;
		std::map<std::string, IAppModule*> m_ModulesByName;
		std::vector<int> m_ModulesInLoop;
		//
		long m_LastClocks;
	};

} // namespace Selene

#endif // SE_APPLICATION_H
