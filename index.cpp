#include <iostream>
#include <string>
#include <fstream>

void initialPage(int);
int nextAction();
void exitBank();

class Bank{
    public:
        void open_account(){
            generate_account();
            std::cout<<" -> Account has been successfully opened, " + first_name +' '+ second_name + "\n -> Your account number is:\t";
            std::cout<<acc_num<<std::endl;
        };

        int check_balance(int account_number){
            if(find_account(account_number)){
                std::ifstream data_file ("data/" + std::to_string(account_number) + ".txt");
                if(data_file.is_open()){
                    std::string line1,line2;
                    std::getline(data_file, line1);
                    std::getline(data_file, line2);
                    std::cout<<" -> "<<line2<<std::endl;
                    return 0;
                }
            } else {
                std::cout<<"\nAccount with" + std::to_string(account_number) + " does not exists. Please try again.\n";
                initialPage(2);
            };
            return -1;
        }

        void display(){
        };
    private:
        //Bank account constants and variables
        int acc_range = 99371, acc_num, acc_balance = 0;
        std::string first_name, second_name;

        //Function
        int generate_acc_number(){
            srand((unsigned) time(NULL));
            return 1 + (rand() % acc_range);
        }
        void generate_account(){
            acc_num = generate_acc_number();
            std::string name;
            std::cout<<" - Opening a bank account:";
            std::cin.ignore();
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

        bool find_account(int account_number){
            std::ifstream data_file ("data/"+std::to_string(account_number)+".txt");
            if(data_file.is_open()) {
                data_file.close();
                return true;
            }
            else return false;
        }
};

void initialPage(int action = 0){
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
        }
        //Checking account balace
        case 2:
        {
            int accNum = 0;
            std::cout<<"\nPlease enter your account number to check the balance: ";
            std::cin>>accNum;
            Bank account;
            account.check_balance(accNum);
            nextAction();
        }
        //Deposit/withdraw money
        case 3:
        {
            int accNum = 0;
            std::cout<<"\nPlease enter your account number to check the balance: ";
            std::cin>>accNum;
            Bank account;
            account.check_balance(accNum);
            std::cout<<"\nSelect next action: \n\t1 = to deposit money to the account\n\t2 = to withdraw money from the account\n"

            nextAction();
        }
        default:
            return ;
    }
};

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

void exitBank(){
    return ;
}

int main(){
    std::cout<<"Welcome to the bank of Kovalov!\nPlease select the service from the options below:";
    initialPage();
};