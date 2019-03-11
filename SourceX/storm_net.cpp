#include "dvlnet/abstract_net.h"
#include "pch.h"

namespace dvl {

static std::unique_ptr<net::abstract_net> dvlnet_inst;

BOOL STORMAPI SNetReceiveMessage(int *senderplayerid, char **data, int *databytes)
{
	if (!dvlnet_inst->SNetReceiveMessage(senderplayerid, data, databytes)) {
		SErrSetLastError(STORM_ERROR_NO_MESSAGES_WAITING);
		return FALSE;
	}
	return TRUE;
}

BOOL STORMAPI SNetSendMessage(int playerID, void *data, unsigned int databytes)
{
	return dvlnet_inst->SNetSendMessage(playerID, data, databytes);
}

BOOL STORMAPI SNetReceiveTurns(int a1, int arraysize, char **arraydata, unsigned int *arraydatabytes,
    DWORD *arrayplayerstatus)
{
	if (a1 != 0)
		UNIMPLEMENTED();
	if (arraysize != MAX_PLRS)
		UNIMPLEMENTED();
	if (!dvlnet_inst->SNetReceiveTurns(arraydata, arraydatabytes, arrayplayerstatus)) {
		SErrSetLastError(STORM_ERROR_NO_MESSAGES_WAITING);
		return FALSE;
	}
	return TRUE;
}

BOOL STORMAPI SNetSendTurn(char *data, unsigned int databytes)
{
	return dvlnet_inst->SNetSendTurn(data, databytes);
}

int __stdcall SNetGetProviderCaps(struct _SNETCAPS *caps)
{
	return dvlnet_inst->SNetGetProviderCaps(caps);
}

void *__stdcall SNetUnregisterEventHandler(int evtype, void(__stdcall *func)(struct _SNETEVENT *))
{
	return dvlnet_inst->SNetUnregisterEventHandler(*(event_type *)&evtype, func);
}

void *__stdcall SNetRegisterEventHandler(int evtype, void(__stdcall *func)(struct _SNETEVENT *))
{
	return dvlnet_inst->SNetRegisterEventHandler(*(event_type *)&evtype, func);
}

BOOL STORMAPI SNetDestroy()
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetDropPlayer(int playerid, DWORD flags)
{
	return dvlnet_inst->SNetDropPlayer(playerid, flags);
}

BOOL STORMAPI SNetGetGameInfo(int type, void *dst, unsigned int length, unsigned int *byteswritten)
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetLeaveGame(int type)
{
	return dvlnet_inst->SNetLeaveGame(type);
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
	dvlnet_inst = net::abstract_net::make_net(provider);
	return ui_info->selectnamecallback(client_info, user_info, ui_info, fileinfo, provider, NULL, 0, NULL, 0, NULL);
}

/**
 * @brief Called by engine for single, called by ui for multi
 */
BOOL STORMAPI SNetCreateGame(const char *pszGameName, const char *pszGamePassword, const char *pszGameStatString,
    DWORD dwGameType, char *GameTemplateData, int GameTemplateSize, int playerCount,
    char *creatorName, char *a11, int *playerID)
{
	if (GameTemplateSize != 8)
		ABORT();
	net::buffer_t game_init_info(GameTemplateData, GameTemplateData + GameTemplateSize);
	dvlnet_inst->setup_gameinfo(std::move(game_init_info));

	char addrstr[129] = "0.0.0.0";
	SRegLoadString("dvlnet", "bindaddr", 0, addrstr, 128);
	*playerID = dvlnet_inst->create(addrstr, pszGamePassword);
	return *playerID != -1;
}

BOOL STORMAPI SNetJoinGame(int id, char *pszGameName, char *pszGamePassword, char *playerName, char *userStats, int *playerID)
{
	*playerID = dvlnet_inst->join(pszGameName, pszGamePassword);
	return *playerID != -1;
}

/**
 * @brief Is this the mirror image of SNetGetTurnsInTransit?
 */
BOOL __stdcall SNetGetOwnerTurnsWaiting(DWORD *turns)
{
	return dvlnet_inst->SNetGetOwnerTurnsWaiting(turns);
}

BOOL STORMAPI SNetGetTurnsInTransit(int *turns)
{
	return dvlnet_inst->SNetGetTurnsInTransit(turns);
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

}
