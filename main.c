//Bruno Portilla Hinojosa
//ITESM A01411232
//This program is a system to sell tickets for the concert to fund Mr. G. This concert has a variety of zones, and payment methods. The theather has 400 rows and 200 seat numbers each row.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//This void shows the menu to the user
void MainMenu(){
    printf("WELCOME TO THE MR. G CONCERT TICKET SYSTEM!.\nWhat do you want to do?\n1.- Buy a Ticket.\n2.- Save sells data.\n3.- View reports.\nEnter 0 to exit.\n");
}

// Showa thw report section menu.
void MenuRep(){
    printf("Report Sections\nWhat do you want to do?\n1.- View total tickets sold.\n2.- View total tickets sold per zone.\n3.- View total income.\n4.- View total income per zone.\n5.- View occupation rate.\n6.- View occupation rate per zone.\n");
}
// Shows the Zones.
void zones(){
    printf("Zones:\n1.- VIP: $100\n2.- Platinum: $85\n3.- Gold: $70\n4.- Silver: $55\n5.- Green: $45\n6.- Yellow: $40\n7.- Red: $30\n8.- Sky Blue: $50\n9.- Navy Blue: $35\n10.- Deep Blue: $20\n");
}

struct seats{
    char name[30];      //This struct saves all the preferences and the name of the client.
    int ticket;
    bool seat;
    int payment;

}
        seats[400][200];
void oFile(FILE *fp) {
    fp = fopen("MrG.txt", "wb"); //creates or opens the file

    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 200; j++) {
            strcpy(seats[i][j].name, "");
            seats[i][j].payment = 0;
            seats[i][j].seat = false;

            if (j < 50 || j > 149) {
                if (i < 100) {                  //checks the price based on the zone
                    seats[i][j].ticket = 50;
                } else if (i < 300) {
                    seats[i][j].ticket = 35;
                } else {
                    seats[i][j].ticket = 20;
                }

            } else {

                if (i < 5) {
                    seats[i][j].ticket = 100;
                } else if (i < 10) {
                    seats[i][j].ticket = 85;
                } else if (i < 50) {
                    seats[i][j].ticket = 70;
                } else if (i < 100) {
                    seats[i][j].ticket = 55;
                } else if (i < 250) {
                    seats[i][j].ticket = 45;
                } else if (i < 350) {
                    seats[i][j].ticket = 40;
                } else {
                    seats[i][j].ticket = 30;
                }
            }
        }
    }

    fwrite(&seats, sizeof(seats), 1, fp); //storing in the file
}
void buy() {
    char name[30];
    char option;
    int row;
    int first;
    int last;
    int seatnum;
    int payment_meth;
    zones();
    printf("What zone do you want?\n");
    scanf("%d", &option);

    switch (option) {
        case 1:
            first = 1;
            last = 5;
            break;
        case 2:
            first = 6;
            last = 10;
            break;

        case 3:
            first = 11;
            last = 50;
            break;

        case 4:
            first = 51;
            last = 100;
            break;

        case 5:
            first = 101;
            last = 250;
            break;

        case 6:
            first = 251;
            last = 350;
            break;

        case 7:
            first = 351;
            last = 400;
            break;

        case 8:
            first = 1;
            last = 100;
            break;

        case 9:
            first = 101;
            last = 300;
            break;

        case 10:
            first = 301;
            last = 400;
            break;

        default:
            printf("Going back.\n");
            return;

    }



    do {
        printf("Choose a row between %d-%d:", first, last);
        scanf("%d", &row);
    } while (row < first || row > last);

    if (option > 7) {
        do {
            printf("Choose a seat number between 1-50 or 151-200:");
            scanf("%d", &seatnum);
        } while ((seatnum < 1 || seatnum > 50) && (seatnum < 151 || seatnum > 200));

    } else {
        do {
            printf("Choose a seat number between 51-150:");
            scanf("%d", &seatnum);
        } while (seatnum < 51 || seatnum > 150);
    }



    // Shows what are the options to pay the ticket
    printf("Select your Payment Method:\n1. Visa\n2. MasterCard\n3. American Express\n");

    scanf("%d", &payment_meth);

    if (payment_meth < 1 || payment_meth > 3) {
        printf("Going back.\n");
        return;
    }

    printf("Enter your name:");
    fflush(stdin);
    fgets(name, sizeof(name), stdin);

    printf("Enter 0 to accept. Enter other value to cancel,\n");
    scanf("%c", &option);

    if (!option) {
        if (seats[row - 1][seatnum - 1].seat) {
            printf("Sorry this seat is taken.\n");
        } else {
            seats[row - 1][seatnum - 1].seat = true;
            seats[row - 1][seatnum - 1].payment = payment_meth;
            strcpy(seats[row - 1][seatnum - 1].name, name);
            printf("Congrats, purchase completed.\n");
        }


    } else{
        printf("Going back.");
    }
}


int income(int first, int last, int firstseat, int lastseat, int reserved) {
    int count = 0;
    int sales = 0;
    for (int i = first - 1; i < last; i++) {
        for (int j = firstseat - 1; j < lastseat; j++) {
            if (seats[i][j].seat) {
                count++;
                sales += seats[i][j].ticket;
            }
        }
    }
    if (reserved) {
        return count;
    }
    return sales;
}

int ZoneFull(int zone, int reserved) {
    int count = 0;
    int first;
    int last;
    switch (zone) {
        case 1:
            first = 1;
            last = 5;
            break;

        case 2:
            first = 6;
            last = 10;
            break;

        case 3:
            first = 11;
            last = 50;
            break;

        case 4:
            first = 51;
            last = 100;
            break;

        case 5:
            first = 101;
           last = 250;
            break;

        case 6:
            first = 251;
            last = 350;
            break;

        case 7:
            first = 351;
            last = 400;
            break;

        case 8:
            first = 1;
           last = 100;
            break;

        case 9:
            first = 101;
            last = 300;
            break;

        case 10:
            first = 301;
            last = 400;
            break;

        default:
            first = 1;
            last = 200;
            break;
    }
    if (zone > 7) {
        count += income(first, last, 1, 50, reserved);
        count += income(first, last, 151, 200, reserved);

    } else {
        count += income(first, last, 51, 150, reserved);
    }
    return count;
}
void Reports() {
    int option;
    int zone = 0;
    int count = 0;
    float rowsize;

    MenuRep();

    printf("Enter any other number to return:\n");

    scanf("%d", &option);

    switch (option) {
        case 1:
            count = ZoneFull(zone, 1);
            printf("Te number of tickets solg is %d", count);
            break;

       case 2:
           do {
                zones();
                printf("Enter a zone:");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);

            count = ZoneFull(zone, 1);
            printf("The number of tickets sold in this zone is %d", count);
            break;

        case 3:
            count = ZoneFull(zone, 0);
            printf("The total income is $%d", count);
            break;

        case 4:
            do {
                zones();
                printf("Enter a zone:\n");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);

            count = ZoneFull(zone, 0);
            printf("The total income in this zone is $%d", count);
            break;

        case 5:
            count = ZoneFull(zone, 1);
            printf("The occupation rate is %f%%", count * 100.0 / 80000);
            break;

        case 6:
            do {
                zones();
                printf("What zone do you want?");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);
            count = ZoneFull(zone, 1);

           switch (zone) {

                case 1:

                case 2:
                    rowsize = 5;
                    break;              //doing because of the changing sizes of the zones

                case 3:
                    rowsize = 40;
                    break;

                case 4:

                case 6:

                case 7:
                    rowsize = 50;
                    break;

                case 8:

                case 10:
                    rowsize = 100;
                    break;

                case 5:
                    rowsize = 150;
                    break;

                case 9:
                default:
                    rowsize = 200;
                   break;
            }
            printf("Occupation rate in this zone: %f%%", count / rowsize);
            break;
        default:
            printf("Back");
            return;
    }

}

void wFile(FILE *fp) {
    fp = fopen("MrG.txt", "wb");
    fwrite(&seats, sizeof(seats), 1, fp);
    fclose(fp);
}

int main() {

    FILE *fp;
    int option;

    fp = fopen("mrg.txt", "rb");

    if (fp == NULL) {
        oFile(fp);
    } else {
        while (fread(&seats, sizeof(seats), 1, fp));
    }

    fclose(fp); //Closes the file


    do {
        MainMenu();
        scanf("%d", &option);
        fflush(stdin);

        switch (option) {
            case 1:
                buy();
                break;
            case 2:
                wFile(fp);
                printf("Data saved.\n");
                break;
            case 3:
                Reports();
                break;
            case 0:
                wFile(fp);
                printf("\nGoodbye!\n");
                break;
            default:
                printf("\ninvalid. Try again.\n");
                break;
        }

    } while (option != '0');
    return 0;

}