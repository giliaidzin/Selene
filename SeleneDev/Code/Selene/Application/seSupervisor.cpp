// Supervisor

#include "Selene/Application/seSupervisor.h"
#include "Selene/Resources/seResourceManager.h"
//#include "managers/RenderManager.h"
//#include "managers/UpdateManager.h"
//#include "managers/InputManager.h"

#include "Selene/Utils/seUtils.h"


Selene::CSupervisor::CSupervisor()
{
	m_pResMan = new CResourceManager();
	m_pVFS = NULL;
	m_pGraphics = NULL;
	m_pInputMan = NULL;
}

Selene::CSupervisor::~CSupervisor()
{
	SAFE_DELETE(m_pResMan);
}

Selene::CResourceManager* Selene::CSupervisor::GetResMan() const
{
	return m_pResMan;
}

Selene::CVirtualFileSystem* Selene::CSupervisor::GetVFS() const
{
	return m_pVFS;
}

Selene::CGraphics* Selene::CSupervisor::GetGraphics() const
{
	return m_pGraphics;
}

Selene::CInputManager* Selene::CSupervisor::GetInputMan() const
{
	return m_pInputMan;
}

Selene::CSceneNode* Selene::CSupervisor::GetGameRoot() const
{
	return m_pGameRoot;
}
