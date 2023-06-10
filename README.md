# Welcome to the Bank of Kovalov!

To enjoy using the services of our bank, please download index.cpp file onto your machine first. Then, proceed to compile the index file by utilizing automatic compiler in [online IDE](https://www.codechef.com/ide) or by [using the terminal](https://www.codecademy.com/article/cpp-compile-execute-locally).

# Structure

`int main()` function is the start of the program, it initializes new class (Bank) variable and runs `initialPage()` function.

`initialPage(int = 0, int = 0)` function is (void) and has 2 optional parameters (int)action and (int)c_acc.
    -> (int)action runs the switch-case logic for the next function
    -> (int)c_acc carries current account_number, when it was entered at any point.

> NOTE: Once the account has been created or account_number entered in the system, to use a different account **you will have to exit** the system first.


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