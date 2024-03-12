// libraries import
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>

//Creating the inventroy struct
struct Inventory
{
        char Name_of_Supplier[100];
        char supply_code[100];
	char donator[100];
        char hospitalName[100];
        char status[100];
        int number_of_shipment;
        float qty_received,new_qty_received, qty_distrubuted, current_qty_neg, current_qty_pos;
}I;

// list of the functions used
void addrecords();
void listrecords();
void update_donation_quantities();
void searchrecords();
void bubble_sort();

// variable declaration
char get;

// main function
int main()
{	
	//local variable
    int choice;
    int i;
    int q;
	printf("\n\n");

    printf("*******************************************\n");
    printf("*******************************************\n");
    printf("*                                         *\n");
    printf("*    COVID-19 DONATION MANAGEMENT SYSTEM  *\n");
    printf("*                                         *\n");
    printf("*                                         *\n");
    printf("*******************************************\n");
    printf("*******************************************\n\n\n");


    //local variable
    int k;
    int space;

    //loop for printing pattern
    for (i = 1; i <= 6; ++i)
    {
        k=0;
        for (space = 1; space <= 10 - i; ++space) {
        printf("  ");
    }
    while (k != 2 * i - 1)
    {
         printf("* ");
         ++k;
    }

        printf(" \n");
    }

    while(choice != 7)//Loop condition until choice entered is not equal to 6
    {

        printf("----------------------------------------------\n");
        printf("|   \t**ENTER THE COMMAND**                |\n");
        printf("|                                            |\n");
        printf("|   \t1. Inventory Creation                |\n");
        printf("|   \t2. List Records                      |\n");
        printf("|   \t3. SEARCH Donation Available         |\n");
        printf("|   \t4. Viewing Donations                 |\n");
        printf("|   \t0. EXIT                              |\n");
        printf("|                                            |\n");
        printf("----------------------------------------------\n\n");
        printf("   \tCOMMAND SELECTED : ");

        scanf("%d",&choice);//choice for option

        fflush(stdin);// used to clear the buffer or stream
        switch(choice)
        {
        case 1 :
                 addrecords();//function call
                 break;

        case 2 : 
                 listrecords();//function call
                 break;

        case 3 : 
                 searchrecords();//function call
                 break;
        case 4 : update_donation_quantities();
                 break;

	// case 0 : EXIT();//function call
        //          break;

        default : 
                printf("\n\nInvalid input , try again by using valid inputs");
        
        printf("\n\n");
		}
	return 0;
	}

}






// function to add information about the doantion
void addrecords(){


	FILE *fp; // file declaration
        
	fp=fopen("donation.txt","ab+");
        system("cls");
	printf("\n Enter Supply Name:");
	fflush(stdin);
	scanf("%[^\n]",&I.Name_of_Supplier);
	printf("\n Enter Supply Code:");
	fflush(stdin);
	scanf("%[^\n]",&I.supply_code);
        printf("\n Enter The Donator:");
	fflush(stdin);
	scanf("%[^\n]",&I.donator);
	printf("\n Enter Number of shipment:");
	scanf("%d",&I.number_of_shipment);
        printf("\n Enter The Quantities :");
        scanf("%f", &I.qty_received);
	fwrite(&I,sizeof(I),1,fp);
        printf(" record successfully added");
	fclose(fp);main();
}

// function to show the list of records donated and their relatifs information
void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("dist.txt","rb"))==NULL) // checking if the file exist 
		main();
	printf("Supply Code\t\tDonator Name\t\t\tQty_Distrubuted\t\tHospital Name\n");
	for(i=0;i<95;i++)
		printf("-");
	while(fread(&I,sizeof(I),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\t\t%.1f\t\t%-10s",I.supply_code,I.donator,I.qty_distrubuted, I.hospitalName);
	}
	printf("\n");
	for(i=0;i<95;i++)
		printf("-");

fclose(f);
main();
}

// function to search about a particular donation by using his code 
void searchrecords()
{
	FILE *fp;
	char supply_code[100];
	int flag=1;
        int i;
	fp=fopen("donation.txt", "r");
	if(fp==0)
	main();
	fflush(stdin);
	printf("Enter The Supply Code: ");
	scanf("%s", &supply_code);
	while(fread(&I,sizeof(I),1,fp)==1)
	{
		if(strcmp(I.supply_code,supply_code)==0)
		{
			printf("\n<<<<<< Record Found >>>>>>>>> ");
                        printf("\n");
			printf("\nName of supplier\tSupplier Code\t\tdonator\t\tNumber of shipment\tQuantities(Millions)\n");
                        printf("\n%-10s\t\t%-10s\t\t%-10s\t\t%d\t\t\t\t%.1f",I.Name_of_Supplier,I.supply_code,I.donator, I.number_of_shipment, I.qty_received);
                        printf("\n");
			flag=0;
			break;
		}

	}
        fclose(fp);
        main();
}

// function to update a donation by receiving or donate quantities to a particular hospitals
void update_donation_quantities()
{

        FILE *f;
        FILE *fp;
	char supply_code[100];
	long int size=sizeof(I);
        int choice;
        fp=fopen("dist.txt", "ab+");
	if((f=fopen("donation.txt","rb+"))==NULL)
		exit(0);
	printf("Enter the supply code:");
	scanf("%[^\n]",supply_code);
	fflush(stdin);
	while(fread(&I,sizeof(I),1,f)==1)
	{
		if(strcmp(I.supply_code,supply_code)==0)
		{
			printf("|   \t1. Received Quantities |\n");
                        printf("|   \t2. Donate Quantities   |\n");
                        printf("\n");
                        scanf("%d",&choice);//choice for option
                        switch(choice)
                        {
                                case 1 :
                                printf("\nThe Available quantities are: %.1f", I.qty_received);
                                printf("\n");
                                printf("Enter the Quantities to received :");
                                scanf("%f",&I.new_qty_received);
                                I.qty_received = I.new_qty_received + I.qty_received;
                                printf("The Current Quantities available are :  %.1f", I.qty_received);
                                break;
                                
                                case 2 :
                                printf("\nThe Available quantities are: %.1f", I.qty_received);
                                printf("\n");
                                printf("Enter the Hospital Name to be distrubuted : ");
                                scanf("%s", I.hospitalName);
                                printf("Enter the Quantities to be Distrubuted :");
                                scanf("%f",&I.qty_distrubuted);
                                if(I.qty_distrubuted > I.qty_received){
                                        printf("Sorry we don't have that available Quantities");
                                        main();
                                                }
                                else{
                                        I.qty_received = (I.qty_received - I.qty_distrubuted );
                                        printf("The Current Quantities available : %.1f :", I.qty_received);
                                        break;
                                        main();
                                }   
                                default : 
                                printf("\n\nInvalid input , try again by using valid inputs");
                                printf("\n\n");
                                main();
                        }
                        // using the file to update the changes then write to new changes.
			fseek(f,-size,SEEK_CUR);
			fwrite(&I,sizeof(I),1,f);
                        fwrite(&I, sizeof(I),1,fp);
			break;
		}
	}
	fclose(f);
        fclose(fp);
        main();
}

