#ifndef SE_RENDER_MODULE_H
#define SE_RENDER_MODULE_H

#include "Selene/Application/seAppModule.h"

namespace Selene
{
	class CSceneGraph;
	class CGraphics;
	class CCamera;
	class CSceneNode;

	class CRenderModule : public IAppModule
	{
	public:
		CRenderModule();
		~CRenderModule();

		virtual void Init();
		virtual void Terminate();
		virtual void Reset();
		virtual void Tick(float deltaTime);
		virtual bool Finished();

		CSceneNode* GetGameRoot() const;
		CSceneNode* GetSystemRoot() const;
		CSceneNode* GetDebugRoot() const;

	private:
		CSceneGraph* m_pSceneGraph;
		CGraphics* m_pGraphics;
		CCamera* m_pDefaultCamera;
		CSceneNode* m_pGameRoot;
		CSceneNode* m_pSystemRoot;
		CSceneNode* m_pDebugRoot;
	};
}

#endif // SE_RENDER_MODULE_H
