#include "Verwaltung.hpp"

Verwaltung::Verwaltung()
{
	std::cout << "Verwaltung wurde erstellt." << std::endl;
	_activ = true;
	_exist_accounts["wurst@hans"] = "lol";
	//check die email und dann account ertellen
}

Verwaltung::~Verwaltung()
{
	std::cout << "Verwaltung wurde beendet." << std::endl;
}

bool Verwaltung::is_activ()
{
	return _activ;
}

void Verwaltung::_close()
{
	_activ = false;
}

void Verwaltung::_register_account()
{
	system("cls");
	std::string vorname = "***", nachname = "***", e_mail = "***", psw1 = "***", psw2 = "***";
	bool psw_match = false;

	std::cout << "Account Registrierung" << std::endl;

	_input_string("Vorname : ", vorname);
	_input_string("Nachname: ", nachname);
	_input_string("E-Mail  : ", e_mail);

	while (psw_match == false)
	{
		_input_string("Passwort ", psw1);
		_input_string("Geben Sie das Passwort zur Kontrolle ein: ", psw2);
		if (psw1.length() < 10)
		{
			std::cout << "\n\nDas Passwort muss mindestens 10 Zeichen haben,\nversuchen Sie es noch ein Mal" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		else if (psw1 != psw2)
		{
			std::cout << "\n\nDie Passwoerter stimmen nicht ueber ein,\nversuchen Sie es noch ein Mal" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		else
			psw_match = true;

	}



}

void Verwaltung::_input_string(std::string string, std::string& eingabe)
{
	bool flag = false;
	char escape = '?';
	while (flag == false)
	{
		system("cls");
		std::cout << string;
		std::cin >> eingabe;
		std::cout << "Ist die Eingabe " << eingabe << " richtig?" << std::endl;
		std::cout << "\nWenn ja geben sie j ein, sonnst Enter drücken!";
		std::cin >> escape;
	
		if (string == "E-Mail  : " && (escape == 'j' || escape == 'J'))
		{
			escape = '?';
			if (_exist_accounts.find(eingabe) != _exist_accounts.end())
			{
				std::cout << "\nE-Mail Adresse schon vergeben." << std::endl;
				std::cout << "Geben sie j ein um eine andere E-Mail einzugeben, sonnst Enter druecken!";
				std::cin >> escape;
			}
				
		}
		
		if (escape == 'j' || escape == 'J')
		{
			flag = true;
		}

	}

}


void Verwaltung::main_menu()
{
	system("cls");
	int eingabe = 0;
	std::cout << "Haupt Menue was moechten sie machen" << std::endl;
	std::cout << "(1) einlogen" << std::endl;
	std::cout << "(2) regestrieren" << std::endl;
	std::cout << "(3) beenden" << std::endl;
	
	std::cin >> eingabe;

	switch (eingabe)
	{
	case(1): break;
	case(2): this->_register_account(); break;
	case(3): this->_close(); break;
	default: std::cout << "Falsche Eingabe, Bitte noch ein Mal versuchen!" << std::endl; break;
	}


}

void Verwaltung::_add_account()
{
}

