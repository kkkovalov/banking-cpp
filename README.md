# Welcome to the Bank of Kovalov!

To enjoy using the services of our bank, please download index.cpp file onto your machine first. Then, proceed to compile the index file by utilizing automatic compiler in [online IDE](https://www.codechef.com/ide) or by [using the terminal](https://www.codecademy.com/article/cpp-compile-execute-locally).

# Structure

`int main()` function is the start of the program, it initializes new class (Bank) variable and runs `initialPage()` function.

`initialPage(int = 0, int = 0)` function is (void) and has 2 optional parameters (int)action and (int)c_acc.
- (int)action runs the switch-case logic for the next function
- (int)c_acc carries current account_number, when it was entered at any point.

> NOTE: Once the account has been created or account_number entered in the system, to use a different account **you will have to exit** the system first.


This message is displayed when `initialPage()` function is run for the first time.
```
		Welcome to the Bank of Kovalov!

Please select the service from the options below:
	1 = Open a new account
	2 = Check account balance
	3 = Deposit/Withdraw money
	4 = Close an account
	5 = Exit the bank

0 - Select option: 
```

- 1 = Open a new account:
- Generates a random account_number, requires the user to enter his first and last name. Names are verified to be non-empty *strings*.

- 2 = Check account balance:
- Displays current account number and balance when logged in, otherwise requests account number to check the balance. 

- 3 = Deposit/Withdraw money:
- Opens up a window to select deposit or withdraw action and requests the sum. If logged in, checks for sufficient funds and displays the balance. Otherwise, returns an error.

- 4 = Close an account:
- Closes current or entered account number file in the bank.

- 5 = Exit the bank:
- You can guesss.

> NOTE: All cases, if successful or not, result in `nextAction()` function execution.

`nextAction(int = 0)` function prompts the user to continue using the services of the bank or exit the bank. Optional parameter (int)c_acc - verifies current session or starts a new one.

# Services & Setup

No additional libraries or npm packages required, simple C++11 compiler will be more than enough. 

>Please refer to your IDE documentation for compiling instructions and setup.