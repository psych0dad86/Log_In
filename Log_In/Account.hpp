#pragma once
#include <string>
#include <iostream>
class Account
{
public:
	Account(std::string vorname, std::string nachname, std::string e_mail);
	~Account();



private:
	std::string _vorname;
	std::string _nachname;
	std::string _e_mail;
};

