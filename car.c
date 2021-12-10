#include <stdio.h>
#include "conio2.h"
#include "car.h"
#include <string.h>

void addAdmin()
{
    FILE *fp;
    fp = fopen("admin.bin","rb");
    if(fp == NULL)
    {
        fp = fopen("admin.bin","wb");
        User u[2] = {{"admin1","pwd1","Sahil"},{"admin2","pwd2","Sachin"}};
        fwrite(u,sizeof(u),1,fp);
        printf("File Saved!");
        fclose(fp);
        getch();
    }
    else
        fclose(fp);
}
User *getInput()
{
    int i;
    clrscr();
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i = 1; i <= 80; i++)
        printf("%c",247);
    gotoxy(32,5);
    printf("* LOGIN PANEL *");
    gotoxy(1,7);
    textcolor(LIGHTCYAN);
    for(i = 0; i < 80; i++)
        printf("%c",247);
    gotoxy(1,15);
    for(i = 0; i < 80; i++)
        printf("%c",247);
    textcolor(WHITE);
    gotoxy(60,8);
    printf("Press 0 to exit");
    textcolor(LIGHTCYAN);
    gotoxy(25,10);
    printf("Enter user id :");
    textcolor(WHITE);
    static User u;
    fflush(stdin);
    fgets(u.userid,20,stdin);
    char *pos;
    pos = strchr(u.userid,'\n');
    if(pos!=NULL)
    {
        *pos = '\0';
    }
    if(strcmp(u.userid,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("Login Cancelled");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    textcolor(LIGHTCYAN);
    gotoxy(25,11);
    printf("Enter password :");
    fflush(stdin);
    i = 0;
    textcolor(WHITE);
    for(;;)
    {
        u.pwd[i] = getch();
        if(u.pwd[i] == 13)
        {
            break;
        }
        else if(u.pwd[i] == 8)
        {
            printf("\b \b");
            i = i-2;
        }
        else
        printf("*");
        i++;
    }
    u.pwd[i] = '\0';
    if(strcmp(u.pwd,"0") == 0)
    {
        textcolor(LIGHTRED);
        gotoxy(30,17);
        printf("Login Cancelled");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    return &u;
}
int checkUserExist(User u,char *usertype)
{
    if(strlen(u.userid)==0 || strlen(u.pwd)== 0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Both fields are mandatory. Try again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t");
        return 0;
    }
    FILE *fp;
    if(strcmp(usertype,"admin") == 0)
    {
        fp = fopen("admin.bin","rb");
    }
    else
    {
        fp = fopen("emp.bin","rb");
    }
    if(fp == NULL)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Sorry! Cannot open the file");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t");
        return -1;
    }
    int found = 0;
    User user;
    while(fread(&user,sizeof(user),1,fp) == 1)
    {
        if((strcmp(u.userid,user.userid) == 0) && (strcmp(u.pwd,user.pwd) == 0))
        {
            found = 1;
            break;
        }
    }
    if(found == 0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Invalid userid/password. Try again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
    }
    else
    {
        gotoxy(28,20);
        textcolor(GREEN);
        printf("Login successful!");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t\t\t\t");
    }
    fclose(fp);
    return found;
}
int adminMenu()
{
    int choice,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("ADMIN MENU\n");
    for(i = 1; i <= 80; i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Add Employee");
    gotoxy(32,9);
    printf("2. Add Car Details");
    gotoxy(32,10);
    printf("3. Show Employee");
    gotoxy(32,11);
    printf("4. Show Car Details");
    gotoxy(32,12);
    printf("5. Delete Employee");
    gotoxy(32,13);
    printf("6. Delete Car Details");
    gotoxy(32,14);
    printf("7. Exit\n\n");
    printf("Enter choice : ");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;

}
void addEmployee()
{
    char temp[20];
    char choice;
    char *pos;
    User u;
    FILE *fp;
    fp = fopen("emp.bin","ab+");
    fseek(fp,0,SEEK_END);
    int total_rec=ftell(fp)/sizeof(User);
    if(total_rec!=0)
     {
        fseek(fp,-60,SEEK_END);
        fread(temp,sizeof(temp),1,fp);
        getch();
        pos=strchr(temp,'-');
        total_rec=atoi(pos+1);
        getch();
     }
    total_rec++;
    sprintf(u.userid,"EMP-%d",total_rec);
    fseek(fp,0,SEEK_END);
    do
    {
        clrscr();
        gotoxy(32,2);
        textcolor(LIGHTRED);
        printf("CAR RENTAL APP");
        textcolor(LIGHTGREEN);
        int i;
        gotoxy(1,3);
        for(i=1;i<=80;i++)
            printf("~");
        textcolor(WHITE);
        gotoxy(25,5);
        printf("***** ADD EMPLOYEE DETAILS *****");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter Employee Name:");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.name,20,stdin);
        pos=strchr(u.name,'\n');
        if(pos!=NULL)
        {
            *pos='\0';
        }
        textcolor(YELLOW);
        printf("Enter Employee Pwd:");
        fflush(stdin);
        textcolor(WHITE);
        fgets(u.pwd,20,stdin);
        pos=strchr(u.pwd,'\n');
        if(pos!=NULL)
        {
            *pos='\0';
        }
        fwrite(&u,sizeof(u),1,fp);
        gotoxy(30,15);
        textcolor(LIGHTGREEN);
        printf("EMPLOYEE ADDED SUCCESSFULY!");
        printf("\nEMPLOYEE ID is %s",u.userid);
        getch();
        gotoxy(1,20);
        textcolor(LIGHTRED);
        printf("Do you want to add more employees (Y/N)?");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&choice);
        if(choice == 'N'|| choice == 'n')
            break;
        total_rec++;
        sprintf(u.userid,"EMP-%d",total_rec);
    }while(1);
    fclose(fp);

}

void addCarDetails()
{
    char choice;
    char *pos;
    Car C;
    FILE *fp;
    fp = fopen("car.bin","ab+");
    fseek(fp,0,SEEK_END);
    int total_rec = ftell(fp)/sizeof(C);
    if(total_rec!=0)
     {
        int temp;
        fseek(fp,-sizeof(C),SEEK_END);
        fread(&temp,sizeof(temp),1,fp);
        total_rec = temp;
     }
     total_rec++;
     C.car_id = total_rec;
     do
     {
         clrscr();
         gotoxy(32,2);
         textcolor(LIGHTRED);
         printf("CAR RENTAL APP");
         int i;
         gotoxy(1,3);
         textcolor(GREEN);
         for(i = 1; i <= 80; i++)
            printf("~");
        textcolor(WHITE);
        gotoxy(24,5);
        printf("***** ADD CAR DETAILS *****");
        gotoxy(1,8);
        textcolor(YELLOW);
        printf("Enter Car Model: ");
        fflush(stdin);
        textcolor(WHITE);
        fgets(C.car_name,50,stdin);
        pos=strchr(C.car_name,'\n');
        if(pos!=NULL)
        {
            *pos='\0';
        }
        textcolor(YELLOW);
        printf("Enter Car Capacity: ");
        textcolor(WHITE);
        scanf("%d",&C.capacity);
        textcolor(YELLOW);
        printf("Enter Car Count: ");
        textcolor(WHITE);
        scanf("%d",&C.car_count);
        textcolor(YELLOW);
        printf("Enter Car Price For Per Day: ");
        textcolor(WHITE);
        scanf("%d",&C.price);
        fseek(fp,0,SEEK_END);
        fwrite(&C,sizeof(C),1,fp);
        gotoxy(29,15);
        textcolor(LIGHTGREEN);
        printf("CAR ADDED SUCCESSFULLY");
        gotoxy(2,16);
        printf("CAR ID IS: %d",C.car_id);
        gotoxy(1,19);
        textcolor(LIGHTRED);
        printf("DO YOU WANT TO ADD MORE CARS(Y/N): ");
        textcolor(WHITE);
        fflush(stdin);
        scanf("%c",&choice);
        if(choice == 'N' || choice == 'n')
            break;
        total_rec++;
        C.car_id = total_rec;
     }while(1);
     fclose(fp);

}
void viewEmployee()
{
    FILE *fp;
    fp = fopen("emp.bin","rb");
    User ur;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i = 0; i < 80; i++)
        printf("%c",247);
    gotoxy(31,5);
    printf("* EMPLOYEE DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i = 0; i < 80; i++)
        printf("%c",247);
    if(fp == NULL)
    {
        gotoxy(31,9);
        textcolor(LIGHTRED);
        printf("Sorry! No employees added yet!");
        getch();
        return ;
    }
    gotoxy(1,8);
    printf("Employee ID\t\t\tName\t\t\tPassword");
    gotoxy(1,9);
    for(i = 0; i < 80; i++)
        printf("%c",247);
    int row = 10;
    textcolor(YELLOW);
    while(fread(&ur,sizeof(ur),1,fp) == 1)
    {
        gotoxy(2,row);
        printf("%s",ur.userid);
        gotoxy(33,row);
        printf("%s",ur.name);
        gotoxy(57,row);
        printf("%s",ur.pwd);
        row++ ;
    }
    fclose(fp);
    getch();

}

void showCarDetails()
{
    FILE *fp=fopen("car.bin","rb");
    Car C;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1; i<=80; i++)
        printf("%c",247);
    gotoxy(31,5);
    textcolor(YELLOW);
    printf("* ALL CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1; i<80; i++)
        printf("%c",247);
    if(fp==NULL)
    {
        gotoxy(31,9);
        textcolor(LIGHTRED);
        printf("Sorry! No cars present");
        getch();
        return;
    }

    gotoxy(1,8);
    printf(" Car ID\t   Model\t\t   Capacity\tAvailable\tPrice/Day");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=1; i<80; i++)
        printf("%c",247);
    int row = 10;
    textcolor(YELLOW);

    while(fread(&C,sizeof(C),1,fp)==1)
    {
        gotoxy(2,row);
        printf("%d",C.car_id);
        gotoxy(12,row);
        printf("%s",C.car_name);
        gotoxy(38,row);
        printf("%d",C.capacity);
        gotoxy(50,row);
        printf("%d",C.car_count);
        gotoxy(68,row);
        printf("%d",C.price);
        row++;
    }
    fclose(fp);
    getch();
}

int deleteEmp()
{
    FILE *fp1;
    fp1 = fopen("emp.bin","rb");
    char empid[10];
    int i,result;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1; i<=80; i++)
        printf("%c",247);
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("* DELETE EMPLOYEE RECORD *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1; i<80; i++)
        printf("%c",247);
    gotoxy(1,12);
    for(i=1; i<80; i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo Employee Added Yet!");
        return -1;
    }
    FILE *fp2;
    fp2 = fopen("temp.bin","wb+");
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Employee Id to delete the record:");
    textcolor(WHITE);
    scanf("%s",empid);
    User U;
    int found=0;
    while(fread(&U,sizeof(U),1,fp1)==1)
    {
        if(strcmp(U.userid,empid)!=0)
        {
            fwrite(&U,sizeof(U),1,fp2);
        }
        else
        {
            found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.bin");
    }
    else
    {
        result=remove("emp.bin");
        if(result!=0)
            return 2;

        result=rename("temp.bin","emp.bin");
        if(result!=0)
            return 2;
    }
    return found;

}

int empMenu()
{
    int choice,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i = 1; i <= 80; i++)
    {
        printf("*");
    }
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1. Rent A Car");
    gotoxy(32,9);
    printf("2. Booking Details");
    gotoxy(32,10);
    printf("3. Available Car Details");
    gotoxy(32,11);
    printf("4. Show All Car Details");
    gotoxy(32,12);
    printf("5. Return Car Model");
    gotoxy(32,13);
    printf("6. Exit");
    gotoxy(32,15);
    printf("Enter choice:");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;
}

int deleteCarModel()
{
    Car C;
    int found=0;
    clrscr();
    FILE *fp1=fopen("car.bin","rb");
    int id;
    int i,result;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(BLUE);
    for(i=1; i<=80; i++)
        printf("%c",247);
    gotoxy(29,5);
    textcolor(YELLOW);
    printf("* DELETE CAR RECORD *");
    gotoxy(1,7);
    textcolor(BLUE);
    for(i=1; i<=80; i++)
        printf("%c",247);
    gotoxy(1,12);
    for(i=1; i<80; i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo Car Added Yet!");
        getch();
        return -1;
    }
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Car  Id to delete the record:");
    textcolor(WHITE);
    scanf("%d",&id);
    gotoxy(1,10);
    textcolor(GREEN);
    FILE *fp2=fopen("temp.bin","wb+");
    while(fread(&C,sizeof(C),1,fp1)==1)
    {
        if(C.car_id!=id)
        {
            fwrite(&C,sizeof(C),1,fp2);
        }
        else
            found = 1;
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
        remove("temp.bin");
    else
    {
        result = remove("car.bin");
        if(result!=0)
        {
            gotoxy(32,17);
            perror("");
            getch();
            return 2;
        }
        result=rename("temp.bin","car.bin");
        if(result!=0)
        {
            gotoxy(32,17);
            perror("");
            getch();
            return 2;
        }
    }
    return found;
}

int selectCarModel()
{
    int flag;
    FILE *fp=fopen("car.bin","rb");
    Car C;
    int choice,row = 9;
    gotoxy(34,row);
    int carCount = 0;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_count>0)
        {
            printf("%d. %s",C.car_id,C.car_name);
            gotoxy(34,++row);
            ++carCount;
        }
    }
    if(carCount == 0)
    {
        fclose(fp);
        return -2;
    }
    gotoxy(34,row+2);
    printf("Enter your choice(0 to quit):");
    while(1)
    {
        flag=0;
        scanf("%d",&choice);
        if(choice == 0)
        {
            fclose(fp);
            return 0;
        }
        rewind(fp);
        while(fread(&C,sizeof(C),1,fp)==1)
        {
            if(C.car_id==choice && C.car_count > 0)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            fclose(fp);
            return C.car_id;
        }
        gotoxy(37,row+4);
        textcolor(LIGHTRED);
        printf("Wrong Input");
        getch();
        gotoxy(35,row+4);
        printf("\t\t\t");
        gotoxy(52,row+2);
        printf("\t");
        gotoxy(52,row+2);
        textcolor(WHITE);
    }

}

int isValidDate(struct tm dt)
{
    gotoxy(22,16);
    time_t now = time(0);
    struct tm *sd = localtime(&now);
    sd->tm_mon = sd->tm_mon+1;
    sd->tm_year = 1900 + sd->tm_year;

    if(dt.tm_mon < sd->tm_mon)
        return 0;

    else if(dt.tm_mon == sd->tm_mon && dt.tm_mday < sd->tm_mday)
        return 0;

    if(dt.tm_year >= 2021 && dt.tm_year <= 2022)
    {
        if(dt.tm_mon >= 1 && dt.tm_mon <= 12)
        {
            if((dt.tm_mday >= 1 && dt.tm_mday <= 31) && (dt.tm_mon == 1 || dt.tm_mon == 3 || dt.tm_mon == 5 || dt.tm_mon == 7 || dt.tm_mon == 8 || dt.tm_mon == 10 || dt.tm_mon == 12))
                return 1;
            else if((dt.tm_mday >= 1 && dt.tm_mday <= 30) && (dt.tm_mon == 4 || dt.tm_mon == 6 || dt.tm_mon == 9 || dt.tm_mon == 11))
                return 1;
            else if((dt.tm_mday >= 1 && dt.tm_mday <= 28) && (dt.tm_mday == 2))
                return 1;
            else if(dt.tm_mday == 29 && dt.tm_mon == 2 && (dt.tm_year % 400 == 0 || (dt.tm_year % 4 == 0 && dt.tm_year % 100 != 0)))
                return 1;
            else
                return 0;
        }
    }
    else
        return 0;
}

void updateCarCount(int c)
{
    FILE *fp;
    fp = fopen("car.bin","rb+");
    if(fp == NULL)
    {
        printf("Sorry! File cannot be opened.");
        getch();
        return ;
    }
    Car C;
    while(fread(&C,sizeof(Car),1,fp) == 1)
    {
        if(C.car_id == c)
        {
            fseek(fp,-8,SEEK_CUR);
            int cc_new = C.car_count-1;
            fwrite(&cc_new,sizeof(cc_new),1,fp);
            fseek(fp,-4,SEEK_CUR);
            getch();
        }
    }
    fclose(fp);
}

void bookedCarDetails()
{
    clrscr();
    FILE *fp;
    fp = fopen("customer.bin","rb");
    Customer_Car_Details CC;
    int i;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i = 1; i <= 80; i++)
        printf("%c",247);
    gotoxy(31,5);
    textcolor(YELLOW);
    printf("* BOOKED CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i = 1; i <= 80; i++)
        printf("%c",247);
    gotoxy(1,8);
    printf("Model\t Cust Name\t Pick Up\t Drop\t\t S_Date\t\tE_Date");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i = 1; i <= 80; i++)
        printf("%c",247);
    int row = 10;
    textcolor(YELLOW);
    while(fread(&CC,sizeof(Customer_Car_Details),1,fp) == 1)
    {
        gotoxy(1,row);
        printf("%s",getCarName(CC.car_id));
        gotoxy(13,row);
        printf("%s",CC.cust_name);
        gotoxy(27,row);
        printf("%s",CC.pick);
        gotoxy(44,row);
        printf("%s",CC.drop);
        gotoxy(58,row);
        printf("%d-%d-%d",CC.sd.tm_mday,CC.sd.tm_mon,CC.sd.tm_year);
        gotoxy(70,row);
        printf("%d-%d-%d",CC.ed.tm_mday,CC.ed.tm_mon,CC.ed.tm_year);
        row++;
    }
    fclose(fp);
}

char *getCarName(int car_id)
{
    FILE *fp;
    fp = fopen("car.bin","rb");
    if(fp == NULL)
    {
        printf("Sorry! File cannot be opened.");
        return 0;
    }
    static Car C;
    while(fread(&C,sizeof(C),1,fp) == 1)
    {
        if(C.car_id == car_id)
        {
            break;
        }
    }
    fclose(fp);
    return C.car_name;
}

int rentCar()
{
    Customer_Car_Details CC;
    int i,c;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i = 1; i <= 80; i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    c = selectCarModel();
    if(c == 0 || c == -2)
        return c;
    CC.car_id = c;
    clrscr();
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MENU\n");
    for(i = 1; i <= 80; i++)
        printf("*");
    gotoxy(1,17);
    for(i = 1; i <= 80; i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(27,9);
    printf("Enter Customer Name:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.cust_name,30,stdin);
    char *pos;
    pos = strchr(CC.cust_name,'\n');
    *pos = '\0';
    gotoxy(27,10);
    textcolor(YELLOW);
    printf("Enter Pickup Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.pick,30,stdin);
    pos = strchr(CC.pick,'\n');
    *pos = '\0';
    gotoxy(27,11);
    textcolor(YELLOW);
    printf("Enter Drop Point:");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.drop,30,stdin);
    pos = strchr(CC.drop,'\n');
    *pos = '\0';
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date (dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
        int datevalid = isValidDate(CC.sd);
        if(datevalid == 0)
        {
            gotoxy(27,18);
            textcolor(LIGHTRED);
            printf("Wrong Date");
            getch();
            gotoxy(27,18);
            printf("\t\t");
            gotoxy(56,12);
            printf("\t\t\t");
            gotoxy(56,12);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);
    gotoxy(27,13);
    textcolor(YELLOW);
    printf("Enter end date (dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
        int datevalid = isValidDate(CC.ed);
        if(datevalid == 0)
        {
            gotoxy(27,18);
            textcolor(LIGHTRED);
            printf("Wrong Date");
            getch();
            gotoxy(27,18);
            printf("\t\t\t\t");
            gotoxy(54,13);
            printf("\t\t\t");
            gotoxy(54,13);
            textcolor(WHITE);
        }
        else
            break;
    }while(1);

    FILE *fp;
    fp = fopen("Customer.bin","ab+");
    if(fp == NULL)
    {
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        getch();
        gotoxy(27,18);
        printf("\t\t");
        return -1;
    }
    fwrite(&CC,sizeof(Customer_Car_Details),1,fp);
    gotoxy(27,18);
    textcolor(WHITE);
    printf("Booking Done for car %d",CC.car_id);
    printf("\nPress any key to continue...");
    getch();
    fclose(fp);
    updateCarCount(c);
    bookedCarDetails();
    return 1;

}


void availableCarDetails()
{

    FILE *fp1;
    int i;
    fp1=fopen("car.bin","rb");
    Car C;
    if(fp1==NULL)
    {
        gotoxy(32,1);
        textcolor(RED);
        printf("No file exist!First add cars!!");
        getch();
        return ;
    }
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM");
    gotoxy(1,2);
    fseek(fp1,0,SEEK_END);
    int n=ftell(fp1)/sizeof(C);
    if(n==0)
    {
        gotoxy(1,5);
        textcolor(RED);
        printf("Sorry!No Car Exist");
        getch();
        return ;
    }
    rewind(fp1);
    textcolor(LIGHTGRAY);
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(30,5);
    textcolor(YELLOW);
    printf("AVAILABLE CAR DETAILS");
    gotoxy(1,8);
    textcolor(LIGHTGRAY);
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(1,10);
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(1,9);
    int row=11;
    textcolor(YELLOW);
    textcolor(LIGHTBLUE);
    printf("CAR ID");
    gotoxy(15,9);
    printf("CAR NAME");
    gotoxy(30,9);
    printf("Capacity");
    gotoxy(45,9);
    printf("Available");
    gotoxy(60,9);
    printf("PRICE/DAY");
    textcolor(YELLOW);

    while(fread(&C,sizeof(C),1,fp1)==1)
    {
        if(C.car_count>0)
        {
            gotoxy(1,row);
            printf("%d",C.car_id);
            gotoxy(15,row);
            printf("%s",C.car_name);
            gotoxy(30,row);
            printf("%d",C.capacity);
            gotoxy(45,row);
            printf("%d",C.car_count);
            gotoxy(60,row);
            printf("%d",C.price);
            row++;
        }
    }
    fclose(fp1);
    return ;
}

void allCarDetails()
{
    FILE *fp1;
    int i;
    fp1=fopen("car.bin","rb");
    Car C;
    if(fp1==NULL)
    {
        gotoxy(32,1);
        textcolor(RED);
        printf("No file exist!First add cars!!");
        getch();
        return ;
    }
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM");
    gotoxy(1,2);
    fseek(fp1,0,SEEK_END);
    int n=ftell(fp1)/sizeof(C);
    if(n==0)
    {
        gotoxy(1,5);
        textcolor(RED);
        printf("Sorry!No Car Exist");
        getch();
        return ;
    }
    rewind(fp1);
    int row = 11;
    if(fp1 == NULL)
    {
        printf("Sorry ! NO CAR Exist");
        getch();
        return NULL;
    }
    textcolor(LIGHTGREEN);
    for(i = 1;i <= 80;i++)
        printf("%c",247);
    gotoxy(30,5);
    textcolor(YELLOW);
    printf("* ALL CAR DETAILS *");
    gotoxy(1,8);
    textcolor(LIGHTGREEN);
    for(i = 1;i <= 80;i++)
        printf("%c",247);
    gotoxy(1,10);
    for(i = 1;i <= 80;i++)
        printf("%c",247);
    gotoxy(1,9);
    textcolor(LIGHTBLUE);
    printf("CAR ID");
    gotoxy(15,9);
    printf("CAR NAME");
    gotoxy(33,9);
    printf("Capacity");
    gotoxy(50,9);
    printf("AVAILABLE");
    gotoxy(68,9);
    printf("PRICE/DAY");
    textcolor(YELLOW);
    while(fread(&C,sizeof(C),1,fp1)==1)
    {
        gotoxy(1,row);
        printf("%d",C.car_id);
        gotoxy(15,row);
        printf("%s",C.car_name);
        gotoxy(36,row);
        printf("%d",C.capacity);
        gotoxy(54,row);
        printf("%d",C.car_count);
        gotoxy(70,row);
        printf("%d",C.price);
        row++;

    }
    fclose(fp1);
    getch();
}

int returnCar()
{
    FILE *fp1;
    fp1=fopen("returncar.bin","ab");
    if(fp1==NULL)
    {
        textcolor(RED);
        printf("Sorry!can't create file");
        getch();
        return -1;
    }
    Return_Car_Details R;
    clrscr();
    Customer_Car_Details CC;
    int i;
    textcolor(RED);
    gotoxy(32,2);
    textcolor(RED);
    printf("CAR RENTAL SYSTEM");
    gotoxy(1,3);
    textcolor(YELLOW);
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(30,5);
    textcolor(GREEN);
    printf("* RETURN CAR MODEL *");
    gotoxy(1,7);
    textcolor(YELLOW);

    for(i=0;i<80;i++)
        printf("%c",247);
    FILE *fp;
    fp=fopen("customer.bin","rb");
    if(fp==NULL)
    {
        gotoxy(32,16);
        printf("Sorry! No car booked");
        getch();
        return -1;
    }
    int row=11;
    gotoxy(1,10);
    textcolor(LIGHTCYAN);
    int c=printf("ENTER CAR ID WHICH YOU WANT TO RETURN:");
    int count=0;
    textcolor(WHITE);
    scanf("%d",&R.car_id);
    while(fread(&CC,sizeof(CC),1,fp)==1)
    {
        if(CC.car_id==R.car_id)
        {
            count=1;
            break;
        }
        else
            continue;
    }
    if(count==0)
    {
        textcolor(RED);
        gotoxy(32,20);
        printf("Wrong Car Id!");
        getch();
    }
    gotoxy(1,row+1);
    textcolor(LIGHTCYAN);
    c=printf("Return Date:");
    while(1)
    {
        textcolor(WHITE);
        scanf("%d/%d/%d",&R.endDate.tm_mday,&R.endDate.tm_mon,&R.endDate.tm_year);
        int res=isValidDate(R.endDate);
        if(res==1)
            break;
        gotoxy(32,25);
        textcolor(RED);
        printf("Wrong date");
        getch();
        gotoxy(32,25);
        printf("\t\t\t\t");
        gotoxy(1+c,row+4);
        printf("\t\t\t");
        gotoxy(1+c,row+4);
        textcolor(WHITE);
    }
    rewind(fp);
    int found=0;
    while(fread(&CC,sizeof(CC),1,fp)==1)
    {
        if(R.car_id==CC.car_id)
            found=1;
        else
            found=0;
    }
    gotoxy(1,row+6);
    textcolor(GREEN);
    gotoxy(1,row+7);
    textcolor(WHITE);
    textcolor(GREEN);

    if(found==1)
    {
        fwrite(&R,sizeof(R),1,fp1);
    }
    fclose(fp);
    fclose(fp1);

return found;

}



