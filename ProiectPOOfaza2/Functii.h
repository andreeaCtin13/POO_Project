#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include <regex>

using namespace std;

bool verifSiruriCaractere(const char* prenume) {
    if (strlen(prenume) >= 3) {
        for (int i = 0; i < strlen(prenume) ; i++) {
            if (!(prenume[i] >= 65 && prenume[i] <=122)) {
                return false;
            }
        }
         return true;
    }
    else {
        return false;
    }
}

bool verifSpecializare(string specializare,const string *listaSpecializari) {
    for (int i = 0; i < 8; i++) {
        if (specializare == listaSpecializari[i]) {
            return true;
        }
    }
    return false;
}

template<typename TIP>
TIP* verifIstoric( const TIP istoric[], TIP vechimeCentru, TIP val) {
    TIP* aux = new TIP[12];
    if (vechimeCentru > 0) {
        if (vechimeCentru > 12) {
            for (int i = 0; i < 12; i++) {
                if (istoric[i] < val) {
                     aux[i] = val;
                }
                else {
                    aux[i] = istoric[i];
                }
            }

        }
        else {
            for (int i = 0; i < vechimeCentru; i++) {
                if (istoric[i] < val) {

                   aux[i] = val;
                }
                else {
                    aux[i] = istoric[i];
                }
            }
            for (int i = vechimeCentru; i < 12; i++) {
                aux[i] = 0;
            }

        }

    }
    return aux;
}

bool verifTelefon(const char *phoneNumber) {
    regex r("\\d{4}\\d{3}\\d{3}");  
    auto isValidPhoneNumber = regex_match(phoneNumber, r);
    if (isValidPhoneNumber) {
        return true;
    }
    else {
        return false;
    }
}

#pragma region Functii_DATE

bool eAnBisect(int numar)
{
    if ((numar % 4 == 0) && (numar % 100 != 0))
        return true;
    if (numar % 400 == 0)
        return true;
    return false;
}
bool esteAnulOk(int an) {
    if (an > 0)
    {
        return true;
    }
    return false;
}
bool esteLunaOk(int luna) {
    if (luna > 12 || luna <= 0) {
        return false;
    }
    return true;
}

bool esteDataOk(int zi, int luna, int an) {
    if (esteAnulOk(an) && esteLunaOk(luna))
    {
        if (zi < 0) {
            return false;
        }
    }
    else {
        return false;
    }
    if (luna == 2) {
        if (eAnBisect(an))
        {
            if (zi <= 29) {
                return true;
            }
        }
        else {
            if (zi <= 28) {
                return true;
            }
        }
    }
    else {
        if (luna == 1 || luna == 3 || luna == 5 || luna == 7 || luna == 8 || luna == 10 || luna == 12) {
            if (zi <= 31) {
                return true;
            }
        }
        else {
            if (zi <= 30) {
                return true;
            }
        }
    }
    return false;
}

#pragma endregion
