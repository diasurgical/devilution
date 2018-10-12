//HEADER_GOES_HERE
#ifndef __MSGCMD_H__
#define __MSGCMD_H__

void __cdecl msgcmd_send_chat();
BOOL __fastcall msgcmd_add_server_cmd_W(const char *chat_message);
void __fastcall msgcmd_add_server_cmd(const char *command);
void __cdecl msgcmd_cmd_cleanup();

#endif /* __MSGCMD_H__ */
