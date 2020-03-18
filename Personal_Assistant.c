//   Main program for Personal Assistant.
/*
              By  Akhil
	          Viswanadh
		  Appala
              Finished on 18 03 2020.
*/
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<termios.h>
#include<time.h>
#include<string.h>
#include"header.h"
int global;
char owner[27];
void main()
{
    int a,choice,option,chck;
    FILE *Usr_name;
    system("clear");
    Usr_name=fopen(".USER_NAME","rb");
    if (Usr_name==NULL)
    {
	Usr_name=fopen(".USER_NAME","wb");
	if (Usr_name==NULL)
	{
	    puts("Sorry!Computer is unable to open FILE");
	    exit(1);
	}
	puts("To use PERSONAL ASSISTANT please sign_in\n");
	Usr_name=signin(Usr_name);
	fclose(Usr_name);
	Usr_name=fopen(".USER_NAME","rb");
	if (Usr_name!=NULL)
	    puts("SUCESSFULLY SIGNED IN");
	else 
	{
	    puts("Unable to Sign_in");
	    exit(1);
	}

    }
    else
    {
 sos:
	printf("\n\t\t1.Log_in\n\t\t2.Exit\n");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:
		system("clear");
		a=login(Usr_name);
		if(a==0)                //correct username and password.
		{
		    while(1)
		    {
		    system("clear");
		    Reminders();
		    printf("\n\t\t\t");
		    puts("SUCCESSFULLY LOGGED_IN");
		    printf("\t\t\tWELCOM TO PERSONAL ASSISTANT\n");
		    printf("\tPlease select one of the options :");
		    printf("\n\t\t1.CALANDER\n\t\t2.CONTACT_MANAGEMENT\n\t\t3.EVERNOTE\n\t\t4.EXIT");
		    scanf("%d",&option);
		    
			switch(option)
			{
			    case 1:
				CALANDER();
				break;
			    case 2:
				CONTACT_MANAGEMENT();
				break;
			    case 3:
				EVERNOTE();
				    break;
			    case 4:
				    printf("THANK YOU %s for using PERSONAL ASSISTANT",owner);
				    exit(1);
				    break;
			    default:
				    printf("Sorry %s you have entered an invalid option",owner);
				break;
			}
		    }
		}
		else if(a==-1)
		{
		    puts("INVALID USERNAME OR PASSWORD");
		    goto sos;
		}
		else if(a==2)                  //Impossible case.              
		    puts("first please sign_in");
		break;
	    case 2:
		printf("\t\tThank for using Personal Assistant\n\t\t\t\t-Your Brothers.\n");
		break;
	    default:
		puts("Please select valid option");
		goto sos;
	}
    }
}
