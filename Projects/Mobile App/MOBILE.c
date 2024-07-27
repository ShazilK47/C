#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define MAX_PASSWORD_LENGTH 20
#define MAX_PHONE_NUMBER_LENGTH 15
#define MAX_MESSAGE_LENGTH 100
#define MAX_CONTACTS 200

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

struct Contact
{
    char name[20];
    char pn[15];
    char email[40];
};

struct Contact contacts[MAX_CONTACTS];
int numContacts = 0;

//******************************Startup and Password **********************************

void displayStartup()
{
    system(CLEAR_SCREEN);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tWelcome to C Based Mobile Phone!\n");
    printf("\t\t\t\t\t\t\t\t\tOS is opening...\n");
    sleep(2);
}

int getPassword(char *password)
{
    system(CLEAR_SCREEN);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tEnter your password: ");
    scanf("%s", password);
    return 1;
}

// ***************************** STARTUP MENU *********************************************

void displayMenu()
{
    system(CLEAR_SCREEN);
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t====== Mobile Phone Menu ======\n");
    printf("\t\t\t\t\t\t\t\t\t1. Call\n");
    printf("\t\t\t\t\t\t\t\t\t2. Send Message\n");
    printf("\t\t\t\t\t\t\t\t\t3. Contacts\n");
    printf("\t\t\t\t\t\t\t\t\t4. Settings\n");
    printf("\t\t\t\t\t\t\t\t\t5. Exit\n");
    printf("\t\t\t\t\t\t\t\t\t==============================\n");
    printf("\t\t\t\t\t\t\t\t\tEnter your choice: ");
}

// ************************************* CALL ********************************************

void makeCall()
{
    char phoneNumber[MAX_PHONE_NUMBER_LENGTH];
    printf("Enter the phone number to call: ");
    scanf("%s", phoneNumber);
    printf("Dialing %s...\n", phoneNumber);
    sleep(3);
    printf("Call ended.\n");
}

// ************************************ MESSAGE ******************************************
void sendMessage()
{
    char recipient[MAX_PHONE_NUMBER_LENGTH];
    char message[MAX_MESSAGE_LENGTH];
    printf("Enter the recipient's phone number: ");
    scanf("%s", recipient);
    printf("Enter the message: ");
    getchar();
    fgets(message, MAX_MESSAGE_LENGTH, stdin);
    printf("Sending message to %s: %s\n", recipient, message);
}

// ********************************** CONTACTS ***************************************
void addContact()
{
    if (numContacts >= MAX_CONTACTS)
    {
        printf("Contact list is full. Cannot add more contacts.\n");
        return;
    }

    struct Contact newContact;

    printf("Enter name: ");
    scanf("%s", newContact.name);
    printf("Enter phone number: ");
    scanf("%s", newContact.pn);
    printf("Enter email address: ");
    scanf("%s", newContact.email);

    contacts[numContacts] = newContact;
    numContacts++;

    printf("Contact added successfully.\n");
}

void displayContacts()
{
    if (numContacts == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    system(CLEAR_SCREEN);
    printf("\n\n\tContact List:\n");
    printf("\t**************\n\n");
    for (int i = 0; i < numContacts; i++)
    {
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].pn);
        printf("Email: %s\n", contacts[i].email);
        printf("-------------------\n");
    }
}

void searchContact()
{
    char searchName[20];
    printf("Enter the name to search: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < numContacts; i++)
    {
        if (strcmp(contacts[i].name, searchName) == 0)
        {
            system(CLEAR_SCREEN);
            printf("Contact found:\n");
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].pn);
            printf("Email: %s\n", contacts[i].email);
            printf("-------------------\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        system(CLEAR_SCREEN);
        printf("Contact not found.\n");
    }
}

void deleteContact()
{
    char deleteName[20];
    printf("Enter the name to delete: ");
    scanf("%s", deleteName);

    int found = 0;
    for (int i = 0; i < numContacts; i++)
    {
        if (strcmp(contacts[i].name, deleteName) == 0)
        {
            for (int j = i; j < numContacts - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }
            numContacts--;
            printf("Contact deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nContact not found.\n");
    }
}

void editContact()
{
    char editName[20];
    printf("Enter the name to edit: ");
    scanf("%s", editName);

    int found = 0;
    for (int i = 0; i < numContacts; i++)
    {
        if (strcmp(contacts[i].name, editName) == 0)
        {
            printf("Enter new phone number: ");
            scanf("%s", contacts[i].pn);
            printf("Enter new email address: ");
            scanf("%s", contacts[i].email);
            printf("Contact edited successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nContact not found.\n");
    }
}
//******************************************************GAME TIC TAC TOC *********************************************

void printBoard(char board[]);
int checkWin(char board[], char mark);
int checkDraw(char board[]);

void playTicTacToe()
{
    char board[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char charmark;
    int input;
    int player1 = 1, player2 = 0;
    int currentPlayer = player1;

    for (int turn = 1; turn <= 9; ++turn)
    {
        system(CLEAR_SCREEN);
        printBoard(board);

        printf("Player %d, enter a number: ", currentPlayer);
        scanf("%d", &input);

        if (input < 1 || input > 9 || board[input] == 'x' || board[input] == 'o')
        {
            printf("Invalid input. Try again.\n");
            --turn;
            continue;
        }

        charmark = (currentPlayer == player1) ? 'x' : 'o';
        board[input] = charmark;

        if (checkWin(board, charmark))
        {
            printBoard(board);
            printf("Player %d wins!\n", currentPlayer);
            break;
        }
        else if (checkDraw(board))
        {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }
}

void printBoard(char board[])
{
    printf("\n\n");
    printf("\t\tTIC TAC TOE\n");
    printf("\n\n");
    printf("\t\t %c | %c | %c \n", board[1], board[2], board[3]);
    printf("\t\t___|___|___\n");
    printf("\t\t %c | %c | %c \n", board[4], board[5], board[6]);
    printf("\t\t___|___|___\n");
    printf("\t\t %c | %c | %c \n", board[7], board[8], board[9]);
    printf("\t\t   |   |   \n");
}

int checkWin(char board[], char mark)
{
    return ((board[1] == mark && board[2] == mark && board[3] == mark) ||
            (board[4] == mark && board[5] == mark && board[6] == mark) ||
            (board[7] == mark && board[8] == mark && board[9] == mark) ||
            (board[1] == mark && board[4] == mark && board[7] == mark) ||
            (board[2] == mark && board[5] == mark && board[8] == mark) ||
            (board[3] == mark && board[6] == mark && board[9] == mark) ||
            (board[1] == mark && board[5] == mark && board[9] == mark) ||
            (board[3] == mark && board[5] == mark && board[7] == mark));
}

int checkDraw(char board[])
{
    for (int i = 1; i <= 9; ++i)
    {
        if (board[i] != 'x' && board[i] != 'o')
        {
            return 0;
        }
    }
    return 1;
}
//************************************ CALENDER *******************************************

int getFirstWeekday(int year)
{
    return (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year) / 400) + 1) % 7;
}

int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

void printCalendar(int year)
{

    int month, day, daysInMonth, weekDay = 0, startingDay;

    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(year))
        monthDays[1] = 29;

    startingDay = getFirstWeekday(year);

    for (month = 0; month < 12; month++)
    {
        daysInMonth = monthDays[month];
        printf("\n---------------%s-------------------\n", months[month]);
        printf("\n  Sun  Mon  Tue  Wed  Thurs  Fri  Sat\n");

        for (weekDay = 0; weekDay < startingDay; weekDay++)
            printf("     ");

        for (day = 1; day <= daysInMonth; day++)
        {
            printf("%5d", day);

            if (++weekDay > 6)
            {
                printf("\n");
                weekDay = 0;
            }
            startingDay = weekDay;
        }
    }
}

// ***************************************** CALCULATOR **********************************************

int factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

//**************************************************************** MAIN FUNCTION ************************************************************
int main()
{
    int option;
    char password[MAX_PASSWORD_LENGTH];
    char userPassword[MAX_PASSWORD_LENGTH] = "1234";
    int choose;
    double num1, num2, result;
    displayStartup();

    if (getPassword(password) && strcmp(password, userPassword) == 0)
    {
        printf("\t\t\t\t\t\t\t\t\tPassword accepted. Welcome!\n");
        system(CLEAR_SCREEN);

        do
        {

            printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t====== Mobile Phone Menu ======\n");
            printf("\t\t\t\t\t\t\t\t\t1. Call\n");
            printf("\t\t\t\t\t\t\t\t\t2. Send Message\n");
            printf("\t\t\t\t\t\t\t\t\t3. Contacts\n");
            printf("\t\t\t\t\t\t\t\t\t4. Play Tic Tac Toe\n");
            printf("\t\t\t\t\t\t\t\t\t5. Display Calendar\n");
            printf("\t\t\t\t\t\t\t\t\t6. Calculator\n");
            printf("\t\t\t\t\t\t\t\t\t7. Settings\n");
            printf("\t\t\t\t\t\t\t\t\t8. Powerd OFF\n");
            printf("\t\t\t\t\t\t\t\t\t==============================\n");
            printf("\t\t\t\t\t\t\t\t\tEnter your choice: ");
            scanf("%d", &option);
            system(CLEAR_SCREEN);

            switch (option)
            {
            case 1:
                makeCall();
                break;
            case 2:
                sendMessage();
                break;
            case 3:
                while (1)
                {

                    printf("\n\nContact Management System\n");
                    printf("1. Add Contact\n");
                    printf("2. Display Contacts\n");
                    printf("3. Search Contact\n");
                    printf("4. Delete Contact\n");
                    printf("5. Edit Contact\n");
                    printf("6. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &option);

                    switch (option)
                    {
                    case 1:
                        addContact();
                        break;
                    case 2:
                        displayContacts();
                        break;
                    case 3:
                        searchContact();
                        break;
                    case 4:
                        deleteContact();
                        break;
                    case 5:
                        editContact();
                        break;
                    case 6:
                        system(CLEAR_SCREEN);
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                    }

                    if (option == 6)
                        break;
                }
                break;
            case 4:
                playTicTacToe();
                break;
            case 5:
            {
                int year;
                printf("Enter the desired year: ");
                scanf("%d", &year);
                system(CLEAR_SCREEN);
                printCalendar(year);
            }
            break;
            case 6:
                // ********************************************* code for calculator ********************************************************

                do
                {

                    printf("\nAdvanced Calculator Menu:\n");
                    printf("1. Addition\n");
                    printf("2. Subtraction\n");
                    printf("3. Multiplication\n");
                    printf("4. Division\n");
                    printf("5. Square Root\n");
                    printf("6. Power\n");
                    printf("7. Factorial\n");
                    printf("0. Return to Main Menu\n");

                    printf("Enter your choice: ");
                    scanf("%d", &choose);

                    switch (choose)
                    {
                    case 1:
                        printf("Enter 1st number: ");
                        scanf("%lf", &num1);
                        printf("Enter 2nd number: ");
                        scanf("%lf", &num2);
                        result = num1 + num2;
                        printf("Result: %.2f\n", result);
                        break;
                    case 2:
                        printf("Enter 1st number: ");
                        scanf("%lf", &num1);
                        printf("Enter 2nd number: ");
                        scanf("%lf", &num2);
                        result = num1 - num2;
                        printf("Result: %.2f\n", result);
                        break;
                    case 3:
                        printf("Enter 1st number: ");
                        scanf("%lf", &num1);
                        printf("Enter 2nd number: ");
                        scanf("%lf", &num2);
                        result = num1 * num2;
                        printf("Result: %.2f\n", result);
                        break;
                    case 4:
                        printf("Enter 1st number: ");
                        scanf("%lf", &num1);
                        printf("Enter 2nd number: ");
                        scanf("%lf", &num2);
                        scanf("%lf %lf", &num1, &num2);
                        if (num2 != 0)
                        {
                            result = num1 / num2;
                            printf("Result: %.2f\n", result);
                        }
                        else
                        {
                            printf("Error: Division by zero!\n");
                        }
                        break;
                    case 5:
                        printf("Enter a number: ");
                        scanf("%lf", &num1);
                        if (num1 >= 0)
                        {
                            result = sqrt(num1);
                            printf("Result: %.2f\n", result);
                        }
                        else
                        {
                            printf("Error: Square root of a negative number is undefined!\n");
                        }
                        break;
                    case 6:
                        printf("Enter base and exponent: ");
                        scanf("%lf %lf", &num1, &num2);
                        result = pow(num1, num2);
                        printf("Result: %.2f\n", result);
                        break;
                    case 7:
                        printf("Enter a number: ");
                        scanf("%lf", &num1);
                        if (num1 >= 0 && (int)num1 == num1)
                        {
                            result = factorial((int)num1);
                            printf("Result: %.0f\n", result);
                        }
                        else
                        {
                            printf("Error: Factorial is defined only for non-negative integers!\n");
                        }
                        break;
                    case 0:
                        system(CLEAR_SCREEN);
                        break;
                    default:
                        printf("Invalid choice! Please enter a valid option.\n");
                        break;
                    }

                } while (choose != 0);

                // ******************************************************************************************************************
                break;
            case 7:
                printf("Adjusting settings...\n");
                break;
            case 8:
                printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tPowerd Off...\n\n\n\n\n\n\n\n\n\n\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        } while (option != 7);
    }
    else
    {
        printf("Invalid password. Exiting...\n");
    }

    return 0;
}