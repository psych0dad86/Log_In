#include "Passwort_Manager.hpp"

Passwort_Manager::Passwort_Manager(): _file_name("accont_psw.txt")
{
	std::cout << "Passwort Manager wurde erstellt" << std::endl;
}

Passwort_Manager::~Passwort_Manager()
{
	std::cout << "Passwort Manager wurde beendet" << std::endl;
}

void Passwort_Manager::set_new_account(const size_t &schlussel, const size_t &wert)
{
	_accounts_psw_hash[schlussel] = wert;
	this->_save_in_file(schlussel, wert);
}

void Passwort_Manager::_save_in_file(const size_t& schlussel, const size_t& wert)
{
	std::ofstream datei(_file_name, std::ios::app);

	if (!datei)
	{
		std::cerr << "PSW Datei konnte nicht geöffnet werden!" << std::endl;

	}
	datei << schlussel << " " << wert << std::endl;

	datei.close();

	std::cout << "PSW daten wurden erflogreich in die Datei geschriegen." << std::endl;

}


