// Supervisor
#ifndef SE_SUPERVISOR_H
#define SE_SUPERVISOR_H

namespace Selene
{
	class CResourceManager;
	class CVirtualFileSystem;
	class CGraphics;
	class CInputManager;
	class CSceneNode;

	class CSupervisor
	{
		friend class CApplication;

	public:
		CSupervisor();
		~CSupervisor();

		CResourceManager* GetResMan() const;
		CVirtualFileSystem* GetVFS() const;
		CGraphics* GetGraphics() const;
		CInputManager* GetInputMan() const;
		CSceneNode* GetGameRoot() const;

	private:
		CResourceManager* m_pResMan;
		CVirtualFileSystem* m_pVFS;
		CGraphics* m_pGraphics;
		CInputManager* m_pInputMan;
		CSceneNode* m_pGameRoot;
	};

} // namespace Selene

#endif // SE_SUPERVISOR_H
