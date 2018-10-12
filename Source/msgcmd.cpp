//HEADER_GOES_HERE

#include "../types.h"
//#include <new>

// remove this when <new> is available
static __inline void* operator new(size_t count, void* _p) { return _p; }

static float msgcmd_cpp_init_value = INFINITY;

// hack to get the object name from a pointer without using type_info.raw_name()
#define OBJECT_NAME(obj) (((const char*)&typeid(obj))+8)

// double-linked list implementation
struct LListNode {
	struct LListNode *prev;
	struct LListNode *next;
	LListNode() : prev(NULL), next(NULL) {}
	~LListNode();
};

struct EXTERNMESSAGE {
	struct LListNode node;
	char command[128];
	// stupid compiler won't generate a scalar destructor, fake it
	void* Cleanup(char final=0);
};

struct ChatCmd {
	int default_size;
	struct LListNode node;
	ChatCmd();
	~ChatCmd() { Cleanup(); }
	struct LListNode* delete_server_cmd_W(struct EXTERNMESSAGE* msg);
	struct EXTERNMESSAGE* msgcmd_alloc_event(int type, size_t extra_len=0, int flags=0);
	void msgcmd_event_type(struct EXTERNMESSAGE *msg, int type, struct LListNode *tail);
	void msgcmd_free_event();
	void Cleanup();
};

static ChatCmd sgChat_Cmd;

void __cdecl msgcmd_cmd_cleanup()
{
	sgChat_Cmd.msgcmd_free_event();
}

void __cdecl msgcmd_send_chat()
{
	static DWORD sgdwMsgCmdTimer;
	DWORD tick;
	struct EXTERNMESSAGE *msg;

	if ((int)sgChat_Cmd.node.next <= 0)
		return;

	msg = (struct EXTERNMESSAGE*)sgChat_Cmd.node.next;
	tick = GetTickCount();
	if (tick - sgdwMsgCmdTimer >= 2000) {
		sgdwMsgCmdTimer = tick;
		SNetSendServerChatCommand(msg->command);
		sgChat_Cmd.delete_server_cmd_W(msg);
	}
}

BOOL __fastcall msgcmd_add_server_cmd_W(const char *chat_message)
{
	if (chat_message[0] != '/')
		return FALSE;
	msgcmd_add_server_cmd(chat_message);
	return TRUE;
}

void __fastcall msgcmd_add_server_cmd(const char *command)
{
	size_t len = strlen(command);
	if (len && ++len <= 128) {
		struct EXTERNMESSAGE *msg = sgChat_Cmd.msgcmd_alloc_event(2);
		memcpy(msg->command, command, len);
	}
}

ChatCmd::ChatCmd()
{
	node.prev = &node;
	default_size = 0;
	node.next = (struct LListNode*)~((int)&node);
}

void ChatCmd::msgcmd_free_event() {
	while (1) {
		struct EXTERNMESSAGE *msg = (struct EXTERNMESSAGE*)node.next;
		if ((int)msg <= 0)
			return;
		msg->Cleanup();
		SMemFree(msg, OBJECT_NAME(*msg), SLOG_OBJECT);
	}
}

struct LListNode* ChatCmd::delete_server_cmd_W(struct EXTERNMESSAGE *msg) {
	struct LListNode *n;
	struct LListNode *Node;

	Node = msg ? &msg->node : &node;
	if ((int)Node->next <= 0)
		n = NULL;
	else
		n = Node->next;

	msg->Cleanup();
	SMemFree(msg, OBJECT_NAME(*msg), SLOG_OBJECT);
	return n;
}

struct EXTERNMESSAGE* ChatCmd::msgcmd_alloc_event(int type, size_t extra_len, int flags) {
	struct EXTERNMESSAGE *msg;
	void *obj = SMemAlloc(sizeof(*msg)+extra_len, OBJECT_NAME(*msg), SLOG_OBJECT, flags|SMEM_CLEAR);
	msg = new(obj) EXTERNMESSAGE();
	if (type)
		msgcmd_event_type(msg, type, NULL);
	return msg;
}

void* EXTERNMESSAGE::Cleanup(char final)
{
	// BUGFIX: no need to explicitly call member destructor
	node.~LListNode();
	this->~EXTERNMESSAGE();
	if (final&1 && this)
		SMemFree(this, "delete", SLOG_FUNCTION);
	return this;
}

void ChatCmd::msgcmd_event_type(struct EXTERNMESSAGE *msg, int type, struct LListNode *tail) {
	int len;
	struct LListNode *Node = &msg->node;
	struct LListNode *head;
	if (msg == NULL)
		Node = &node;
	if (Node->prev)
		Node->~LListNode();
	if (tail == NULL)
		tail = &node;
	switch (type) {
		case 1:
			Node->prev = tail;
			Node->next = tail->next;
			head = tail->next;
			len = default_size;
			if ((int)head <= 0)
				head = (struct LListNode*)~(int)head;
			else {
				if (len < 0)
					len = (char*)tail - (char*)tail->prev->next;
				head = (struct LListNode*)((char*)head + len);
			}
			head->prev = Node;
			tail->next = &msg->node;
			break;
		case 2:
			head = tail->prev;
			Node->prev = head;
			Node->next = head->next;
			head->next = &msg->node;
			tail->prev = Node;
	}
}

void ChatCmd::Cleanup()
{
	while (1) {
		if ((int)node.next <= 0)
			return;
		node.next->~LListNode();
	}
}

LListNode::~LListNode()
{
	struct LListNode *n;
	struct LListNode *p = prev;

	if (p) {
		n = next;
		if ((int)n <= 0)
			n = (struct LListNode*)~((size_t)n);
		else
			n = (struct LListNode*)((size_t)this - (size_t)p->next + (size_t)n);

		n->prev = p;
		prev->next = next;
		prev = NULL;
		next = NULL;
	}
}

