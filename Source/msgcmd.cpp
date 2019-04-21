#include "diablo.h"
#include "list.h"

#define COMMAND_LEN 128

// static float msgcmd_init_cpp_value = 0x7F800000;

struct EXTERNMESSAGE {
	LIST_LINK(EXTERNMESSAGE) m_Link;
	char command[COMMAND_LEN];
	~EXTERNMESSAGE()
	{
		// BUGFIX: this is already called by m_Link's destructor
		m_Link.Unlink();
	}
	static void operator delete(void *p) {
		if (p)
			SMemFree(p, "delete", SLOG_FUNCTION, 0);
	}
};

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
