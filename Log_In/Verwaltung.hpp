#pragma once
#include "Account.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <map>
#include <functional>
#include <array>
#include <sstream>
class Verwaltung
{
public:
	Verwaltung();
	~Verwaltung();


	void main_menu();
	bool is_activ();
	void print_all_accounts();



private:
	void _close();
	void _register_account();
	bool _input_string(const std::string string, std::string* eingabe);
	bool _input_psw(const std::string string, std::string* eingabe, std::string* eingabe2);
	void _press_enter();
	void _load_accounts();
	bool _account_exists(const std::string* e_mail);
	

	std::vector<std::unique_ptr<Account>> _accounts;
	bool _activ;
	std::string _file_name;
	Passwort_Manager _passwort_manager;

};

