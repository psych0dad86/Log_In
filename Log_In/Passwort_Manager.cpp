#include "Passwort_Manager.hpp"

Passwort_Manager::Passwort_Manager(): _file_name("accont_psw.txt")
{
	std::cout << "Passwort Manager wurde erstellt" << std::endl;
}

Passwort_Manager::~Passwort_Manager()
{
	std::cout << "Passwort Manager wurde beendet" << std::endl;
}

void Passwort_Manager::set_new_account(const size_t &wert)
{
	_accounts_psw_hash = wert;
	this->_save_in_file(wert);
}

bool Passwort_Manager::check_password(const size_t& wert)
{
    std::ifstream datei(_file_name);

    if (!datei) {
        std::cerr << "PSW Datei konnte nicht geöffnet werden!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return false;
    }

    size_t gespeicherter_hash;
    bool gefunden = false;

    while (datei >> gespeicherter_hash) {
        if (gespeicherter_hash == wert) {
            gefunden = true;
            break;
        }
    }

    datei.close();

    if (gefunden) {
        return true;
    }
    else {
        return false;
    }
}

void Passwort_Manager::_save_in_file(const size_t& wert)
{
	std::ofstream datei(_file_name, std::ios::app);

	if (!datei)
	{
		std::cerr << "PSW Datei konnte nicht geöffnet werden!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

	}
	datei <<  wert << std::endl;

	datei.close();

	std::cout << "PSW daten wurden erflogreich in die Datei geschriegen." << std::endl;

}


