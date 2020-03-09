#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"aheader.h"
void main()
{
    int opt;
    FILE *fp;
    contact c;
    char a[30]="";
    int b,choice;
    int *temp;
    system("clear");
    while(1)
    { 	printf("\n\t1.CREATE CONTACT.\n\t2.DISPLAY.\n\t3.SEARCH.\n\t4.DELETE.\n\t5.DELETE CONTACT LIST\n\t6.EDIT CONTACT.\n\t7.EXIT");	
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
				fp=insert(c,fp,temp);
				//{
				  //  puts("already existing contact");
				    //puts("please enter once again");
				   // continue;
				
				//}
				//else
				    break;
			}
		        break;
		}
		break;///////////////CASE BREAK(1)
            case 2://////////////////////////display	
	                          Display_contacts(fp);
				  break;////////////    CASE BREAK(2)
	    case 3://///////////////////////search
				  printf("\nPlease enter some charecters");
				  scanf("%s",a);
				  search(fp,a);
				  break;
	    case 4://////////////////////////////delete
				  printf("\nplease enter following details");
				  puts("First_name:");
				    scanf("%s",c.first_name);
				   puts("Second_name");
                                    scanf("%s",c.middle_name);
				  puts("Last_name");
				  scanf("%s",c.last_name);
				   fp=Delete(c,fp);
				  break;
	    case 5://///////////////////////////delete full list
				  fp=Delete_contacts(fp);
				  break;
	    case 6://///////////////////////////edit
				  printf("\n what u want to edit");
				  printf("\n 1.NAME.\n 2.NUMBER");
				  scanf("%d",&opt);
				  if(opt==1)
				  {
				  printf("\nenter the number");
				  scanf("%s",c.number);
				  fp=edit_contact_name(c,fp);
				  }
				  else if(opt==2)
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
	    case 7:////////////////////////exit
				  exit(-1);
				  break;
	    default:printf("\n PLEASE ENTER VALID INPUT");
	}
	fclose(fp);
    }
}
