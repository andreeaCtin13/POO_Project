#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Pacient.h"
#include "Consultatie.h"
#include "Medic.h"
#include "Asistent.h"
#include "Angajat.h"
#include "FileManager.h"
#include "Colectie.h"
#include "Data.h"
#include "ConsultatieExtinsa.h"
#include "PacientExtins.h"
#include "Rezident.h"


using namespace std;

void actualizareAngajati(FileManager &medici, FileManager &asistenti, FileManager &angajati) {
	medici.setColectieFile();
	asistenti.setColectieFile();

	int lungime_asistenti = asistenti.getAsistenti().getNrObiecte();
	int lungime_medici = medici.getMedici().getNrObiecte();
	int lungime_angajati = lungime_medici + lungime_asistenti;
	Angajat* angajati_array = new Angajat[lungime_angajati];
	for (int i = 0; i < lungime_medici; i++) {
		angajati_array[i] = medici.getMedici()[i];
	}
	for (int i = lungime_medici; i < lungime_angajati; i++) {
		angajati_array[i] = asistenti.getAsistenti()[i - lungime_medici];
	}

	angajati.setColectieAngajati(angajati_array, lungime_angajati);
}


void actualizareConsultatii(FileManager& consultatii, FileManager& pacienti) {
	pacienti.setColectieFile();
	int nrPacienti = pacienti.getPacienti().getNrObiecte();
	int nrConsultatii = 0;
	for (int i = 0; i < nrPacienti; i++) {
		nrConsultatii += pacienti.getPacienti()[i].getNrConsultatii();
	}
	Consultatie* c = new Consultatie[nrConsultatii];
	int index = 0;
	for (int i = 0; i < nrPacienti; i++) {
		for (int j = 0; j < pacienti.getPacienti()[i].getNrConsultatii(); j++) {
			c[index] = pacienti.getPacienti()[i].getViitoareConsultatie()[j];
			index++;
		}
	}
	consultatii.setColectieConsultatii(c, index);
}

void displayMenu(string filePacienti, string fileConsultatii, string fileMedici, string fileAngajati, string fileAsistenti) {
	
	FileManager pacienti(filePacienti, "DatePacienti.txt", "RaportPacienti.txt", "Pacienti");
	FileManager consultatii(fileConsultatii, "DateConsultatii.txt", "RaportConsultatii.txt", "Consultatii");
	FileManager medici(fileMedici, "DateMedici.txt", "RaportMedici.txt", "Medici");
	FileManager asistenti(fileAsistenti, "DateAsistenti.txt", "RaportAsistenti.txt", "Asistenti");
	FileManager angajati(fileAngajati, "DateAngajati.txt", "RaportAngajati.txt", "Angajati");
	
	int i = 0; 
	pacienti.closeFileInTxt();
	actualizareConsultatii(consultatii, pacienti);
	consultatii.closeFileInTxt();

	medici.setColectieFile();
	asistenti.setColectieFile();

	pacienti.closeFileInTxt();
	asistenti.closeFileInTxt();
	medici.closeFileInTxt();

	actualizareAngajati(medici, asistenti, angajati);
	angajati.closeFileInTxt();

	while (i != 7) {
		cout << "Aveti urmatoarele optiuni: \n";
		cout << "1 - Generati un raport\n";
		cout << "2 - Scrieti in fisier text datele colectiilor\n";
		cout << "3 - Actualizati datele pentru o inregistrare\n";
		cout << "4 - Adaugarea unei noi inregistrari\n";
		cout << "5 - Salvati datele aplicatiei in fisiere binare\n";
		cout << "6 - Adaugati inregistrari de tip Pacient din fisiere csv\n";
		cout << "7 - Testati array-ul de pointeri aferent familiei Angajat, Medic, Asistent si Rezident\n";
		cout << "8 - Testati functionalitatile extinderilor\n";
		cout << "9 - Accesati un fisier de la o anumita cale, in cazul uneia dintre colectii\n";
		cout << "10 - Iesiti\n";
		cin >> i;

		if (i == 1) {
			int ok = 1;
			do {
				cout << "Ati ales optiunea de a genera un raport. Alegeti subiectul raportului:\n";
				cout << "1 - Pacienti\n";
				cout << "2 - Consultatii\n";
				cout << "3 - Medici\n";
				cout << "4 - Asistenti\n";
				cout << "5 - Angajati\n";
				cout << "6 - Inapoi\n";
				int j;
				cin >> j;
				if (j == 1) {
					ok = 0;
					pacienti.closeFileInTxt();
					pacienti.setColectieFile();
					pacienti.generareRaportPacienti();
					cout << "A fost generat raportul sub numele de RaportPacienti.txt\n";
				}
				else if (j == 2) {
					ok = 0;
					consultatii.closeFileInTxt();
					pacienti.closeFileInTxt();
					actualizareConsultatii(consultatii, pacienti);
					consultatii.generareRaportConsultatii();
					cout << "A fost generat raportul sub numele de RaportConsultatii.txt\n";
				}
				else if (j == 3) {
					ok = 0;
					medici.closeFileInTxt();
					medici.setColectieFile();
					medici.generareRaportMedici();
					cout << "A fost generat raportul sub numele de RaportMedici.txt\n";
				}
				else if (j == 4) {
					ok = 0;
					asistenti.closeFileInTxt();
					asistenti.setColectieFile();
					asistenti.generareRaportAsistenti();
					cout << "A fost generat raportul sub numele de RaportAsistenti.txt\n";
				}
				else if (j == 5) {
					ok = 0;
					medici.closeFileInTxt();
					asistenti.closeFileInTxt();
					actualizareAngajati(medici, asistenti, angajati);
					angajati.generareRaportAngajati();
					cout << "A fost generat raportul sub numele de RaportAngajati.txt\n";
				}
				else if (j == 6) {
					ok = 0;
				}
				else {
					cout << "Ati introdus o comanda invalida. Mai incercati o data:\n";
				}
			} while (ok == 1);
		}
		else if (i == 2) {
			int ok = 1;
			do {
				cout << "Ati ales optiunea de a scrie in fisier text datele colectiilor. Alegeti colectia de interes:\n";
				cout << "1 - Pacienti\n";
				cout << "2 - Consultatii\n";
				cout << "3 - Medici\n";
				cout << "4 - Asistenti\n";
				cout << "5 - Angajati\n";
				cout << "6 - Inapoi\n";
				int j;
				cin >> j;
				if (j == 1) {
					ok = 0;
					if (pacienti.getPacienti().getNrObiecte() != 0) {
						pacienti.closeFileInTxt();
						pacienti.setColectieFile();
						pacienti.printPacienti();
					}
					else {
						cout << "Nu exista niciun pacient inregistrat\n";
					}
				}
				else if (j == 2) {
					ok = 0;
					if (consultatii.getConsultatie().getNrObiecte() != 0) {
						consultatii.closeFileInTxt();
						pacienti.closeFileInTxt();
						actualizareConsultatii(consultatii, pacienti);
						consultatii.printConsultatii();
					}
					else {
						cout << "Nu exista nicio consultatie inregistrata\n";
					}
				}
				else if (j == 3) {
					ok = 0;
					if (medici.getMedici().getNrObiecte() != 0) {
						medici.closeFileInTxt();
						medici.setColectieFile();
						medici.printMedici();
					}
					else {
						cout << "Nu exista niciun medic inregistrat\n";
					}
				}
				else if (j == 4) {
					ok = 0;
					if (asistenti.getAsistenti().getNrObiecte() != 0) {
						asistenti.closeFileInTxt();
						asistenti.setColectieFile();
						asistenti.printAsistenti();
					}
					else {
						cout << "Nu exista niciun asistent inregistrat\n";
					}
				}
				else if (j == 5) {
					ok = 0;
					asistenti.closeFileInTxt();
					medici.closeFileInTxt();

					actualizareAngajati(medici, asistenti, angajati);
					if (angajati.getAngajati().getNrObiecte() != 0) {
						angajati.printAngajati();
					}
					else {
						cout << "Nu exista niciun angajat inregistrat\n";
					}
				}
				else if (j == 6) {
					ok = 0;
				}
				else {
					cout << "Ati introdus o comanda invalida. Mai incercati o data:\n";
				}
			} while (ok == 1);
		}
		else if (i == 3) {
			int ok = 1;
			do {
				cout << "Ati ales optiunea de a modifica datele dintr-un anumit fisier. Alegeti colectia de interes:\n";
				cout << "1 - Pacienti (orice modificare aplicata consultatiilor pacientilor va fi vizibila si in cadrul fisierelor aferente consultatiilor centrului medical)\n";
				cout << "2 - Medici (orice modificare aplicata medicilor, va fi vizibila si in fisierele aferente angajatilor centrului medical)\n";
				cout << "3 - Asistenti (orice modificare aplicata medicilor, va fi vizibila si in fisierele aferente angajatilor centrului medical)\n";
				cout << "4 - Inapoi\n";
				int j;
				cin >> j;
				if (j == 1) {
					pacienti.closeFileInTxt();
					pacienti.setColectieFile();
					int numarPacienti = pacienti.getPacienti().getNrObiecte();
					cout << "Ati ales sa modificati date referitoare la pacientii centrului medical\n";
					int ok = 1;
					Pacient* p;
					p = new Pacient[numarPacienti];
					for (int i = 0; i < numarPacienti; i++) {
						p[i] = pacienti.getPacienti().getColectie()[i];
					}
					do {
						cout << "Introduceti indexul pacientului de interes. Tineti cont de faptul ca in momentul de fata sunt inregistrati " << numarPacienti << " pacienti. Indexarea se face de la 0." << endl;
						int index;
						cin >> index;
						if (index < numarPacienti) {
							cout << "Alegeti ce doriti sa modificati: \n";
							cout << "1 - Modificati numele pacientului\n";
							cout << "2 - Modificati prenumele pacientului\n";
							cout << "3 - Cresteti varsta pacientului\n";
							cout << "4 - Modificati adresa pacientului\n";
							cout << "5 - Modificati numarul de telefon al pacientului\n";
							cout << "6 - Modificati statusul asigurarii de sanatate a pacientului\n";
							cout << "7 - Adaugati o plata la istoricul de plati ale pacientului\n";
							cout << "8 - Programati o noua consultatie pacientului\n";
							cout << "9 - Semnalati moartea pacientului\n";
							cout << "10 - Schimbati identitatea pacientului\n";
							cout << "11 - Inapoi\n";
							int instr;
							cin >> instr;
							if (instr == 1) {
								ok = 0;
								string nume;
								cout << "Numele actual al pacientului este: " << pacienti.getPacienti()[index].getNume() << endl;
								cout << "Introduceti noul nume al pacientului\n";
								cin >> nume;
								p[index].setNume(nume);
							}
							else if (instr == 2) {
								ok = 0;
								string prenume;
								cout << "Prenumele actual al pacientului este: " << p[index].getPrenume() << endl;
								cout << "Introduceti noul prenume al pacientului\n";
								cin >> prenume;
								p[index].setPrenume(prenume.c_str());
							}
							else if (instr == 3) {
								ok = 0;
								cout << "Vechea valoare a varstei pacientului este: " << p[index].getVarsta() << endl;
								//p[index]++;
								cout << "Actuala varsta a pacientului este: " << p[index].getVarsta() << endl;
							}
							else if (instr == 4) {
								ok = 0;
								cout << "Actuala adresa a pacientului este: " << endl;
								cout << p[index].getAdresa();
								getchar();
								cout << "Introduceti noua adresa a pacientului:\n";
								char adresa[60];
								cin.getline(adresa, strlen(adresa));
								p[index].setAdresa(adresa);
							}
							else if (instr == 5) {
								ok = 0;
								cout << "Actualul numar de telefon al pacientului este: " << p[index].getPhoneNumber() << endl;
								cout << "Introduceti noul numar de telefon al pacientului:\n";
								char telefon[10];
								cin >> telefon;
								p[index].setPhoneNumber(telefon);
							}
							else if (instr == 6) {
								ok = 0;
								bool eAsig = p[index].getEsteAsigurat();
								if (eAsig) {
									cout << "Pacientul a fost asigurat pana in momentul de fata.\n";
								}
								else {
									cout << "Pacientul nu a fost asigurat pana in momentul de fata.\n";
								}
								p[index].setEsteAsigurat(!eAsig);
								cout << "Statusul asigurarii a fost moficiat.\n";
							}
							else if (instr == 7) {
								ok = 0;
								cout << "Introduceti noua valoarea noii plati:\n";
								float plata;
								cin >> plata;
								int nrPlati = p[index].getNrPlati() + 1;
								float* vectorPlati = new float[nrPlati];
								for (int i = 0; i < nrPlati - 1; i++) {
									vectorPlati[i] = p[index].getIstoricPlati()[i];
								}
								vectorPlati[nrPlati - 1] = plata;
								p[index].setNrPlati(nrPlati);
								p[index].setIstoricPlati(vectorPlati);
								cout << "Platile au fost actualizate.\n";
							}
							else if (instr == 8) {
								ok = 0;
								int okay = 1;
								do {
									cout << "Introduceti ziua in care va avea loc consultatia:\n";
									int zi;
									cin >> zi;
									cout << "Introduceti luna in care va avea loc consultatia:\n";
									int luna;
									cin >> luna;
									cout << "Introduceti anul in care va avea loc consultatia:\n";
									int an;
									cin >> an;
									cout << "Introduceti ora la care va avea loc consultatia:\n";
									int ora;
									cin >> ora;
									int reusita = p[index].adaugaConsultatieStandard(zi, luna, an, ora);
									if (reusita == 1) {
										cout << "Consultatia a fost programata.\n";
										okay = 0;
									}
									else {
										cout << "Datele consultatiei nu sunt valide. Incercati din nou.\n";
									}
								} while (okay == 1);
							}
							else if (instr == 9) {
								p[index].Moare();
								cout << "A fost inregistrata moartea pacientului.\n";
							}
							else if(instr == 10){
								p[index].SchimbaIdentitatea();
								cout << "A fost inregistrata schimbarea identitatii pacientului.\n";
							}
							else if (instr == 11) {
								ok = 0;
							}
							else {
								cout << "Ati introdus o comanda invalida. Mai incercati o data.\n";
							}
							pacienti.setColectiePacienti(p, numarPacienti);
							pacienti.updateColllection(pacienti.getPacienti());
							pacienti.closeFileInTxt();
							actualizareConsultatii(consultatii, pacienti);
						}
						else {
							cout << "Nu ati introdus un index valid. Incercati din nou.";
						}
					} while (ok == 1);
					pacienti.closeFileInTxt();
					pacienti.setColectieFile();
					pacienti.printPacienti();
				}
				else if (j == 2) {
					medici.closeFileInTxt();
					medici.setColectieFile();
					int numarMedici = medici.getMedici().getNrObiecte();
					cout << "Ati ales sa modificati date referitoare la medicii centrului medical\n";
					int ok = 1;
					Medic* m;
					m = new Medic[numarMedici];
					for (int i = 0; i < numarMedici; i++) {
						m[i] = medici.getMedici().getColectie()[i];
					}
					do {
						cout << "Introduceti indexul medicului de interes. Tineti cont de faptul ca in momentul de fata sunt inregistrati " << numarMedici << " medici. Indexarea se face de la 0." << endl;
						int index;
						cin >> index;
						if (index < numarMedici) {
							cout << "Alegeti ce doriti sa modificati: \n";
							cout << "1 - Modificati numele medicului\n";
							cout << "2 - Modificati prenumele medicului\n";
							cout << "3 - Cresteti varsta medicului\n";
							cout << "4 - Modificati salariul medicului\n";
							cout << "5 - Cresteti vechimea medicului in cadrul centrului si actualizati istoricurile\n";
							cout << "6 - Actualizati istoricul lunar, intrucat am intrat intr-un nou an\n";
							cout << "7 - Modificati specializarea medicului\n";
							cout << "8 - Adauga un bonus medicului\n";
							cout << "9 - Scadeti salariul medicului\n";
							cout << "10 - Semnalati moartea medicului\n";
							cout << "11 - Schimbati identitatea medicului\n";
							cout << "12 - Inapoi\n";
							int j;
							cin >> j;
							if (j == 1) {
								ok = 0;
								string nume;
								cout << "Numele actual al medicului este: " << m[index].getNume() << endl;
								cout << "Introduceti noul nume al medicului: \n";
								cin >> nume;
								m[index].setNume(nume.c_str());
							}
							else if (j == 2) {
								ok = 0;
								string prenume;
								cout << "Prenumele actual al medicului este: " << m[index].getPrenume() << endl;
								cout << "Introduceti noul prenume al medicului:\n";
								cin >> prenume;
								m[index].setPrenume(prenume);
							}
							else if (j == 3) {
								ok = 0;
								cout << "Vechea varsta a medicului este " << m[index].getVarsta() << endl;
								m[index].setVarsta(m[index].getVarsta() + 1);
								cout << "Noua varsta a medicului este " << m[index].getVarsta() << endl;
							}
							else if (j == 4) {
								ok = 0;
								cout << "Salariul actual al medicului este de " << m[index].getSalariu() << endl;
								cout << "Introduceti noul salariu al medicului: \n";
								float  salariu;
								cin >> salariu;
								m[index].setSalariu(salariu);
								cout << "Salariul a fost actualizat\n";
							}
							else if (j == 5) {
								ok = 0;
								m[index].setVechime(m[index].getVechime() + 1);
								//sa vad cum fac sau las asa
							}
							else if (j == 6) {
								ok = 0;
								int salariu;
								cout << "Introduceti salariul medicului de anul acesta\n";
								cin >> salariu;
								m[index].OneYearPassed(salariu);
								cout << "Istoricul lunar a fost actualizat\n";
							}
							else if (j == 7) {
								ok = 0;
								string specializare;
								cout << "Actuala specializare a medicului este " << m[index].getSpecializare() << endl;
								cout << "Introduceti noua specializare a medicului: \n";
								cin >> specializare;
								int aMers = m[index].setSpecializare(specializare);
								if (aMers) {
									cout << "Specializarea a fost actualizata\n";
								}
								else {
									cout << "Specializarea nu a fost actualizata, intrucat aceasta nu este inregistrata in sistem\n";
								}
							}
							else if (j == 8) {
								ok = 0;
								cout << "Bonusul pe care doriti sa il adaugati la salariul medicului va fi calculat in functie de istoricul orelor lucrate.\n";
								m[index].adaugaBonus();
								cout << "Salariul a fost actualizat\n";
							}
							else if (j == 9) {
								ok = 0;
								float val;
								cout << "Introduceti valoarea pe care doriti sa o scadeti din salaiu:\n";
								cin >> val;
								m[index] - val;
								cout << "Salariul  a fost actualizat. In momentul de fata salariul medicului este de " << m[index].getSalariu() << endl;
							}
							else if (j == 10) {
								m[index].Moare();
								cout << "A fost inregistrata moartea medicului.\n";
							}
							else if (j == 11) {
								m[index].SchimbaIdentitatea();
								cout << "A fost schimbata identitatea medicului.\n";
							}
							else if (j == 12) {
								ok = 0;
							}
							else {
								cout << "Ati introdus o comanda invalida. Incercati inca o data.\n";
							}
						}
						medici.setColectieMedici(m, numarMedici);
						medici.updateColllection(medici.getMedici());
						medici.closeFileInTxt();
						asistenti.closeFileInTxt();
						actualizareAngajati(medici, asistenti, angajati);

					} while (ok == 1);
					medici.closeFileInTxt();
					medici.setColectieFile();
					medici.printMedici();
					angajati.printAngajati();
				}
				else if (j == 3) {
					asistenti.closeFileInTxt();
					asistenti.setColectieFile();
					int numarAsistenti = asistenti.getAsistenti().getNrObiecte();
					cout << "Ati ales sa modificati date referitoare la asistentii centrului medical\n";

					Asistent* m;
					m = new Asistent[numarAsistenti];
					for (int i = 0; i < numarAsistenti; i++) {
						m[i] = asistenti.getAsistenti().getColectie()[i];
					}
					int okay = 1;
					do {
						cout << "Introduceti indexul asistentului de interes. Tineti cont de faptul ca in momentul de fata sunt inregistrati " << numarAsistenti << " asistenti. Indexarea se face de la 0." << endl;
						int index;
						cin >> index;
						if (index < numarAsistenti) {
							cout << "Alegeti ce doriti sa modificati: \n";
							cout << "1 - Modificati numele asistentului\n";
							cout << "2 - Modificati prenumele asistentului\n";
							cout << "3 - Cresteti varsta asistentului\n";
							cout << "4 - Modificati salariul asistentului\n";
							cout << "5 - Cresteti vechimea asistentului in cadrul centrului si actualizati istoricurile\n";
							cout << "6 - Actualizati istoricul lunar, intrucat am intrat intr-un nou an\n";
							cout << "7 - Modificati numarul de ore de pregatire lunara\n";
							cout << "8 - Adauga un bonus asistentului\n";
							cout << "9 - Scadeti salariul asistentului\n";
							cout << "10 - Adaugati un medic asociat asistentului\n";
							cout << "11 - Semnalati moartea asistentului\n";
							cout << "12 - Schimbati identitatea asistentului\n";
							cout << "13 - Inapoi\n";
							int j;
							cin >> j;
							if (j == 1) {
								okay = 0;
								string nume;
								cout << "Numele actual al asistentului este: " << m[index].getNume() << endl;
								cout << "Introduceti noul nume al asistentului: \n";
								cin >> nume;
								m[index].setNume(nume.c_str());
							}
							else if (j == 2) {
								okay = 0;
								string prenume;
								cout << "Prenumele actual al asistentului este: " << m[index].getPrenume() << endl;
								cout << "Introduceti noul prenume al asistentului:\n";
								cin >> prenume;
								m[index].setPrenume(prenume);
							}
							else if (j == 3) {
								okay = 0;
								cout << "Vechea varsta a asistentului este " << m[index].getVarsta() << endl;
								m[index].setVarsta(m[index].getVarsta() + 1);
								cout << "Noua varsta a asistentului este " << m[index].getVarsta() << endl;
							}
							else if (j == 4) {
								okay = 0;								cout << "Salariul actual al asistentului este de " << m[index].getSalariu() << endl;
								cout << "Introduceti noul salariu al asistentului: \n";
								float  salariu;
								cin >> salariu;
								m[index].setSalariu(salariu);
								cout << "Salariul a fost actualizat\n";
							}
							else if (j == 5) {
								okay = 0;
								m[index].setVechime(m[index].getVechime() + 1);
								//sa vad cum fac sau las asa
							}
							else if (j == 6) {
								okay = 0;								int salariu;
								cout << "Introduceti salariul asistentului de anul acesta\n";
								cin >> salariu;
								m[index].OneYearPassed(salariu);
								cout << "Istoricul lunar a fost actualizat\n";
							}
							else if (j == 7) {
								okay = 0;								cout << "Numarul actual de ore de pregatire lunara ale asistentului este de: " << m[index].getOrePregatireLunara() << endl;
								cout << "Introduceti noul numar de ore de pregatire lunara ale asistentului:\n";
								int ore;
								cin >> ore;
								m[index].setOrePregatireLunara(ore);
								cout << "Numarul de ore de pregatire lunara ale asistentului a fost actualizat\n";
							}
							else if (j == 8) {
								okay = 0;								cout << "Bonusul pe care doriti sa il adaugati la salariul asistentului va fi calculat in functie de istoricul orelor lucrate.\n";
								m[index].adaugaBonus();
								cout << "Salariul a fost actualizat\n";
							}
							else if (j == 9) {
								okay = 0;								float val;
								cout << "Introduceti valoarea pe care doriti sa o scadeti din salaiu:\n";
								cin >> val;
								m[index] - val;
								cout << "Salariul  a fost actualizat. In momentul de fata salariul asistentului este de " << m[index].getSalariu() << endl;
							}
							else if (j == 10) {
								okay = 0;
								Medic nou;
								cout << "Ati ales sa adaugati un nou medic asociat asistentului.\n";
								medici.closeFileInTxt();
								medici.setColectieFile();
								int numarMedici = medici.getMedici().getNrObiecte();
								Medic* maux;
								maux = new Medic[numarMedici];
								for (int i = 0; i < numarMedici; i++) {
									maux[i] = medici.getMedici().getColectie()[i];
								}
								cout << "Alegeti index-ul medicului pe care doriti sa il asociati asistentului. Va informam ca in momentul de fata sunt inregistrati " << medici.getMedici().getNrObiecte() << " medici. Indexarea se face de la 0\n";
								int indexMedic;
								cin >> indexMedic;
								if (indexMedic < medici.getMedici().getNrObiecte()) {
									m[index].addMedic(maux[indexMedic]);
									cout << "Medicul a fost adaugat ca medic asociat al asistentului\n";
								}

							}
							else if (j == 11) {
								m[index].Moare();
								cout << "A fost inregistrata moartea asistentului.\n";
							}
							else if (j == 12) {
								m[index].SchimbaIdentitatea();
								cout << "A fost  schimbata identitatea asistentului.\n";
							}
							else if (j == 13) {
								okay = 0;
								ok = 0;
							}
							else {
								cout << "Ati introdus o comanda invalida. Incercati inca o data.\n";
							}
							asistenti.setColectieAsistenti(m, numarAsistenti);
							asistenti.updateColllection(asistenti.getAsistenti());
							asistenti.closeFileInTxt();
							medici.closeFileInTxt();
						}
						else {
							cout << "Indexul pe care l-ati introdus nu este valid\n";
						}
					} while (okay == 1);
					asistenti.closeFileInTxt();
					asistenti.setColectieFile();
					asistenti.printMedici();
					angajati.printAngajati();
				}
				else if(j==4) {
					ok = 0;
				}
				else {
					cout << "Ati introdus o comanda invalida. Incercati din nou: \n";
				}
			}while (ok == 1);
		}
		else if (i == 4 ) {
			int ok = 1;
			do {
				cout << "Ati ales optiunea de a adauga o noua inregistrare\n";
				cout << "Alegeti ce fel de inregistrare doriti sa adaugati:\n";
				cout << "1 - Pacienti\n";
				cout << "2 - Medici\n";
				cout << "3 - Asistenti\n";
				cout << "4 - Inapoi\n";
				int j;
				cin >> j;
				if (j == 1) {
					ok = 0;
					Pacient* p;
					int nrPacienti = pacienti.getPacienti().getNrObiecte() + 1;
					Pacient nou;
					cout << "Introduceti un nou pacient:\n";
					cin >> nou;
					p = new Pacient[nrPacienti];
					for (int i = 0; i < nrPacienti - 1; i++) {
						p[i] = pacienti.getPacienti().getColectie()[i];
					}
					p[nrPacienti - 1] = nou;
					pacienti.setColectiePacienti(p, nrPacienti);
					pacienti.updateColllection(pacienti.getPacienti());
					pacienti.closeFileInTxt();
					actualizareConsultatii(consultatii, pacienti);
					consultatii.updateColllection(consultatii.getConsultatie());
				
				}
				else if (j == 2) {
					ok = 0;
					Medic* m;
					int nrMedici = medici.getMedici().getNrObiecte() + 1;
					Medic nou;
					cout << "Introduceti un nou medic:\n";
					cin >> nou;
					m = new Medic[nrMedici];
					for (int i = 0; i < nrMedici - 1; i++) {
						m[i] = medici.getMedici().getColectie()[i];
					}

					m[nrMedici - 1] = nou;
					medici.setColectieMedici(m, nrMedici);
					medici.updateColllection(medici.getMedici());
					medici.closeFileInTxt();
					asistenti.closeFileInTxt();
					actualizareAngajati(medici, asistenti, angajati);
					angajati.updateColllection(angajati.getAngajati());
				}
				else if (j == 3) {
					ok = 0;
					Asistent* m;
					int nrAsistenti = asistenti.getAsistenti().getNrObiecte() + 1;
					Asistent nou;
					cout << "Introduceti un nou medic:\n";
					cin >> nou;
					m = new Asistent[nrAsistenti];
					for (int i = 0; i < nrAsistenti - 1; i++) {
						m[i] = asistenti.getAsistenti().getColectie()[i];
					}
					m[nrAsistenti - 1] = nou;
					asistenti.setColectieAsistenti(m, nrAsistenti);
					asistenti.updateColllection(asistenti.getAsistenti());
					medici.closeFileInTxt();
					asistenti.closeFileInTxt();
					actualizareAngajati(medici, asistenti, angajati);
					angajati.updateColllection(angajati.getAngajati());
				}
				else if (j == 4) {
					ok = 0;
				}
				else {
					cout << "Comanda invalida. Incercati din nou\n";
				}
			} while (ok == 1);
		}
		else if (i == 5) {
			pacienti.closeFileInTxt();
			asistenti.closeFileInTxt();
			medici.closeFileInTxt();
			consultatii.closeFileInTxt();
			cout << "Ati ales optiunea de a salva datele aplicatiei in fisiere binare\n";
			if (pacienti.getPacienti().getNrObiecte() != 0) {
				pacienti.setFileOutBinary("DatePacientiBinar.bin");
				pacienti.setColectieFile();
				pacienti.printBinaryPacienti();
				cout << "A fost creat fisierul binar DatePacientiBinar.bin, unde sunt salvate datele despre pacienti\n";
			}
			else {
				cout << "Nu exista pacienti inregistrati, prin urmare nu a fost creat fisierul binar.\n";
			}
			if (consultatii.getConsultatie().getNrObiecte() != 0) {
				consultatii.setFileOutBinary("DateConsultatiiBinar.bin");
				consultatii.closeFileInTxt();
				pacienti.closeFileInTxt();
				actualizareConsultatii(consultatii, pacienti);
				consultatii.printBinaryConsultatii();
				cout << "A fost creat fisierul binar DateConsultatiiBinar.bin, unde sunt salvate datele despre consultatii\n";
			}
			else {
				cout << "Nu exista consultatii inregistrate, prin urmare nu a fost creat fisierul binar.\n";
			}
			if (medici.getMedici().getNrObiecte() != 0) {
				medici.setFileOutBinary("DateMediciBinar.bin");
				medici.setColectieFile();
				medici.printBinaryMedici();
				cout << "A fost creat fisierul binar DateMediciBinar.bin, unde sunt salvate datele despre medici\n";
			}
			else {
				cout << "Nu exista medici inregistrati, prin urmare nu a fost creat fisierul binar.\n";
			}
			if (asistenti.getAsistenti().getNrObiecte() != 0) {
				asistenti.setFileOutBinary("DateAsistentiBinar.bin");
				asistenti.setColectieFile();
				asistenti.printBinaryAsistenti();
				cout << "A fost creat fisierul binar DateAsistentiBinar.bin, unde sunt salvate datele despre asistenti\n";
			}
			else {
				cout << "Nu exista asistenti inregistrati, prin urmare nu a fost creat fisierul binar.\n";
			}
			medici.closeFileInTxt();
			angajati.closeFileInTxt();
			asistenti.closeFileInTxt();
			actualizareAngajati(medici, asistenti, angajati);
			if (angajati.getAngajati().getNrObiecte() != 0) {
				angajati.setFileOutBinary("DateAngajatiBinar.bin");
				angajati.printBinaryAngajati();
				cout << "A fost creat fisierul binar DateAngajatiBinar.bin, unde sunt salvate datele despre angajati\n";
			}
			else {
				cout << "Nu exista angajati inregistrati, prin urmare nu a fost creat fisierul binar.\n";
			}
			cout << "Au fost salvate toate datele aferente aplicatiei\n";
		}	
		else if (i == 6) {
			cout << "Ati ales optiunea de a adauga inregistrari de tip Pacient dintr-un fisier CSV\n";
			char delimitator[5];
			cout << "Introduceti delimitatorul (recomandam virgula): \n";
			cin >> delimitator;
			string numeCSV;
			cout << "Introduceti numele fisierului CSV:\n";
			cin >> numeCSV;
			pacienti.setFileCSV(numeCSV);
			pacienti.readPacientiFromCSV(delimitator);
			pacienti.updateColllection(pacienti.getPacienti());	
		}		
		else if (i == 7) {
			cout << "Ati ales optiunea de a testa array-ul de pointeri aferent familiei Angajat, Medic, Asistent si Rezident.\n";
			cout << "Pentru asta, se vor citi cate un angajat,un medic, un asistent si un rezident, de la atstatura.\n";
			cout << "Introduceti datele aferente angajatului: \n";
			Angajat ang;
			cin >> ang;
			cout << "Introduceti datele aferente medicului: \n";
			Medic m;
			cin >> m;
			cout << "Introduceti datele aferente asistentului: \n";
			Asistent a;
			cin >> a;
			cout << "Introduceti datele aferente rezidentului:\n";
			Rezident r;
			cin >> r;
			
			Angajat** lista;

			lista = new Angajat * [4];
			lista[0] = new Angajat(ang);
			lista[0] = &ang;
			lista[1] = new Asistent(a);
			lista[1] = &a;
			lista[2] = new Medic(m);
			lista[2] = &m;
			lista[3] = new Rezident(r);
			lista[3] = &r;
			ofstream f, g, j, k;
			cout << "Datele aferente fiecaruia vor fi accesibile in fisierele tip: Date_TipClasa_Pointeri.txt.\n";
			f.open("Date_Angajati_Pointeri.txt", ios::out);
			g.open("Date_Asistenti_Pointeri.txt", ios::out);
			j.open("Date_Medici_Pointeri.txt", ios::out);
			k.open("Date_Rezidenti_Pointeri.txt", ios::out);
			lista[0]->creareRaport(f);
			lista[1]->creareRaport(g);
			lista[2]->creareRaport(j);
			lista[3]->creareRaport(k);
		}
		else if (i == 8) {
			ConsultatieExtinsa ce1,ce2;
			cout << "\n------------------------------------------------------------------\n";
			cout << "Se vor citi doua consultatii extinse.\n";
			cin >> ce1 >> ce2;
			cout << "\n------------------------------------------------------------------\n";
			cout << "Se vor afisa cele doua consultatii extinse.\n";
			cout << ce1 << ce2;
			cout << "\n------------------------------------------------------------------\n";
			cout << "Se va egala consultatia extinsa 2 cu consultatia exinsa 1 si vor fi afisate ulterior.\n";
			ce2 = ce1;
			cout << ce1 << ce2;
			cout << "\n------------------------------------------------------------------\n";
			cout << "Vor fi afisati in fisierul DateConsultatiiExtinse.txt, datele aferente consultatiilor extinse inregistrate\n";
			ofstream f;
			f.open("DateConsultatiiExtinse.txt", ios::out);
			f << ce1 << ce2;
			cout << "\n------------------------------------------------------------------\n";
			cout << "Doriti sa cititi dintr-un fisier date extinse?\n";
			cout << "1 - da\n";
			cout << "2 - nu\n";
			int i;
			cin >> i;
			if (i == 1) {
				cout << "\n------------------------------------------------------------------\n";
				cout << "Introduceti numele fisierului din care doriti sa se citeasca datele\n";
				string numeFisier;
				cin >> numeFisier;
				ifstream g;
				g.open(numeFisier, ios::in);
				if (g.is_open()) {
					g >> ce1 >> ce2;
					cout << ce1 << ce2;
				}
			}
		
			cout << "\n------------------------------------------------------------------\n";
			cout << "Introduceti doi pacienti extinsi\n";
			PacientExtins pe1, pe2;
			cin >> pe1 >> pe2;
			cout << "\n------------------------------------------------------------------\n";
			cout << "Iata pacientii extinsi mai jos:\n";
			cout << pe1 << pe2;
			cout << "\n------------------------------------------------------------------\n";
			cout << "Se vor afisa cei doi pacienti extinsi in fisierul DatePacientiExtinsi.txt";
			ofstream h;
			h.open("DatePacientiExtinsi.txt", ios::out);
			h << pe1 << pe2;
				
			
			cout << "\n------------------------------------------------------------------\n";
			cout << "Se vor egala cei doi pacienti extinsi.\n";
			pe1 = pe2;
			cout << pe1 << pe2;
		}
		else if (i == 9) {
			int ok = 0;
			while (ok == 0) {
				cout << "Schimbati calea unde se gasesc datele pentru: \n";
				string path;
				cout << "1 - Pacienti\n";
				cout << "2 - Medici\n";
				cout << "3 - Asistenti\n";
				cout << "4 - Inapoi\n";
				int i;
				cin >> i;
				if (i == 1) {
					ok = 1;
					cout << "Introduceti calea catre respectivul fisier: \n";
					cin >> path;
					pacienti.setFileInTxt(path);
					if (pacienti.getFileInTxt().is_open()) {
						cout << "A fost schimmbata calea catre fisierul cu date.\n";
					}
					else {
						cout << "Nu ati introdus o cale valida.\n";
					}
				}
				else if (i == 2) {
					ok = 1;
					cout << "Introduceti calea catre respectivul fisier: \n";
					cin >> path;
					medici.setFileInTxt(path);
					if (medici.getFileInTxt().is_open()) {
						cout << "A fost schimmbata calea catre fisierul cu date.\n";
					}
					else {
						cout << "Nua ti introdus o cale valida.\n";
					}
				}
				else if (i == 3) {
					ok = 1;
					cout << "Introduceti calea catre respectivul fisier: \n";
					cin >> path;
					medici.setFileInTxt(path);
					if (medici.getFileInTxt().is_open()) {
						cout << "A fost schimmbata calea catre fisierul cu date.\n";
					}
					else {
						cout << "Nua ti introdus o cale valida.\n";
					}
				}
				else if (i == 4) {
					ok = 1;
				}
				else {
					cout << "Ati introdus o comanda invalida.\n";
				}
			}
		}
		else if (i == 10) {
			return;
		}
		else {
			cout << "Ati introdus o comanda invalida\n";
		}

	}
}