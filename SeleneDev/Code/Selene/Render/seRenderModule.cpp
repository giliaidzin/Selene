#include "Selene/Render/seRenderModule.h"
#include "Selene/Render/seGraphics.h"
#include "Selene/Render/seCamera.h"
#include "Selene/Render/seSceneGraph.h"
#include "Selene/Render/seSceneNode.h"

#include "Selene/Application/seSupervisor.h"

#include "Selene/Utils/seUtils.h"


Selene::CRenderModule::CRenderModule()
{
	m_pSceneGraph = NULL;
	m_pGraphics = NULL;
	m_pDefaultCamera = NULL;
	m_pGameRoot = NULL;
	m_pSystemRoot = NULL;
	m_pDebugRoot = NULL;
}

Selene::CRenderModule::~CRenderModule()
{
}

void Selene::CRenderModule::Init()
{
	m_pSceneGraph = new CSceneGraph();

	m_pGameRoot = new CSceneNode();
	m_pSystemRoot = new CSceneNode();
	m_pDebugRoot = new CSceneNode();

	m_pSceneGraph->AddRootNode(m_pGameRoot);
	m_pSceneGraph->AddRootNode(m_pSystemRoot);
	m_pSceneGraph->AddRootNode(m_pDebugRoot);

	ASSERT(GetSupervisor() != NULL, "Supervisor is null!");
	m_pGraphics = GetSupervisor()->GetGraphics();
	ASSERT(m_pGraphics != NULL, "Graphics is null!");

	m_pDefaultCamera = new CCamera();
	m_pGraphics->SetActiveCamera(m_pDefaultCamera);
}

void Selene::CRenderModule::Terminate()
{
	SAFE_DELETE(m_pDefaultCamera);
	m_pGraphics = NULL;
	m_pSceneGraph->Clear();
	SAFE_DELETE(m_pDebugRoot);
	SAFE_DELETE(m_pSystemRoot);
	SAFE_DELETE(m_pGameRoot);
	SAFE_DELETE(m_pSceneGraph);
}

void Selene::CRenderModule::Reset()
{
}

void Selene::CRenderModule::Tick(float deltaTime)
{
	m_pGraphics->StartFrame();

	m_pSceneGraph->Render();

	m_pGraphics->EndFrame();
}

bool Selene::CRenderModule::Finished()
{
	return false;
}

Selene::CSceneNode* Selene::CRenderModule::GetGameRoot() const
{
	return m_pGameRoot;
}

Selene::CSceneNode* Selene::CRenderModule::GetSystemRoot() const
{
	return m_pSystemRoot;
}

Selene::CSceneNode* Selene::CRenderModule::GetDebugRoot() const
{
	return m_pDebugRoot;
}
