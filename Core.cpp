#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

/*Function for logging in the user*/
int check_user(string us,string pw)
{
    int fg =0;
    string user("admin"),pass("12345678"),test;
    fstream my_file("..\\Data\\Admin.out");
    fstream log_file("..\\Data\\Login.out",iostream::app);
    while(!my_file.eof())
    {
        my_file>>user;
        my_file>>pass;
        if(user==us && pass==pw)

        {
            fg=1;
            time_t CurrentTime;
            time(&CurrentTime);
            log_file<<user<<" logged in at "<<ctime(&CurrentTime)<<endl;
            break;
        }
        else if(user==us && pass!=pw)
        {
            fg=3;
            break;
        }
    }
    my_file.close();
    if(fg!=1 && fg!=3)
    {
        my_file.open("Users.txt");
        while(!my_file.eof())
        {
            my_file>>user;
            my_file>>pass;
            if(user==us && pass==pw)
            {
                fg=2;
                time_t CurrentTime;
                time(&CurrentTime);
                log_file<<user<<" logged in at "<<ctime(&CurrentTime)<<endl;
                break;
            }
            else if(user==us && pass!=pw)
            {
                fg=3;
                break;
            }
        }
    }
    my_file.close();
    if(fg==0)
        fg=4;
    return fg;
}


int filebug(int id, string user)
{
    int n = 0;
    char bugnum[20];
    char op[200];
    time_t CurrentTime;
    char name[200];
    //char bugtype[50];
    char bugdescription[50][100];
    char bugpriority[30];
    //int bugstatus;
    struct stat statbuf;
    char newname[200];
    int scancount;
    int i;
    FILE* ptr;
    printf("**********FILING A BUG***********\n");
    time(&CurrentTime);
    printf(  "\tCurrent Bug List:\n" );
    system("dir ..\\Data\\*.txt");
    printf("Enter the next available bug number (Maximum of 999 bugs):\n");
    scancount = scanf("%s", bugnum);
    id = atoi(bugnum);
    while (1) {
        memset(name, 0, sizeof(name));
        printf("Enter the name of the bug (Maximum 25 characters):\n");
        scancount = scanf("%s", name);
        if (scancount >= 25)
        {
            printf("Name of the bug is too long; try again\n");
        }
        else {
            break;
        }
    }
    char ids[10];
    char idsAdjusted[10];
    while (1) {
        _itoa(id, ids, 10);
        if (id <= 9)
        {
            strcpy(idsAdjusted , "00");
            strcat(idsAdjusted, ids);
            strcpy(ids, idsAdjusted);
        }
        else {
            if (id <=99)
            {
                strcpy(idsAdjusted, "0");
                strcat(idsAdjusted, ids);
                strcpy(ids, idsAdjusted);
            }
        }
        
        char ex[] = ".txt";
        memset(newname, 0, sizeof(newname));
        strcpy(newname, "..\\Data\\");
        strcat(newname, ids);
        strcat(newname, "-");
        strcat(newname, name);
        strcat(newname, ex);
        printf("Filename : %s\n", newname);
        if (stat(newname, &statbuf) == 0)
        {
            id++;
        }
        else {
            strcpy(name, newname);
            break;
        }
    }
    ptr = fopen(name, "w");
    if (ptr == NULL) {
        printf("Quiting -- cannot create file!!![%s]\n", name);
        return -1;
    }
    fprintf(ptr, "DATE AND TIME : %s",
        ctime(&CurrentTime));
    fprintf(ptr, "BUG ID    :    %d\n", id);
    fprintf(ptr, "\n");
    printf("BUG ID:%d\n", id);
    n = (int)user.length();
    //char op[n+1];
    strcpy(op, user.c_str());
    fprintf(ptr, "BUG FILED BY: %s\n",
        op);
    fprintf(ptr, "\n");
    while (1) {
        memset(bugpriority, 0, sizeof(bugpriority));
        printf("Enter name of bug priority: Severity is of 5 types:\n    Critical, Major, Moderate, Minor, and Cosmetic.\n");
        scanf(" %[^\n]s", bugpriority);
        if (strcmp(bugpriority, "Critical") == 0)break;
        if (strcmp(bugpriority, "Major") == 0)break;
        if (strcmp(bugpriority, "Moderate") == 0)break;
        if (strcmp(bugpriority, "Minor") == 0)break;
        if (strcmp(bugpriority, "Cosmetic") == 0)break;
        printf("Incorrect priority name entered -- try again\n");

    }
    fprintf(ptr, "BUG PRIORITY: %s\n",
        bugpriority);
    fprintf(ptr, "\n");
    printf("Enter the bug description:\n(Fifty (50) lines maximum - last line must only contain '#'\n");
    for (i = 0; i < 50; i++)
    {
    
    scanf(" %[^\n]s", bugdescription[i]);
    if (bugdescription[i][0] == '#') 
        {
        break;
        }
    }
    fprintf(ptr, "BUG DESCRIPTION: \n");
    for (i = 0; i < 50; i++) {
        fprintf(ptr, "     %s\n",  bugdescription[i]);
        if (bugdescription[i][0] == '#') break;

    }
    fprintf(ptr, "\n");
    printf("Status of bug:\n");
    printf("   1. NOT YET ASSIGNED\n");
    printf("   2. IN PROCESS\n   3. FIXED\n");
    printf("   4. DELIVERED\nENTER THE NUMBER OF YOUR CHOICE: ");
    int j;
    scanf("%d", &j);
    // Date and time of Bug Creation
    fprintf(ptr, "DATE AND TIME: %s",
            ctime(&CurrentTime));
    fprintf(ptr, "BUG STATUS: ");
    switch (j) {
    case 1:
        fprintf(ptr, "NOT YET ASSIGNED\n");
        break;
    case 2:
        fprintf(ptr, "IN PROCESS\n");
        break;
    case 3:
        fprintf(ptr, "FIXED\n");
        break;
    case 4:
        fprintf(ptr, "DELIVERED\n");
        break;
    default:
        printf("invalid choice\n");
        break;
    }
    fclose(ptr);
    return 0;
}
/*Function to change the status of a bug*/
void changestat(string user)
{
    char ids[10];
    char idsAdjusted[10];
    int bgidInt = 0;
    cout << "\t*****Changing The Status*****" << endl;
    string bgname, bgid;
    int bgstatus;
    printf("\tCurrent Bug List:\n");
    system("dir ..\\Data\\*.txt");
    cout << "Enter the bugname: ";
    cin >> bgname;
    cout << "Enter the bug id: ";
    cin >> bgid;
    strcpy(ids, bgid.c_str());
    bgidInt = atoi(ids);
    
    if (bgidInt <= 9)
    {
        strcpy(idsAdjusted, "00");
        strcat(idsAdjusted, ids);
        strcpy(ids, idsAdjusted);
    }
    else {
        if (bgidInt <= 99)
        {
            strcpy(idsAdjusted, "0");
            strcat(idsAdjusted, ids);
            strcpy(ids, idsAdjusted);
        }
    }
    bgid = ids;
    string pp = ids; //to_string(bgid);
    string ed(".txt");
    string dash("-");
    string directory("..\\Data\\");
    string fullpath=directory + bgid + dash + bgname+ed;
    fstream my_file;
    my_file.open(fullpath);
    my_file.seekp(0,ios::end);
    cout << "Updating " << fullpath <<"\n";
    cout<< "Enter the bug status by choosing one of the following:\n 1. Not yet assigned\n 2. In process\n 3. Fixed\n 4. Delivered\n";
    cout<<"Your choice: ";
    cin>>bgstatus;
    time_t CurrentTime;
    time(&CurrentTime);
    my_file<<"Status of the bug updated by "<<user<<" at "<<ctime(&CurrentTime)<<endl;
    my_file << "Bug status: \t";// << endl;
    switch(bgstatus)
    {
    case 1:
        {
            my_file<<"Not yet assigned"<<endl;
            break;
        }
    case 2:
        {
            my_file<<"In process"<<endl;
            break;
        }
    case 3:
        {
            my_file<<"Fixed"<<endl;
            break;
        }
    case 4:
        {
            my_file<<"Delivered"<<endl;
            break;
        }
    default:
        {
            my_file<<"Undefined"<<endl;
        }
    }
    my_file.close();
}

/*Function to get report on a bug*/
void getreport()
{
    string bgname,line;  
    char idsAdjusted[10];
    char ids[10];
    int bgid;
    cout<<"\t*****Reporting the Bug*****"<<endl;
    cout << "\tPossible Bugs:" << endl;
    system("dir ..\\Data\\*.txt");
    cout<<"Enter the bugname: ";
    cin>>bgname;   
    cout<<"Enter the bug id: ";
    cin>>bgid;
     _itoa(bgid, ids, 10);
        if (bgid <= 9)
        {
            strcpy(idsAdjusted , "00");
            strcat(idsAdjusted, ids);
            strcpy(ids, idsAdjusted);
        }
        else {
            if (bgid <=99)
            {
                strcpy(idsAdjusted, "0");
                strcat(idsAdjusted, ids);
                strcpy(ids, idsAdjusted);
            }
        }
        string pp = ids; //to_string(bgid);
    string dash("-");
    string en=".txt";
    string directory = "..\\Data\\";
    string fullpath= directory+ pp + dash + bgname+en;
    fstream my_file(fullpath);
    cout<<"********* "<<fullpath<<" *********"<<endl;
    while (std::getline(my_file, line)) {
        cout<<line<<endl;
    }
    cout<<endl;
    my_file.close();
}

/*Function to add/remove a user*/
void aruser()
{
    string nwuser(""),nwpassword("");
    string us(""),pw("");
    cout<<"\t*****Adding/Removing a User*****"<<endl;
    int ad;
    cout<<"Enter 1 to remove a user and otherwise to add: ";
    cin>>ad;
    int flag=0;
    if(ad==1)
    {
        ifstream fin;
        fin.open("..\\Data\\Admin.out");
        ofstream temp;
        temp.open("temp.txt");
        cout << "Enter the username of the user to be removed: ";
        cin >> nwuser;
        while (getline(fin,us))
        {
            getline(fin,pw);
            if(us!=nwuser)
            {
                temp<<us<<endl;
                temp<<pw<<endl;
            }
            if(us==nwuser)
                flag=1;
        }
        temp.close();
        fin.close();
        remove("..\\Data\\Admin.out");
        rename("temp.txt","..\\Data\\Admin.out");

        if(flag!=1)
        {
            ifstream fin;
            fin.open("..\\Data\\Users.out");
            ofstream temp;
            temp.open("\\Data\\temp.out");
            while (getline(fin,us))
            {
                getline(fin,pw);
                if(us!=nwuser)
                {
                    temp<<us<<endl;
                    temp<<pw<<endl;
                }
                if(us==nwuser)
                    flag=1;
            }
            fin.close();
            temp.close();
            remove("..\\Data\\Users.out");
            rename("..\\Data\\temp.out","..\\Data\\Users.out");
        }
        cout<<"The user has been removed!!"<<endl;
    }
    else
    {
        int auth;
        cout<<"Enter the username of the user to be added: ";
        cin>>us;
        cout<<"Enter the password of the new user: ";
        cin>>pw;
        cout<<"Enter 0 if the user to be added is an admin and any other value if otherwise";  
        cin>>auth;
        if(auth==0)
        {
            ofstream temp;
            temp.open("..\\Data\\Admin.out",ifstream::app);
            temp<<endl;
            temp<<us<<endl;
            temp<<pw<<endl;
            temp.close();
        }
        else
        {
            ofstream temp;
            temp.open("..\\Data\\Users.out",ifstream::app);
            temp<<endl;
            temp<<us<<endl;
            temp<<pw<<endl;
            temp.close();
        }
    }
}

/*Function to check login history of users*/
void checkhist()
{
    cout<<"\t*****Reporting Login History*****"<<endl;
    ifstream my_file("..\\Data\\Login.out");
    if (my_file.is_open()) {
    std::string line;
    while (std::getline(my_file, line)) {
        cout<<line<<endl;
    }
    }
    cout<<endl;
    my_file.close();
}

/*Function to logout the user*/
void logout(string user)
{
    fstream log_file;
    log_file.open("..\\Data\\Login.out",fstream::app);
    cout<<"\tLogging Out............."<<endl;
    time_t CurrentTime;
    time(&CurrentTime);
    log_file<<user<<" logged out at "<<ctime(&CurrentTime)<<endl;
    log_file.close();
}

void ex(string user)
{
    cout<<endl<<"Exiting... "<<endl;
    fstream log_file;
    log_file.open("..\\Data\\Login.out",fstream::app);
    time_t CurrentTime;
    time(&CurrentTime);
    log_file<<user<<" exited the program at "<<ctime(&CurrentTime)<<endl;
    log_file.close();
}

/*Driver code*/
int main()
{
    cout<<"********************** WELCOME TO THE BUG TRACKING SYSTEM **********************"<<endl;
    int exit=0;
    int flag=0;
    int count=0;
    int id=0;
    string username,password;
    while(exit!=1)
    {
        flag=0;
        for(int i=3;i>0;i--)
        {
            if(flag!=0)
            cout<<"You have "<<i<<" tries left!!"<<endl<<endl;
            cout<<"\t Please login by giving username and password below: "<<endl;
            cout<<" Username: ";
            cin>>username;
            cout<<" Password: ";
            cin>>password;
            flag=check_user(username,password);
            if(flag==1)
                break;
            else if(flag==2)
                break;
            else if(flag==3)
                cout<<"Incorrect Password for this Username!!"<<endl;
            else
                cout<<"User does not exist!!"<<endl;
        }
        if(flag==3 || flag==4)
        {
            exit=1;
            continue;
        }
        else if(flag==1)
        {
            cout<<"\t\t Welcome "<<username<<"!!"<<endl;
            int choice=0;
            while((choice!=6 )&& (choice!=7))
            {
                cout<<"\nPlease choose from an option below:"<<endl;
                cout<<"1. File a new bug\n2. Change the status of the bug\n3. Get report of the bugs\n4. Add/Remove a user to the database\n5. Check login history\n6. Logout\n7. Exit"<<endl;
                cout<<"Your choice: ";
                cin>>choice;
                switch(choice)
                {
                    case 1: {
                        id++;
                        filebug(id,username);
                        break;
                    }
                    case 2: {
                        changestat(username);
                        break;
                    }
                    case 3: {
                        getreport();
                        break;
                    }
                    case 4: {
                        aruser();
                        break;
                    }
                    case 5:{
                        checkhist();
                        break;
                    }
                    case 6:{
                        logout(username);
                        choice=6;
                        break;
                    }
                    case 7:{
                        choice=7;
                        exit=1;
                        break;
                    }
                }
                if(choice==6 || choice==7)
                    break;
            }
        }
        else
        {
            cout<<"\t\t Welcome "<<username<<"!!"<<endl;
            int choice=0;
            while((choice!=4) &&( choice!=5))
            {
                cout<<"Please choose from an option below:"<<endl;
                cout<<"1. File a new bug\n2. Change the status of the bug\n3. Get report of the bugs\n4. Logout\n5. Exit"<<endl;
                cout<<"Your choice: ";
                cin>>choice;
                switch(choice)
                {
                    case 1: {
                        id++;
                        filebug(id,username);
                        break;
                    }
                    case 2: {
                        changestat(username);
                        break;
                    }
                    case 3: {
                        getreport();
                        break;
                    }
                    case 4:{
                        logout(username);
                        choice=4;
                        break;
                    }
                    case 5:{
                        choice=5;
                        ex(username);
                        exit=1;
                        break;
                    }
                }
                if(choice==4 || choice==5)
                    break;
            }
        }
    }
   
}
