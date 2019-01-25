/** @file
 *
 * A minimal implementation of the Storm network stack necessary for local play.
 */
#include "../types.h"

struct StubMessage {
	int playerid;
	std::string data;
};

/** A queue of messages waiting to be processed. */
static std::deque<StubMessage> snet_messages;
/**
 * Last message returned from SNetReceiveMessage().
 * Must always be kept alive because the caller will read the data afterwards.
 */
static StubMessage snet_current_message;

BOOL STORMAPI SNetReceiveMessage(int *senderplayerid, char **data, int *databytes)
{
	DUMMY_ONCE();

	if (snet_messages.empty()) {
		SErrSetLastError(STORM_ERROR_NO_MESSAGES_WAITING);
		return FALSE;
	}

	snet_current_message = std::move(snet_messages.front());
	snet_messages.pop_front();

	*senderplayerid = snet_current_message.playerid;
	*data = const_cast<char *>(snet_current_message.data.data());
	*databytes = snet_current_message.data.size();

	return TRUE;
}

BOOL STORMAPI SNetSendMessage(int playerID, void *data, unsigned int databytes)
{
	DUMMY_ONCE();

	snet_messages.push_back(StubMessage{playerID, std::string((char *)data, databytes)});
	return TRUE;
}

int __stdcall SNetInitializeProvider(unsigned long a1, struct _SNETPROGRAMDATA *client_info,
                                     struct _SNETPLAYERDATA *user_info, struct _SNETUIDATA *ui_info,
                                     struct _SNETVERSIONDATA *fileinfo)
{
	DUMMY();

	ui_info->selectnamecallback(client_info, user_info, ui_info, fileinfo, 0, NULL, 0, NULL, 0, NULL);

	return TRUE;
}

BOOL STORMAPI SNetCreateGame(const char *pszGameName, const char *pszGamePassword, const char *pszGameStatString,
                             DWORD dwGameType, char *GameTemplateData, int GameTemplateSize, int playerCount,
                             char *creatorName, char *a11, int *playerID)
{
	DUMMY();
	return TRUE;
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

BOOL STORMAPI SNetPerformUpgrade(DWORD *upgradestatus)
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetReceiveTurns(int a1, int arraysize, char **arraydata, unsigned int *arraydatabytes,
                               DWORD *arrayplayerstatus)
{
	DUMMY_ONCE();
	return TRUE;
}

BOOL STORMAPI SNetSendTurn(char *data, unsigned int databytes)
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetSetGameMode(DWORD modeFlags, bool makePublic)
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetSendServerChatCommand(const char *command)
{
	DUMMY();
	return TRUE;
}

BOOL STORMAPI SNetGetTurnsInTransit(int *turns)
{
	DUMMY_ONCE();
	return TRUE;
}

BOOL __stdcall SNetGetOwnerTurnsWaiting(DWORD *)
{
	DUMMY();
	return TRUE;
}

void *__stdcall SNetUnregisterEventHandler(int, void(__stdcall *)(struct _SNETEVENT *))
{
	DUMMY();
	return (void *)-1;
}

void *__stdcall SNetRegisterEventHandler(int, void(__stdcall *)(struct _SNETEVENT *))
{
	DUMMY();
	return (void *)-1;
}

BOOLEAN __stdcall SNetSetBasePlayer(int)
{
	DUMMY();
	return TRUE;
}

int __stdcall SNetGetProviderCaps(struct _SNETCAPS * caps)
{
	memset(caps, 0, sizeof(struct _SNETCAPS));
	caps->maxplayers = 1;
	caps->bytessec = 100000;
	return 1;
}
