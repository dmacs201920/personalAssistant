//Header file for Personal Assistant
//       By  A Appala.
//           M Viswanadh.
//           S Akhil.
//       Finished on  15 03 2020. 	

typedef struct takedate      //used in evernote
{
    int d;      //date
    int m;      //month
    int y;      //year
}tdate;

typedef struct contact       //used in contact managment
{
    char first_name[30];
    char middle_name[30];
    char last_name[30];
    char  number[30];
    char emailid[30];
}contact;

typedef struct{           //used in calender
    int day;
    int month;
    int year;
    char event[100];;
}Event;



typedef struct sign_in   //used for sign_in
{
    char user_name[30];
    char pass_word[15];
}sign_in;
typedef sign_in log_in;   //used for log in


FILE *signin(FILE *fp);           //m  header for main sign_in func.
int login(FILE *fp);              //m  header for main log_in func.
void Reminders();                 //prints reminders
//___________VISWANADH+++++++++++++++VISWANADH--------------------------VISWANADH_________________________________VISWANADH__-------------++++++++++++++++++++__________
int EVERNOTE();                     //main in functions
int Count_file(FILE *);         //v counts no.of sentenses in file.
void insert(FILE *);             //v  inserts in given file
int display(FILE *);     //v Display for NOTES
int Insert(FILE *,char *);   //v    insert for categori fife.
int isleapyear(int );      //v     cheacks for leap year.
int checkdate(int ,int ,int );       //v   checks wheather given date is proper or no.
void Options_case_1(FILE *);  //v    asks options
int checkyear(int ); //v                 checks year formate yyyy
void FIND_curses(FILE *); //v;            searchs a word using ncurses
int Search(FILE *,char *); //v         searches given word
void TInsert(FILE *,char *);   //v     //Insert for to do list main file.
void tinsert(FILE *); //v        to do list day file insert fun. .
void Delete(char *,int ,int ,int);        //v       //Delete for to do list.
void Search_Display_year(); //v         display progress for given year.
void Search_Display_mon(); //v            display progress for given month and year.
void Search_Display_date(); //v           display progress for given date. 
void Search_Display_now(); //v                 display today's progress. 
int num_of_pos(FILE *); //v              returns no.of NEGATIVE's in to do list
int num_of_neg(FILE *); //v          returns no.of POSITIVE's in to do list
int Search_year(char* ,FILE *); //v        Searches given year in todofiles dir..
int search_mon(char*,char*,FILE *); //v  Searches given year and month in todofiles dir..
int search_date(char*,char*,char*,FILE *); //v        Searches given year,month,date in todofiles dir..
int search_int_date(char*,FILE *); //v     Searches given year,month,date in todofiles dir.(for int date).
char * itoa(long int ); //v            Converts integer to char pointer.
char *Chara_chars(char ); //v     //Converts char to char*.
//___________VISWANADH+++++++++++++++VISWANADH--------------------------VISWANADH_________________________________VISWANADH__-------------++++++++++++++++++++__________
//______________APPALA____+++++++++++++APPALA-------------------APPALA_______________________________APPALA+++++++++++++++++++++++++++++++++++APPALA____________________
int CALANDER();
int find_day(int d,int m,int y);
int num_days_beg_of_year( int y, int m, int d); // to check no. of days from beginning of the year
int is_leap_year( int year );        //to check whether it is leap or not
int leap_years( int year );         // to check no. of leap years from starting
void Calendar(int y); //to display calendar of a year
void calendar(int m, int y,int d);       //to add events
int days( int y, int m, int d);   // Total number of days
void name_of_the_day(int day);
void print_month(int , int ); //to dispaly calendar of a month
void Cal_display(int); //to dispaly events or reminders
void Curseyear(int ); //function using ncurses
//______________APPALA____+++++++++++++APPALA-------------------APPALA_______________________________APPALA+++++++++++++++++++++++++++++++++++APPALA____________________
//_________________AKHIL+++++++++AKHIL----------------AKHIL+++++++++++++++++++++++++++AKHIL____________________________________________________________________________
int CONTACT_MANAGEMENT();
int is_existing_number(char [] ,FILE *);// checks if the number is in file or not
FILE *Create_contact(contact ,FILE *);// makes the contact list in ascending order after inserting the contact
void Display_contacts(FILE *);//display contact list           
void search(FILE *,char []);// search a contact by name
FILE *Delete_contact (contact  , FILE  *);// delete a single contact
FILE *Delete_contacts(FILE *);//delete full contact list
FILE *edit_contact_name(contact ,FILE *);//edit  name
FILE *edit_contact_number(contact ,FILE *);//edit  number
void  numsearch(FILE *,char []);//search by number
int structnum(FILE *);// total no.of contacts

