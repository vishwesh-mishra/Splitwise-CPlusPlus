#include<iostream>
#include "../Models/User.h"
#include "../Services/UserService.hpp"
#include "../Services/ExpenseService.hpp"

class TestCases {
public:
	void tc1();
	void tc2();
};

void TestCases::tc1() {
	UserService* userService = new UserService();
	userService->addUser(new User("u1", "User1", "user1@splitwise.com", 123));
	userService->addUser(new User("u2", "User2", "user2@splitwise.com", 123));
	userService->addUser(new User("u3", "User3", "user3@splitwise.com", 123));
	userService->addUser(new User("u4", "User4", "user4@splitwise.com", 123));

	ExpenseService* expenseService = new ExpenseService();
	expenseService->showBalances(userService->userTable);
	expenseService->showBalances(userService->userTable, "u1");

	expenseService->addExpenseAndShares("u1", 1000, { "u1","u2","u3","u4" }, "EQUAL");
	expenseService->showBalances(userService->userTable, "u4");
	expenseService->showBalances(userService->userTable, "u1");

	expenseService->addExpenseAndShares("u1", 1250, { "u2","u3" }, "EXACT", { 370, 880 });
	expenseService->showBalances(userService->userTable);

	expenseService->addExpenseAndShares("u4", 1200, { "u1","u2","u3","u4" }, "PERCENT", { 40,20,20,20 });
	expenseService->showBalances(userService->userTable, "u1");
	expenseService->showBalances(userService->userTable);

	expenseService->printExpenseShares();

	cout << endl;
}

void TestCases::tc2() {
	UserService* userService = new UserService();
	userService->addUser(new User("u1", "User1", "user1@splitwise.com", 123));
	userService->addUser(new User("u2", "User2", "user2@splitwise.com", 123));
	userService->addUser(new User("u3", "User3", "user3@splitwise.com", 123));
	userService->addUser(new User("u4", "User4", "user4@splitwise.com", 123));
	
	ExpenseService* expenseService = new ExpenseService();
	expenseService->addExpenseAndShares("u1", 720, { "u1","u2","u3","u4" }, "EQUAL");
	expenseService->addExpenseAndShares("u2", 1250, { "u3","u4" }, "EXACT", { 430, 560 });
	expenseService->addExpenseAndShares("u4", 1200, { "u1","u2","u3","u4" }, "PERCENT", { 40,20,20,20 });

	expenseService->printExpenseShares();

}
