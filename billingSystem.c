#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int file,elementSize,total;

struct date{
    int month;
    int day;
    int year;
};

struct account {
    int number;
    char name[100];
    int accountNo;
    float mobile_no;
    char street[100];
    char city[100];
    char accountType;
    float oldBalance;
    float newBalance;
    float payment;
    struct date paymentAtLast;
}customer;
void input()
{
    FILE *fp=fopen("customer.dat","rb");
    fseek (fp,0,SEEK_END);
    file = ftell(fp);
    elementSize = sizeof(customer);
    total = file / elementSize;
    fseek(fp, (total - 1) * elementSize, SEEK_SET);
    fread(&customer,sizeof(customer),1,fp);
    printf("\nCustomer no:%d\n",++customer.number);
    fclose(fp);
    printf("         Account number:");
    scanf("%d",&customer.accountNo);
    printf("\n       Name:");
    scanf("%s",customer.name);
    printf("\n       Mobile no:");
    scanf("%f",&customer.mobile_no);
    printf("         Street:");
    scanf("%s",customer.street);
    printf("         City:");
    scanf("%s",customer.city);
    printf("         Previous balance:");
    scanf("%f",&customer.oldBalance);
    printf("         Current payment:");
    scanf("%f",&customer.payment);
    printf("         Payment date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &customer.paymentAtLast.month, &customer.paymentAtLast.day, &customer.paymentAtLast.year);
    return;
}

void writefile()
{
    FILE *fp;
    fp=fopen("customer.dat","ab");
    fwrite(&customer, sizeof(customer),1, fp);
    fclose(fp);
    return;
}

void output()
{
    printf("\n\n    Customer no    :%d\n",customer.number);
    printf("    Name 	   :%s\n",customer.name);
    printf("    Mobile no      :%.f\n",customer.mobile_no);
    printf("    Account number :%d\n",customer.accountNo);
    printf("    Street         :%s\n",customer.street);
    printf("    City           :%s\n",customer.city);
    printf("    Old balance    :%.2f\n",customer.oldBalance);
    printf("    Current payment:%.2f\n",customer.payment);
    printf("    New balance    :%.2f\n",customer.newBalance);
    printf("    Payment date   :%d/%d/%d\n\n", customer.paymentAtLast.month, customer.paymentAtLast.day, customer.paymentAtLast.year);
    printf("    Account status :");
    switch(customer.accountType)
    {
        case 'C':
            printf("CURRENT\n\n");
            break;
        case 'O':
            printf("OVERDUE\n\n");
            break;
        case 'D':
            printf("DELINQUENT\n\n");
            break;
        default:
            printf("ERROR\\n\n");
    }
    return;
}

void search()
{
    char ch;
    char nam[100];
    int n,i,m=1;
    FILE *fp;
    fp=fopen("customer.dat","rb");
    if (ch != '1') {
        do {
            printf("\nEnter your choice:");
            ch = getchar();
        } while (ch != '2');
    } else {
        printf("\nEnter your choice:");
        ch = getchar();
    }
    switch(ch){
        case '1':
            fseek(fp,0,SEEK_END);
            file=ftell(fp);
            total= file / elementSize;
            do{
                printf("\nChoose customer number:");
                scanf("%d",&n);
                if (n<=0 || n > total) {
                    printf("\nEnter correct\n");
                } else{
                    fseek(fp, (n-1) * elementSize, SEEK_SET);
                    fread(&customer, elementSize, 1, fp);
                    output();
                }
                printf("\n\nAgain?(y/n)");
                ch=getchar();
            } while(ch=='y');
            fclose(fp);
            break;
        case '2':
            fseek(fp,0,SEEK_END);
            file=ftell(fp);
            elementSize=sizeof(customer);
            total = file / elementSize;
            fseek(fp, (total - 1) * elementSize, SEEK_SET);
            fread(&customer,sizeof(customer),1,fp);
            n=customer.number;

            do{
                printf("\nEnter the name:");
                scanf("%s",nam);
                fseek(fp,0,SEEK_SET);
                for(i=1; i <= n; i++)
                {
                    fread(&customer,sizeof(customer),1,fp);
                    if (strcmp(customer.name, nam) != 0)
                        continue;
                    output();
                    m=0;
                    break;
                }
                if(m!=0)
                    printf("\n\nDoesn't exist\n");
                printf("\nAnother?(y/n)");
                ch=getchar();
            }while(ch=='y');
            fclose(fp);
    }
    return;
}

int main()
{
    int i,n;
    char charactor;
    system("cls");


    printf("   BILLING SYSTEM \n\n");
    printf("===============================\n");
    printf("\n1:Add account on list\n");
    printf("2:Search customer account\n");
    printf("3:Exit\n");
    printf("\n================================\n");
    do{
        printf("\nSelect what do you want to do?");
        charactor = getchar();
    } while('0' >= charactor || '3' < charactor);
    switch(charactor){
        case '1':
            system("cls");
            printf("\nHow many customer accounts?");
            scanf("%d",&n);
            for(i=0;i<n;i++){
                input();
                customer.accountType = customer.payment > 0 ? (customer.payment < 0.1 * customer.oldBalance) ? 'O' : 'D'
                                                            : (customer.oldBalance > 0) ? 'D' : 'C';
                customer.newBalance= customer.oldBalance - customer.payment;
                writefile();
            }
            main();
        case '2':
            system("cls");
            printf("Search by what?\n");
            printf("\n1 --- Search by customer number\n");
            printf("2 --- Search by customer name\n");
            search();
            charactor=getchar();
            main();
        case '3':
            system("cls");
            exit(1);
    }
    return 0;
}