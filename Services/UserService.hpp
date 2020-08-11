#include<vector>
#include<map>
#include "../Models/User.h"

class UserService {
public:
	map<string, User*> userTable;
	void addUser(User* u);

	map<string, User*> getAllUsers();
};

void UserService::addUser(User* u) {
	this->userTable[u->userId] = u;
}

map<string, User*> UserService::getAllUsers() {
	return this->userTable;
};