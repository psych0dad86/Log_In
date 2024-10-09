#pragma once
#include "Account.hpp"

class Verwaltung
{
public:
	Verwaltung();
	~Verwaltung();


	void main_menu();
	bool is_activ();
	void print_all_accounts();



private:
	void _log_in();
	bool _log_in_menu(const std::string &email);
	void _change_first_name(const int& index);
	void _change_last_name(const int& index);
	void _change_password(const int& index);
	void _close();
	void _register_account();
	bool _input_string(const std::string string, std::string* eingabe);
	bool _input_psw(const std::string string, std::string* eingabe, std::string* eingabe2);
	void _press_enter();
	void _load_accounts();
	bool _account_exists(const std::string* e_mail);
	void _sleep_2_sec();

	
	

	std::vector<std::unique_ptr<Account>> _accounts;
	bool _activ;
	std::string _file_name;
	Passwort_Manager _passwort_manager;

};

