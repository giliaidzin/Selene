#include "Selene/Render/seTextRenderer.h"

#include "Selene/Utils/seUtils.h"

Selene::CTextRenderer::CTextRenderer()
:m_Enabled(true)
{
}

Selene::CTextRenderer::~CTextRenderer()
{
}

void Selene::CTextRenderer::Render()
{
}

void Selene::CTextRenderer::Enable()
{
	m_Enabled = true;
}

void Selene::CTextRenderer::Disable()
{
	m_Enabled = false;
}

void Selene::CTextRenderer::SetEnabled(bool enabled)
{
	m_Enabled = enabled;
}

bool Selene::CTextRenderer::IsEnabled() const
{
	return m_Enabled;
}
