#ifndef SD_GAME_H
#define SD_GAME_H

#include "Selene/Application/seAppModule.h"

namespace SeleneDev
{
	class CTestNode;
	class CFpsNode;
	class CHudNode;

	class CGame : public Selene::IAppModule
	{
	public:
		CGame();
		virtual ~CGame();

		virtual void Init();
		virtual void Terminate();
		virtual void Reset();
		virtual void Tick(float deltaTime);
		virtual bool Finished();

	private:
		CTestNode* m_pTestNode;
		CFpsNode* m_pFpsNode;
		CHudNode* m_pHudNode;
		float m_ElapsedTime;
	};

} // namespace SeleneDev

#endif // SD_GAME_H
