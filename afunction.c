#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"aheader.h"
int is_existing_number(char number[],FILE *f)
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
//____________________________________________________________
FILE *insert(contact p,FILE *f1,int *i)
{   int flag=0;
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
	if(fread(&q,sizeof(contact),1,f1)==0)
	{
	    fwrite(&p,sizeof(contact),1,f1);
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
		    fwrite(&q,sizeof(contact),1,f2);
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
                   *i=1;		    
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
	    remove("file.txt");
	    rename("temp","file.txt");
	    f1=fopen("file.txt","ab+");
	    return f1;
	}
    }
}
//_______________________________________________________________________________________________________________________
void Display_contacts(FILE *fp)
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
	printf("\nnumber\tfirstname\tmiddlename\tlastname\temailid\n");
	while(fread(&p,sizeof(contact),1,fp)==1)
	{
	    printf("\n%s	%9s	%9s	%9s	%9s",p.number,p.first_name,p.middle_name,p.last_name,p.emailid);
	}
    }
}
//_______________________________________________________________________________________________________________________________
FILE *Delete(contact p,FILE *f1)
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
//____________________________________________________________________________________
FILE *Delete_contacts(FILE *f1)
{
    char c;
    contact q;
    printf("\n ARE YOU SURE TO DELETE YOUR CONTACT LIST");
    printf("\n TYPE 'y' FOR YES  OR TYPE 'n' FOR NO  ");
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
//____________________________________________________________________________________________
void search(FILE *f1,char a[])
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
	    if(strncmp(a,p.first_name,strlen(a))==0)
	    {
		fwrite(&p,sizeof(contact),1,f2);
		flag=0;
	    }
	    else if(strncmp(a,p.middle_name,strlen(a))==0)
	    {
		fwrite(&p,sizeof(contact),1,f2);
		flag=0;
	    }
	    else if(strncmp(a,p.last_name,strlen(a))==0)
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
//____________________________________________________________
FILE *edit_contact_name(contact q,FILE *f1)
{
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
		f1=insert(q,f1,&i);
		if(i==0)
		f1=Delete(p,f1);
		return f1;
	    }
	    else
		continue;
	}
	printf("\n no matching contacts were found");
	return f1;

    }
}
//____________________________________________________________________________
FILE *edit_contact_number(contact q,FILE *f1)
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
		f1=Delete(p,f1);
		f1=insert(q,f1,&i);
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
