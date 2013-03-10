#ifndef SE_SCENE_NODE_H
#define SE_SCENE_NODE_H

#include "Selene/Utils/seStdIncludes.h"

namespace Selene
{

	class CSceneNode
	{
	public:
		CSceneNode();
		virtual ~CSceneNode();

		virtual void Render();

		CSceneNode* GetChild();

		void AddChild(CSceneNode* pChildNode);
		void ClearChildren();

		virtual void Enable();
		virtual void Disable();
		virtual void SetEnabled(bool enabled);
		virtual bool IsEnabled() const;

	protected:
		std::vector<CSceneNode*> m_Children;

	private:
		bool m_Enabled;
	};
}

#endif // SE_SCENE_NODE_H
