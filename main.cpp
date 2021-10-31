#include <iostream>
#include <cstring>
#include <fstream>
#include "BankingSystem.h"

using namespace std;

//This class is to give customer specific functionalities
class Customer : public BankingSystem
{
    private:
        char *customerAddress_;

        //Date dateOfLastTransaction;
    
    public:
        void customerAddress(const char *s)
        {
            int len = strlen(s) + 1;
            customerAddress_ = new char[len];
            strcpy(customerAddress_,s);
        }

        char* get_customerAddress()
        {
            return customerAddress_;
        }

        //This method shows the transaction information to the customer specific to that person's account number

        void static showCustomerInformation(long accountNumber)
        {
            //Open the customer file and search for this person's account number
            //then retrieve the information for that account
            fstream readFromFile;

            char buffer[20];
            char inputBuffer[50];

            readFromFile.open("CustomerTransactions.txt", ios::in | ios::out);

                while(readFromFile)
                {
                    readFromFile>>buffer;

                    if(atoi(buffer) == accountNumber)
                    {
                        readFromFile.getline(inputBuffer,50);
                        cout<<inputBuffer<<endl;
                    }

                }

                readFromFile.close();

        }

        //This method calculates the interest if a person has not withdrawn for more than a month
        void calculateInterest()
        {
            //Date part yet to be implemented 
            //If date of withdrawal more than a month before calculate the interest

            
        }

};


int main()
{
    int ch1,ch2; //By default a customer choice is taken

    int flag=1;

    long number; //var to store account number

    BankingSystem accountList[20];//List to store the accounts
    
    int n; // Number of accounts to be taken as input

    cout<<"\n\n***********Welcome to this Banking Service***********\n\n";

    while(1)
    {

        cout<<"Are you \n1. An Employee \n2. A Customer: ";
        cin>>ch1;
        if(ch1==1)
        {
            
        
            cout<<"\n\nEnter your choice:\n1. Enter new account into the database \n2. Remove account from the database\n";
            cout<<"3. Show existing Account Holder Information\n4. Check for an Account Number\n5. Show Last Transaction Entry";
            cout<<"\n6. Show information about all accounts\n7. Exit\n";
            cin>>ch2;

        
            switch(ch2)
            {
                case 1:
                    cout<<"\nEnter the number of accounts you want to enter in the bank: ";
                    cin>>n;

                    for(int i=0; i<n; i++)
                    {
                        accountList[i].openNewAccount();
                    }
                    break;
            
                case 2:
                    

                    cout<<"\nEnter the account number which you want to remove: ";
                    cin>>number;

                    for(int i=0; i<n; i++)
                    {
                        if(accountList[i].checkAccountNumber(number))
                            accountList[i].removeAccount(number);
                    }
                    break;
            
                case 3:

                    cout<<"\nEnter the account number which you want to view: ";
                    cin>>number;

                    Customer::showCustomerInformation(number);
                    break;    

                case 4:
                    cout<<"\nEnter the account number which you want to check for: ";
                    cin>>number;

                    for(int i=0; i<n; i++)
                    {
                        accountList[i].checkAccountNumber(number);                        
                    }
                    break;

                case 5:
                    cout<<"\nThe last transaction entry is: ";
                    BankingSystem::showLastEntry;

                    break;

                case 6:
                    cout<<"\nAll Banking Information is as follows: ";
                    BankingSystem::showAllInformation();
                    break;

                case 7:
                    flag = 0;
                    exit(0);

                default:
                    cout<<"\nWrong choice, please try again";

            }
        }
        else
        {
            BankingSystem temp;

            float sum=0.0;
            
            cout<<"\n\nEnter your choice:\n1. Deposit money into your account\n2. Withdraw money from your account";
            cout<<"\n3. Show account balance\n4. Exit\n";
            cin>>ch2;

            switch(ch2)
            {
                case 1:
                    cout<<"\nEnter your account number: ";
                    cin>>number;

                    cout<<"\nEnter the amount you want to deposit: ";
                    cin>>sum;

                    for(int i=0; i<n; i++)
                    {
                        if(accountList[i].get_accountNumber()==number)
                            accountList[i].depositAmount(sum);
                    }
                
                    break;

                case 2:
                    cout<<"\nEnter your account number: ";
                    cin>>number;

                    cout<<"\nEnter the amount you want to withdraw: ";
                    cin>>sum;

                    for(int i=0; i<n; i++)
                    {
                        if(accountList[i].get_accountNumber()==number)
                            accountList[i].withdrawAmount(sum);
                    }
                
                    break;

                case 3:
                    cout<<"\nEnter your account number: ";
                    cin>>number;

                    cout<<"\nYour account balance is as follows: ";

                    for(int i=0; i<n; i++)
                    {
                        if(accountList[i].get_accountNumber()==number)
                            accountList[i].get_balanceAmount();
                    }
                    break;

                case 4:
                    exit(0);

                default:
                    cout<<"\nWrong choice, please try again";
            }
        }
    }
    
    
    return 0;
}
