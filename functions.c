//Functions for personal assistant project.
/*
               By  M VISWANADH.
	           S AKHIL.
		   A APPALA.
	       FINISHED ON  17 03 2020
*/


#include<stdio.h>
#include<ncurses.h>
#include<time.h>
#include<stdlib.h>
#include<termios.h>
#include<string.h>
#include"header.h"

FILE *signin(FILE *fp)                 //Function for signin.
{
    sign_in a;                           //a is variable of data type sign in.
    rewind(fp);
    printf("Please enter your user name of atmost length 25\n ");
    printf("\t\t\tUSER NAME : ");
    scanf("%25s",a.user_name);
    printf("Please enter your password of almostlength 10\n");
    printf("\t\t\tPASSWORD : ");
    scanf("%10s",a.pass_word);
    fwrite(&a,sizeof(sign_in),1,fp);
    return fp;	
}
//_____________________________________________________________________________
int login(FILE *fp)
{
    extern char owner[27];
    strcpy(owner,"");
    log_in a,b;
    rewind(fp);             //remove and check.
    if(fread(&a,sizeof(sign_in),1,fp)==0)
	return 2;             //impossible case.
    else
    { 
	rewind(fp);
	printf("\n Please enter your USER NAME : ");
	getchar();
	scanf("%[^\n]s",b.user_name);
	getchar();
	printf("\n Please enter your PASS WORD :  ");
	scanf("%10s",b.pass_word);
	if(strcmp(b.user_name,a.user_name)==0)
	    if(strcmp(a.pass_word,b.pass_word)==0)
	    {
		strcat(owner,a.user_name);
		return 0;
	    }
	    else
		return -1;
	else
	    return -1;	
    }
}
//_______________________________________________________________________________
void Reminders()
{
    Event p;
    FILE*f2=fopen("special_days","r");
    time_t T= time(NULL);
    struct  tm *t = localtime(&T);
    if (f2==NULL)
	puts("Unable to open file");
    else
    {
	printf("\n\t\t----------------------------------------------\n");
	while(fread(&p,sizeof(p),1,f2)==1)
	{
	    if (p.day==t->tm_mday)
		if(p.month==t->tm_mon+1)
		    printf("\t\t**  TODAY IS %d %d %d \n\t\t\t%s",t->tm_mday,t->tm_mon+1,t->tm_year+1900,p.event);

	}
	 printf("\n\t\t----------------------------------------------\n");


    }

}


//__++++++++++++++++++VISWANADH------------------------_VISWANADH__---------VISWANADH=+++++++++++++++++++__________VISWANADH________________________________

int Count_file(FILE *f)         //Returns numberof lines in a file.
{
    rewind(f);
    int c=0;
    char *s=malloc(20);
    while (!feof(f))
    {
	s=fgets(s,20,f);
	c++;
    }
    free(s);
    return c-1;
}

void insert(FILE *f1)                                                                                         //Takes input from user and inserts in file.
{
    char a;
    printf("\nINSTRUCTIONS\n1.For Closing The File Press | and then ENTER\n");
    a=getchar();
    while (a!='|')
    {
	fputc(a,f1);
	a=getchar();
    }
    fputc('\n',f1);
}

void tinsert(FILE *fp)               //Insert function for TO DO LIST.
{
    char c;
    int i=0;
    printf("\nINSTRUCTIONS\n1.For Closing The File Press | and then ENTER\n");
    c=getchar();
    while (c=='\n')
	c=getchar();
    while (c!='|')
    {
	i=1;
	if (c=='\n')
	{
	    while(c=='\n'&&c!='|')
		c=getchar();
	    if (c=='|')
		break;
	    fprintf(fp,"    NEGATIVE\n");
	    fputc(c,fp);
	    c=getchar();
	    continue;
	}
	fputc(c,fp);
	c=getchar();
    }
    if (i==1)
    {
	c=fgetc(fp);
	if (c!='\n')
	    fprintf(fp,"    NEGATIVE\n");
    }
}

int display(FILE *fp)     //Display for NOTES & to do list.
{
    char a;
    if (fp==NULL)
    {
	puts("Unable to open file,since file does not exist for reading");
	return 0;
    }
    else
    {
	printf("\n");
	while((a=fgetc(fp))!=EOF)
	    printf("%c",a);
	fclose(fp);
	return 1;
    }
}

char * itoa(long int a)                        //Converts inter to char pointer.
{
    char *s;
    int i=-1;
    long int t=a;
    while(t!=0)
    {
	t=t/10;
	i++;
    }
    if(i==-1)
    {
	s=(char *)malloc(2);
	s[0]='0';
	s[1]='\0';
	return s;
    }
    s=(char*)malloc(i+1);
    s[i+1]='\0';
    while(a!=0)
    {
	t=a%10;
	a=a/10;
	s[i]=t+48;
	i--;
    }
    return s;
}

void Delete(char string[],int d,int m,int y)              //Delete function for to do list.
{
    FILE *f1;
    f1=fopen(string,"r");
    if (f1==NULL)
	printf("\n\nYOU HAVE NOT CREATED TO DO LIST ON THIS DATE %d-%d-%d\n\n",d,m,y);
    else
    {
	fclose(f1);
	remove(string);
    }

}

int Search(FILE *fp,char *s)    //Searches a word in a file using scanf.
{
    char a,c[30];
    rewind(fp);
    if ((a=fgetc(fp))==EOF)
    {
	return 0;
    }
    else
    {
	rewind(fp);
	while (fscanf(fp,"%s",c)!=EOF)
	{
	    if (strcmp(s,c)==0)
	    {
		return 1;
	    }
	}
	return 0;
    }
}

char *Chara_chars(char a)                            //Converts char variable to char pointer.
{
    char *s=malloc(sizeof(char)*2);
    if (s==NULL)
	puts("Unable to do dynamic allocation in *chara_chars");
    else
	*s=a;
    return s;
}

int NoteSearch(FILE *fp,char *s) //Search a word using fgetc.Return 0 if not found.
{
    char a;
    char s1[30];
    char *s2=malloc(sizeof(char)*2);
    rewind(fp);
    if ((a=fgetc(fp))==EOF)
	return 0;
    else
    {
	rewind(fp);
	while((a=fgetc(fp))!=EOF)
	{
	    strcpy(s1,"");
	    while(a!='\n')
	    {
		s2=Chara_chars(a);
		strcat(s1,s2);
		a=fgetc(fp);
	    }
	    printf("\nVAlues of s1 are %s",s1);
	    if (strcmp(s1,s)==0)
		return 1;
	}
	return 0;
    }
}

void TInsert(FILE *fp,char *s)  //Insert for todolist file.
{
    fseek(fp,0,2);
    if(Search(fp,s)==0)
	fprintf(fp,"%s\n",s);
}

int Insert(FILE *fp,char *s)   //Insert for Categories file.
{
    FILE *f=fopen("temp","w");
    char *t=malloc(sizeof(char)*50);
    if (t==NULL)
	puts("NO MEMORY");
    int i,c=Count_file(fp);
    if (NoteSearch(fp,s)==0)        //if name not found.Change to Note search.
    {
	rewind(fp);
	for(i=1;i<c;i++)
	{
	    fgets(t,49,fp);
	    fputs(t,f);
	}
	fputs(s,f);
	fgets(t,49,fp);
	fprintf(f,"\n");
	fputs(t,f);
	fclose(fp);
	fclose(f);
	remove("Categories");
	rename("temp","Categories");
	fp=fopen("Categories","r+");
	free (t);
	return 1;
    }
    else
    {
	printf("Sorry!You cannot create file on this name,%s,as file already exist ",s);
	printf("\nPlease select any one of belo Categories\n");
	return 0;
    }
}

int isleapyear(int y)                            //Reterns 1 if given year is Leap year or returns 0.
{
    return (y%400==0)||((y%4==0)&&(y%100!=0));
}

int checkdate(int d,int m,int y)                             //This function checks given date is valid or no.
{
    int daysinmonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (d<1||m<1||y<1)
	return 0;
    if (isleapyear(y))
	daysinmonth[2]=29;
    if (1<=m&&m<=12)
    {
	if (d<=daysinmonth[m])
	    return 1;
	else
	    return 0;
    }
    else
	return 0;
}

void Options_case_1(FILE *fp)                         //Asks options for selectin notes.
{
    int i,c;
    char *s=malloc(sizeof(char)*20);
    i=Count_file(fp);
    rewind(fp);
    for(c=1;i>0;c++)
    {
	s=fgets(s,20,fp);
	printf("%d.%s\n",c,s);
	i--;
    }

}

int checkyear(int y)                        //Checks given year is four digit or no.
{
    if ((y/10!=0)&&(y/100!=0)&&(y/1000!=0)&&(y/10000==0))
	return 1;
    else
	return 0;
}

void FIND_curses(FILE *fp)                         //Searches a word using ncurses in given file.
{
    char a,s[20],input[20];
    scanf("%s",input);
    initscr();
    while(fscanf(fp,"%s",s)!=EOF)
    {
	if (strcmp(s,input)==0)
	{
	    attron(A_BLINK);
	    printw("%s",s);
	    refresh();
	    attroff(A_BLINK);
	}
	else
	    printw("%s",s);
	refresh();

	while((a=fgetc(fp))==' '||a=='\n'||a=='\t')
	    printw("%c",a);
	fseek(fp,-1,1);
	refresh();
    }
    getch();
    clear();
    refresh();
    endwin();
}

int search_year(char y[],FILE *fp)                         //Searches a given year from tododates file.
{
    char a,c[11];
    if ((a=fgetc(fp))==EOF)
	return 0;
    else
    {
	rewind(fp);
	while (fscanf(fp,"%s",c)!=EOF)
	{
	    if (strncmp(y,c,4)==0)
	    {
		return 1;
	    }
	}
	return 0;
    }
}

int num_of_pos(FILE *f)                                    //returns numbet of poaitives in to do list.
{
    int p=0;
    char s[]="POSITIVE";
    char t[30];
    rewind(f);

    while (fscanf(f,"%s",t)!=EOF)
    {
	if (strcmp(t,s)==0)
	    p=p+1;

    }
    printf("\nvalue of p is %d",p);
    return p;
}

int search_mon(char y[],char mon[],FILE *fp)               //returns 1 if given year and month exist in tododates file.
{
    char a,c[11],m[8]="";
    if ((a=fgetc(fp))==EOF)
	return 0;
    else
    {
	strcpy(m,"");
	strcat(m,y);
	strcat(m,"_");
	if (strlen(mon)==1)
	{
	    strcat(m,"0");
	    strcat(m,mon);
	}
	else
	    strcat(m,mon);
	rewind(fp);
	while (fscanf(fp,"%s",c)!=EOF)
	{
	    if (strncmp(m,c,7)==0)
	    {
		return 1;
	    }
	}
	return 0;
    }

}

int search_date(char y[],char mon[],char d[],FILE *fp)                            //returns 1 if given date month year exist in tododates file.
{
    char a,c[11],m[11]="";
    if ((a=fgetc(fp))==EOF)
	return 0;
    else

    {
	printf("\nmonth is %s",mon);
	strcpy(m,"");
	strcat(m,y);
	strcat(m,"_");
	if (strlen(mon)==1)
	{
	    strcat(m,"0");
	    strcat(m,mon);
	}
	else
	    strcat(m,mon);
	strcat(m,"_");
	if (strlen(d)==1)
	{
	    strcat(m,"0");
	    strcat(m,d);
	}
	else
	    strcat(m,d);
	rewind(fp);
	printf("\n value of m is %s",m);
	while (fscanf(fp,"%s",c)!=EOF)
	{
	    if (strncmp(m,c,10)==0)
	    {
		return 1;
	    }
	}
	puts("It returned 0");
	return 0;
    }

}

int search_int_date(char d[],FILE *fp)                          //searches integer date in given file.
{
    char a,c[11];
    if ((a=fgetc(fp))==EOF)
	return 0;
    else
    {
	rewind(fp);
	while (fscanf(fp,"%s",c)!=EOF)
	{
	    if (strncmp(d,c,10)==0)
	    {
		return 1;
	    }
	}
	return 0;
    }

}


int num_of_neg(FILE *f)                       //returns number of negatives in hiven todo list.
{
    int n=0;
    char s[]="NEGATIVE";
    char t[30];
    rewind(f);

    while (fscanf(f,"%s",t)!=EOF)
    {
	if (strcmp(t,s)==0)
	    n=n+1;
    }
    return n;

}

void Search_Display_year()                         //Display progress for given year.
{
    char y[5],s[11];
    FILE *f;
    int p=0,n=0;
    char *string=malloc(sizeof(char)*40);
    if (string==NULL)
	puts("Unable to do malloc in func.search display year");
    FILE *fp=fopen("ToDoDates","r");
    if (fp==NULL)
	puts("You have not created any to do list on till now");
    else
    {
	printf("\nPlease enter year\n");
	scanf("%s",y);
	if (search_year(y,fp)==0)
	{
	    printf("You have not created to do list in year %s\n",y);
	}
	else
	{
	    rewind(fp);
	    while ((fscanf(fp,"%s",s))!=EOF)
	    {
		if (strncmp(s,y,4)==0)
		{
		    strcpy(string,"");
		    strcpy(string,"./ToDoFiles/");
		    strcat(string,s);
		    f=fopen(string,"r");
		    p=p+num_of_pos(f);
		    n=n+num_of_neg(f);
		    fclose(f);

		}
	    }
	    printf("\nYou taught to finish %d\nYou have finished %d\nyou are yet to finish %d\n",p+n,p,n);
	    fclose(fp);
	}
    }
}
void Search_Display_mon()                            //       Display progress for given year. 
{
    char y[5],m[3],s[11],s1[8]="";
    FILE *f;
    int p=0,n=0;
    char *string=malloc(sizeof(char)*40);
    if (string==NULL)
	puts("Unable to do malloc in func.search display month");
    FILE *fp=fopen("ToDoDates","r");
    if (fp==NULL)
	puts("You have not created any to do list on till now");
    else
    {
	printf("\nPlease enter year\n");
	scanf("%s",y);
	printf("\nPlease enter month\n");
	scanf("%s",m);
	strcat(s1,y);
	strcat(s1,"_");
	if (strlen(m)==2)
	    strcat(s1,m);
	else
	{
	    strcat(s1,"0");
	    strcat(s1,m);
	}
	if (search_mon(y,m,fp)==0)
	    printf("You have not created to do list for %s-%s\n",m,y);
	else
	{
	    rewind(fp);
	    while ((fscanf(fp,"%s",s))!=EOF)

	    {
		printf("\nvalue of s is %s",s);
		if (strncmp(s,s1,7)==0)
		{
		    strcpy(string,"");
		    strcpy(string,"./ToDoFiles/");
		    printf("\nvalue of s is %s",s);
		    strcat(string,s);
		    f=fopen(string,"r");
		    p=p+num_of_pos(f);
		    n=n+num_of_neg(f);
		    fclose(f);
		}
	    }
	    printf("\nYou taught to finish %d\nYou have finished %d\nyou are yet to finish %d\n",p+n,p,n);
	    fclose(fp);
	}
    }
}

void Search_Display_date()                                          //Display progress for given date.
{
    char y[5],m[3],d[3],s[11],s1[11]="";
    FILE *f;
    int p=0,n=0;
    char *string=malloc(sizeof(char)*40);
    if (string==NULL)
	puts("Unable to do malloc in func.search display month");
    FILE *fp=fopen("ToDoDates","r");
    if (fp==NULL)
	puts("You have not created any to do list on till now");
    else
    {
	printf("\nPlease enter year\n");
	scanf("%s",y);
	printf("\nPlease enter month\n");
	scanf("%s",m);
	printf("\nPlease enter date\n");
	scanf("%s",d);
	strcat(s1,y);
	strcat(s1,"_");
	if (strlen(m)==2)
	    strcat(s1,m);
	else
	{
	    strcat(s1,"0");
	    strcat(s1,m);
	}
	strcat(s1,"_");
	if (strlen(d)==2)
	    strcat(s1,d);
	else
	{
	    strcat(s1,"0");
	    strcat(s1,d);
	}
	if (search_date(y,m,d,fp)==0)
	    printf("You have not created to do list for %s-%s-%s\n",d,m,y);
	else
	{
	    rewind(fp);
	    while ((fscanf(fp,"%s",s))!=EOF)
	    {
		if (strncmp(s,s1,10)==0)
		{
		    strcpy(string,"");
		    strcpy(string,"./ToDoFiles/");
		    strcat(string,s);
		    f=fopen(string,"r");
		    p=p+num_of_pos(f);
		    n=n+num_of_neg(f);
		    fclose(f);
		}
	    }
	    printf("\nYou taught to finish %d\nYou have finished %d\nyou are yet to finish %d\n",p+n,p,n);
	    fclose(fp);
	}
    }
}

void Search_Display_now()                                        //Display progress for today.
{
    time_t T=time(NULL);
    struct tm*t=localtime(&T);
    T=time(NULL);
    t=localtime(&T);
    char s[11],s1[11]="";
    FILE *f;
    char *s2=malloc(sizeof(char )*3);
    int p=0,n=0;
    char *string=malloc(sizeof(char)*40);
    if (string==NULL)
	puts("\nUnable to do malloc in func.search display month\n");
    FILE *fp=fopen("ToDoDates","r");
    if (fp==NULL)
	puts("\nYou have not created any to do list on till now\n");
    else
    {
	sprintf(s1,"%d",t->tm_year+1900);
	strcat(s1,"_");
	if (t->tm_mon+1>=10)
	{
	    strcpy(s2,"");
	    s2=itoa(t->tm_mon+1);
	    strcat(s1,s2);
	}
	else
	{
	    strcpy(s2,"");
	    strcat(s1,"0");
	    s2=itoa(t->tm_mon+1);
	    strcat(s1,s2);
	}
	strcat(s1,"_");
	if (t->tm_mday>=10)
	{
	    strcpy(s2,"");
	    s2=itoa(t->tm_mday);
	    strcat(s1,s2);
	}
	else
	{
	    strcpy(s2,"");
	    strcat(s1,"0");
	    s2=itoa(t->tm_mday);
	    strcat(s1,s2);
	}
	if (search_int_date(s1,fp)==0)
	    printf("\nYou have not created to do list on today's date\n");
	else
	{
	    rewind(fp);
	    while ((fscanf(fp,"%s",s))!=EOF)
	    {
		if (strncmp(s,s1,10)==0)
		{
		    strcpy(string,"");
		    strcpy(string,"./ToDoFiles/");
		    strcat(string,s);
		    f=fopen(string,"r");
		    p=p+num_of_pos(f);
		    n=n+num_of_neg(f);
		    fclose(f);
		}
	    }
	    printf("\nYou taught to finish %d\nYou have finished %d\nyou are yet to finish %d\n",p+n,p,n);
	    fclose(fp);
	}
    }
}

int EVERNOTE()                                                      //Main program for evre note.
{
    int main,c,choice,i,*array,j;            //keep i=0.
    char a;
    char string[40]="./ToDoFiles/",st[11],*s=malloc(sizeof(char)*30);                  //st is used for taking date from user.
    char string1[40]="./NoteFiles/";
    FILE *f1,*fp,*ft;                //fp==Categories,f1==somefile,ft=todofile
    tdate t;
    while (1)
    {
	system("clear");
	printf("Please select any one of the options below\n");
	printf("\t\t1.NOTES\n\t\t2.TO DO LIST\n\t\t3.DISPLAY PROGRESS\n\t\t4.BACK\n");
	scanf("%d",&main);getchar();
	switch (main)
	{
	    case 1:
		while(1)
		{
		    printf("Please select any one option from below catagory\n");
		    printf("\n\t\t1.Take Notes\n\t\t2.Display Notes\n\t\t3.Back\n");
		    scanf("%d",&c);
		    fp=fopen("Categories","r+");
		    if (fp==NULL)
		    {
			fp=fopen("Categories","w");
			if (fp==NULL)
			{
			    printf("Unable to open FILE\n");
			    exit(1);
			}
			fprintf(fp,"General_Notes\n");
			fprintf(fp,"Create_Category\n");
			fclose(fp);
			fp=fopen("Categories","r+");
		    }
		    if (c==1)
		    {
			system("clear");
sos:                    Options_case_1(fp);                         //for printing options in for selecting catagories.
			scanf("%d",&choice);getchar();
			if (choice==1)         //for general notes.
			{
			    strcpy(string1,"");
			    strcpy(string1,"./NoteFiles/");
			    strcat(string1,"General_Notes");
			    f1=fopen(string1,"a");
			    if (f1==NULL)
			    {
				f1=fopen("General_Notes","w");
				if (f1==NULL)
				{
				    puts("Unable to open file");
				    exit(1);
				}
			    }
			    printf("\n\n\n\n\n");
			    insert(f1);
			    printf("\n\n\n\n\n");
			    fclose(f1);
			}
			else
			    if (choice==Count_file(fp))        //if choice is to create.
			    {
				printf("Please enter name of the new file that you want to create\n");
				fgets(s,28,stdin);                //for new file name.
				s[strlen(s)-1]='\0';
				if (Insert(fp,s)==1)     //Insert in CAtegories file.
				{
				    strcpy(string1,"");
				    strcpy(string1,"./NoteFiles/");
				    strcat(string1,s);
				    f1=fopen(string1,"w");
				    printf("\n\n\n\n\n");
				    insert(f1);
				    printf("\n\n\n\n\n");
				    fclose(f1);
				}
				else goto sos;
			    }
			    else{                                //if choice is not to create.
				if (choice>Count_file(fp))
				    printf("\nYou choose an invalid option\n");
				else
				{
				    rewind(fp);
				    for (i=1;i<=choice;i++)
					fgets(s,20,fp);
				    s[strlen(s)-1]='\0';                                 //since s is takin Last character as ?.
				    strcpy(string1,"");
				    strcpy(string1,"./NoteFiles/");
				    strcat(string1,s);
				    f1=fopen(string1,"a");
				    if (f1==NULL)
				    {
					printf("Unable to open selected category\n");
				    }
				    else
				    {
					printf("\n\n\n\n\n");
					insert(f1);
					printf("\n\n\n\n\n");
					fclose(f1);
				    }
				}
			    }
			fclose(fp);
		    }
		    else if (c==2)                                        //for Display of notes.
		    {
			system("clear");
			printf("Please select which notes you want to see\n");
			Options_case_1(fp);
			scanf("%d",&choice);
			getchar();
			if (choice>=Count_file(fp))
			    printf("\nYou choose an invalid option\n");
			else
			{
			    rewind(fp);
			    for (i=0;i<choice;i++)
				fgets(s,20,fp);
			    s[strlen(s)-1]='\0';
			    strcpy(string1,"");
			    strcpy(string1,"./NoteFiles/");
			    strcat(string1,s);
			    f1=fopen(string1,"r");
			    if (f1==NULL)
				printf("Nothing is there to display \n");
			    else
			    {
				printf("\n");
				display(f1);
				printf("\n");
				puts("Press 1 for search a word in above file");
				scanf("%d",&c);
				if (c==1)
				{
				    puts("Please enter word that you want to search");
				    f1=fopen(string1,"r");
				    if (f1==NULL)
					puts("\nUnable to open file for ncurses\n");
				    FIND_curses(f1);
				}
			    }
			}
		    }
		    else if (c==3)
			break;                             //For coming out from Case 1.
		    else
			puts("You entered a wrong Option\n");

		}
		break;

	    case 2:                                                       //To do list .
		while (1)
		{
		    printf("Please select any one option from below\n");
		    printf("1.OPEN TO-DO-LIST\n2.DISPLAY TO-DO-LIST\n3.SELECT FINISHED ONES\n4.DELETE FULL DAYS TO DO LIST\n5.Back\n");
		    scanf("%d",&choice);
		    i=0;
		    if (choice==5)
			break;
		    while (i==0)                                   //Checks for given date is in formate of dd mm yyyy.
		    {
			printf("Please enter Date,Month,Year in format dd mm yyyy\n");
			scanf("%d%*c%d%*c%d",&t.d,&t.m,&t.y);
			if (t.d<10&&t.m<10)
			    sprintf(st,"%d_0%d_0%d",t.y,t.m,t.d);
			else if (t.d>=10&&t.m<10)
			    sprintf(st,"%d_0%d_%d",t.y,t.m,t.d);
			else if (t.d<10&&t.m>=10)
			    sprintf(st,"%d_%d_0%d",t.y,t.m,t.d);
			else
			    sprintf(st,"%d_%d_%d",t.y,t.m,t.d);
			i=checkyear(t.y);
			if (i==1)
			    i=checkdate(t.d,t.m,t.y);
		    }
		    strcpy(string,"");
		    strcpy(string,"./ToDoFiles/");
		    if (choice==1)                                 //Open to do list.
		    {
			system("clear");
			ft=fopen("ToDoDates","a+");
			if (ft==NULL)
			    puts("UNABLE TO OPEN TO DO Dates file");
			strcat(string,st);
			TInsert(ft,st);
			fp=fopen(string,"a");
			if (fp==NULL)
			{
			    puts("Unable to open FILE");
			    exit(1);
			}
			printf("\n\n\n\n\n");
			tinsert(fp);
			fflush(stdin);            
			printf("\n\n\n\n\n");
			fclose(fp);
			fclose(ft);
		    }
		    else if (choice==2)                          //Display to do list.
		    {
			system("clear");
			strcat(string,st);
			f1=fopen(string,"r");
			printf("\n\n\n\n\n");
			display(f1);
			printf("\n\n\n\n\n");
		    }
		    else if (choice==3)                                   //Updating to do list ,if completed.
		    { 
			system("clear");
			strcat(string,st);                          
			printf("\nvalue of string is %s",string);    
			f1=fopen(string,"r+");                       
			printf("Your To Do List :%d-%d-%d",t.d,t.m,t.y);
			printf("\n");                   
			if (display(f1)==1)
			{
			    f1=fopen(string,"r+");
			    puts("Please enter how many have you finished?\n");
			    scanf("%d",&c);
			    printf("You have entered %d",c);
			    array=malloc(sizeof(int)*c);
			    rewind(f1);
			    puts("Please enter line numbers");
			    for(i=0;i<c;i++)
			    {
				scanf("%d",&array[i]);
			    }
			    for(i=0;i<c;i++)
			    {
				rewind(f1);
				for(j=0;j<array[i];j++)
				{
				    while (1)
				    {
					a=fgetc(f1);
					if (a=='\n')
					    break;
				    }
				}
				fseek(f1,-9,1);
				fprintf(f1,"POSITIVE");
			    }
			}
			fclose(f1);
		    }
		    else if (choice==4)                    //Delete full day's to do list.
		    {
			system("clear");
			strcat(string,st);
			Delete(string,t.d,t.m,t.y);
		    }
		    else if (choice==5)
			break;
		    else
			puts("You entered wrong option\n");
		}
		break;

	    case 3:                                               //Display progress.
		puts("Please select one of the options from below");
		printf("\n1.Display progress for an given year.\n2.Display progress for an given month\n3.Display progress for an given date\n4.Display today's progress\n");
		scanf("%d",&i);
		switch (i)
		{
		    system("clear");
		    case 1:
			Search_Display_year();                           //Display progress for given year.
			break;
		    case 2:
			Search_Display_mon();                            //Display progress for given month and year.
			break;
		    case 3:
			Search_Display_date();                           //Display progress for given particular date.
			break;
		    case 4:
			Search_Display_now();                            //Display today's progress .
			break;
		    default:
			puts("You have entered an wrong option");
			break;
		}
		break;

	    case 4:                                                          //Back.It goes from ever note to Personal Assistant.
		return 1;
		break;

	    default:
		printf("Please select valid option\n");
		break;

	}
    }
}

//___________________VISWANADH___+++++++++++++++++++++VISWANADH---------------------VISWANADH-------------++++++++++++++++VISWANADH___________________________________
//___________________AKHIL___+++++++++++++++++++++AKHIL-------------------------AKHIL-----------------++++++++++++++++AKHIL_________________-------------______________
int is_existing_number(char number[],FILE *f)       // checking  if number alredy exists
{
    contact p;
    rewind(f);
    while(fread(&p,sizeof(p),1,f)==1)
    {   
	if(strcmp(p.number,number)==0)
	{
	    return 0;
	}

    }

    return 1;
}

FILE *Create_contact(contact p,FILE *f1)           // inserting the contact in ascending order into the file
{
    extern int global;
    int flag=0;
    contact q;
    char s[90]="";
    char t[90]="";
    FILE *f2=fopen("temp","ab+");
    if(f2==NULL)
    {printf("can not open the file "); 
	exit(-1);
    }
    else
    {
	rewind(f1);
	strcat(s,p.first_name);
	strcat(s,p.middle_name);
	strcat(s,p.last_name);
	if(fread(&q,sizeof(contact),1,f1)==0)   // contact list is empty
	{
	    fwrite(&p,sizeof(contact),1,f1);    //directly writes the names
	    fclose(f2); 
	    remove("temp");

	    printf("\njust now you entered a contact");
	    fclose(f1);
	    f1=fopen("file.txt","ab+");
	    return f1;
	}
	else
	{
	    rewind(f1);
	    while(fread(&q,sizeof(contact),1,f1)==1)
	    {   	
		strcat(t,q.first_name);
		strcat(t,q.middle_name);
		strcat(t,q.last_name);
		if(strcmp(s,t)>0)
		{
		    fwrite(&q,sizeof(contact),1,f2);    //writing into temp file
		}
		else if(strcmp(s,t)<0) 
		{   flag=1;
		    fwrite(&p,sizeof(contact),1,f2);
		    fwrite(&q,sizeof(contact),1,f2);
		    while(fread(&q,sizeof(contact),1,f1)==1)
		    {  
			fwrite(&q,sizeof(contact),1,f2);
		    }	
		    break;
		}
		else
		{flag=1;
		    global=1;		    
		    printf("\nalready existing...this contact already exixts .please enter the details once again.\n"); 
		    fwrite(&q,sizeof(contact),1,f2);
		    while(fread(&q,sizeof(contact),1,f1)==1)
		    {  
			fwrite(&q,sizeof(contact),1,f2);
		    }	

		    break;
		}
		strcpy(t,"");
	    }
	    if(flag==0)
		fwrite(&p,sizeof(contact),1,f2);
	    fclose(f2);
	    fclose(f1);
	    remove("file.txt");          //deletes the file.txt
	    rename("temp","file.txt");  //file.txt  is temp(renaming)
	    f1=fopen("file.txt","ab+");
	    return f1;
	}
    }
}
void Display_contacts(FILE *fp)          // displays the contact list in the file
{
    rewind(fp);
    contact p;
    if(fread(&p,sizeof(contact),1,fp)==0)
    {
	puts("nothing to display in contact list");

    }
    else
    {
	rewind(fp);
	printf("\n************************list of contacts*********************************************");
	printf("\nnumber\t\tfirstname\t\tmiddlename\t\tlastname\t\temailid\n");
	while(fread(&p,sizeof(contact),1,fp)==1)
	{
	    printf("\n%s	%10s	%10s	%10s	%10s",p.number,p.first_name,p.middle_name,p.last_name,p.emailid);
	}
    }
}
FILE *Delete_contact(contact p,FILE *f1)          //delete the contact what user wants to delete
{
    FILE *f2=fopen("temp","ab+");
    int flag=1;
    char a[100]="";
    char b[100]="";
    rewind(f1);
    strcat(a,p.first_name);
    strcat(a,p.middle_name);
    strcat(a,p.last_name);
    contact q;
    if(fread(&q,sizeof(contact),1,f1)==0)
	printf("\ncontact is empty");
    else
    {
	flag=0;
	rewind(f1);
	while(fread(&q,sizeof(contact),1,f1)==1)
	{
	    strcat(b,q.first_name);
	    strcat(b,q.middle_name);
	    strcat(b,q.last_name);
	    if(strcmp(a,b)==0)
	    {
		while(fread(&p,sizeof(p),1,f1)==1)
		    fwrite(&p,sizeof(contact),1,f2);
		fclose(f1);
		fclose(f2);
		remove("file.txt");
		rename("temp","file.txt");
		f2=fopen("file.txt","ab+");
		return f2;
	    }
	    else
	    {
		fwrite(&q,sizeof(contact),1,f2);
	    }
	    strcpy(b,"");
	}
	if(flag==0)
	    puts("this name is not there in your list");
	fclose(f2);
	remove("temp");
    }
    return f1;
}
FILE *Delete_contacts(FILE *f1)         // deletes the full contact list
{
    char c;
    contact q;
    printf("\n ARE YOU SURE TO DELETE YOUR CONTACT LIST");
    printf("\n TYPE 'y' FOR YES. ");
    scanf("%c",&c);  getchar();
    if(c=='y')
    {
	rewind(f1);
	if(fread(&q,sizeof(q),1,f1)==0)
	{
	    printf("\n list is empty");
	    return f1;
	}
	else
	{
	    fclose(f1);
	    f1=fopen("file.txt","wb");
	    if(f1==NULL)
	    {   
		printf("error");
		exit(-1);
	    }


	    printf("\n DELETED SUCCESSFULLY");  
	    fclose(f1);
	    f1=fopen("file.txt","ab+");
	    return f1;

	}
    }
    else
	return f1;
}
void search(FILE *f1,char a[])              // searches the contact by name
{
    FILE *f2=fopen("temp","ab+");
    contact p;
    int flag=1;
    if(fread(&p,sizeof(contact),1,f1)==0)
	printf("\n EMPTY LIST");
    else
    {
	rewind(f1);
	while(fread(&p,sizeof(contact),1,f1)==1)
	{
	    if(strncmp(a,p.first_name,strlen(a))==0)  //charecters entered by user were matching with first_name 
	    {
		fwrite(&p,sizeof(contact),1,f2); 
		flag=0;
	    }
	    else if(strncmp(a,p.middle_name,strlen(a))==0)//charecters entered by user were matching with middle_name
	    {
		fwrite(&p,sizeof(contact),1,f2);
		flag=0;
	    }
	    else if(strncmp(a,p.last_name,strlen(a))==0)//charecters entered by user were matching with last_name
	    {
		fwrite(&p,sizeof(p),1,f2);
		flag=0;
	    }
	    else
		continue;
	}
    }
    if(flag==1)
	printf("\nno matches found");
    else
    {
	printf("\n matching contacts are:");
	Display_contacts(f2); 
    }
    fclose(f2);
    remove("temp");
}

FILE *edit_contact_name(contact q,FILE *f1)      // if user wants to edit the name
{
    extern int global;
    int i=0;
    contact p;
    if(fread(&p,sizeof(p),1,f1)==0)
    {
	printf("\ncontact list is empty");
	return f1;
    }
    else
    {
	rewind(f1);
	while(fread(&p,sizeof(contact),1,f1)==1)
	{
	    if(strcmp(q.number,p.number)==0)
	    {
		printf("\n Please enter the new details.");  
		printf("\n1.FIRST NAME:");
		scanf("%s",q.first_name);
		printf("\n2.MIDDLE NAME:");
		scanf("%s",q.middle_name);
		printf("\n3.LAST NAME:");
		scanf("%s",q.last_name);
		printf("\n3.EMAIL ID:");
		scanf("%s",q.emailid);
		f1=Create_contact(q,f1);
		if(global==0)
		    f1=Delete_contact(p,f1);
		return f1;
	    }
	    else
		continue;
	}
	printf("\n no matching contacts were found");
	return f1;

    }
}
FILE *edit_contact_number(contact q,FILE *f1)       //if user wants to edit the number
{
    int i=0;
    int n;
    char a[90]="";
    char b[90]="";
    contact p;
    strcat(a,q.first_name);
    strcat(a,q.middle_name);
    strcat(a,q.last_name);
    if(fread(&p,sizeof(p),1,f1)==0)
    {
	printf("\ncontact list is empty");
	return f1;
    }
    else
    {
	rewind(f1);
	while(fread(&p,sizeof(contact),1,f1)==1)
	{
	    strcat(b,p.first_name);
	    strcat(b,p.middle_name);
	    strcat(b,p.last_name);
	    if(strcmp(a,b)==0)
	    {
		printf("\n Please enter the new details.");
		printf("\n1.NUMBER");
		scanf("%s",q.number);
		n=is_existing_number(q.number,f1);
		if(n==0)
		{
		    puts("already existing. you cant edit");
		    puts("please do once again");
		    return f1;
		}
		else
		{

		    printf("\n2.EMAIL ID:");
		    scanf("%s",q.emailid);
		    f1=Delete_contact(p,f1);
		    f1=Create_contact(q,f1);
		    return f1;
		}
	    }
	    else
	    {
		strcpy(b,"");
		continue;
	    }
	}
	printf("\n no matching contacts were found");
	return f1;

    }
}
void  numsearch(FILE *fp,char num[])       // searching contacts by number
{
    int flag =1;
    contact p;
    FILE *f1=fopen("temp","ab+");
    FILE *f2=fopen("recentsearch","ab+");//recent
    if(fread(&p,sizeof(contact),1,fp)==0)
    {
	printf("\n Nothing to display");
	fclose(f1);
	remove("temp");
    }
    else
    {
	rewind(fp);
	while(fread(&p,sizeof(contact),1,fp)==1)
	{
	    if(strcmp(p.number,num)==0)
	    {
		flag =0;
		fwrite(&p,sizeof(contact),1,f1);
		fseek(f2,0,2);//recent
		fwrite(&p,sizeof(contact),1,f2);//recent
		Display_contacts(f1); 
		fclose(f1);
		fclose(f2);//recent
		remove("temp");
	    }
	}
	if(flag==1)
	{
	    fclose(f1);
	    fclose(f2);//recent
	    remove("temp");
	    printf("\n This Number is not there in your list");
	}

    }
}
int structnum(FILE *fp)    //  no.of contacts
{
    int i=0;
    contact p;
    if(fread(&p,sizeof(contact),1,fp)==0)
	return 0;
    rewind(fp);
    while(fread(&p,sizeof(contact),1,fp)==1)
	i++;
    return i;
}
int CONTACT_MANAGEMENT()
{
    int z,y=1;
    char x;
    char num[30];
    int opt;
    FILE *fp;
    contact c;
    char a[30]="";
    int b,choice;
    system("clear");
    while(1)
    { 	
	printf("\n\t1.CREATE CONTACT.\n\t2.DISPLAY.\n\t3.SEARCH.\n\t4.DELETE.\n\t5.DELETE CONTACT LIST\n\t6.EDIT CONTACT.\n\t7. NO.OF.CONTACTS\n\t8. BACK\n");	
	scanf("%d",&choice); getchar();
	fp=fopen("file.txt","ab+");
	switch(choice)
	{
	    case 1:////////////////////////////CREATE CONTACT
		printf("PLEASE ENTER THE FOLLOWING DETAILS\n");
		while(1)
		{ printf("\tNUMBER:\n");   
		    scanf("%s",c.number);
		    b=is_existing_number(c.number,fp);
		    if(b==0)
		    {   puts("already existing number");	
			puts("please enter once again");
			continue;}
		    else
			while(1)
			{   puts("		FIRSTNAME:");   
			    scanf("%s",c.first_name);
			    puts("		MIDDLE_NAME:");
			    scanf("%s",c.middle_name);
			    puts("		LAST_NAME:");
			    scanf("%s",c.last_name);	
			    puts("		EMAILID:");
			    scanf("%s",c.emailid);
			    fp=Create_contact(c,fp);
			    break;
			}
		    break;
		}
		break;///////////////CASE BREAK(1)
	    case 2://////////////////////////display	
		Display_contacts(fp);
		break;////////////    CASE BREAK(2)
	    case 3://///////////////////////search
		system ("clear");
		printf("\n By what you want to Search");
		printf("\n 1.NAME. \n 2.NUMBER.");
		scanf("%c",&x);getchar();
		if(x=='1')
		{
		    printf("\nPlease enter some charecters");  
		    scanf("%s",a);
		    search(fp,a);
		}
		else if(x=='2')
		{
		    printf("\n please enter the number");
		    scanf("%s",num);
		    numsearch(fp,num); 
		}
		else
		    printf("\n please enter a valid input");
		break;
	    case 4://////////////////////////////delete
		printf("\nplease enter following details");
		puts("First_name:");
		scanf("%s",c.first_name);
		puts("Second_name");
		scanf("%s",c.middle_name);
		puts("Last_name");
		scanf("%s",c.last_name);
		fp=Delete_contact(c,fp);
		break;
	    case 5://///////////////////////////delete full list
		fp=Delete_contacts(fp);
		break;
	    case 6://///////////////////////////edit
		printf("\n what u want to edit");
		printf("\n 1.NAME.\n 2.NUMBER");
		scanf("%d",&opt);
		if(opt==1)//  edit name
		{
		    printf("\nenter the number");
		    scanf("%s",c.number);
		    fp=edit_contact_name(c,fp);
		}
		else if(opt==2)//edit number
		{
		    printf("\n please enter the following details");
		    printf("\n 1.FIRST NAME");
		    scanf("%s",c.first_name);
		    printf("\n2.MIDDLE NAME");
		    scanf("%s",c.middle_name);
		    printf("\n2.LAST NAME");
		    scanf("%s",c.last_name);
		    fp=edit_contact_number(c,fp);
		}
		else
		    printf("\n PLEASE ENTER A VALID INPUT");
		break;
	    case 7:////////////////////////no.of contacts
		z= structnum(fp);
		system("clear");
		printf("\n NO.OF CONTACTS IN YOUR LIST:%d",z);
		break;
	    case 8://///////////////exit
		return 1;
		break;
	    default:printf("\n PLEASE ENTER VALID INPUT");
	}

	fclose(fp);
	
    }
}
//_______________APPALA+++++++++++++++++++++APPALA---------------------------------APPALA++++++++++++++++++++++++APPALA--------------------------APPALA________________
int find_day(int d, int m, int y)  //returns the day number of the week
{   int month[]={0,3,3,6,1,4,6,2,5,0,3,5};
    int year[]={0,5,3,1,6,4,2};
    int c[]={6,4,2,0,-1};
    int s=d+month[m-1]+year[((y%100)/4)%7]+(y%4)+c[(((y/100)+1)%17)];
    if(y >= 1900 && ( is_leap_year(y)==1) && m <=2)
	s=s-1;
    return s%7;
}
//////////////////////////////////////////////////////////////////////////////////////////////
int is_leap_year(int y) //to check whether it is leap year or not
{
    if(y%4==0)
    {
	if ((y%100!=0) ||(y%400==0))
	    return 1;
	else
	    return 0;
    }
    else return 0;

}
////////////////////////////////////////////////////////////////////////////////////////////////
void name_of_the_day(int day){ //returns the which day  of the week
    switch(day){
	case 0 :puts("sunday");
		break;
	case 1 :puts("monday");
		break;
	case 2 :puts("Tuesday");
		break;
	case 3 :puts("wednesday");
		break;
	case 4 :puts("Thursday");
		break;
	case 5 :puts("friday");
		break;
	case 6 :puts("saturday");
		break;
	default:puts(" ");
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void Calendar(int y){//this function to display calendar of a year
    FILE *fp;
    Event* ev, event;
    int len, j,is_event_present,m[13]={0,1,2,3,4,5,6,7,8,9,10,11,12};
    char *chk_month_name[] = { NULL,"January", "February", "March", "April", "May", "June","July", "August", "September", "October", "November", "December"}; 
    char week[] = "Su   Mo   Tu   we   Th   Fr   Sa";
    int num_days_in_each_month[] =
    { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
    int chk_top_day_of_week[13];
    chk_top_day_of_week[0]=0;
    printw("press left arrow to see previous year's calendar and right arrow to see next year's calendar from current year\n");
    refresh();
    for(int i=1;i<=12;i++)
    {
	chk_top_day_of_week[i]=days(y,i,1)%7;
    }
    fp = fopen("reminders.out", "rb");
    if (fp == NULL) {
	printw("can't read events\n");
	refresh();
    }
    len = 0;
    while(fread(&event,sizeof(Event),1,fp)) {
	if(event.year==y) {
	    len++;
	}
    }
    rewind(fp);
    j = 0;
    ev =(Event*)malloc(sizeof(Event)*len);
    while(fread(&event,sizeof(Event),1,fp)) {
	if(event.year==y) {
	    ev[j]=event;
	    j++;
	}
    }
    int r=1;
    int z=1;
    int day[12]={1,1,1,1,1,1,1,1,1,1,1,1};int M=1,m_no=1;
    fclose(fp);
    int chk=1,f;
    int i[12]={0,0,0,0,0,0,0,0,0,0,0,0};
    if(is_leap_year(y))
	num_days_in_each_month[2] = 29;

    printw("\n\t\t\t\t\t\t  %d\n",y);
    refresh();
    while(M<=4){
	printw("\t %s\t\t\t\t   %s\t\t\t\t   %s\n%s     %s     %s\n",chk_month_name[m_no],chk_month_name[m_no+1],chk_month_name[m_no+2],week,week,week);
	refresh();
	while(z<=6){     
	    while(chk<4){
		if(z==1){
		    for(i[r-1]=0;i[r-1]<((5*chk_top_day_of_week[r]));i[r-1]++)
		    {
			printw(" ");
			refresh();
		    }
		}
		if(z==1)
		    i[r-1]=chk_top_day_of_week[r];
		for(;day[r-1]<=num_days_in_each_month[m[r]];i[r-1]++,day[r-1]++){
		    is_event_present=0;
		    for(j=0;j<len;j++) {
			if((ev[j].day==day[r-1])&&(ev[j].month == m[r])&&(ev[j].year==y)) {
			    if(day[r-1]<10){
				attron(A_BLINK); //this attribute used to highlight whereever events are present	
				printw(" %d   ",day[r-1]);
				attroff(A_BLINK);
				refresh();}
			    else{
				if(day[r-1]!=num_days_in_each_month[r])
				    printw("%d   ",day[r-1]);
				else
				    printw("%d",day[r-1]);
				refresh();
			    }
			    is_event_present = 1;
			    break;
			}
		    }
		    if(is_event_present==0) {
			if(day[r-1]<10){
			    printw(" %d   ",day[r-1]);
			    refresh();}
			else{
			    if(day[r-1]!=num_days_in_each_month[r])
				printw("%d   ",day[r-1]);
			    else
				printw("%d",day[r-1]);
			    refresh();
			}
		    }
		    if(i[r-1]%7==6){
			printw("  ");
			refresh();
			if(day[r-1]==num_days_in_each_month[r])
			    printw("   ");
			refresh();
			break;
		    }

		}++day[r-1];
		r++; 
		++chk;
		if((day[r-2]-2)==num_days_in_each_month[r-1]){
		    f=chk_top_day_of_week[r-1]+(num_days_in_each_month[r-1]%7)-1;
		    while(f<7){
			printw("     ");
			refresh();
			++f;
		    }
		}
		else if ((day[r-2]-2)>num_days_in_each_month[r-1]){
		    f=1;
		    while(f<8){
			printw("     ");
			refresh();
			++f;
		    }
		    printw("  ");
		    refresh();
		}
	    }
	    ++z;i[r-4]=0;i[r-3]=0;i[r-2]=0;r-=3;
	    chk=1;
	    addstr("\n"); 
	    refresh();
	}++M;
	m_no+=3;
	r+=3;       
	z=1;
	chk=1; 
    }
    addstr("\n");  
    refresh();
    printw("Press esc to come out\n");
    refresh();
}
///////////////////////////////////////////////////////////////////////////////////////////
void print_month(int m, int y){ //this function to print calendar of a month
    char *chk_month_name[] = { NULL,"January", "February", "March", "April", "May", "June","July", "August", "September", "October", "November", "December"};
    char week[] = "Su   Mo   Tu   We   Th   Fr   Sa";
    int num_days_in_each_month[] =
    { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
    int chk_top_day_of_week;
    int i,day;
    chk_top_day_of_week=days(y,m,1) %7;
    if(is_leap_year(y))
	num_days_in_each_month[2]=29;
    printf("\t   %d\n         %s\n%s\n",y,chk_month_name[m],week);
    for(i=0;i<(5*chk_top_day_of_week);i++)
	printf(" ");
    for(i=chk_top_day_of_week,day=1;day<=num_days_in_each_month[m];i++,day++){
	printf("%2d   ",day);
	if(i%7==6)
	    printf("\n");
    }												      
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////
void Curseyear(int y)
{ 
    int ch;
    initscr();
    cbreak();
    keypad(stdscr,TRUE);
    Calendar(y);
    while ((ch=getch())!=27)
    {
	switch(ch)
	{                     //function using ncurses to dispaly calendar of previous and next year's      
	    case KEY_LEFT:
		clear();
		y=y-1;
		Calendar(y);
		break;
	    case KEY_RIGHT:
		clear();
		y=y+1;
		Calendar(y);
		break;
	}
    }
    clear();
    refresh;
    endwin();
}
//////////////////////////////////////////////////////////////////////////////////////////
int leap_years( int y ) //to check number of leap years
{
    return y/4 - y/100 + y/400;
}
/////////////////////////////////////////////////////////////////////////////////////////////
int num_days_beg_of_year( int y, int m, int d) //to check number of days from beginning of the year
{
    int num_days_in_each_month[] =
    { -1,0,31,59,90,120,151,181,212,243,273,304,334};
    int s;
    s= num_days_in_each_month[m]+d;
    if(m>2 && ( is_leap_year(y)==1))
	s+=1;
    return s;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int days(int y, int m, int d)  //to check total number of days 
{ 
    int last_year;
    last_year = y -1;
    return 365 * last_year + leap_years(last_year) +  num_days_beg_of_year(y,m,d);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void calendar(int y, int m, int d){//this function is to add events or reminders to any paticular year as necessary     
    FILE *fp;
    Event* ev,event;
    fp=fopen("reminders.out","rb");
    if (fp==NULL) {
	printf("Can't read events\n");
    }
    int len=0;
    while(fread(&event,sizeof(Event),1,fp)) {
	if(event.year==y&&event.month==m&&event.day==d) {
	    len++;
	}
    }
    rewind(fp);
    int j=0;
    ev=(Event*)malloc(sizeof(Event)*len);
    while(fread(&event, sizeof(Event),1,fp)) {
	if(event.year==y&&event.month==m&&event.day==d) {
	    ev[j]=event;
	    j++;
	}
    }
    fclose(fp);
    if(j!=0){
	printf("various events present are %d %d %d\n",d,m,y);
	for (j=0;j<len;j++) {
	    printf("%s\n",ev[j].event);
	}
    }
    else  {
	puts("there is no event present");
	return;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void Cal_display(int year){ //to dispaly events in particular year
    Event e;
    FILE *fp=fopen("reminders.out","rb");
    while(fread(&e,sizeof(Event),1,fp)){
	if(e.year==year){
	    printf("%d %d ",e.day,e.month);
	    puts(e.event);
	}

    }
    fclose(fp);
}

int CALANDER()
{
    int year,month, day;
    char choice;
    Event event;
    FILE *fp;

    fp = fopen("reminders.out", "r");
    if (fp == NULL) {
	fp = fopen("reminders.out", "w");
    } 
    fclose(fp);
    int i;
    int Month[12]={1,2,3,4,5,6,7,8,9,10,11,12};
    int days_in_month[]={31,28,31,30,31,30,31,31,30,31,30,31};
    while(1) {
	printf("1.To find the day of the week\n2.To print calendar of a month\n3.To add events or reminder's\n4.To print calendar of year\n5.To display events\n6.back");
	printf("\nenter your choice:- ");
	scanf("\n%c", &choice);
	switch(choice) {
	    case '1':
		printf("enter day, month and year:- ");
		scanf("%d %d %d", &day, &month, &year);
		name_of_the_day(find_day(day, month, year));
		break;
	    case '2':
		printf("enter the month and year:- ");
		scanf("%d %d", &month, &year);
		print_month(month,year);
		break;
	    case '3':
		printf("enter the day, month and year: ");
		scanf("%d %d %d", &event.day, &event.month, &event.year);
		getchar();
		if ((event.day<days_in_month[event.month-1])||(event.day==29 && event.month==2 && is_leap_year(event.year)==1)){
		    printf("enter the event:- ");
		    fgets(event.event, 100,stdin);
		    fp = fopen("reminders.out", "a+");
		    if (fp == NULL) 
		    {
			printf("reminders can't open\n");
			exit(1);
		    }
		    fwrite(&event, sizeof(Event), 1, fp);
		    printf("events sucessfully added\n");
		    fclose(fp);
		}
		else
		    puts("invalid input");
		break;
	    case '4':
		printf("enter the year: ");
		scanf("%d", &year);
		Curseyear(year);
		break;
	    case '5':
		printf("enter the year:");
		scanf("%d",&year);
		Cal_display(year);
		break;		
	    case '6':
		return 1;
		break;
	    default:
		printf("\nthere is no valid event present");
		break;
	}
    }
}
