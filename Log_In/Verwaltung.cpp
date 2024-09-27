#include "Verwaltung.hpp"

Verwaltung::Verwaltung(): _file_name("accounts.txt")
{
	std::cout << "Verwaltung wurde erstellt." << std::endl;
	_activ = true;
	this->_load_accounts();
	this->_press_enter();

}

Verwaltung::~Verwaltung()
{
	system("cls");
	std::cout << "Verwaltung wurde beendet." << std::endl;
}

bool Verwaltung::is_activ()
{
	return _activ;
}

void Verwaltung::print_all_accounts()
{
	system("cls");
	for (auto& account : _accounts)
	{
		account->print_account_details();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	this->_press_enter();
}

void Verwaltung::_close()
{
	_activ = false;
}

void Verwaltung::_register_account()
{
	system("cls");
	bool abbruch = false;
	std::string vorname = "***", nachname = "***", e_mail = "***", psw1 = "***", psw2 = "***";
	std::array<std::string, 4> eingabe_label = {
		"Vorname : ",
		"Nachname: ",
		"E-Mail  : ",
		"Passwort: "
	};

	std::array<std::string*, 5> string_referenzen{ &vorname, &nachname, &e_mail, &psw1,&psw2 };

	for (int i = 0; i < eingabe_label.size(); i++)
	{
		
		if (abbruch == true)
		{
			system("cls");
			printf("Registrierung wurde abgebrochen!\n");
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		else if (eingabe_label[i] == "Passwort: ")
		{
			abbruch = _input_psw(eingabe_label.at(i), string_referenzen.at(i), string_referenzen.at(i+1));
		}
		else
			abbruch =_input_string(eingabe_label.at(i), string_referenzen.at(i));

	}

	if (abbruch == true)
	{
		system("cls");
		printf("Registrierung wurde abgebrochen!\n");
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else if (abbruch == false)
	{
		std::hash<std::string> hash_fn1, hash_fn2;

		_accounts.push_back(std::make_unique<Account>(vorname, nachname, e_mail, _file_name, true));
		_passwort_manager.set_new_account(hash_fn1(e_mail), hash_fn2(psw1 + e_mail));
		printf("Registrierung war erfolgreich!\n");
		this->_press_enter();
	}

}

bool Verwaltung::_input_string(const std::string string, std::string* eingabe)
{
	bool flag = false;
	char escape = '?';
	std::string input = " ";
	while (flag == false)
	{
		
		system("cls");
		std::cout << string;
		std::getline(std::cin, *eingabe);
		std::cout << "Ist die Eingabe " << *eingabe << " richtig?" << std::endl;
		std::cout << "\n(j)a, (n)ein, (a)bbrechen: ";
		std::cin.get(escape);
		std::cin.ignore();
		
	
	
		if (string == "E-Mail  : " && (escape == 'j' || escape == 'J'))
		{
			// >>>>>>>>>>>>> hier vergleich machen mit Account.
			if (_account_exists(eingabe) == true)
			{
				
				std::cout << "\nE-Mail Adresse schon vergeben." << std::endl;
				std::cout << "Andere E-Mail eingeben (j)a, (a)bbrechen: ";
				std::cin.get(escape);
				std::cin.ignore();
				if (escape == 'j')
				{
					continue;
				}
					
			}
			
		}

		if (escape == 'j')
		{
			flag = true;


		}
		else if (escape == 'a')
		{

			return true;
		}


	}

	return false;
}

bool Verwaltung::_input_psw(const std::string string, std::string* eingabe, std::string* eingabe2)
{
	bool psw_match = false;
	char escape = '?';
	std::string input1, input2;

	while (psw_match == false)
	{
		system("cls");
		
		std::cout << string;
		std::getline(std::cin, input1);
		std::cout << string;
		std::getline(std::cin, input2);
		*eingabe = input1;
		*eingabe2 = input2;

		if (input1.length() < 10)
		{
			std::cout << "\n\nDas Passwort muss mindestens 10 Zeichen haben,\nversuchen Sie es noch ein Mal" << std::endl;
			std::cout << "Passwort noch ein Mal eingeben (j)a, (n)ein: ";
			std::cin.get(escape);
		}
		else if (*eingabe != *eingabe2)
		{
			std::cout << "\n\nDie Passwoerter stimmen nicht ueber ein,\nversuchen Sie es noch ein Mal" << std::endl;
			std::cout << "Passwort noch ein Mal eingeben (j)a, (n)ein: ";
			std::cin.get(escape);
		}
		else
		{
			psw_match = true;
			return false;
		}
		
		if (escape != 'j')
		{
			
			return true;
		}
		std::cin.ignore();
	}
	return false;
}

void Verwaltung::_press_enter()
{
	char escape = '*';
	std::cout << "Druecken Sie Enter um weiter zu kommen." << std::endl;
	escape = std::cin.get();
}

void Verwaltung::_load_accounts()
{
	std::ifstream datei(_file_name);
	
	if (!datei)
	{
		std::cerr << "Die Datei konnte nicht geöffnte werden!" << std::endl;
	
	}

	std::string zeile;
	
	while (std::getline(datei, zeile))
	{
		std::istringstream ss(zeile);
		std::string vorname, nachname, e_mail;

		if (ss >> vorname >> nachname >> e_mail)
		{
			_accounts.push_back(std::make_unique<Account>(vorname, nachname, e_mail, _file_name, false));
			
		}
		else
		{
			std::cerr << "Fehler beim einlesen der Zeile: " << zeile << std::endl;
		}
		
	}
	datei.close();
}

bool Verwaltung::_account_exists(const std::string* e_mail)
{
	for (const auto &mail : _accounts)
	{
		if (mail->get_email() == *e_mail)
		{
			return true;
		}
	}
	return false;
}


void Verwaltung::main_menu()
{
	system("cls");
	int eingabe = 0;
	std::cout << "Haupt Menue was moechten sie machen" << std::endl;
	std::cout << "(1) einlogen" << std::endl;
	std::cout << "(2) regestrieren" << std::endl;
	std::cout << "(3) beenden" << std::endl;
	std::cout << "(4) alle Acconts ausgeben" << std::endl;
	
	std::cin >> eingabe;
	
	switch (eingabe)
	{
	case(1): break;
	case(2):std::cin.ignore(); this->_register_account(); break;
	case(3):std::cin.ignore(); this->_close(); break;
	case(4):std::cin.ignore(); this->print_all_accounts();
	default: std::cout << "Falsche Eingabe, Bitte noch ein Mal versuchen!" << std::endl; break;
	}


}

