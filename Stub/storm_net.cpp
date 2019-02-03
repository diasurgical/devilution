#include "../types.h"

BOOL STORMAPI SNetReceiveMessage(int *senderplayerid, char **data, int *databytes)
{
	if (!dvlnet::inst->SNetReceiveMessage(senderplayerid, data, databytes)) {
		SErrSetLastError(STORM_ERROR_NO_MESSAGES_WAITING);
		return FALSE;
	}
	return TRUE;
}

BOOL STORMAPI SNetSendMessage(int playerID, void *data, unsigned int databytes)
{
	return dvlnet::inst->SNetSendMessage(playerID, data, databytes);
}

BOOL STORMAPI SNetReceiveTurns(int a1, int arraysize, char **arraydata, unsigned int *arraydatabytes,
    DWORD *arrayplayerstatus)
{
	if (a1 != 0)
		UNIMPLEMENTED();
	if (arraysize != MAX_PLRS)
		UNIMPLEMENTED();
	return dvlnet::inst->SNetReceiveTurns(arraydata, arraydatabytes, arrayplayerstatus);
}

BOOL STORMAPI SNetSendTurn(char *data, unsigned int databytes)
{
	return dvlnet::inst->SNetSendTurn(data, databytes);
}

int __stdcall SNetGetProviderCaps(struct _SNETCAPS *caps)
{
	return dvlnet::inst->SNetGetProviderCaps(caps);
}

void *__stdcall SNetUnregisterEventHandler(int evtype, void(__stdcall *func)(struct _SNETEVENT *))
{
	return dvlnet::inst->SNetUnregisterEventHandler(evtype, func);
}

void *__stdcall SNetRegisterEventHandler(int evtype, void(__stdcall *func)(struct _SNETEVENT *))
{
	return dvlnet::inst->SNetRegisterEventHandler(evtype, func);
}

BOOL STORMAPI SNetDestroy()
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetDropPlayer(int playerid, DWORD flags)
{
	UNIMPLEMENTED();
}

BOOL STORMAPI SNetGetGameInfo(int type, void *dst, unsigned int length, unsigned int *byteswritten)
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetLeaveGame(int type)
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetSendServerChatCommand(const char *command)
{
	DUMMY();
	return TRUE;
}

/**
 * @brief Called by engine for single, called by ui for multi
 * @param provider BNET, IPXN, MODM, SCBL or UDPN
 * @param fileinfo Ignore
 */
int __stdcall SNetInitializeProvider(unsigned long provider, struct _SNETPROGRAMDATA *client_info,
    struct _SNETPLAYERDATA *user_info, struct _SNETUIDATA *ui_info,
    struct _SNETVERSIONDATA *fileinfo)
{
	if (provider == 'UDPN') {
		dvlnet::buffer_t game_init_info((char*)client_info->initdata,
												(char*)client_info->initdata + client_info->initdatabytes);
		dvlnet::inst = std::make_unique<dvlnet_udp>(std::move(game_init_info));
	} else if (provider == 'SCBL' || provider == 0) {
		dvlnet::inst = std::make_unique<dvlnet_null>();
	} else {
		ABORT();
	}

	return ui_info->selectnamecallback(client_info, user_info, ui_info, fileinfo, provider, NULL, 0, NULL, 0, NULL);
}

/**
 * @brief Called by engine for single, called by ui for multi
 */
BOOL STORMAPI SNetCreateGame(const char *pszGameName, const char *pszGamePassword, const char *pszGameStatString,
    DWORD dwGameType, char *GameTemplateData, int GameTemplateSize, int playerCount,
    char *creatorName, char *a11, int *playerID)
{
	// hack: cannot create game until UI is ready
	//       first instance will create, second will join
	int ret;
	if (ret = dvlnet::inst->create("0.0.0.0", "mypass") == -1)
		ret = dvlnet::inst->join("127.0.0.1", "mypass");
	*playerID = ret;
	return TRUE;
}

/**
 * @brief Is this the mirror image of SNetGetTurnsInTransit?
 */
BOOL __stdcall SNetGetOwnerTurnsWaiting(DWORD *turns)
{
	*turns = 0;
	return TRUE;
}

BOOL STORMAPI SNetGetTurnsInTransit(int *turns)
{
	*turns = 0; // We do not queue turns at all
	return TRUE;
}

/**
 * @brief engine calls this only once with argument 1
 */
BOOLEAN __stdcall SNetSetBasePlayer(int)
{
	return TRUE;
}

/**
 * @brief since we never signal STORM_ERROR_REQUIRES_UPGRADE the engine will not call this function
 */
BOOL STORMAPI SNetPerformUpgrade(DWORD *upgradestatus)
{
	UNIMPLEMENTED();
}

/**
 * @brief not called from engine
 */
BOOL STORMAPI SNetSetGameMode(DWORD modeFlags, bool makePublic)
{
	UNIMPLEMENTED();
	return TRUE;
}
