// Selene application interface
#include <time.h>

#include "Selene/Application/seApplication.h"
#include "Selene/Application/seAppConfig.h"
#include "Selene/Application/seSupervisor.h"
#include "Selene/Application/seAppModule.h"

#include "Selene/Resources/seVirtualFileSystem.h"
#include "Selene/Resources/seVirtualFile.h"

#include "Selene/Render/seGraphics.h"
#include "Selene/Render/seRenderModule.h"
#include "Selene/Render/seSceneGraph.h"

#include "Selene/Utils/seUtils.h"


Selene::CApplication::CApplication()
{
	m_pAppConfig = new CAppConfig();
	ASSERT(m_pAppConfig != NULL, "App config not created!");
	m_pSupervisor = new CSupervisor();
	ASSERT(m_pSupervisor != NULL, "Supervisor not created!");
	m_pVFS = new CVirtualFileSystem();
	ASSERT(m_pVFS != NULL, "Virtual file system not created!");
	m_pGraphics = new CGraphics();
	ASSERT(m_pGraphics != NULL, "Graphics not created!");

	m_pSupervisor->m_pVFS = m_pVFS;
	m_pSupervisor->m_pGraphics = m_pGraphics;

	// vfs test
	m_pVFS->MountDir("Data", "E:\\Selene\\SeleneDev\\Code\\VisualStudio\\SeleneDev\\Data");
	CVirtualFile* pFile = m_pVFS->Open("/Data/moon.sir");
	m_pVFS->Close(pFile);
	//

	//m_ModulesInLoop.clear();

	m_LastClocks = clock();
}

Selene::CApplication::~CApplication()
{
	m_ModulesInLoop.clear();
	m_ModulesByName.clear();
	m_Modules.clear();
	SAFE_DELETE(m_pGraphics);
	SAFE_DELETE(m_pVFS);
	SAFE_DELETE(m_pSupervisor);
	SAFE_DELETE(m_pAppConfig);
}

void Selene::CApplication::ParseCommandLine(int argc, char* argv[])
{
}

void Selene::CApplication::Init()
{
	CRenderModule* pRenderModule = new CRenderModule();
	int renderModuleID = AddModule("RenderModule", pRenderModule);

	pRenderModule->Init();
	m_pSupervisor->m_pGameRoot = pRenderModule->GetGameRoot();

	for (std::vector<int>::iterator it = m_ModulesInLoop.begin();
		 it != m_ModulesInLoop.end();
		 it++)
	{
		int moduleID =(*it);
		if (moduleID != -1)
		{
			m_Modules[moduleID]->Init();
		}
	}

	AddToLoop(renderModuleID);

	m_LastClocks = clock();
}

void Selene::CApplication::Terminate()
{
	for (std::vector<int>::iterator it = m_ModulesInLoop.begin();
		 it != m_ModulesInLoop.end();
		 it++)
	{
		int moduleID =(*it);
		if (moduleID != -1)
		{
			m_Modules[moduleID]->Terminate();
		}
	}
	m_ModulesInLoop.clear();
	m_ModulesByName.clear();
	m_Modules.clear();
}

void Selene::CApplication::Loop()
{
	long currentClocks = clock();
	long deltaClocks = currentClocks - m_LastClocks;
	float deltaTime = (float) deltaClocks / (float) CLOCKS_PER_SEC;
	m_LastClocks = currentClocks;

	for (std::vector<int>::iterator it = m_ModulesInLoop.begin();
		 it != m_ModulesInLoop.end();
		 it++)
	{
		int moduleID =(*it);
		if (moduleID != -1)
		{
			m_Modules[moduleID]->Tick(deltaTime);
			if (m_Modules[moduleID]->Finished())
			{
				(*it) = -1;
				it = m_ModulesInLoop.erase(it);
			}
		}
	}
}

bool Selene::CApplication::ShouldQuit() const
{
	return false;
}

int Selene::CApplication::AddModule(const char* name, IAppModule* pModule)
{
	ASSERT(name != NULL, "Module name is null!");
	ASSERT(pModule != NULL, "Module is null!");

	m_Modules.push_back(pModule);
	m_ModulesByName[name] = pModule;
	int id = m_Modules.size() - 1;
	pModule->SetID(id);
	pModule->SetSupervisor(m_pSupervisor);
	return id;
}

bool Selene::CApplication::AddToLoop(int moduleID)
{
	m_ModulesInLoop.push_back(moduleID);
	return true;
}

bool Selene::CApplication::AddToLoop(const char* moduleName)
{
	if (m_ModulesByName.find(moduleName) == m_ModulesByName.end())
	{
		return false;
	}
	m_ModulesInLoop.push_back(m_ModulesByName[moduleName]->GetID());
	return true;
}

Selene::CAppConfig* Selene::CApplication::GetAppConfig() const
{
	return m_pAppConfig;
}

Selene::CSupervisor* Selene::CApplication::GetSupervisor() const
{
	return m_pSupervisor;
}

Selene::CVirtualFileSystem* Selene::CApplication::GetVFS() const
{
	return m_pVFS;
}

Selene::CGraphics* Selene::CApplication::GetGraphics() const
{
	return m_pGraphics;
}
