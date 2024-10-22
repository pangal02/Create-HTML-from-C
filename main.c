/*  Panagiotis Galiotos
    AM: 2022202000033
    dit20033@go.uop.gr
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void Guide(void);
void ListToFile(cmdList *head, FILE **fp); 
void CommandsToFile(cmdList *h, FILE **fp);

int main(int argc, char *argv){
   cmdList temp, *head = NULL;
   FILE *myFile, *file;
   int plt = 0, pll = 0, i = 0, s = 0, cntH = 0, cnt = 0, len = 0, flag = 0, ti = 0;
   char ch;

	Guide();

	do{
		memset(temp.cmd, 0, 10);
		printf("\nMake your choice: ");
		scanf("%[^ \n]", temp.cmd );
		ch = getchar(); //space
		
		if(strcmp( temp.cmd, "newTitle") == 0)
		{
            if(ti != 0)
		        head = delete_S(head);
			temp.text = (char *) malloc(50 * sizeof(char) );
			if(temp.text == NULL ){
			    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				exit(EXIT_FAILURE);
			}
			scanf("%[^\n]",temp.text);
			while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
			temp.param1 = temp.param2 = -1;
            head = insert_S(head, temp);
            ti = 1;
		}
		
		else if(strcmp(temp.cmd, "newHeading") == 0){
		    scanf("%d", &temp.param1); 
		    temp.text = (char *) malloc(80 * sizeof(char) );
			if(temp.text == NULL ){
			    printf("\nERROR:Memory allocation failed - not enough memory.\n");
			    exit(EXIT_FAILURE);
			}
		    
		    ch = getchar(); //space
		    scanf("%[^\n]",temp.text);
			while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
			while( (temp.param1 <= 0) && (temp.param1 > 6)){
		        printf("\nGive the size of Heading (1-6): ");
		        scanf("%d", &temp.param1);
		        while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
		    }
			temp.param2 = -1;
			head = insert_L(head, temp);
		}
		
		else if(strcmp( temp.cmd, "newLine") == 0){
		    head = insert_L(head, temp);
		}
		
		else if(strcmp( temp.cmd, "newPar") == 0)
		{
			temp.text = (char *) malloc(250 * sizeof(char) );
			if(temp.text == NULL ){
			    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				exit(EXIT_FAILURE);
			}
			temp.text[0] = ' ';
			scanf("%[^\n]",&temp.text[1]); 
			len = strlen(temp.text);
			temp.text[len] = ' ';
			while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
			temp.param1 = temp.param2 = -1;
            head = insert_L(head, temp);
		}
		
		else if(strcmp( temp.cmd, "newTable") == 0){
		   do{
		        scanf("%d %d", &temp.param1, &temp.param2);
		        ch = getchar(); //space
                plt = (temp.param1 * temp.param2); //plithos stoixeiwn pinaka
		        plt = plt + plt;
		        temp.text = (char *) malloc(plt * sizeof(char) );
			    if(temp.text == NULL ){
			        printf("\nERROR:Memory allocation failed - not enough memory.\n");
				    exit(EXIT_FAILURE);
			    }
		    
		        scanf("%[^\n]",temp.text);
		        while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
                s = strlen(temp.text);
                if(s > plt-1){
                    printf("ERROR: Dosate plithos stoixeiwn pou upervainei ta oria tou pinaka!\n");
                    printf("Table[%d][%d] = ", temp.param1, temp.param2);
                }
                
                if( (temp.param1 * temp.param2) <=0 ){
                    printf("\nERROR: Dwsate lathos mh egkuro plithos keliwn tou pinaka! Dwste apo thn arxh ta stoixeia tou newTable\n");
                    printf("newTable: ");
                }
		    }while( (s > plt-1) || ( (temp.param1 * temp.param2) <=0) );
		    
		    head = insert_L(head, temp);
		}
		
		else if(strcmp( temp.cmd, "newBlist") == 0){//3 abc,def,ghi
			scanf("%d", &temp.param1);
			ch = getchar();//space
            pll = (temp.param1 * temp.param1);
		    pll = pll + temp.param1;
			temp.text = (char *) malloc(pll * sizeof(char) );
			if(temp.text == NULL ){
			    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				exit(EXIT_FAILURE);
			}
		    do{
		        scanf("%[^\n]",temp.text);
		        while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
                s = strlen(temp.text);
                if(s > pll-1){
                    printf("ERROR: Dosate plithos stoixeiwn pou upervainei ta oria tis listas!\n");
                    printf("Blist with [%d] --> ", temp.param1);
                }
		    }while(s > pll-1);
			temp.param2 = -1;
            head = insert_L(head, temp);
		}
		
		else if(strcmp( temp.cmd, "newNlist") == 0){
			scanf("%d", &temp.param1);
			ch = getchar();//space
            pll = (temp.param1 * temp.param1);
		    pll = pll + temp.param1;
			temp.text = (char *) malloc(pll * sizeof(char) );
            if(temp.text == NULL ){
			    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				exit(EXIT_FAILURE);
			}
		    do{
		        scanf("%[^\n]",temp.text);
		        while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
                s = strlen(temp.text);
                if(s > pll-1){
                    printf("ERROR: Dosate plithos stoixeiwn pou upervainei ta oria tis listas!\n");
                    printf("Nlist with [%d] --> ", temp.param1);
                }
		    }while(s > pll-1);
			temp.param2 = -1;
            head = insert_L(head, temp);
		}
		
		else if(strcmp( temp.cmd, "undo") == 0){
		    if(head == NULL){
		        printf("ERROR: List is already empty!\n");
		    }
		    else
		        head = delete_E(head);
		}
		
		else if(strcmp(temp.cmd, "print-l2f") == 0){
		    scanf("%d", &temp.param1);
		    while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
		    temp.param2 = 0;
		    printLtF(head, temp.param1, &cnt);
            printf(".\n");
            cnt = 0;
		}
		
		else if(strcmp(temp.cmd, "print-f2l") == 0){
		    scanf("%d", &temp.param1);
		    while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
            printFtL(head, temp.param1);
		}
		
		else if(strcmp(temp.cmd, "show") == 0){
		    temp.text = (char *) malloc(10 * sizeof(char) );
			if(temp.text == NULL ){
			    printf("\nERROR:Memory allocation failed - not enough memory for this text.\n");
				exit(EXIT_FAILURE);
			}
			scanf("%[^\n]",temp.text);
            printf("mainShow=|%s|",temp.text);
			while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
			temp.param1 = temp.param2 = -1;
			Show_print(head, temp.text);
		}
		
		else if(strcmp(temp.cmd, "load") == 0){
		    temp.text = (char *) malloc(10 * sizeof(char) );
			if(temp.text == NULL ){
			    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				exit(EXIT_FAILURE);
			}
            scanf("%d", &temp.param1);
            
            ch = getchar(); //space
            scanf("%[^\n]",temp.text);
			while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
            while(temp.param1 <= 0){
                printf("Dwse thetiko gia to diabasma grammwn apo to arxeio: ");
                scanf("%d", &temp.param1);
                while( (ch = getchar() )!= '\n' && ch != EOF); //'\n'
            }
            
			temp.param2 = -1;
        /*Anoigma arxeiou**************************************************************************************************************/
            myFile = fopen(temp.text, "r");
            if(myFile == NULL)
                printf("\nError: %s can not be opened\n", temp.text);
            else{
            memset(temp.cmd, 0, 10);
                printf("\n%s is opened successfully!\n", temp.text);
                    i = 0;
                    flag = temp.param1;
                    while(!(feof(myFile) )&& (i < flag)){
                        
                        fscanf(myFile, "%s", temp.cmd);
                        if(strcmp( temp.cmd, "newTitle") == 0)
		                {
                            if(ti != 0)  
		                        head = delete_S(head);
			                temp.text = (char *) malloc(50 * sizeof(char) );
			                if(temp.text == NULL ){
			                    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				                flag = 0;
				                break;
			                }
			                ch = fgetc(myFile); //space
			                fscanf(myFile, "%[^\r]",temp.text);
			                while( ((ch = fgetc(myFile) )!= '\r' && ch !='\n') && ch != EOF); //'\n'
			                temp.param1 = temp.param2 = -1;
                            head = insert_S(head, temp);
                            ti = 1;
		                }
		
		                else if(strcmp(temp.cmd, "newHeading") == 0){
                            fscanf(myFile, "%d", &temp.param1);
		                    temp.text = (char *) malloc(80 * sizeof(char) );
			                if(temp.text == NULL ){
			                    printf("\nERROR:Memory allocation failed - not enough memory.\n");
			                    flag = 0;
				                break;
			                }
		                    ch = fgetc(myFile); //space
		                    fscanf(myFile, "%[^\r]",temp.text);
			                while( (ch = fgetc(myFile) )!= '\r' && ch != '\n' && ch != EOF); //'\n'
			                if( (temp.param1 <= 0) && (temp.param1 > 6)){
		                        printf("\nERROR: in File the size of Heading is %d <> (1-6)...",temp.param1);
		                        flag = 0;
				                break;
			                }
			                temp.param2 = -1;
			                head = insert_L(head, temp);
                       }
		            
		                else if(strcmp( temp.cmd, "newLine") == 0){
		                    temp.param1 = temp.param2 = -1;
		                    head = insert_L(head, temp);
		                }
		
		                else if(strcmp( temp.cmd, "newPar") == 0){
			                temp.text = (char *) malloc(250 * sizeof(char) );
			                if(temp.text == NULL ){
			                    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				                flag = 0;
				                break;
			                }
			                temp.text[0] = ' ';
			                fscanf(myFile, "%[^\r]",&temp.text[1]);
		                    len = strlen(temp.text);
			                temp.text[len] = ' ';
			                while( (ch = fgetc(myFile) )!= '\r' && ch != '\n' && ch != EOF); //'\n'
			                temp.param1 = temp.param2 = -1;
                            head = insert_L(head, temp);
		                }
		
		                else if(strcmp( temp.cmd, "newTable") == 0){
		                    fscanf(myFile, "%d %d", &temp.param1, &temp.param2);
		                    ch = fgetc(myFile); //space
                            plt = (temp.param1 * temp.param2); //plithos stoixeiwn pinaka
		                    plt = plt + plt;
		                    temp.text = (char *) malloc(plt * sizeof(char) );
			                if(temp.text == NULL ){
			                    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				                flag = 0;
				                break;
			                }
		                    fscanf(myFile,"%[^\r]",temp.text);
                            while( (ch = fgetc(myFile) )!= '\r' && ch != '\n' && ch != EOF); //'\n'
                            s = strlen(temp.text);
                            if(s > plt-1){
                                printf("ERROR: To plithos twn stoixeiwn upervainei ta oria tou pinaka!\nARRAY[%d][%d]...", temp.param1, temp.param2);
                                flag = 0;
                                break;
                            }
                            if( (temp.param1 * temp.param2) <=0 ){
                                printf("\nERROR: Sto arxeio dwsate mh egkuro plithos keliwn tou pinaka...\n");
                                flag = 0;
                                break;
                            }
		                    head = insert_L(head, temp);
		                }
		
		                else if(strcmp( temp.cmd, "newBlist") == 0){
			                fscanf(myFile, "%d", &temp.param1);
			                ch = fgetc(myFile);//space
                            pll = (temp.param1 * temp.param1);
		                    pll = pll + temp.param1;
			                temp.text = (char *) malloc(pll * sizeof(char) );
			                if(temp.text == NULL ){
			                    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				                flag = 0;
                                break;
			                }
		                    fscanf(myFile, "%[^\r]",temp.text);
		                    while( (ch = fgetc(myFile) )!= '\r' && ch != '\n' && ch != EOF); //'\n'
                            s = strlen(temp.text);
                            if(s > pll-1){
                                printf("ERROR: Sto arxeio dosate plithos stoixeiwn pou upervainei ta oria ths listas!\n");
                                printf("Blist with [%d] stoixeia...", temp.param1);
                                flag = 0;
                                break;
                            }
			                temp.param2 = -1;
                            head = insert_L(head, temp);
		                }
		
		                else if(strcmp( temp.cmd, "newNlist") == 0){
			                fscanf(myFile,"%d", &temp.param1);
			                ch = fgetc(myFile);//space
                            pll = (temp.param1 * temp.param1);
		                    pll = pll + temp.param1;
			                temp.text = (char *) malloc(pll * sizeof(char) );
                            if(temp.text == NULL ){
			                    printf("\nERROR:Memory allocation failed - not enough memory.\n");
				                flag = 0;
                                break;
			                }
		                    fscanf(myFile,"%[^\r]",temp.text);
		                    while( (ch = fgetc(myFile) )!= '\r' && ch != '\n' && ch != EOF); //'\n'
                            s = strlen(temp.text);
                            if(s > pll-1){
                                printf("ERROR: Dosate plithos stoixeiwn pou upervainei ta oria tis listas!\n");
                                printf("Nlist with [%d]... ", temp.param1);
                                flag = 0;
                                break;
                            }
			                temp.param2 = -1;
                            head = insert_L(head, temp);
		                }
                                        
                        else if(strcmp( temp.cmd, "undo") == 0){
		                    if(head == NULL){
		                        printf("ERROR: List is already empty!\n");
		                    }
		                    else
		                        head = delete_E(head);
		                }
                        
                        else if(strcmp(temp.cmd, "print-l2f") == 0){
		                    fscanf(myFile, "%d", &temp.param1);
		                    while( (ch = fgetc(myFile) )!= '\r' &&ch !='\n' && ch != EOF); //'\n'
		                    temp.param2 = 0;
		                    printLtF(head, temp.param1, &cnt);
                            printf(".\n");
                            cnt = 0;
		                }
		                else if(strcmp(temp.cmd, "print-f2l") == 0){
		                    fscanf(myFile, "%d", &temp.param1);
		                    while( (ch = fgetc(myFile) )!= '\r' &&ch !='\n' && ch != EOF); //'\n'
                            printFtL(head, temp.param1);
		                }
		
		                else if(strcmp(temp.cmd, "show") == 0){
		                    temp.text = (char *) malloc(10 * sizeof(char) );
			                if(temp.text == NULL ){
			                    printf("\nERROR:Memory allocation failed - not enough memory for this text in File.\n");
				                break;
			                }
			                fscanf(myFile, "%[^ \t\n]",temp.text);
                                                           printf("1show.temp=|%s|",temp.text);
			                while( (ch = fgetc(myFile) )!= '\r' &&ch !='\n' && ch != EOF); //'\n'
			                temp.param1 = temp.param2 = -1;
                               printf("2show.temp=|%s|",temp.text);
			                Show_print(head, temp.text);
		                }
                        else if(strcmp(temp.cmd, "help") == 0){
                            Guide();
                        }
                        
		                else{
		                    printf("ERROR: on File, in row <%d>\n",i+1);
		                    flag = 0;
		                    break;
		                }
                        memset(temp.cmd, 0, 10);
		               i++;
                    }//while
            }//else
            
        //Kleisimo arxeiou
            if(myFile != NULL){
	            fclose(myFile);
	            printf("\nThe File is closed successfully\n");
            }
		}
		
		else if(strcmp(temp.cmd, "help") == 0){
            Guide();
        }
		
		else if(strcmp( temp.cmd, "save") != 0){
		    printf("\nLathos entoli\n");
			printf("Press \"Enter\" to continue...\n");
		    while( (ch = getchar() )!= '\n'  && ch != EOF);
		}
		

	}while(strcmp( temp.cmd, "save") != 0);//save myfile.html
	scanf("%[^\n]",temp.text);
	strcat(temp.text,".html");
	
//anoigma arxeiou
    if( (file = fopen(temp.text, "w")) == NULL)
        printf("Eroor: File \"%s\" can not be opened!\n", temp.text);
    ListToFile(head, &file); 
    fclose(file);
    printf("\nThe file \"%s\" has been created!", temp.text);
    
    head = FreeTheList(head);
    if(head == NULL){
        printf("\nH lista adeiase!\n");
    }
    else{
        printf("\nH lista DEN adeiase!\n");
    }
	printf("\nEND OF RUN\n\n");
   return 0;
} //main


void ListToFile(cmdList *head, FILE **fp)
{
    if(head == NULL){
        printf("THE LIST IS EMPTY\n");
            return;
    }
    else if(head->next == NULL){
            printf("\nA html file must contain at least 2 elements HEAD and BODY!\n");
            return;
    }
    else{
        fprintf((*fp), "<HTML>\n");
        while( (head->next != NULL) ){
            CommandsToFile(head, fp);
            head = head->next;
        }
        if(head->next == NULL){
            CommandsToFile(head, fp);
            head = head->next;
        }
    }
    fprintf((*fp), "\n</BODY>\n");
    fprintf((*fp), "\n</HTML>\n");
    
}


void CommandsToFile(cmdList *h, FILE **fp)
{
  int i , j, n = 0;
  char *str = NULL;
  
  n = (h->param1) * (h->param2);
  
    
    if(strcmp( h->cmd, "newTitle") == 0)
    {
        fprintf((*fp), "<HEAD>\n\t<TITLE>%s</TITLE>\n</HEAD>\n", h->text);
        fprintf((*fp), "\n<BODY>\n");
    }
    else if(strcmp(h->cmd, "newHeading") == 0){
        fprintf((*fp), "\n\t<H%d> %s </H%d>", h->param1,  h->text, h->param1);
    }
    else if(strcmp(h->cmd, "newLine") == 0){
        fprintf((*fp),"\n<HR>\n");
    }
    else if(strcmp(h->cmd, "newPar") == 0){
        fprintf((*fp), "\n<P>%s\n", h->text);
    }
    
    else if(strcmp(h->cmd, "newTable") == 0){
        
        fprintf((*fp), "\n<TABLE BORDER=1\n");
        //fprintf((*fp), "\n\t<CAPITON ALIGN=BOTOM>TABLE</CAPTION>\n");
        str = strtok(h->text, ",");
        for(i = 0; i < h->param1; i++){
            if(str == NULL)
                break;
            fprintf((*fp), "\n\t<TR>\n");
            for(j = 0; j < h->param2; j++)
            {
                fprintf((*fp), "\t\t<TD>%s</TD>\n",str);
                if(str != NULL){
                    str = strtok(NULL, ",");
                }
                else
                    break;
            }
            fprintf((*fp), "\n\t</TR>\n");
        }
        fprintf((*fp), "\n</TABLE>\n");
    }
    else if(strcmp( h->cmd, "newBlist") == 0){
        str = strtok(h->text, ",");
        fprintf( (*fp), "\n<UL>\n");
        for(i = 0; i < h->param1; i++){
            if(str == NULL)
                    break;
            fprintf((*fp), "\t\t<LI>%s</LI>\n",str);
            if(str != NULL){
                str = strtok(NULL, ",");
            }
                else
                    break;
        }
        fprintf((*fp), "</UL>\n");
    }
    
    else if(strcmp( h->cmd, "newNlist") == 0){
        str = strtok(h->text, ",");
        fprintf((*fp), "\n<OL>\n");
        
        for(i = 0; i < h->param1; i++){
                if(str == NULL)
                    break;
                fprintf((*fp), "\t<LI>%s\n", str);
                if(str != NULL){
                    str = strtok(NULL, ",");
                }
                else
                    break;
            
        }
        fprintf((*fp), "</OL>\n");
    }

}    



void Guide(void)
{
    printf("\nThis programm creat a new HTML file\n");
    printf("\t\tMENU\n=====================================================\n");
	printf("To create a new Title, type \"newTitle [text]\"\n");
	printf("To create a new Heading, type \"newHeading x [test]\"\n");
	printf("To create a new Line, type \"newLine\"\n");
	printf("To create a new Paragraph, type \"newPar [text]\"\n");
	printf("To create a new Table, type \"newTable x y [text]\"\n");
	printf("To create a new Bulled List, type \"newBlist x [text]\"\n");
	printf("To create a new List, type \"newNlist x [text]\"\n");
    printf("To print the list Start --> End, type \"print-f2l x\"\n");
    printf("To print the list End --> Start, type \"print-l2f x\"\n");
    printf("To undo the last selection, type \"undo\"\n");
    printf("To fill the list from file, type \"load x [file_name]\"\n");
    printf("To save the list to file, type \"save [filename]\"\n");
    printf("To help, type \"help\"\n");
}
