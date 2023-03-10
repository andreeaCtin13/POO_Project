#pragma once
#include <iostream>
using namespace std;
#include <string.h>
#include <fstream>
#include <time.h>
#include <list>
#include "Functii.h"
#include "Medic.h"
#include "Consultatie.h"
#include <map>
#pragma region Clasa_ConsultatieExtinsa
class ConsultatieExtinsa:public Consultatie {
	string servicii="";
	static list<string> listaServicii;
	static map<float, string> listaPreturi;

public:

	#pragma region Constructori

	ConsultatieExtinsa():Consultatie() {
		this->servicii = "";
		ConsultatieExtinsa::setListaServicii();
		ConsultatieExtinsa::setListaPreturi();
	}

	ConsultatieExtinsa(const int ora, const int zi, const int luna, const int an, string servicii):Consultatie(ora,zi,luna, an) {
		ConsultatieExtinsa::setListaServicii();
		ConsultatieExtinsa::setListaPreturi();

		list<string>::iterator itList;
		int ok = 0;
		for (itList = ConsultatieExtinsa::listaServicii.begin(); itList != ConsultatieExtinsa::listaServicii.end(); itList++) {
			if (*itList == servicii) {
				ok = 1;
				this->servicii = servicii;
				this->setPret(this->getStaticPreturi(this->servicii));
			}
		}

		if (ok == 0) {
			this->servicii = *ConsultatieExtinsa::listaServicii.begin();
		}
	}

	ConsultatieExtinsa(const int ora, const int zi, const int luna, const int an, const Medic medic, string servicii):Consultatie(ora, zi, luna, an, medic) {
		ConsultatieExtinsa::setListaServicii();
		ConsultatieExtinsa::setListaPreturi();
		list<string>::iterator itList;
		int ok = 0;
		for (itList = ConsultatieExtinsa::listaServicii.begin(); itList != ConsultatieExtinsa::listaServicii.end(); itList++) {
			if (*itList == servicii) {
				ok = 1;
				this->servicii = servicii;
				this->setPret(this->getStaticPreturi(this->servicii));
			}
		}
		if (ok == 0) {
			this->servicii = *ConsultatieExtinsa::listaServicii.begin();
		}
	}

	ConsultatieExtinsa(const Consultatie c, const string servicii) {
		ConsultatieExtinsa::setListaServicii();
		list<string>::iterator itList;
		ConsultatieExtinsa::setListaPreturi();

		int ok = 0;
		cout << endl<<"hahahahahahahaha"<< endl;
		for (itList = ConsultatieExtinsa::listaServicii.begin(); itList != ConsultatieExtinsa::listaServicii.end(); itList++) {
			if (*itList == servicii) {
				ok = 1;
				this->servicii = servicii;
				this->setPret(this->getStaticPreturi(this->servicii));
			}
		}
		if (ok == 0) {
			this->servicii = *ConsultatieExtinsa::listaServicii.begin();
		}
	}

	ConsultatieExtinsa(const ConsultatieExtinsa& c) :Consultatie(c) {

		list<string>::iterator itList;
		int ok = 0;
		for (itList = ConsultatieExtinsa::listaServicii.begin(); itList != ConsultatieExtinsa::listaServicii.end(); itList++) {
			if (*itList == c.servicii) {
				ok = 1;
				this->servicii = c.servicii;
				this->setPret(this->getStaticPreturi(this->servicii));
			}
		}
		if (ok == 0) {
			this->servicii = *ConsultatieExtinsa::listaServicii.begin();
		}
	}

#pragma endregion

	#pragma region MetodeStatice
	static void setListaServicii() {
		ConsultatieExtinsa::listaServicii.push_back("control");
		ConsultatieExtinsa::listaServicii.push_back("analize");
		ConsultatieExtinsa::listaServicii.push_back("operatie");
		ConsultatieExtinsa::listaServicii.push_back("terapie");
		ConsultatieExtinsa::listaServicii.push_back("urgenta");
	}

	static void setListaPreturi() {
		list<string>::iterator itList;
		map<float, string>::iterator itMap;
		float v[5] = {50, 125.5, 700, 200, 400};
		string* serv = new string[5];
		int i = 0;
		for (itList = ConsultatieExtinsa::listaServicii.begin(); itList != ConsultatieExtinsa::listaServicii.end(); itList++){
			ConsultatieExtinsa::listaPreturi[v[i]] = *itList;
			i++;
		}
		i = 0;

	}
#pragma endregion

	#pragma region MetodeAccesor
	float getStaticPreturi(string serviciu){
		 for (map<float,string>::iterator i = ConsultatieExtinsa::listaPreturi.begin(); i != ConsultatieExtinsa::listaPreturi.end(); i++)
		 {
			 if ((*i).second == serviciu) {
				 return (*i).first;
			 }
		 }
	}

	 string getServicii() {
		 return this->servicii;
	 }

	 void setPretServiciu() {
		 list<string>::iterator itList;
		 int ok = 0;
		 for (itList = ConsultatieExtinsa::listaServicii.begin(); itList != ConsultatieExtinsa::listaServicii.end(); itList++) {
			 if (*itList == this->servicii) {
				 ok = 1;
				 this->setPret(this->getStaticPreturi(this->servicii));
			 }
		 }
	 }

#pragma endregion

	#pragma region OperatorulEgal
	ConsultatieExtinsa& operator= (ConsultatieExtinsa& c) {
		if (*this != c) {
			Consultatie::operator=(c);
			list<string>::iterator itList;
			int ok = 0;
			for (itList = ConsultatieExtinsa::listaServicii.begin(); itList != ConsultatieExtinsa::listaServicii.end(); itList++) {
				if (*itList == c.servicii) {
					ok = 1;
					this->servicii = c.servicii;
				}
			}
			if (ok == 0) {
				this->servicii = *ConsultatieExtinsa::listaServicii.begin();
			}
		}
		return *this;
	}
#pragma endregion

	#pragma region OperatorScriere
	friend ostream& operator << (ostream& out, const ConsultatieExtinsa& c) {
		out << (Consultatie)c;
		out << "Serviciile solicitate in cadrul consultatiei sunt urmatoarele: " << c.servicii << endl;
		return out;
	}
#pragma endregion
	
	#pragma region OperatorCitire
	friend istream& operator >> (istream& in, ConsultatieExtinsa& c) {
		int zi;
		int luna;
		int an;
		bool ok = false;
		while (ok == false) {
			cout << "Introduceti anul in care va avea loc consultatia: \n";
			in >> an;
			cout << "Introduceti luna in care va avea loc consultatia: \n";
			in >> luna;
			cout << "Introduceti ziua in care va avea loc consultatia: \n";
			in >> zi;
			Data aux;
			aux.setData(zi, luna, an);
			ok = c.setDataConsultatie(aux);
			if (!ok) {
				cout << "Data nu este corespunzatoare\n";
			}
		}

		cout << "Introduceti ora la care va avea loc consultatia (Consultatia poate avea loc doar la ore fixe. ex: 9):\n";
		int ora;
		in >> ora;
		ok = false;
		while (ok == false) {
			ok = c.setOra(ora);
			if (!ok) {
				cout << "Ora nu e corespunzatoare, mai incercati odata: \n";
				in >> ora;
			}
		}
		Medic m;
		cin >> m;
		cout << m;
		c.setMedic(m);
		ok = false;
		while (ok == false) {
			string serviciuOferit;
			cout << "Intorduceti tipul de servicii aferent consultatiei. Aveti urmatoarele variante: \n";
			list<string>::iterator itList;
			for (itList = ConsultatieExtinsa::listaServicii.begin(); itList != ConsultatieExtinsa::listaServicii.end(); itList++) {
				cout << *itList << endl;
			}
			cout << "Introduceti serviciul oferit in cadrul consultatiei:\n";
			in >> serviciuOferit;
			list<string>::iterator itList1;
			for (itList1 = ConsultatieExtinsa::listaServicii.begin(); itList1 != ConsultatieExtinsa::listaServicii.end(); itList1++) {
				if (*itList1 == serviciuOferit) {
					ok = true;
					c.servicii = serviciuOferit;
				}
			}
			if (ok == false) {
				cout << "Serviciile introduse nu se regasesc in lista posibila, mai incercati o data.\n";
			}
		}
		c.setPretServiciu();
		return in;
	}
#pragma endregion

	#pragma region CitireFisier
	friend ifstream& operator>>(ifstream& in, ConsultatieExtinsa& c) {
		int zi;
		int luna;
		int an;
		int ok = 0;
		in >> zi;
		in >> luna;
		in >> an;

		Data aux;
		aux.setData(zi, luna, an);
		if (c.setDataConsultatie(aux) == true) {
			c.setDataConsultatie(aux);
		}
		int ora;
		in >> ora;
		c.setOra(ora);
		ok = 0;
		float pret; 
		in >> pret;
		c.setPret(pret);
		return in;
	}
#pragma endregion

	#pragma region ScriereFisier

	friend ofstream& operator<<(ofstream& out, const ConsultatieExtinsa& c) {
		out << c.getData().getZi() << " " << c.getData().getLuna() << " " << c.getData().getAn() << endl;
		out << c.getOra() << endl;
		out << c.getPret() << endl;

		return out;
	}

#pragma endregion

};
list <string>ConsultatieExtinsa::listaServicii;
map<float, string>ConsultatieExtinsa::listaPreturi;