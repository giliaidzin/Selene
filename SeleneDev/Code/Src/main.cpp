#include "Selene/Selene.h"

#include "Src/Game/sdGame.h"

void Selene::Entry(CApplication& rApp)
{
	Selene::CAppConfig* pConfig = rApp.GetAppConfig();
	pConfig->SetAppName("SeleneDev");

	SeleneDev::CGame* pGame = new SeleneDev::CGame();
	int gameID = rApp.AddModule("Game", pGame);
	(void) gameID;

	rApp.AddToLoop(gameID);
}
