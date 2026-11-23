/**
 * @file msgcmd.cpp
 *
 * Functions for sending commands to Battle.net.
 *
 * See http://classic.battle.net/info/commands.shtml for a list of commands.
 */
#include "all.h"
#include "../3rdParty/Storm/Source/storm.h"

#ifndef HELLFIRE

#include <stddef.h> // for offsetof
// for typeid: the CRT's type_info
class type_info {
public:
	virtual ~type_info();
private:
	void *_m_data;
	char _m_d_name[1];
};

#include "list.h"

#define COMMAND_LEN 128

// static float msgcmd_init_cpp_value = 0x7F800000;

struct EXTERNMESSAGE {
	LIST_LINK(EXTERNMESSAGE)
	m_Link;
	char command[COMMAND_LEN];
	void *operator new(size_t n, DWORD extralen, int flags)
	{
		return SMemAlloc(n + extralen, (char *)OBJECT_NAME(EXTERNMESSAGE), SLOG_OBJECT, flags | (1 << 3));
	}
	void operator delete(void *address)
	{
	}
	void *Delete(DWORD flags);
};

// inline: in 1.09b it is emitted with the list functions, after its callers
inline void *EXTERNMESSAGE::Delete(DWORD flags)
{
	// BUGFIX: this is already called by m_Link's destructor
	m_Link.Unlink();
	this->~EXTERNMESSAGE();
	if ((flags & 0x1) && this) {
		SMemFree(this, "delete", SLOG_FUNCTION, 0);
	}
	return this;
}

static TList<EXTERNMESSAGE> sgChat_Cmd;

void msgcmd_cmd_cleanup()
{
	sgChat_Cmd.DeleteAll();
}

void msgcmd_send_chat()
{
	DWORD tick;
	struct EXTERNMESSAGE *msg = sgChat_Cmd.Head();

	if (msg) {
		static DWORD sgdwMsgCmdTimer;
		tick = GetTickCount();
		if (tick - sgdwMsgCmdTimer >= 2000) {
			sgdwMsgCmdTimer = tick;
			SNetSendServerChatCommand(msg->command);
			sgChat_Cmd.Remove(msg);
		}
	}
}

BOOL msgcmd_add_server_cmd_W(const char *chat_message)
{
	if (chat_message[0] != '/')
		return FALSE;
	msgcmd_add_server_cmd(chat_message);
	return TRUE;
}

void msgcmd_add_server_cmd(const char *command)
{
	size_t len = strlen(command);
	if (len && ++len <= COMMAND_LEN) {
		struct EXTERNMESSAGE *msg = sgChat_Cmd.Create();
		memcpy(msg->command, command, len);
	}
}
#endif
