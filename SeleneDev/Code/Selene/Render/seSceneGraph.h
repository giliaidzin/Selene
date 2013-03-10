#ifndef SE_SCENE_GRAPH_H
#define SE_SCENE_GRAPH_H

#include "Selene/Utils/seStdIncludes.h"

namespace Selene
{
	class CSceneNode;

	class CSceneGraph
	{
	public:
		CSceneGraph();
		~CSceneGraph();

		void Render();

		void AddRootNode(CSceneNode* pNode);
		void Clear();

	private:
		std::vector<CSceneNode*> m_RootNodes;
	};
}

#endif // SE_SCENE_GRAPH_H
