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

bool Passwort_Manager::update_password(const size_t& alter_hash, const size_t& neuer_hash)
{

	std::string temp_name = "temp_psw.txt";
	std::ifstream original_datei(_file_name);
	std::ofstream temp_datei(temp_name, std::ios::app);
	

	if (!original_datei)
	{
		std::cerr << "Fehler beim oeffnen der original Datei: " << _file_name << std::endl;
		return false;
	}
	if (!temp_datei)
	{
		std::cerr << "Fehler beim oeffnen der original Datei: " << temp_name << std::endl;
		return false;
	}

	size_t gespeicherter_hash;
	bool gefunden = false;

	while (original_datei >> gespeicherter_hash)
	{
		if (gespeicherter_hash == alter_hash)
		{
			temp_datei << neuer_hash << std::endl;
			gefunden = true;
			
		}
		else
		{
			temp_datei << gespeicherter_hash << std::endl;
		}
	}

	original_datei.close();
	temp_datei.close();

	if (gefunden)
	{
		std::remove(_file_name.c_str());
		std::rename(temp_name.c_str(), _file_name.c_str());
		return true;
	}
	else
	{
		std::cerr << "Altes Passwort wurde nicht gefunden!" << std::endl;
		std::remove("temp_psw.txt");
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


