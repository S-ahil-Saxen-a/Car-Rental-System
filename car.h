#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <time.h>

//                          STRUCTURES DECLARATIONS
//                       -----------------------------
struct User
{
    char userid[20];   // For storing -> User id
    char pwd[20];      //                User password
    char name[20];     //                User name
};

struct Car
{
    int car_id;           // For storing ->  car id
    char car_name[50];    //                 car name
    int capacity;         //                 capacity of car
    int car_count;        //                 no. of cars
    int price;            //                 rental price

};

struct Customer_Car_Details
{
    int car_id;             // For storing ->  car id
    char cust_name[30];     //
    char pick[30];          //                 pickup location
    char drop[30];          //                 drop location
    struct tm sd;           //                 starting date
    struct tm ed;           //                 ending date
};

struct Return_Car_Details
{
    int car_id;
    struct tm ed;
    char cust_name[30];
    struct tm sd;
    struct tm endDate;
    char car_name[30];
};

// *********** Typedef of Structures ***********

typedef struct User User;
typedef struct Car Car;
typedef struct Customer_Car_Details Customer_Car_Details;
typedef struct Return_Car_Details Return_Car_Details;

//                         FUNCTIONS DECLARATIONS
//                      ----------------------------

void addAdmin(); // For inserting admin’s data in the file

User* getInput(); // For accepting userid and password from user, storing it in a struct User variable and returning it's address

int checkUserExist(User , char *); // For validating userid and password which is inputted by user.It will accept a struct User variable and a string indicating usertype as argument. It will return 1 or 0 based upon whether the validation was successful or not

int adminMenu(); // For displaying admin menu options and returning the option selected by the user

void addEmployee();  // For inserting employee details in file

void viewEmployee();  // For displaying record of all employees

void addCarDetails();  // For inserting cars record in the file

void showCarDetails(); // For displaying record of all cars

int deleteEmp();  // For removing details of the employee from file and returning 1 or 0 to indicate whether deletion was successful or not

int deleteCarModel(); // For removing record of the car from file and returning 1 or 0 to indicate whether deletion was successful or not

int empMenu();

int selectCarModel();

int rentCar();

int isValidDate(struct tm);

void updateCarCount(int);

void bookedCarDetails();

char *getCarName(int);

void availableCarDetails();

void allCarDetails();

int returnCar();


#endif // CAR_H_INCLUDED
