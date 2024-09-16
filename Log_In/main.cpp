#include "Verwaltung.hpp"

int main()
{
	Verwaltung verwaltung;
	
	do
	{
		verwaltung.main_menu();
	} while (verwaltung.is_activ());

	return 0;
}