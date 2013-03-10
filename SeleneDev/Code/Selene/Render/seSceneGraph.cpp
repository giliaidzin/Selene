#include "Selene/Render/seSceneGraph.h"
#include "Selene/Render/seSceneNode.h"

#include "Selene/Utils/seUtils.h"

Selene::CSceneGraph::CSceneGraph()
{
}

Selene::CSceneGraph::~CSceneGraph()
{
	Clear();
}

void Selene::CSceneGraph::Render()
{
	for (std::vector<CSceneNode*>::iterator it = m_RootNodes.begin();
		 it != m_RootNodes.end();
		 it++)
	{
		(*it)->Render();
	}
}

void Selene::CSceneGraph::AddRootNode(CSceneNode* pNode)
{
	m_RootNodes.push_back(pNode);
}

void Selene::CSceneGraph::Clear()
{
	m_RootNodes.clear();
}
