/*
 * Copyright (С) since 2019+ AzerothCore <www.azerothcore.org>
 * Licence MIT https://opensource.org/MIT
 */

#include "Chat.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "World.h"
#include "BattlefieldWG.h"
#include "WorldSession.h"

using namespace Acore::ChatCommands;

class wgwinner_commandscript : public CommandScript
{
public:
    wgwinner_commandscript() : CommandScript("wgwinner_commandscript") {}

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable winwgCommands =
            {
                {"set", HandleWGWINSetWinner, SEC_PLAYER, Console::Yes},
            };

        static ChatCommandTable commandTable =
            {
                {"winwg", winwgCommands},
            };

        return commandTable;
    }
    static bool HandleWGWINSetWinner(ChatHandler *handler, uint64 factioninput)
    {
        Player *player = handler->GetPlayer();

        // If The Module Is Enabled
        if (sConfigMgr->GetOption<bool>("WGWINCHANGER.Enable", true) || factioninput != NULL)
        {
            handler->SendSysMessage("Changing Wintergrasp Winning Faction.");
            handler->SetSentErrorMessage(true);
            sWorld->setWorldState(3802, uint64(factioninput));
            sWorld->LoadWorldStates();
            return true;
        }
        else
        {
            handler->SendSysMessage("WG Win Changer Does Not Enabled In Your WorldServer");
            handler->SetSentErrorMessage(true);
            return true;
        }
    }
};

void AddwintergraspwinchangerScripts()
{
    new wgwinner_commandscript();
};
