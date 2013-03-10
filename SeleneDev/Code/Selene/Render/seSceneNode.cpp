#include "Selene/Render/seSceneNode.h"

#include "Selene/Utils/seUtils.h"

Selene::CSceneNode::CSceneNode()
:m_Enabled(true)
{
}

Selene::CSceneNode::~CSceneNode()
{
	m_Children.clear();
}

void Selene::CSceneNode::Render()
{
	for (std::vector<CSceneNode*>::iterator it = m_Children.begin();
		 it != m_Children.end();
		 it++)
	{
		(*it)->Render();
	}
}

void Selene::CSceneNode::AddChild(CSceneNode* pChildNode)
{
	m_Children.push_back(pChildNode);
}

void Selene::CSceneNode::ClearChildren()
{
	m_Children.clear();
}

void Selene::CSceneNode::Enable()
{
	m_Enabled = true;
}

void Selene::CSceneNode::Disable()
{
	m_Enabled = false;
}

void Selene::CSceneNode::SetEnabled(bool enabled)
{
	m_Enabled = enabled;
}

bool Selene::CSceneNode::IsEnabled() const
{
	return m_Enabled;
}
