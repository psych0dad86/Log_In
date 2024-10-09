#include "Account.hpp"


Account::Account(std::string vorname, std::string nachname, std::string e_mail, std::string file_name, bool new_account):
	_vorname(vorname), _nachname(nachname), _e_mail(e_mail), _file_name(file_name), _new_account(new_account)
{

	if (_new_account == true)
	{
		std::cout << "Account fuer " << _vorname << " " << _nachname << " wurde erstellt!" << std::endl;
		this->_save_new_account();
	}
	else
	{
		std::cout << "Account fuer " << _vorname << " " << _nachname << " wurde geladen!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}
Account::~Account()
{
	std::cout << "Account von " << _vorname << " " << _nachname << " wurde geloescht!" << std::endl;
}

void Account::print_account_details()
{
	std::cout << "Vorname : " << _vorname << std::endl;
	std::cout << "Nachname: " << _nachname << std::endl;
	std::cout << "E-Mail  : " << _e_mail << std::endl;
	std::cout << std::endl;

}

const std::string& Account::get_email() const
{
	return _e_mail;
}

const std::string& Account::get_first_name() const
{
	return _vorname;
}

const std::string& Account::get_last_name() const
{
	return _nachname;
}

void Account::_save_new_account()
{
	std::ofstream datei(_file_name, std::ios::app);

	if (!datei)
	{
		std::cerr << "Account Datei konnte nicht geöffnet werden!" << std::endl;
	
	}
	datei << _vorname << " " << _nachname << " " << _e_mail << std::endl;

	datei.close();

	std::cout << "Account Daten wurden erflogreich in die Datei geschriegen." << std::endl;
	_new_account = false;
}
