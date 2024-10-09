#pragma once
#include "Passwort_Manager.hpp"

class Account
{
public:
	Account(std::string vorname, std::string nachname, std::string e_mail,
		std::string file_name, bool new_account);
	~Account();

	void print_account_details();
	const std::string& get_email() const;
	const std::string& get_first_name() const;
	const std::string& get_last_name() const;

	



private:
	void _save_new_account();

	std::string _vorname;
	std::string _nachname;
	std::string _e_mail;
	std::string _file_name;
	bool _new_account;	

};

