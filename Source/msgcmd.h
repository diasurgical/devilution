//HEADER_GOES_HERE
#ifndef __MSGCMD_H__
#define __MSGCMD_H__

void msgcmd_cmd_cleanup();
void msgcmd_send_chat();
BOOL msgcmd_add_server_cmd_W(const char *chat_message);
void msgcmd_add_server_cmd(const char *command);

#endif /* __MSGCMD_H__ */
