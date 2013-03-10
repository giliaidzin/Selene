// Selene application config
#ifndef SE_APP_CONFIG_H
#define SE_APP_CONFIG_H

#include "Selene/Utils/seStdIncludes.h"

namespace Selene
{

	class CAppConfig
	{
	public:
		CAppConfig();
		virtual ~CAppConfig();

		inline void SetAppName(const char* name);
		inline void SetWindowWidth(int width);
		inline void SetWindowHeight(int height);
		inline void SetFullscreen(bool fullscreen);

		inline const char* GetAppName() const;
		inline int GetWindowWidth() const;
		inline int GetWindowHeight() const;
		inline bool GetFullscreen() const;

	private:
		std::string m_AppName;
		int m_WindowWidth;
		int m_WindowHeight;
		bool m_Fullscreen;
	};

	// inline functions
	inline void CAppConfig::SetAppName(const char* name)
	{
		m_AppName = name;
	}
	inline void CAppConfig::SetWindowWidth(int width)
	{
		m_WindowWidth = width;
	}
	inline void CAppConfig::SetWindowHeight(int height)
	{
		m_WindowHeight = height;
	}
	inline void CAppConfig::SetFullscreen(bool fullscreen)
	{
		m_Fullscreen = fullscreen;
	}
	inline const char* CAppConfig::GetAppName() const
	{
		return m_AppName.c_str();
	}
	inline int CAppConfig::GetWindowWidth() const
	{
		return m_WindowWidth;
	}
	inline int CAppConfig::GetWindowHeight() const
	{
		return m_WindowHeight;
	}
	inline bool CAppConfig::GetFullscreen() const
	{
		return m_Fullscreen;
	}

} // namespace Selene

#endif // SE_APP_CONFIG_H
