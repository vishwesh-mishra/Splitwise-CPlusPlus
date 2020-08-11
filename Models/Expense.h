#pragma once
#include<string>

using namespace std;

class Expense
{
public:
	int eId;
	string payerId;
	double expense;
	Expense(int eId, string payerId, double expense) {
		this->eId = eId;
		this->payerId = payerId;
		this->expense = expense;
	}
};

