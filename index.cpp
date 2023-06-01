#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

void initialPage(int);
int nextAction();
void exitBank();

class Bank{
    public:

        //Public (void)function to open a new account, no parameter required
        void open_account(){
            generate_account();
            std::cout<<" -> Account has been successfully opened, " + first_name +' '+ second_name + "\n -> Your account number is:\t";
            std::cout<<acc_num<<std::endl;
        };

        //Public (int)function to check account balance, requires (int)'account_number' parameter
        int check_balance(int account_number){
            if(find_account(account_number)){
                std::ifstream data_file ("data/" + std::to_string(account_number) + ".txt");
                if(data_file.is_open()){
                    std::string line1,line2;
                    std::getline(data_file, line1);
                    std::cout<<" -> "<<line1<<std::endl;
                    std::getline(data_file, line2);
                    std::cout<<" -> "<<line2<<std::endl;
                    data_file.close();
                    return 0;
                }
            } else {
                std::cout<<"\nAccount `" + std::to_string(account_number) + "` does not exists. Please try again.\n";
                initialPage(2);
            };
            return -1;
        }
        
        //Public (int)function to deposit or withdraw money 
        void deposit_withdraw(int account_number){
            check_balance(account_number);
            std::cin.ignore();
            std::cout<<"Select the service below: \n"<<"\t1 = to deposit\n\t2 = to withdraw\n\t3 = to exit\n";
            int action = 0;
            std::cin>>action;
            switch(action){
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
                                
                                std::cout<<"Enter the amount to deposit: ";
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
                        std::cout<<"Failed to open the file, please try again\n";
                        initialPage(3);
                    }
                    nextAction();
                    return ;
                };
                case 2:
                {
                    std::ifstream data_file ("data/" + std::to_string(account_number) + ".txt");
                    std::ofstream new_file ("data/temp.txt");
                    if(data_file.is_open() && new_file.is_open()){
                        std::string s_balance, line;
                        int i_balance = 0, withdraw = 0, i = 0;
                        while(getline(data_file, line)){
                            i++;
                            if(i == 2) {
                                std::cout<<"Enter the amount to withdraw: ";
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
                        std::cout<<"Failed to open the file, please try again\n";
                        initialPage(3);
                    }
                    nextAction();
                    return ;
                    std::cout<<"case 2";
                    return ;
                }
                default:
                    std::cout<<"default";                            
                    return ;
            };
        };


        //Public (void)functio to close existing account, requires (int)'account_number' parameter
        void close_account(int account_number){
            if(find_account(account_number)){
                return ;
            } else {
                std::cout<<"\n -> Account: " + std::to_string(account_number) + " does not exists. Please verify the account number. \n\n";
                initialPage(4);
            };
        }
        //Public (void)function to display account details, requires (int)'account_number' parameter
        void display(){
            return ;
        };
    
    private:
        //Bank account constants and variables
        int acc_range = 99371, acc_num, acc_balance = 0;
        std::string first_name, second_name;

        //Private (int)function to generate random account number
        int generate_acc_number(){
            srand((unsigned) time(NULL));
            return 1 + (rand() % acc_range);
        }
        
        //Private (void)function to generate a new account, function is tied to (public void) 'open_account' function
        void generate_account(){
            //generate random account number and check whether it exists already.
            do{
                acc_num = generate_acc_number();
            }while(!find_account(acc_num));

            std::string name;
            std::cout<<" - Opening a bank account:";
            std::cin.ignore();

            //Enter a first name for the account created.
            while(true){
                std::cout<<"Enter your first name: ";
                std::getline(std::cin, name);
                if(name.length() == 0) {
                    std::cout<<"Invalid first name, please try again.\n\n";
                    name.clear();
                } else {
                    first_name = name;
                    break;
                }
            };

            //Enter a last name for the account created.
            while(true){
                std::cout<<"Enter your second name: ";
                std::getline(std::cin, name);
                if(name.length() == 0) {
                    std::cout<<"Invalid second name, please try again.\n\n";
                    name.clear();
                } else {
                    second_name = name;
                    break;
                };
            };

            std::cout<<std::endl;
            
            //Writing new account to the data.txt file
            std::ofstream data_file ("data/"+std::to_string(acc_num) + ".txt");
            if(data_file.is_open()){
                data_file << "Account number: " + std::to_string(acc_num);
                data_file << "\nAccount balance: " + std::to_string(acc_balance);
                data_file << "\nFirst name: " + first_name + "\nSecond name: " + second_name + '\n';
                data_file.close();
            } else std::cout<<"Unable to create a file";
        };

        //Private (bool)function to check whether account exists
        bool find_account(int account_number){
            std::ifstream data_file ("data/"+std::to_string(account_number)+".txt");
            if(data_file.is_open()) {
                data_file.close();
                return true;
            }
            else return false;
        }
};

//Global (void)function to interact with banking console
void initialPage(int action = 0){
    Bank account;
    if(action == 0){
        std::cout<<"\nPlease select the service from the options below:";
        std::cout<<"\n\t1 = Open a new account\n\t2 = Check account balance\n\t3 = Deposit/Withdraw money\n\t4 = Close an account\n\t5 = Exit the bank\n";
        std::cout<<"Select option: ";
        std::cin>>action;
        initialPage(action);
    } else switch(action){
        //Opening new account
        case 1:
        {
            Bank new_account;
            new_account.open_account();
            nextAction();
            return ;
        }
        //Checking account balace
        case 2:
        {
            int accNum = 0;
            std::cout<<"\nPlease enter your account number to check the balance: ";
            std::cin>>accNum;
            account.check_balance(accNum);
            nextAction();
            return ;
        }
        //Deposit/withdraw money
        case 3:
        {
            int accNum = 0;
            std::cout<<"\nPlease enter your account number to enter the banking system: ";
            std::cin>>accNum;
            account.deposit_withdraw(accNum);
            return ;
        }
        //To close the account
        case 4:
        {
            int accNum = 0;
            std::cout<<"\nPlease enter your account number to enter the banking system: ";
            std::cin>>accNum;
            account.close_account(accNum);
            return ;
        }
        default:
            return ;
    }
};

//Global (int)function to iterate between banking options
int nextAction(){
    std::cout<<"Enter 1 - to continue using the bank or enter 2 - to exit.\n";
            int nextAct = 0;
            std::cin>>nextAct;
            switch(nextAct){
                case 1:
                    initialPage();
                case 2:
                    exitBank();
                default:
                    return 0;
            };
}

//Global (void)function to exit the banking system
void exitBank(){
    return ;
}


//MAIN FUNCTION
int main(){
    std::cout<<"Welcome to the bank of Kovalov!\nPlease select the service from the options below:";
    initialPage();
};