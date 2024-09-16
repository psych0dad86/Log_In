#pragma once
#include "Account.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <map>
#include <functional>
class Verwaltung
{
public:
	Verwaltung();
	~Verwaltung();


	void main_menu();
	bool is_activ();



private:
	void _add_account();
	void _close();
	void _register_account();
	void _input_string(std::string string, std::string& eingabe);
	

	std::vector<Account> _accounts;
	bool _activ;
	std::map<std::string, /*std::hash<*/std::string/*>*/> _exist_accounts;
	//map eirichten
};

