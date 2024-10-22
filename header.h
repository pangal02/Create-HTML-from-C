typedef struct commandList
{
	char cmd[10];
	int param1;
	int param2;
	char *text;
	struct commandList *next;
} cmdList;

cmdList *insert_S(cmdList *head, cmdList list);
cmdList *insert_L(cmdList *head, cmdList list);
cmdList *Undo_L(cmdList *head );
void printLtF(cmdList *h, int num, int *cnt);
void printFtL(cmdList *h, int num);
cmdList *delete_S(cmdList *header);
cmdList *delete_E(cmdList *header);
cmdList *FreeTheList(cmdList *header);
void Show_print(cmdList *h, char *str1);
