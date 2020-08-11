#include<iostream>
#include<vector>
#include<cctype>
#include<algorithm>
#include<map>

#include "../Models/Expense.h"
#include "../Models/ExpenseShare.h"

typedef pair<string, string> pss;

class ExpenseService {
private:
	int eId;
public:
	vector<Expense*> expenseTable;
	vector<ExpenseShare*> expenseShareTable;

	ExpenseService() {
		this->eId = 1;
	}

	void addExpenseAndShares(string payerId, double amount, vector<string> receivers, string type, vector<double> shareWeights);

	void addExpense(Expense* e);
	void addExpenseShare(ExpenseShare* es);

	void printExpenseShares() {
		for (auto es : expenseShareTable) cout << es->eId << " " << es->payerId << " " << es->receiverId << " " << es->share << endl;
	}

	void showBalances(map<string, User*> userTable, string userId);
};

void ExpenseService::addExpenseAndShares(string payerId, double amount, vector<string> receivers, string type, vector<double> shareWeights = {}) {
	Expense* e = new Expense(this->eId, payerId, amount);
	transform(type.begin(),type.end(),type.begin(),::tolower);

	int i, numReceivers = receivers.size();
	vector<double> shares(numReceivers);
	if (type == "equal") for (i = 0;i < numReceivers;i++) shares[i] = amount / numReceivers;
	else if (type == "exact") shares = shareWeights;
	else for (i = 0;i < numReceivers;i++) shares[i] = amount*(shareWeights[i]/100);
	
	this->addExpense(e);
	for (i = 0;i < numReceivers;i++) {
		if(receivers[i] != payerId)
			this->addExpenseShare(new ExpenseShare(this->eId, payerId, receivers[i], shares[i]));
	}
	this->eId++;
}

void ExpenseService::addExpense(Expense* e) {
	this->expenseTable.push_back(e);
}

void ExpenseService::addExpenseShare(ExpenseShare* es) {
	this->expenseShareTable.push_back(es);
}

void ExpenseService::showBalances(map<string, User*> userTable, string uId = "") {
	map<pss, double> oweMap;
	map<pss, double>::iterator it;
	map<string, User*>::iterator itUser;
	int i, totalUsers = userTable.size();
	string userId;

	if (!uId.empty()) {
		userId = uId;
		for (auto currRow: this->expenseShareTable) {
			if (currRow->payerId == userId)
				oweMap[{userTable[userId]->name, userTable[currRow->receiverId]->name}] += currRow->share;
			else if(currRow->receiverId == userId)
				oweMap[{userTable[userId]->name, userTable[currRow->payerId]->name}] -= currRow->share;
		}
	}
	else {
		for (itUser=userTable.begin(); itUser != userTable.end(); itUser++) {
			userId = itUser->first;
			for (auto currRow : this->expenseShareTable) {
				if (currRow->payerId == userId && oweMap.find({ userTable[currRow->receiverId]->name, userTable[userId]->name }) == oweMap.end()) {
					oweMap[{userTable[userId]->name, userTable[currRow->receiverId]->name}] += currRow->share;
				}
				else if (currRow->receiverId == userId && oweMap.find({ userTable[currRow->payerId]->name, userTable[userId]->name }) == oweMap.end())
					oweMap[{userTable[userId]->name, userTable[currRow->payerId]->name}] -= currRow->share;
			}
		}
	}

	if (oweMap.size() != 0) {
		for (it = oweMap.begin();it != oweMap.end();it++) {
			if (it->second > 0) cout << it->first.second << " owes " << it->first.first << ": " << it->second << endl;
			else if (it->second < 0) cout << it->first.first << " owes " << it->first.second << ": " << -(it->second) << endl;
		}
	}
	else cout << "No balances" << endl;

	cout << endl;
}