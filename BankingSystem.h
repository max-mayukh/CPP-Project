#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

/*There are two files. One is a Employee file which contains the customer information like account number, depositor name
customer address, balance, account type. Second is a Customer file which contains the transaction information for every customer
along with account number and balance*/ 

//Structure to store the last date of transaction
/*struct Date
{
    int day;
    int month;
};*/

//This class is to give employee specific functionalities
class BankingSystem
{
    private:
        char *depositorName_;
        long accountNumber_;
        char *accountType_;
        float balanceAmount_;

        static int accountHolderCount;

    public:

        BankingSystem()
        {
            accountNumber_ = 120000; // Initialising Default Account Number
            balanceAmount_ = 0.00; // Initialising Default Account Balance

            //Initialising the Employee record file

            fstream writeToFile;
            
            writeToFile.open("EmployeeFile.txt", ios::out);

            /*writeToFile.width(15);

            if(accountHolderCount==0)
            {
                writeToFile<<"Account Number  Account Name  Account Type  Account Balance"<<endl;
            }*/
        }

        ~BankingSystem()
        {
            delete [] depositorName_;
        }

        void depositorName(const char *s)
        {
            int len = strlen(s) + 1;
            depositorName_ = new char[len];
            strcpy(depositorName_,s);
        }

        char* get_depositorName()
        {
            return depositorName_;
        }

        void set_accountNumber(int cn)
        {
            accountNumber_ += cn;
        }

        long get_accountNumber()
        {
            return accountNumber_;
        }

        void accountType()
        {
            int ch=1; //By default account type is savings

            cout<<"\nWhat kind of account do you want to open:\n1.Savings\n2.Current: ";
            cin>>ch;

            if(ch==1)
                strcpy(accountType_,"Savings");
            
            else
                strcpy(accountType_,"Current");
            
        }

        char* get_accountType()
        {
            return accountType_;
        }

        float get_balanceAmount()
        {
            return balanceAmount_;
        }

        void depositAmount(float sum)
        {
            balanceAmount_+=sum;
            cout<<"\nMoney deposited succesfully";

            //Opening Customer Transactions file and entering the transaction entry
            fstream writeToFile;
            
            writeToFile.open("CustomerTransactions.txt", ios::out | ios::app);
            writeToFile<<accountNumber_;      
            writeToFile<<" Deposited Rs. "<<sum<<" Updated Balance: Rs. "<<balanceAmount_<<endl;

            writeToFile.close();
        }

        void withdrawAmount(float sum)
        {
            if(sum>balanceAmount_){
                cout<<"\nNot enough balance amount. \nPlease try again.\n";
                this->withdrawAmount(sum);
            }
            else
            {
                balanceAmount_-=sum;
                cout<<"Money withdrawn succesfully.";

                //Opening Customer Transactions file and entering the transaction entry
                fstream writeToFile;
            
                writeToFile.open("CustomerTransactions.txt", ios::out | ios::app);
                writeToFile<<accountNumber_;            
                writeToFile<<" Withdrew Rs. "<<sum<<" Updated Balance: Rs. "<<balanceAmount_<<endl;

                writeToFile.close();
            }
        }

        //This method is called when a new account is opened for a customer
        void openNewAccount()
        {
            char name[20];

            cout<<"Enter your name for Account Opening: ";
            cin.ignore();

            cin.getline(name, 20);

            depositorName(name);

            accountType();

            accountHolderCount++; //Account Number incremented for every new account holder

            set_accountNumber(accountHolderCount);

            //Employee File Handling Part to be implemented here

            fstream writeToFile;
            
            writeToFile.open("EmployeeFile.txt", ios::out | ios::app);

            writeToFile<<accountNumber_<<"  ";

            writeToFile.width(15);
            
            writeToFile<<depositorName_<<"  "<<accountType_<<endl;

            writeToFile.close();

        }

        //This method is called when a customer account is removed from the bank

        void removeAccount(long accountNumber)
        {
            accountHolderCount--;

            cout<<"\nPlease collect your balance amount: "<<balanceAmount_<<endl;

            balanceAmount_ = 0; // Balance amount reset for closed account


            //Employee File Handling Part to be implemented here

            fstream readFromFile;

            char buffer[20];

            char buffer1[50];
            
            readFromFile.open("EmployeeFile.txt", ios::in | ios::out);

            fstream tempFile;

            tempFile.open("Temp.txt", ios::out | ios::app); 

            while(readFromFile)
            {
                readFromFile>>buffer;

                if(atoi(buffer) == accountNumber)
                {
                    cout<<"Account removed succesfully\n";
                    continue;
                }

                readFromFile.getline(buffer1, 50);

                tempFile<<buffer1;
            }

            readFromFile.close();
            remove("EmployeeFile.txt"); // removing the old file
            
            tempFile.close();

            rename("Temp.txt", "EmployeeFile.txt"); //renaming the new file
            
            
        }

        //This function is to show the account number of the last entry

        void static showLastEntry()
        {
            //Last entry needs to be read from the customer specific file
            /*readFromFile.open("CustomerTransactions.txt", ios::in | ios::out);

            char inputBuffer[50];*/

        }

        //This function checks whether an account exists or not

        int checkAccountNumber(long accountNumber)
        {
            //Search through the employee file and if the account number is found, display it
            //Otherwise display the account number does not exist

            fstream readFromFile;

            char buffer[20];
            
            readFromFile.open("EmployeeFile.txt", ios::in | ios::out);

            while(readFromFile)
            {
                readFromFile>>buffer;

                if(atoi(buffer) == accountNumber)
                {
                    cout<<"Account exists\n";
                    return 1;
                }

                else{
                    cout<<"Account Does not exist\n";
                    return 0;
                }
            }

            readFromFile.close();
            
        }

        //This method shows the customer transaction information along with account details when an employee types in an account number

        void static showAllInformation()
        {
            long accountNumber;
            cout<<"Enter the account number for which information is to be displayed: ";
            cin>>accountNumber;

            //Check if this number exists or not
            //First open the Employee file and retrieve the account information with respect to this number
            //Then open the customer file and retrieve the transaction information
          
            
                fstream readFromFile;

                char buffer[20];
                char inputBuffer[50];
            
                readFromFile.open("EmployeeFile.txt", ios::in | ios::out);

                while(readFromFile)
                {
                    readFromFile>>buffer;

                    if(atoi(buffer) == accountNumber)
                    {
                        readFromFile.getline(inputBuffer,50);
                        cout<<inputBuffer<<endl;
                        break;
                    }

                }

                readFromFile.close();

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

};

//static variable globally declared here
int BankingSystem :: accountHolderCount = 0;