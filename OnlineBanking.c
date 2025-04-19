#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char phone[50];
    char account_number[50];
    char password[50];
    float balance;
};

int main() {
    struct user usr, usr1;
    FILE *fp;
    char filename[50], phone[50], pword[50];
    int user_choice, account_choice;
    char cont = 'y';
    float amount;

    printf("\nWhat do you want to do?");
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d", &user_choice);

    if (user_choice == 1) {
        // Register
        printf("Enter your account number:\t");
        scanf("%s", usr.account_number);
        printf("Enter your phone number:\t");
        scanf("%s", usr.phone);
        printf("Enter your new password:\t");
        scanf("%s", usr.password);
        usr.balance = 0;

        strcpy(filename, usr.phone);
        strcat(filename, ".dat");
        fp = fopen(filename, "w");

        if (fp == NULL) {
            printf("\n\nError creating file!");
        } else {
            if (fwrite(&usr, sizeof(struct user), 1, fp)) {
                printf("\n\nAccount successfully registered!");
            } else {
                printf("\n\nSomething went wrong. Please try again!");
            }
            fclose(fp);
        }
    }

    else if (user_choice == 2) {
        // Login
        printf("\nPhone number:\t");
        scanf("%s", phone);
        printf("Password:\t");
        scanf("%s", pword);

        strcpy(filename, phone);
        strcat(filename, ".dat");
        fp = fopen(filename, "r");

        if (fp == NULL) {
            printf("\nAccount not registered.");
        } else {
            fread(&usr, sizeof(struct user), 1, fp);
            fclose(fp);

            if (strcmp(pword, usr.password) == 0) {
                printf("\n\t\tWelcome %s", usr.phone);

                while (cont == 'y' || cont == 'Y') {
                    printf("\n\nPress 1 for balance inquiry");
                    printf("\nPress 2 for depositing cash");
                    printf("\nPress 3 for cash withdrawal");
                    printf("\nPress 4 for online transfer");
                    printf("\nPress 5 for password change");
                    printf("\n\nYour choice:\t");
                    scanf("%d", &account_choice);

                    switch (account_choice) {
                        case 1:
                            printf("\nYour current balance is Rs.%.2f", usr.balance);
                            break;

                        case 2:
                            printf("\nEnter the amount:\t");
                            scanf("%f", &amount);
                            usr.balance += amount;

                            fp = fopen(filename, "w");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            fclose(fp);
                            printf("\nSuccessfully deposited.");
                            break;

                        case 3:
                            printf("\nEnter the amount:\t");
                            scanf("%f", &amount);

                            if (amount > usr.balance) {
                                printf("\nInsufficient balance.");
                            } else {
                                usr.balance -= amount;
                                fp = fopen(filename, "w");
                                fwrite(&usr, sizeof(struct user), 1, fp);
                                fclose(fp);
                                printf("\nYou have withdrawn Rs.%.2f", amount);
                            }
                            break;

                        case 4:
                            printf("\nEnter recipient's phone number:\t");
                            scanf("%s", phone);
                            printf("Enter amount to transfer:\t");
                            scanf("%f", &amount);

                            if (amount > usr.balance) {
                                printf("\nInsufficient balance.");
                                break;
                            }

                            char target_file[50];
                            strcpy(target_file, phone);
                            strcat(target_file, ".dat");
                            fp = fopen(target_file, "r");

                            if (fp == NULL) {
                                printf("\nRecipient account not found.");
                            } else {
                                fread(&usr1, sizeof(struct user), 1, fp);
                                fclose(fp);

                                usr1.balance += amount;

                                fp = fopen(target_file, "w");
                                fwrite(&usr1, sizeof(struct user), 1, fp);
                                fclose(fp);

                                usr.balance -= amount;
                                fp = fopen(filename, "w");
                                fwrite(&usr, sizeof(struct user), 1, fp);
                                fclose(fp);

                                printf("\nTransferred Rs.%.2f to %s", amount, phone);
                            }
                            break;

                        case 5:
                            printf("\nEnter new password:\t");
                            scanf("%s", pword);
                            strcpy(usr.password, pword);

                            fp = fopen(filename, "w");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            fclose(fp);
                            printf("\nPassword successfully changed.");
                            break;

                        default:
                            printf("\nInvalid option.");
                            break;
                    }

                    printf("\n\nDo you want to continue the transaction? [y/n]: ");
                    scanf(" %c", &cont); // note the space before %c to consume leftover newline
                }

            } else {
                printf("\nInvalid password.");
            }
        }
    }

    else {
        printf("\nInvalid selection. Please choose 1 or 2.");
    }

    return 0;
}
