#pragma once
#include<string>

using namespace std;

class ExpenseShare
{
public:
	int eId;
	string payerId, receiverId;
	double share;
	ExpenseShare(int eId, string payerId, string receiverId, double share) {
		this->eId = eId;
		this->payerId = payerId;
		this->receiverId = receiverId;
		this->share = share;
	}
};

