        // Libraries
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

        //Declaration of basic functions to use inside the class

void initialPage(int = 0,int = 0);
int nextAction(int = 0);
void exitBank();

class Bank{
    public:

        //Public (int)function to open a new account, no parameter required. 
        // -> returns (int)account_number varaiable created in the proces, default (int)account_number = 0.
        int openAccount(){
            generateAccount();
            std::cout<<" -> Account has been successfully opened, " + first_name +' '+ second_name + "\n -> Your account number is:\t";
            std::cout<<acc_num<<std::endl;
            return acc_num;
        };

        //Public (void)function to check account balance, requires (int)'account_number' parameter
        void checkBalance(int account_number){
            if(find_account(account_number)){
                std::ifstream data_file ("data/" + std::to_string(account_number) + ".txt");
                if(data_file.is_open()){
                    std::string line1,line2;
                    std::getline(data_file, line1);
                    std::cout<<"\n -> "<<line1<<std::endl;
                    std::getline(data_file, line2);
                    std::cout<<" -> "<<line2<<std::endl;
                    data_file.close();
                }
            } else {
                std::cout<<"\nAccount `" + std::to_string(account_number) + "` does not exists. Please try again.\n";
                initialPage(2);
            };
            return ;
        }
        
        //Public (int)function to deposit or withdraw money 
        void depositWithdraw(int account_number){
            display(account_number);
            std::cin.ignore();
            std::cout<<"Select the service below: \n"<<"\t1 = to deposit\n\t2 = to withdraw\n\t3 = to exit"<<std::endl;
            int action = 0;
            std::cout<<"\n - Select option: ";
            std::cin>>action;
            switch(action){

                //Deposit money to the account
                case 1:
                {
                    std::ifstream data_file ("data/" + std::to_string(account_number) + ".txt");
                    std::ofstream new_file ("data/temp.txt");
                    if(data_file.is_open() && new_file.is_open()){
                        std::string s_balance, line;
                        int i_balance = 0, new_deposit = 0, i = 0;
                        while(getline(data_file, line)){
                            i++;
                            if(i == 2) {
                                
                                std::cout<<" - Enter the amount to deposit: ";
                                std::cin>>new_deposit;
                                i_balance += new_deposit;
                                for(int i = line.find(':') + 2; i < line.length(); i++){
                                    s_balance += line[i];
                                }
                                i_balance += stoi(s_balance);
                                new_file << "Account balance: " + std::to_string(i_balance) + '\n';
                            } else {
                                new_file << line + '\n';
                            }
                        }
                        std::cout<<"\n -> New account balance is: " + std::to_string(i_balance) + "\n";
                        new_file.close();
                        data_file.close();
                        std::string filename = "data/" + std::to_string(account_number) + ".txt";
                        int s_length = filename.length();
                        char *fname = new char[s_length + 1];
                        strcpy(fname, filename.c_str());
                        std::remove(fname);
                        std::rename("data/temp.txt",fname);
                        delete[] fname;
                    } else {
                        std::cout<<" -> Failed to open the file, please try again\n";
                        initialPage(3, account_number);
                    }
                    nextAction(account_number);
                    break;
                };

                //Withdraw money from the account
                case 2:
                {
                    //Stream open data_file(existing) and create stream for a new_file(new)
                    std::ifstream data_file ("data/" + std::to_string(account_number) + ".txt");
                    std::ofstream new_file ("data/temp.txt");
                    if(data_file.is_open() && new_file.is_open()){
                        std::string s_balance, line;
                        int i_balance = 0, withdraw = 0, i = 0;
                        while(getline(data_file, line)){
                            i++;
                            if(i == 2) {
                                std::cout<<" - Enter the amount to withdraw: ";
                                std::cin>>withdraw;
                                for(int i = line.find(':') + 2; i < line.length(); i++){
                                    s_balance += line[i];
                                }
                                i_balance += stoi(s_balance);
                                if(i_balance >= withdraw) {
                                    i_balance -=withdraw;
                                    new_file << "Account balance: " + std::to_string(i_balance) + '\n';
                                } else {
                                    std::cout<<"\n -> Not enough funds on the account! Deposit money first in order to withdraw\n\n";
                                    nextAction();
                                    return ;
                                    new_file << "Account balance: " + std::to_string(i_balance) + '\n';
                                }
                            } else {
                                new_file << line + '\n';
                            }
                        }
                        std::cout<<"\n -> New account balance is: " + std::to_string(i_balance) + "\n\n";
                        new_file.close();
                        data_file.close();
                        std::string filename = "data/" + std::to_string(account_number) + ".txt";
                        int s_length = filename.length();
                        char *fname = new char[s_length + 1];
                        strcpy(fname, filename.c_str());
                        std::remove(fname);
                        std::rename("data/temp.txt",fname);
                        delete[] fname;
                    } else {
                        std::cout<<" -> Failed to open the file, please try again\n";
                        initialPage(3, account_number);
                    }
                    nextAction(account_number);
                    break;
                }
                case 3:
                {
                    exitBank();
                    break;
                }
                default:
                    exitBank();
                    break;
            };
        };

        //Public (void)functio to close existing account, requires (int)'account_number' parameter
        void closeAccount(int account_number){
            if(find_account(account_number)){
                std::cout<<"\n -> Re-enter your account number to confirm closure: ";
                int typed_account_number;
                std::cin>>typed_account_number;
                if(account_number != typed_account_number) return ;
                std::string filename = "data/" + std::to_string(account_number) + ".txt";
                char* fname = new char[filename.length() + 1];
                std::strcpy(fname, filename.c_str());
                std::remove(fname);
                std::cout<<"\n -> Account: " + std::to_string(account_number) + " has been closed. Sorry to see you go.\n\n";
                nextAction();
            } else {
                std::cout<<"\n -> Account: " + std::to_string(account_number) + " does not exists. Please verify the account number. \n\n";
                initialPage(4);
            };
            return;
        }
        
        //Public (void)function to display account details, requires (int)'account_number' parameter
        void display(int account_number){
            if(find_account(account_number)){
                std::ifstream data_file ("data/" + std::to_string(account_number) + ".txt");
                if(data_file.is_open()){
                    std::string line1,line2;
                    std::getline(data_file, line1);
                    std::cout<<"\n -> "<<line1<<std::endl;
                    std::getline(data_file, line2);
                    std::cout<<" -> "<<line2<<std::endl<<std::endl;
                    data_file.close();
                    return ;
                }
            } else {
                std::cout<<"\nAccount `" + std::to_string(account_number) + "` does not exists. Please try again.\n";
                initialPage();
            };
        };
    
        int currentSession(){
            if(acc_num && find_account(acc_num)) return acc_num;
            else return 0;
        };

        int getAccountNumber(){

            return acc_num;
        };

    private:
        //Bank account constants and variables
        int acc_num, acc_balance;
        static const int acc_range = 99371;
        std::string first_name, second_name;

        //Private (int)function to generate random account number
        int generate_acc_number(){
            srand((unsigned) time(NULL));
            return 1 + (rand() % acc_range);
        }
        
        //Private (void)function to generate a new account, function is tied to (public void) 'openAccount' function
        void generateAccount(){

            //Generates random account number and checks whether it exists already.
            do{
                acc_num = generate_acc_number();
            }while(find_account(acc_num));

            std::string name;
            std::cout<<"\n -> Opening a bank account:"<<std::endl;
            std::cin.ignore();

            //Enter a first name for the account created.
            while(true){
                std::cout<<" - Enter your first name: ";
                std::getline(std::cin, name);
                if(name.length() == 0) {
                    std::cout<<" -> Invalid first name, please try again.\n"<<std::endl;
                    name.clear();
                } else {
                    first_name = name;
                    break;
                }
            };
            std::cout<<std::endl;

            //Enter a last name for the account created.
            while(true){
                std::cout<<" - Enter your second name: ";
                std::getline(std::cin, name);
                if(name.length() == 0) {
                    std::cout<<"Invalid second name, please try again.\n"<<std::endl;
                    name.clear();
                } else {
                    second_name = name;
                    break;
                };
            };
            std::cout<<std::endl;
            
            //Writing new account information into the "data/(account_number).txt" file. File is created by the ofstream function
            std::ofstream data_file ("data/"+std::to_string(acc_num) + ".txt");
            if(data_file.is_open()){
                acc_balance = 0;
                data_file << "Account number: " + std::to_string(acc_num);
                data_file << "\nAccount balance: " + std::to_string(acc_balance);
                data_file << "\nFirst name: " + first_name + "\nSecond name: " + second_name + '\n';
                data_file.close();
            } else std::cout<<"Unable to create a file";

            return ;
        };

        //Private (bool)function to check whether account exists
        // -> returns (bool)true when account_number specified is in the data/ directory, else is false
        bool find_account(int account_number){
            std::ifstream data_file ("data/"+std::to_string(account_number)+".txt");
            if(data_file.is_open()) {
                data_file.close();
                return true;
            }
            else return false;
        }
};

//Global (void)function to interact with banking console, parameters (int)action = 0 and int(c_acc) = 0 are optional.
void initialPage(int action, int c_acc){

    Bank account;
    
    switch(action){

        //Default function to initialize system
        case 0:
        {
            std::cout<<"\nPlease select the service from the options below:";
            std::cout<<"\n\t1 = Open a new account\n\t2 = Check account balance\n\t3 = Deposit/Withdraw money\n\t4 = Close an account\n\t5 = Exit the bank\n\n";
            std::cout<</*c_acc<<*/" - Select option: ";
            std::cin>>action;
            initialPage(action, c_acc);
            break;
        }

        //Opening new account
        case 1:
        {
            c_acc = account.openAccount();
            nextAction(c_acc);
            break ;
        }

        //Checking account balance
        case 2:
        {
            if(c_acc) {
                account.checkBalance(c_acc);
            } else {
                std::cout<<"\n - Please enter your account number to check the balance: ";
                std::cin>>c_acc;
                account.checkBalance(c_acc);
            }
            nextAction(c_acc);
            break ;
        }

        //Deposit/withdraw money
        case 3:
        {
            if(c_acc){
                account.depositWithdraw(c_acc);    
            } else {
                std::cout<<"\n - Please enter your account number to enter the banking system: ";
                std::cin>>c_acc;
                account.depositWithdraw(c_acc);
            }
            break ;
        }

        //To close the account
        case 4:
        {
            if(c_acc) {
                account.closeAccount(c_acc);
            } else {
                std::cout<<"\n - Please enter your account number to enter the banking system: ";
                std::cin>>c_acc;
                account.closeAccount(c_acc);
            }
            break ;
        }
        case 5:
        {
            exitBank();
            break;
        }
        default:
            return ;
    };
    return ;
};

//Global (int)function to iterate between banking options, parameter (int)c_acc = 0 is optional
int nextAction(int c_acc){
    std::cout<<"\nEnter 1 - to continue using the bank or enter 2 - to exit.\n";
            int nextAct = 0;
            std::cout<</*c_acc<<*/" - Select option: ";
            std::cin>>nextAct;
            switch(nextAct){
                case 1:
                    initialPage(0,c_acc);
                case 2:
                    exitBank();
                default:
                    return 0;
            };
    return 0;
};

//Global (void)function to exit the banking system
void exitBank(){
    std::cout<<"\n\tThank you for using services of the Bank of Kovalov.\n\t\tHope to see you back soon!\n\n";
    return ;
}


//MAIN FUNCTION
int main(){
    std::cout<<"\n\t\tWelcome to the Bank of Kovalov!\n";
    initialPage();
};
