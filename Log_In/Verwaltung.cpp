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
			_sleep_2_sec();
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
		_sleep_2_sec();
	}
	else if (abbruch == false)
	{
		std::hash<std::string> hash_fn;
		_accounts.push_back(std::make_unique<Account>(vorname, nachname, e_mail, _file_name, true));
		_passwort_manager.set_new_account(hash_fn(e_mail + psw1));
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

void Verwaltung::_sleep_2_sec()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
}




void Verwaltung::_log_in()
{
	system("cls");
	std::string email, passwort;
	char escape = 'n';
	bool close = false;

	do
	{
		system("cls");
		std::cout << "Lot In" << std::endl;
		std::cout << "E-mail  : ";
		std::getline(std::cin, email);
		std::cout << "Passwort: ";
		std::getline(std::cin, passwort);

		std::hash<std::string> hash_fn;
		if (_passwort_manager.check_password(hash_fn(email + passwort)))
		{
			
			close = _log_in_menu(email);
		
		}
		else
		{
			std::cout << "\nFalsche Eigabe" << std::endl;
			std::cout << "Noch ein Mal versuchen (j)a, (n)ein: ";
			std::cin.get(escape);
			std::cin.ignore();
		}
	} while (escape == 'j' && close  == false);

	_sleep_2_sec();
	
}

bool Verwaltung::_log_in_menu(const std::string& email)
{
	int index = 0;
	bool menu_activ = true;
	for (index = 0; index < _accounts.size(); index++)
	{
		if (_accounts.at(index)->get_email() == email)
		{
			break;
		}
	}

	do
	{
		system("cls");
		int eingabe = 0;
		std::cout << "Sie sind eigelogt " << _accounts.at(index)->get_first_name();
		std::cout << " " << _accounts.at(index)->get_last_name() << std::endl;
		std::cout << "(1) Vorname aendern" << std::endl;
		std::cout << "(2) Nachname aendern" << std::endl;
		std::cout << "(3) Passwort aendern" << std::endl;
		std::cout << "(4) Ausloggen" << std::endl;

		std::cin >> eingabe;

		switch (eingabe)
		{
		case(1):std::cin.ignore(); _change_first_name(index); break;
		case(2):std::cin.ignore(); _change_last_name(index); break;
		case(3):std::cin.ignore(); _change_password(index); break;
		case(4):std::cin.ignore(); 
			    std::cout << "Sie sind ausgelogged!" << std::endl;
			    return true;
		default: std::cout << "Falsche Eingabe, Bitte noch ein Mal versuchen!" << std::endl;
			_sleep_2_sec();
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(); break;
			}
		}
		_sleep_2_sec();

	}while(menu_activ);

	return true;
}

void Verwaltung::_change_name(const int& index, const std::string& vor_oder_nach_name)
{
	std::string neuer_wert;
	system("cls");
	std::cout << "Neuen " << vor_oder_nach_name << " eingeben: ";
	std::getline(std::cin, neuer_wert);

	std::string temp_file = "temp.txt";
	std::ifstream original_datei(_file_name);
	std::ofstream temp_datei(temp_file);

	if (!original_datei)
	{
		std::cerr << "Fehler beim oeffnen der original Datei: " << _file_name << std::endl;
		_sleep_2_sec();
		return;
	}
	if (!temp_datei)
	{
		std::cerr << "Fehler beim oeffnen der original Datei: " <<  temp_file << std::endl;
		_sleep_2_sec();
		return;
	}

	std::string zeile;
	std::string email = _accounts.at(index)->get_email();

	bool gefunden = false;

	while (std::getline(original_datei, zeile))
	{
		std::istringstream ss(zeile);
		std::string vorname, nachname, e_mail;

		if (ss >> vorname >> nachname >> e_mail)
		{
			if(e_mail == email)
			{
				if (vor_oder_nach_name == "Vorname")
				{
					temp_datei << neuer_wert << " " << nachname << " " << e_mail << std::endl;
					_accounts.at(index)->set_first_name(neuer_wert);
				}
				else if (vor_oder_nach_name == "Nachname")
				{
					temp_datei << vorname << " " << neuer_wert << " " << e_mail << std::endl;
					_accounts.at(index)->set_last_name(neuer_wert);
				}
				gefunden = true;
			}
			else
			{
				temp_datei << zeile << std::endl;
			}
		}
	}

	original_datei.close();
	temp_datei.close();

	if (gefunden)
	{
		std::remove(_file_name.c_str());
		std::rename(temp_file.c_str(), _file_name.c_str());
		std::cout << vor_oder_nach_name << " wurde erfolgreich geaendert!" << std::endl;
	}
	else
	{
		std::cerr << email << " wurde nicht gefunden!" << std::endl;
		std::remove(temp_file.c_str());
	}
	_sleep_2_sec();
}

void Verwaltung::_change_first_name(const int& index)
{
	_change_name(index, "Vorname");
}

void Verwaltung::_change_last_name(const int& index)
{
	_change_name(index, "Nachname");
}

void Verwaltung::_change_password(const int& index)
{
	std::string altes_passwort, neues_passwort1, neues_passwort2;
	std::string email = _accounts.at(index)->get_email();
	std::hash<std::string> hash_fn;

	system("cls");
	std::cout << "Altes Passwort eingeben: ";
	std::getline(std::cin, altes_passwort);

	if (!_passwort_manager.check_password(hash_fn(email + altes_passwort)))
	{
		std::cerr << "Das alte Passwort ist falsch!" << std::endl;
		_sleep_2_sec();
		return;
	}

	
	if (_input_psw("Neues Passwort: ", &neues_passwort1, &neues_passwort2)) {
		std::cerr << "Passwort-Eingabe wurde abgebrochen." << std::endl;
		return;
	}

	size_t neuer_hash = hash_fn(email + neues_passwort1);
	

	if (_passwort_manager.update_password(hash_fn(email + altes_passwort), neuer_hash))
	{
		std::cout << "Passort wurde erfolgreich geaendert!" << std::endl;
	}
	else
	{
		std::cerr << "Fehler beim Aendern des Passworts." << std::endl;
	}

	_sleep_2_sec();

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
	case(1):std::cin.ignore(); this->_log_in(); break;
	case(2):std::cin.ignore(); this->_register_account(); break;
	case(3):std::cin.ignore(); this->_close(); return;
	case(4):std::cin.ignore(); this->print_all_accounts(); break;
	default: std::cout << "Falsche Eingabe, Bitte noch ein Mal versuchen!" << std::endl;
			 _sleep_2_sec();

			 if (std::cin.fail())
			 {
			 	std::cin.clear();
			 	std::cin.ignore(); break;
			 }
	}
	
}

