typedef struct contact
{
    char first_name[30];
    char middle_name[30];
    char last_name[30];
    char  number[30];
    char emailid[30];
}contact;
int is_existing_number(char number[] ,FILE *);
FILE *insert(contact ,FILE *,int*);
void Display_contacts(FILE *);
void search(FILE *,char a[]);
FILE *Delete (contact  , FILE  *);
FILE *Delete_contacts(FILE *);
FILE *edit_contact_name(contact ,FILE *);
FILE *edit_contact_number(contact ,FILE *);
