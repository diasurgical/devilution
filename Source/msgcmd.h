//HEADER_GOES_HERE
#ifndef __MSGCMD_H__
#define __MSGCMD_H__

void msgcmd_init_event();
void msgcmd_cleanup_chatcmd_atexit();
void __cdecl msgcmd_cleanup_chatcmd(void);
void msgcmd_cmd_cleanup();
void msgcmd_send_chat();
BOOLEAN msgcmd_add_server_cmd_W(char *chat_message);
void msgcmd_add_server_cmd(char *command);
void msgcmd_init_chatcmd(ChatCmd *chat_cmd);
void msgcmd_free_event(ChatCmd *a1);
BOOLEAN msgcmd_delete_server_cmd_W(ChatCmd *cmd, ServerCommand *extern_msg);
ChatCmd *msgcmd_alloc_event(ChatCmd *a1, int a2, int a3, int a4, int a5);
void msgcmd_remove_event(ChatCmd *a1, int a2);
void msgcmd_event_type(ChatCmd *a1, int a2, int *a3, int a4, int a5);
void msgcmd_cleanup_chatcmd_1(ChatCmd *a1);
void msgcmd_cleanup_extern_msg(ServerCommand **extern_msgs);

/* rdata */

#endif /* __MSGCMD_H__ */
