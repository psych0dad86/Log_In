#include "Account.hpp"



Account::Account(std::string vorname, std::string nachname, std::string e_mail)
{
}

Account::~Account()
{
	std::cout << "Account von " << _vorname << " " << _nachname << " wurde gel�scht!" << std::endl;
}
