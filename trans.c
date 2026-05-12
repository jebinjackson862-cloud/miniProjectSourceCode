// ===============================================
//        FULL BANKING MANAGEMENT SYSTEM IN C
// ===============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
    int accNo;
    char name[30];
    char type[20];
    float balance;
};

void createAccount();
void displayAccounts();
void searchAccount();
void depositMoney();
void withdrawMoney();
void updateAccount();
void deleteAccount();

FILE *fp;

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================");
        printf("\n      BANKING MANAGEMENT SYSTEM");
        printf("\n====================================");

        printf("\n1. Create New Account");
        printf("\n2. Display All Accounts");
        printf("\n3. Search Account");
        printf("\n4. Deposit Money");
        printf("\n5. Withdraw Money");
        printf("\n6. Update Account");
        printf("\n7. Delete Account");
        printf("\n8. Exit");

        printf("\n\nEnter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            displayAccounts();
            break;

        case 3:
            searchAccount();
            break;

        case 4:
            depositMoney();
            break;

        case 5:
            withdrawMoney();
            break;

        case 6:
            updateAccount();
            break;

        case 7:
            deleteAccount();
            break;

        case 8:
            printf("\nThank You for using Banking System\n");
            exit(0);

        default:
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

// ===============================================
// CREATE ACCOUNT
// ===============================================

void createAccount()
{
    struct Account acc;

    fp = fopen("bank.dat", "ab");

    if (fp == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\nEnter Account Number : ");
    scanf("%d", &acc.accNo);

    printf("Enter Customer Name : ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Account Type (Saving/Current) : ");
    scanf("%s", acc.type);

    printf("Enter Initial Balance : ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);

    fclose(fp);

    printf("\nAccount Created Successfully!\n");
}

// ===============================================
// DISPLAY ALL ACCOUNTS
// ===============================================

void displayAccounts()
{
    struct Account acc;

    fp = fopen("bank.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n====================================================");
    printf("\nAccNo\tName\t\tType\t\tBalance");
    printf("\n====================================================\n");

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        printf("%d\t%s\t\t%s\t\t%.2f\n",
               acc.accNo,
               acc.name,
               acc.type,
               acc.balance);
    }

    fclose(fp);
}

// ===============================================
// SEARCH ACCOUNT
// ===============================================

void searchAccount()
{
    struct Account acc;
    int accNo, found = 0;

    fp = fopen("bank.dat", "rb");

    if (fp == NULL)
    {
        printf("\nFile not found!\n");
        return;
    }

    printf("\nEnter Account Number to Search : ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            printf("\nAccount Found!");
            printf("\n---------------------------");
            printf("\nAccount Number : %d", acc.accNo);
            printf("\nName           : %s", acc.name);
            printf("\nType           : %s", acc.type);
            printf("\nBalance        : %.2f", acc.balance);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nAccount Not Found!\n");
    }

    fclose(fp);
}

// ===============================================
// DEPOSIT MONEY
// ===============================================

void depositMoney()
{
    struct Account acc;
    int accNo, found = 0;
    float amount;

    fp = fopen("bank.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nFile not found!\n");
        return;
    }

    printf("\nEnter Account Number : ");
    scanf("%d", &accNo);

    printf("Enter Deposit Amount : ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("\nAmount Deposited Successfully!");
            printf("\nUpdated Balance : %.2f\n", acc.balance);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nAccount Not Found!\n");
    }

    fclose(fp);
}

// ===============================================
// WITHDRAW MONEY
// ===============================================

void withdrawMoney()
{
    struct Account acc;
    int accNo, found = 0;
    float amount;

    fp = fopen("bank.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nFile not found!\n");
        return;
    }

    printf("\nEnter Account Number : ");
    scanf("%d", &accNo);

    printf("Enter Withdrawal Amount : ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            if (amount > acc.balance)
            {
                printf("\nInsufficient Balance!\n");
            }
            else
            {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("\nPlease collect cash.");
                printf("\nRemaining Balance : %.2f\n", acc.balance);
            }

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nAccount Not Found!\n");
    }

    fclose(fp);
}

// ===============================================
// UPDATE ACCOUNT
// ===============================================

void updateAccount()
{
    struct Account acc;
    int accNo, found = 0;

    fp = fopen("bank.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nFile not found!\n");
        return;
    }

    printf("\nEnter Account Number to Update : ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            printf("\nEnter New Name : ");
            scanf(" %[^\n]", acc.name);

            printf("Enter New Account Type : ");
            scanf("%s", acc.type);

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("\nAccount Updated Successfully!");

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nAccount Not Found!\n");
    }

    fclose(fp);
}

// ===============================================
// DELETE ACCOUNT
// ===============================================

void deleteAccount()
{
    struct Account acc;
    FILE *temp;

    int accNo, found = 0;

    fp = fopen("bank.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("\nFile Error!\n");
        return;
    }

    printf("\nEnter Account Number to Delete : ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accNo == accNo)
        {
            found = 1;
        }
        else
        {
            fwrite(&acc, sizeof(acc), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (found)
    {
        printf("\nAccount Deleted Successfully!\n");
    }
    else
    {
        printf("\nAccount Not Found!\n");
    }
}
