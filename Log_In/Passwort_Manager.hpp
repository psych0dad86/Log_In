#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <map>
#include <functional>
#include <array>
#include <fstream>

class Passwort_Manager
{
public:
	Passwort_Manager();
	~Passwort_Manager();

	void set_new_account(const size_t &schlussel, const size_t &wert);


private:
	void _save_in_file(const size_t& schlussel, const size_t& wert);
	std::map<size_t, size_t> _accounts_psw_hash;
	std::string _file_name;
};

