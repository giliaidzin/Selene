#ifndef SE_TEXT_RENDERER_H
#define SE_TEXT_RENDERER_H

#include "Selene/Utils/seStdIncludes.h"

namespace Selene
{

	class CTextRenderer
	{
	public:
		CTextRenderer();
		virtual ~CTextRenderer();

		virtual void Render();

		virtual void Enable();
		virtual void Disable();
		virtual void SetEnabled(bool enabled);

		virtual bool IsEnabled() const;

	private:
		bool m_Enabled;
	};
}

#endif // SE_TEXT_RENDERER_H
