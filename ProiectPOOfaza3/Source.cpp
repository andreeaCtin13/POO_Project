#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#include "Angajat.h"
#include "Medic.h"
#include "Asistent.h"
#include "Consultatie.h"
#include "Pacient.h"
#include "Colectie.h"
#include "FileManager.h"
#include "Menu.h"
#include "Colectie.h"
#include "Rezident.h"
#include "PacientExtins.h"
#include "ConsultatieExtinsa.h"
using namespace std;

// int main() {
int main(int argc, char* argv[]) {
	if (argc == 6) {
		displayMenu(argv[1], argv[2], argv[3], argv[4], argv[5]);
	}
	else {
		cout << "Nu ati introdus fisierele de interes ca si parametru in linia de comanda\n";
		cout << "Sunt necesare 5 fisiere text cu date aferente pentru:\n";
		cout << "- Pacientii din cadrul centrului medical\n";
		cout << "- Consultatiile programate in cadrul centrului medical\n";
		cout << "- Medicii din cadrul centrului medical\n";
		cout << "- Angajatii din cadrul centrului medical\n";
		cout << "- Asistentii din cadrul centrului medical\n";
		cout << "\nORDINEA FISIERELOR TREBUIE SA FIE IN CONFORMITATE CU ORDINEA DE MAI SUS\n";
	}
	
	//displayMenu("PacientiDeAdaugat.txt", "ConsultatiiDeAdaugat.txt", "MediciDeAdaugat.txt", "AngajatiDeAdaugat.txt", "AsistentiDeAdaugat.txt");
}