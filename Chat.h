#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <locale.h>

#include "Tree.h"
#include"Message.h"

struct UserLoginExp: public std::exception
{
	const char* what() const noexcept override { return "error: Login is busy"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "error: Name is busy"; }
};

class Chat
{
public:
	void startChat();
	bool isChatWork() const { return _isChatWork; }
	std::shared_ptr<User> getCurrentUser() const { return _currentUser; }
	void showLoginMenu();
	void showUserMenu();
	
	void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
	void unreg(char _login[LOGINLENGTH]);

private:
	bool _isChatWork = false;
	std::vector<User> _users;
	std::vector<Message> _messages;
	std::shared_ptr<User> _currentUser = nullptr;
	
	enum CellStatus {
        free,
        engaged,
        deleted
    };

	void login();
	void singUp();
	void showChat() const;
	void showAllUsersName() const;
	void addMessage();
	void deleteLastMessage();
	std::vector<User>& getAllUsers() { return _users; }
	std::vector<Message>& getAllmessages() { return _messages; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByName(const std::string& name) const;
	
	struct AuthData {


        AuthData() :
            login(""),
            pass_sha1_hash(0),
            status(CellStatus::free) {
        }
        ~AuthData() {
            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
        }
        // копирует логин, забирает внутрь хеш
        AuthData(char _login[LOGINLENGTH], uint* sh1) {
            memcpy(login, _login, LOGINLENGTH);
            pass_sha1_hash = sh1;
            status = CellStatus::engaged;
        }
        // копирует всё
        AuthData& operator = (const AuthData& other) {
            memcpy(login, other.login, LOGINLENGTH);

            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];

            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);

            status = other.status;

            return *this;
        }
        char login[LOGINLENGTH];
        uint* pass_sha1_hash;

        CellStatus status;
    };
};
