#include "../types.h"

BOOL STORMAPI SNetReceiveMessage(int *senderplayerid, char **data, int *databytes)
{
	if (!devilution_net::inst->SNetReceiveMessage(senderplayerid, data, databytes)) {
		SErrSetLastError(STORM_ERROR_NO_MESSAGES_WAITING);
		return FALSE;
	}
	return TRUE;
}

BOOL STORMAPI SNetSendMessage(int playerID, void *data, unsigned int databytes)
{
	return devilution_net::inst->SNetSendMessage(playerID, data, databytes);
}

BOOL STORMAPI SNetReceiveTurns(int a1, int arraysize, char **arraydata, unsigned int *arraydatabytes,
    DWORD *arrayplayerstatus)
{
	if (a1 != 0)
		UNIMPLEMENTED();
	if (arraysize != MAX_PLRS)
		UNIMPLEMENTED();
	return devilution_net::inst->SNetReceiveTurns(arraydata, arraydatabytes, arrayplayerstatus);
}

BOOL STORMAPI SNetSendTurn(char *data, unsigned int databytes)
{
	return devilution_net::inst->SNetSendTurn(data, databytes);
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

void *__stdcall SNetUnregisterEventHandler(int evtype, void(__stdcall *func)(struct _SNETEVENT *))
{
	DUMMY();
	return NULL;
}

void *__stdcall SNetRegisterEventHandler(int evtype, void(__stdcall *func)(struct _SNETEVENT *))
{
	// need to handle:
	// EVENT_TYPE_PLAYER_LEAVE_GAME
	// EVENT_TYPE_PLAYER_CREATE_GAME (raised during SNetCreateGame?)
	// EVENT_TYPE_PLAYER_MESSAGE
	// all by the same function
	DUMMY();
	return (void *)func;
}

int __stdcall SNetGetProviderCaps(struct _SNETCAPS *caps)
{
	return devilution_net::inst->SNetGetProviderCaps(caps);
}

int __stdcall SNetInitializeProvider(unsigned long provider, struct _SNETPROGRAMDATA *client_info,
    struct _SNETPLAYERDATA *user_info, struct _SNETUIDATA *ui_info,
    struct _SNETVERSIONDATA *fileinfo)
{
	// called by engine for single
	// called by ui for multi
	// Ignore: fileinfo
	if (provider == 'UDPN')
		devilution_net::inst = std::make_unique<devilution_net_udp>();
	else if (provider == 'SCBL' || provider == 0)
		devilution_net::inst = std::make_unique<devilution_net_single>();
	else
		ABORT();

	char *cname;
	char *cdesc;
	BOOL *multi;
	ui_info->selectnamecallback(client_info, user_info, ui_info, fileinfo, 0, cname, 0, cdesc, 0, multi);
	return TRUE;
}

BOOL STORMAPI SNetCreateGame(const char *pszGameName, const char *pszGamePassword, const char *pszGameStatString,
    DWORD dwGameType, char *GameTemplateData, int GameTemplateSize, int playerCount,
    char *creatorName, char *a11, int *playerID)
{
	// called by engine for single
	// called by ui for multi
	// hack: cannot create game until UI is ready
	//       first instance will create, second will join
	int ret;
	if (ret = devilution_net::inst->create("0.0.0.0", "mypass") == -1)
		ret = devilution_net::inst->join("127.0.0.1", "mypass");
	*playerID = ret;
	return TRUE;
}

BOOL __stdcall SNetGetOwnerTurnsWaiting(DWORD *turns)
{
	// Is this the mirror image of SNetGetTurnsInTransit?
	*turns = 0;
	return TRUE;
}

BOOL STORMAPI SNetGetTurnsInTransit(int *turns)
{
	*turns = 0; // We do not queue turns at all
	return TRUE;
}

BOOLEAN __stdcall SNetSetBasePlayer(int)
{
	// engine calls this only once with argument 1
	return TRUE;
}

BOOL STORMAPI SNetPerformUpgrade(DWORD *upgradestatus)
{
	// since we never signal STORM_ERROR_REQUIRES_UPGRADE
	// the engine will not call this function
	UNIMPLEMENTED();
}

BOOL STORMAPI SNetSetGameMode(DWORD modeFlags, bool makePublic)
{
	// not called from engine
	UNIMPLEMENTED();
	return TRUE;
}
