#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <array>
#include <fstream>
#include <vector>
#include <sstream>

class Passwort_Manager
{
public:
	Passwort_Manager();
	~Passwort_Manager();

	void set_new_account(const size_t &wert);
	bool check_password(const size_t& wert);


private:
	void _save_in_file(const size_t& wert);
	size_t _accounts_psw_hash;
	std::string _file_name;
};

