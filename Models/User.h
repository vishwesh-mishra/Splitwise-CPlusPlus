#pragma once
#include<string>

using namespace std;

class User {
public:
	string userId, name, email;
	int mobileNum;
	User(string userId, string name, string email, int mobileNum) {
		this->userId = userId;
		this->name = name;
		this->email = email;
		this->mobileNum = mobileNum;
	}
};