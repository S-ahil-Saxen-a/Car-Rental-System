#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "car.h"

int main()
{
    int i,type,k,choice,result;
    User *usr;
    textcolor(YELLOW);
    gotoxy(25,10);
    printf("WELCOME TO CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(20,13);
    printf("* RENT A CAR AND GO WHEREVER YOU NEED *");
    getch();
    addAdmin();
    while(1)
    {
        clrscr();
        textcolor(LIGHTRED);
        gotoxy(32,2);
        printf("CAR RENTAL SYSTEM");
        textcolor(YELLOW);
        gotoxy(1,8);
        for(i = 1; i <= 80; i++)
            printf("*");
        gotoxy(1,17);
        for(i = 1; i <= 80; i++)
            printf("*");
        gotoxy(32,10);
        printf("1. ADMIN");
        gotoxy(32,12);
        printf("2. EMPLOYEE");
        gotoxy(32,14);
        printf("3. QUIT");
        textcolor(WHITE);
        gotoxy(32,16);
        printf("Select Your Role :");
        do
        {
            scanf("%d",&type);
            k = 0;
            if(type == 1)
            {
                do
                {
                    usr = getInput();
                    if(usr == NULL)
                        break;
                    else
                    {
                        k = checkUserExist(*usr,"admin");
                    }
                }while(k == 0);
                if(k == -1)
                    break;
                if(k == 1)
                {
                    gotoxy(1,20);
                    textcolor(WHITE);
                    printf("Press any key to continue");
                    getch();
                    while(1)
                    {
                        clrscr();
                        choice = adminMenu();
                        if(choice == 7)
                        {
                            gotoxy(32,20);
                            clrscr();
                            break;
                        }
                        switch(choice)
                        {
                        case 1:
                            clrscr();
                            addEmployee();
                            break;
                        case 2:
                            clrscr();
                            addCarDetails();
                            break;
                        case 3:
                            clrscr();
                            viewEmployee();
                            break;
                        case 4:
                            clrscr();
                            showCarDetails();
                            break;
                        case 5:
                            clrscr();
                            result = deleteEmp();
                            gotoxy(15,14);
                            if(result == 0)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! No emp found for given emp id");
                            }
                            else if(result == 1)
                            {
                                textcolor(LIGHTGREEN);
                                printf("Record deleted successfully!");
                            }
                            else if(result == 2)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! Error in deletion. Try again!");
                            }
                            textcolor(WHITE);
                            printf("\n\nPress any key to go back to the main screen!");
                            getch();
                            break;
                        case 6:
                            clrscr();
                            result = deleteCarModel();
                            gotoxy(15,14);
                            if(result == 0)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! No Car found for given car id");
                            }
                            else if(result == 1)
                            {
                                textcolor(LIGHTGREEN);
                                printf("Record deleted successfully!");
                            }
                            else if(result == 2)
                            {
                                textcolor(LIGHTRED);
                                printf("Sorry! Error in deletion. Try again!");
                            }
                            textcolor(WHITE);
                            printf("\n\nPress any key to go back to the main screen!");
                            getch();
                            break;
                        default:
                            gotoxy(15,19);
                            textcolor(LIGHTRED);
                            printf("Incorrect Choice!");
                            getch();
                            gotoxy(15,19);
                            printf("\t\t\t\t\t\t");
                            gotoxy(15,14);
                            printf("\t\t\t\t\t");
                            break;
                        }
                    }
                }
            }
            else if(type == 2)
            {
                do
                {
                    usr = getInput();
                    if(usr == NULL)
                        break;
                    else
                        k = checkUserExist(*usr,"emp");
                }while(k == 0);
                if(k == -1)
                    break;
                if(k == 1)
                {
                    gotoxy(1,20);
                    textcolor(WHITE);
                    printf("Press any key to continue");
                    getch();
                    while(1)
                    {
                        clrscr();
                        choice = empMenu();
                        if(choice == 6)
                        {
                            gotoxy(32,20);
                            clrscr();
                            break;
                        }
                        switch(choice)
                        {
                        case 1:
                            clrscr();
                            int rentresp;
                            rentresp = rentCar();
                            if(rentresp == -2)
                            {
                                gotoxy(35,9);
                                textcolor(LIGHTRED);
                                printf("Sorry! All cars booked. Try again later");
                                getch();
                            }
                            else if(rentresp == 0)
                            {
                                gotoxy(27,18);
                                textcolor(LIGHTRED);
                                printf("You did not choose any car");
                                getch();
                            }
                            break;
                        case 2:
                            clrscr();
                            bookedCarDetails();
                            getch();
                            break;
                        case 3:
                            clrscr();
                            availableCarDetails();
                            getch();
                            break;
                        case 4:
                            clrscr();
                            allCarDetails();
                            getch();
                            break;
                        case 5:
                            k = returnCar();

                            if(k == 1)
                            {
                                textcolor(GREEN);
                                gotoxy(32,23);
                                printf("Car Return Successfully");
                                getch();
                            }
                            else if(k == 0)
                            {
                                gotoxy(32,23);
                                textcolor(RED);
                                printf("Invalid Car Id... Please Try Later...");
                                getch();
                            }
                            break;
                        default:
                            gotoxy(32,20);
                            textcolor(LIGHTRED);
                            printf("Incorrect choice");
                            getch();
                            break;
                        }
                    }
                }

            }
            else if (type == 3)
            {
                clrscr();
                textcolor(GREEN);
                gotoxy(30,12);
                printf("Thank you for using the app ");
                getch();
                exit(0);
            }
            else
            {
                textcolor(RED);
                gotoxy(30,20);
                printf("Invalid Choice");
                getch();
                gotoxy(30,20);
                printf("\t\t\t");
                gotoxy(50,16);
                printf("\t\t\t");
                textcolor(WHITE);
                gotoxy(50,16);
            }
            break;
        }while(1);
    }

    return 0;
}
