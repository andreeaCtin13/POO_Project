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

int main(){
//int main(int argc, char* argv[]) {
/*	if (argc == 6) {
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
	*/
	int* note;
	note = new int[4];
	note[0] = 10;
	note[1] = 9;
	note[2] = 10;
	note[3] = 10;
	Rezident s("Facultatea de Medicina UMF Carol Davila", note, 4);
	s.setNume("Ionela");
	s.setPrenume("Viorica");
	Angajat *a;
	Angajat a1("Andreea", "Heheh", 5000.7, 28);
	Medic m("Ana", "mama", 7899, 28, "oftalmolog");
	Asistent a2("Plang", "Plang", 4000, 23, 8);

	a = new Angajat[3];
	a[0] = a1;
	a[1] = m;
	a[2] = a2;
	//a[3] = s;
	Pacient p("andreea", "maria", "0727590226", 20, "Aleea Gornesti nr 1", true);
	Pacient p2("ana", "deaconu", "0727590226", 20, "Aleea Gornesti nr 1", true);

	string* alerg;
	alerg = new string[3];
	alerg[0] = "Capsuni";
	alerg[1] = "Miere";
	alerg[2] = "Ciocolata";
	set<string> boli;
	for (int i = 0; i < 10; i++) {
		string st = to_string(i);
		st = st + "anorexie";
		boli.insert(st);
	}
	PacientExtins pac(p, true, alerg, 3,boli);
	PacientExtins pac2(p2, false, alerg, 0, boli);
	//pac = pac2;

	Angajat** lista;

	lista = new Angajat*[4];
	lista[0] = new Angajat(a1);
	lista[0] = &a1;
	lista[1] = new Asistent(a2);
	lista[1] = &a2;
	lista[2] = new Medic(m);
	lista[2] = &m;
	ofstream f1, f2, f3;
	f1.open("haha " + 1);
	f2.open("haha " + 2);
	f3.open("haha " + 3);

	for (int i = 0; i < 3; i++) {
		cout << *lista[i];
	}

	Medic m2 = m;
	lista[0]->creareRaport(f1);
	lista[1]->creareRaport(f2);
	lista[2]->creareRaport(f3);


	//cin >> pac3;
	//cout << pac3;
	//displayMenu("PacientiDeAdaugat.txt", "ConsultatiiDeAdaugat.txt", "MediciDeAdaugat.txt", "AngajatiDeAdaugat.txt", "AsistentiDeAdaugat.txt");
}