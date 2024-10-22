#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


cmdList *insert_S(cmdList *head, cmdList list)
{
   cmdList *new;

    new = (cmdList *) malloc(sizeof(cmdList));
    if(new == NULL){
        printf("ERROR: not enough space!\n");
        exit(0);
    }
    strcpy(new->cmd, list.cmd);
    new->param1 = list.param1;
    new->param2 = list.param2;
    new->text = strdup(list.text);
    new->next = head;
    
    if(head == NULL) //if list is empty
        head = new;
        
    return new;
}

cmdList *insert_L(cmdList *head, cmdList list)
{
    cmdList *new, *tmp;
    
        new = (cmdList *) malloc(sizeof(cmdList));
        if(new == NULL){
            printf("ERROR: not enough space!\n");
            exit(0);
        }
        strcpy(new -> cmd, list.cmd);
        new->param1 = list.param1;
        new->param2 = list.param2;
        if(list.text!=NULL)
            new->text = strdup(list.text);
        new->next = NULL;
        
        if(head == NULL)
            return new;
        
        else{
            tmp = head;
            while(tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next = new;
            return head;
        }
}


void printLtF(cmdList *h, int num, int *cnt)
{
    if(h==NULL)
        return;
        
    printLtF(h->next, num, cnt);
    *cnt+=1;
    
    if(*cnt <= num)
        printf("%s --> ", h->cmd);
    
    
}


void printFtL(cmdList *h, int num)
{
    int i=0;
    if (h == NULL )
      printf( "List is empty.\n\n" );
      
    else{
        
            while( (h != NULL) && (i < num)){
                    printf( "%s --> ", h->cmd);
                    i++;
                    h = h->next;
            }
            printf(".\n");
        }
    }


cmdList *delete_S(cmdList *header){
   cmdList *tmp2 = header;

    if(header == NULL) //list is empty
        return header;

    else{
        tmp2 = header->next;
        free(header);
        return tmp2;
    }
}

cmdList *delete_E(cmdList *header)
{
    cmdList *tmp1;
    
    tmp1 = header;
    
        if(header == NULL){
            return header;
        }
        else if(header->next == NULL)
        {
            free(header);
            return NULL;
        }
        else{
            while(tmp1->next->next != NULL){
                tmp1 = tmp1->next;
            }
            free(tmp1->next);
            tmp1->next = NULL;
        }
        return header;
}

cmdList *FreeTheList(cmdList *header){
    cmdList *cur, *n;
    cur = header;
    
        while(cur != NULL){
            n = cur->next;
            //free(header->text);
            free(cur);
            cur = n;
        }
        header = NULL;
        return header;
}

void Show_print(cmdList *h, char *str1){
    cmdList *tmp;
    char *ptr = NULL;
    int cnt = 0;
    
    tmp = h;

        if(h == NULL){
            printf("EMPTY LIST\n");
            return;
        }
        else if(tmp->next == NULL){ //1 stoixeio
            ptr = strstr(tmp->cmd, str1);
                if(ptr){
                    printf("\n%s", tmp->cmd);
                    cnt++;
                }
        }
        else{
            while( (tmp->next != NULL) ){
                ptr = strstr(tmp->cmd, str1);
                if(ptr){
                    printf("\n%s", tmp->cmd);
                    cnt++;
                }
                tmp = tmp->next;
            }
                if(tmp->next == NULL){ //1 stoixeio
                    ptr = strstr(tmp->cmd, str1);
                    if(ptr){
                        printf("\n%s", tmp->cmd);
                        cnt++;
                    }
                }   
        }
        if(cnt == 0)
            printf("command not found...\n");
}
