#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cstdio>
using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct Adresat {
    string name, surname, phone, email, address;
    int id,userId;
};
class Rejestracja {
    string nazwa;
    string haslo;
    int userID;
public:
    Rejestracja (string n="", string h="",int ui=0) {
        nazwa=n;
        haslo=h;
        userID=ui;
    }
    void akcja(vector <Uzytkownik> &uzytkownicy) {
        Uzytkownik temp;
        cout << "Podaj nazwe uzytkownika: ";
        cin >> nazwa;
        int i = 0;
        while (i < uzytkownicy.size()) {
            if (uzytkownicy[i].nazwa == nazwa) {
                cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
                cin >> nazwa;
                i = 0;
            } else {
                i++;
            }
        }
        cout << "Podaj haslo: ";
        cin >> haslo;
        temp.nazwa = nazwa;
        temp.haslo = haslo;
        temp.id = uzytkownicy.size()+1;
        uzytkownicy.push_back(temp);
        cout<<"Konto zalozone."<<endl;
        fstream lista;
        lista.open("Uzytkownicy.txt",ios::out | ios::app);
        lista << temp.id << "|";
        lista << temp.nazwa << "|";
        lista << temp.haslo << "|"<<endl;
        lista.close();
        Sleep(2000);
    }
};

class Logowanie {
    string nazwa,haslo;
    int userId;
public:
    Logowanie (string n="", string h="",int ui=0) {
        nazwa=n;
        haslo=h;
        userId=ui;
    }
    int akcja(vector <Uzytkownik> &uzytkownicy) {
        cout << "Podaj login: ";
        cin >> nazwa;
        int i = 0;
        while (i < uzytkownicy.size()) {
            if (uzytkownicy[i].nazwa == nazwa) {
                for(int proby = 0; proby < 3; proby++) {
                    cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                    cin >> haslo;
                    if (uzytkownicy[i].haslo == haslo) {
                        cout << "Zalogowales sie." << endl;
                        Sleep(1000);
                        userId = uzytkownicy[i].id;
                        return userId;
                    }
                }
                cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba." << endl;
                Sleep(3000);
                return 0;
            }
            i++;
        }

        cout << " Nie ma uzytkownika z takim loginem." << endl;
        Sleep(1500);
        return userId = 0;
    }
};

void addContact( vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    string name, surname, phone, email, address, temp;
    vector<string> daneOsobowe;
    vector<string> numbersOfUsers;
    Adresat adresat;
    fstream lista;
    string linia;
    lista.open("KsiazkaAdresow.txt", ios::in);
    while (getline(lista, linia)) {
        daneOsobowe.push_back(linia);
        for(int j = 0; j < linia.length(); j++) {
            if (linia[j] != '|') {
                temp = temp + linia[j];
            } else {
                break;
            }
            numbersOfUsers.push_back(temp);
            temp.clear();
        }
    }
    lista.close();
    if (daneOsobowe.size()!=0) {
        adresat.id = atoi(numbersOfUsers[numbersOfUsers.size()-1].c_str())+1;
        daneOsobowe.clear();
        numbersOfUsers.clear();
    } else {
        adresat.id = 0;
    }
    adresat.userId=idZalogowanegoUzytkownika;

    system("cls");
    cout << "Podaj imie: ";
    cin >> name;
    adresat.name = name;
    cout << "Podaj nazwisko: ";
    cin >> surname;
    adresat.surname = surname;
    cout << "Podaj telefon: ";
    cin >> phone;
    adresat.phone = phone;
    cout << "Podaj email: ";
    cin >> email;
    adresat.email = email;
    cin.sync();
    cout << "Podaj adres: ";
    getline(cin, address);
    adresat.address = address;
    adresaci.push_back (adresat);
    lista.open("KsiazkaAdresow.txt",ios::out | ios::app);
    lista << adresat.id << "|";
    lista << adresat.userId << "|";
    lista << adresat.name << "|";
    lista << adresat.surname << "|";
    lista << adresat.phone << "|";
    lista << adresat.email << "|";
    lista << adresat.address << "|"<< endl;
    lista.close();
    Sleep(2000);
}
void zmianaHasla(vector <Uzytkownik> &uzytkownicy,int idZalogowanegoUzytkownika) {
    string haslo;
    char decision;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for(int i = 0; i < uzytkownicy.size(); i++) {
        if(idZalogowanegoUzytkownika==uzytkownicy[i].id) {
            cout << "Zmieniasz obecne haslo: " <<uzytkownicy[i].haslo << " na nowe: "<< haslo <<endl;
            cout << "Czy zgadzasz sie na zmiane (t): ";
            cin >> decision;
            if ((decision == 't') || (decision == 'T')) {
                uzytkownicy[i].haslo = haslo;
                fstream lista;
                lista.open("Uzytkownicy.txt",ios::out | ios::trunc);
                lista.close();
                lista.open("Uzytkownicy.txt",ios::out | ios::app);
                for (int i = 0; i < uzytkownicy.size(); i++) {
                    lista << uzytkownicy[i].id << "|";
                    lista << uzytkownicy[i].nazwa << "|";
                    lista << uzytkownicy[i].haslo << "|"<< endl;
                }
                lista.close();
                cout << "Haslo zostalo zmienione" << endl;
                Sleep(1500);
            } else
                exit (0);
        }
    }
}
void loadingDataUsers (vector<Uzytkownik> &uzytkownicy) {
    Uzytkownik user;
    vector<string> daneOsobowe;
    string linia;
    string temp = "";
    fstream lista;
    lista.open("Uzytkownicy.txt", ios::in);
    if(lista.good()==false)
        cout << "Nie mozna otworzyc pliku!";
    while(getline(lista, linia)) {
        int dlugoscLinii = 0;
        dlugoscLinii = linia.length();
        for(int j = 0; j < dlugoscLinii; j++) {
            if (linia[j] != '|') {
                temp = temp + linia[j];
            } else {
                daneOsobowe.push_back(temp);
                temp.clear();
            }
        }
        for (int j = 0; j < daneOsobowe.size(); j++) {
            if (j%3 == 0)
                user.id = atoi(daneOsobowe[j].c_str());
            else if (j%3 == 1)
                user.nazwa = daneOsobowe[j];
            else if (j%3 == 2)
                user.haslo = daneOsobowe[j];
        }
        uzytkownicy.push_back(user);
    }
    lista.close();
}
void loadingNewData(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    string name = "";
    string surname = "";
    string phone = "";
    string email = "";
    string address = "";
    int id,userId;
    Adresat adresat;
    vector<string> daneOsobowe;
    string linia;
    string temp = "";
    fstream lista;
    lista.open("tymcz.txt", ios::in);
    if(lista.good() == false)
        cout << "Nie mozna otworzyc pliku!";
    while(getline(lista, linia)) {
        int dlugoscLinii = 0;
        dlugoscLinii = linia.length();
        for(int j = 0; j < dlugoscLinii; j++) {
            if (linia[j] != '|') {
                temp = temp + linia[j];
            } else {
                daneOsobowe.push_back(temp);
                temp.clear();
            }
        }
    }
    for (int j = 0; j < daneOsobowe.size(); j++) {
        if ((idZalogowanegoUzytkownika == atoi(daneOsobowe[j].c_str()))&&(j%7 == 1)) {
            id = atoi(daneOsobowe[j-1].c_str());
            userId = atoi(daneOsobowe[j].c_str());
            name = daneOsobowe[j+1];
            surname = daneOsobowe[j+2];
            phone = daneOsobowe[j+3];
            email = daneOsobowe[j+4];
            address = daneOsobowe[j+5];
            adresat.id = id;
            adresat.userId = userId;
            adresat.name = name;
            adresat.surname = surname;
            adresat.phone = phone;
            adresat.email = email;
            adresat.address = address;
            adresaci.push_back(adresat);
        }
    }
    lista.close();
}
void loadingData(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    adresaci.clear();
    string name = "";
    string surname = "";
    string phone = "";
    string email = "";
    string address = "";
    int id, userId;
    Adresat adresat;
    vector<string> daneOsobowe;
    string linia;
    string temp = "";
    fstream lista, lista2;
    lista.open("KsiazkaAdresow.txt", ios::in);
    if(lista.good() == false)
        cout << "Nie mozna otworzyc pliku!";
    while(getline(lista, linia)) {
        int dlugoscLinii = 0;
        dlugoscLinii = linia.length();
        for(int j = 0; j < dlugoscLinii; j++) {
            if (linia[j] != '|') {
                temp = temp + linia[j];
            } else {
                daneOsobowe.push_back(temp);
                temp.clear();
            }
        }
    }
    int users = daneOsobowe.size()/7;
    for (int j = 0; j < daneOsobowe.size(); j++) {
        if ((idZalogowanegoUzytkownika == atoi(daneOsobowe[j].c_str()))&&(j%7 == 1)) {
            id = atoi(daneOsobowe[j-1].c_str());
            userId = atoi(daneOsobowe[j].c_str());
            name = daneOsobowe[j+1];
            surname = daneOsobowe[j+2];
            phone = daneOsobowe[j+3];
            email = daneOsobowe[j+4];
            address = daneOsobowe[j+5];
            adresat.id = id;
            adresat.userId = userId;
            adresat.name = name;
            adresat.surname = surname;
            adresat.phone = phone;
            adresat.email = email;
            adresat.address = address;
            adresaci.push_back(adresat);
        }
    }
}
void showAll(vector<Adresat> &adresaci) {
    for (int i = 0; i < adresaci.size(); i++) {
        cout << "ID: " << adresaci[i].id << endl;
        cout << "ID uzytkownika: " << adresaci[i].userId << endl;
        cout << "Imie: " << adresaci[i].name << endl;
        cout << "Nazwisko: " << adresaci[i].surname << endl;
        cout << "Numer telefonu: " << adresaci[i].phone << endl;
        cout << "Adres email: " << adresaci[i].email << endl;
        cout << "Adres: " << adresaci[i].address << endl << endl;
    }
    cout << "Nacisnij spacje aby przejsc do glownego menu." << endl;
    system("pause");
}
void searchByName(vector<Adresat> adresaci, int idZalogowanegoUzytkownika) {
    string name;
    cout << "Wpisz imie szukanej osoby: ";
    cin >> name;
    for (int i = 0; i < adresaci.size(); i++) {
        if ((name == adresaci[i].name)&&(idZalogowanegoUzytkownika == adresaci[i].userId)) {
            cout << "ID: " << adresaci[i].id << endl;
            cout << "ID uzytkownika: " << adresaci[i].userId << endl;
            cout << "Imie: " << adresaci[i].name << endl;
            cout << "Nazwisko: " << adresaci[i].surname << endl;
            cout << "Numer telefonu: " << adresaci[i].phone << endl;
            cout << "Adres email: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].address << endl << endl;
        }
    }
    system ("pause");
}
void searchBySurname(vector<Adresat> adresaci, int idZalogowanegoUzytkownika) {
    string surname;
    cout << "Wpisz nazwisko szukanej osoby: ";
    cin >> surname;
    for (int i = 0; i < adresaci.size(); i++) {
        if ((surname == adresaci[i].surname)&&(idZalogowanegoUzytkownika == adresaci[i].userId)) {
            cout << "ID: " << adresaci[i].id << endl;
            cout << "Imie: " << adresaci[i].name << endl;
            cout << "Nazwisko: " << adresaci[i].surname << endl;
            cout << "Numer telefonu: " << adresaci[i].phone << endl;
            cout << "Adres email: " << adresaci[i].email << endl;
            cout << "Adres: " << adresaci[i].address << endl << endl;
        }
    }
    system ("pause");
}
void delatingOneUser(vector<Adresat> &adresaci, int id) {
    string linia, temp;
    vector <string>numbersOfUsers;
    vector<string>daneOsobowe;
    fstream lista, lista2;
    lista.open("KsiazkaAdresow.txt", ios::in);
    if(lista.good() == false)
        cout << "Nie mozna otworzyc pliku!";
    lista2.open("Adresaci_tymczasowy.txt",ios::out | ios::trunc);
    lista2.close();
    while (getline(lista, linia)) {
        daneOsobowe.push_back(linia);
        for(int j = 0; j < linia.length(); j++) {
            if (linia[j] != '|') {
                temp = temp + linia[j];

            } else {
                break;
            }
            numbersOfUsers.push_back(temp);
            temp.clear();
        }
    }
    for (int k = 0; k < daneOsobowe.size(); k++) {
        if (atoi(numbersOfUsers[k].c_str())!= id) {
            lista2.open("Adresaci_tymczasowy.txt",ios::out | ios::app);
            lista2 << daneOsobowe[k] << endl;
            lista2.close();
        }
    }
    numbersOfUsers.clear();
    daneOsobowe.clear();
}


void deleteUser(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    int id, i;
    char decision;
    cout << "Wpisz ID osoby ktora chcesz usunac: ";
    cin >> id;
    for (i=0; i<adresaci.size(); i++) {
        if ((id==adresaci[i].id)&&(idZalogowanegoUzytkownika==adresaci[i].userId)) {
            cout << "Usuwasz osobe: " << adresaci[i].name << " " << adresaci[i].surname << endl;
            cout << "Czy zgadzasz sie na usuniecie (t): ";
            cin >> decision;
            if ((decision=='t') || (decision=='T')) {
                adresaci.erase(adresaci.begin()+i);
                delatingOneUser(adresaci, id);
                remove( "KsiazkaAdresow.txt" );
                rename( "Adresaci_tymczasowy.txt", "KsiazkaAdresow.txt" );
                Sleep(2000);
            } else
                cout << "Nie wyraziles zgody"<< endl;
            Sleep(2000);
        }
    }
}

void changingOneUser(vector<Adresat> &adresaci, int id) {
    string linia, temp;
    vector <string>numbersOfUsers;
    vector<string>daneOsobowe;
    fstream lista, lista2;
    lista.open("KsiazkaAdresow.txt", ios::in);
    if(lista.good() == false)
        cout << "Nie mozna otworzyc pliku!";
    lista2.open("Adresaci_tymczasowy.txt",ios::out | ios::trunc);
    lista2.close();
    while (getline(lista, linia)) {
        daneOsobowe.push_back(linia);
        for(int j = 0; j < linia.length(); j++) {
            if (linia[j] != '|') {
                temp = temp + linia[j];
            } else {
                break;
            }
            numbersOfUsers.push_back(temp);
            temp.clear();
        }
    }
    lista.close();
    for (int k = 0; k < daneOsobowe.size(); k++) {
        if (atoi(numbersOfUsers[k].c_str()) != id) {
            lista2.open("Adresaci_tymczasowy.txt",ios::out | ios::app);
            lista2 << daneOsobowe[k] << endl;
            lista2.close();
        } else {
            lista2.open("Adresaci_tymczasowy.txt",ios::out | ios::app);
            lista2 << adresaci[k].id << "|";
            lista2 << adresaci[k].userId << "|";
            lista2 << adresaci[k].name << "|";
            lista2 << adresaci[k].surname << "|";
            lista2 << adresaci[k].phone << "|";
            lista2 << adresaci[k].email << "|";
            lista2 << adresaci[k].address << "|" << endl;
            lista2.close();
        }
    }
    numbersOfUsers.clear();
    daneOsobowe.clear();
}

void changingData(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    vector<string>daneOsobowe;
    string linia, name, surname, phone, email, address;
    char option, decision;
    int i, id;
    cout << "Podaj ID osoby do modyfikacji: ";
    cin >> id;
    for (i = 0; i < adresaci.size(); i++) {
        if ((id == adresaci[i].id)&&(idZalogowanegoUzytkownika == adresaci[i].userId)) {
            system("cls");
            cout << "1 - Imie" << endl;
            cout << "2 - Nazwisko" << endl;
            cout << "3 - Numer telefonu" << endl;
            cout << "4 - Email" << endl;
            cout << "5 - Adres" << endl;
            cout << "6 - Powrot do menu" << endl;
            cout << "Twoj wybor: " << endl;
            cin >> option;
            if (option == '1') {
                cout << "Wpisz nowe imie: ";
                cin >> name;
                for (int i = 0; i < adresaci.size(); i++) {
                    if (id == adresaci[i].id) {
                        cout << "Zmieniasz obecne imie: " << adresaci[i].name << " na imie: " << name << endl;
                        cout << "Czy zgadzasz sie na zmiane (t): ";
                        cin >> decision;
                        if ((decision=='t') || (decision=='T')) {
                            adresaci[i].name = name;
                        } else
                            exit(0);
                    }
                }
            } else if (option == '2') {
                cout << "Wpisz nowe nazwisko: ";
                cin >> surname;
                for (int i = 0; i < adresaci.size(); i++) {
                    if (id == adresaci[i].id) {
                        cout << "Zmieniasz obecne nazwisko: " << adresaci[i].surname << " na nazwisko: " << surname << endl;
                        cout << "Czy zgadzasz sie na zmiame (t): ";
                        cin >> decision;
                        if ((decision=='t') || (decision=='T')) {
                            adresaci[i].surname = surname;
                        } else
                            exit(0);
                    }
                }
            } else if (option == '3') {
                cout << "Wpisz nowy numer telefonu: ";
                cin >> phone;
                for (int i = 0; i < adresaci.size(); i++) {
                    if (id == adresaci[i].id) {
                        cout << "Zmieniasz obecny numer telefonu: " << adresaci[i].phone << " na numer: " << phone << endl;
                        cout << "Czy zgadzasz sie na zmiame (t): ";
                        cin >> decision;
                        if ((decision=='t') || (decision=='T')) {
                            adresaci[i].phone = phone;
                        } else
                            exit(0);
                    }
                }
            } else if (option == '4') {
                cout << "Wpisz nowy adres email: ";
                cin >> email;
                for (int i = 0; i < adresaci.size(); i++) {
                    if (id == adresaci[i].id) {
                        cout << "Zmieniasz obecne email: " << adresaci[i].email << " na email: " << email << endl;
                        cout << "Czy zgadzasz sie na zmiame (t): ";
                        cin >> decision;
                        if ((decision == 't') || (decision == 'T')) {
                            adresaci[i].email = email;
                        } else
                            exit(0);
                    }
                }
            } else if (option == '5') {
                cout << "Wpisz nowy adres: ";
                cin.sync();
                getline(cin, address);
                for (int i = 0; i < adresaci.size(); i++) {
                    if (id == adresaci[i].id) {
                        cout << "Zmieniasz obecny adres: " << adresaci[i].address << " na adres: " << address << endl;
                        cout << "Czy zgadzasz sie na zmiame (t): ";
                        cin >> decision;
                        if ((decision == 't') || (decision == 'T')) {
                            adresaci[i].address = address;
                        } else
                            exit(0);
                    }
                }
            } else if (option == '6') {
                Sleep(2000);
            }
            changingOneUser(adresaci, id);
            remove( "KsiazkaAdresow.txt" );
            rename( "Adresaci_tymczasowy.txt", "KsiazkaAdresow.txt" );
        } else
            Sleep(2000);
    }
    Sleep(2000);
}

int main() {
    vector<Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    loadingDataUsers(uzytkownicy);
    int iloscUzytkownikow = 0;
    int idZalogowanegoUzytkownika = 0;
    char wybor, wybor2;
    while(1) {
        if(idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "LOGOWANIE DO KSIAZKI ADRESOWEJ" << endl << endl;
            cout << "1. Rejestracja." << endl;
            cout << "2. Logowanie." << endl;
            cout << "9. Zakoncz program." << endl;
            cout << "Twoj wybor:" << endl;
            cin>> wybor;
            if (wybor == '1') {
                Rejestracja rej;
                rej.akcja(uzytkownicy);
            } else if (wybor == '2') {
                Logowanie log;
                idZalogowanegoUzytkownika=log.akcja(uzytkownicy);
                loadingData(adresaci, idZalogowanegoUzytkownika);
            } else if (wybor == '9') {
                exit(0);
            }
        } else if (idZalogowanegoUzytkownika > 0) {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl << endl;
            cout << "1. Dodaj adresata." << endl;
            cout << "2. Wyszukaj po imieniu." << endl;
            cout << "3. Wyszukaj po nazwisku." << endl;
            cout << "4. Wyswietl wszystkich adresatow." << endl;
            cout << "5. Usun adresata." << endl;
            cout << "6. Edytuj adresata." << endl;
            cout << "7. Zmien haslo." << endl;
            cout << "9. Wyloguj sie." << endl;
            cout << "Twoj wybor:" << endl;
            cin >> wybor2;
            if (wybor2 == '1') {
                addContact(adresaci, idZalogowanegoUzytkownika);
            } else if (wybor2 == '2') {
                searchByName(adresaci, idZalogowanegoUzytkownika);
            } else if (wybor2 == '3') {
                searchBySurname(adresaci, idZalogowanegoUzytkownika);
            } else if (wybor2 == '4') {
                showAll(adresaci);
            } else if (wybor2 == '5') {
                deleteUser(adresaci, idZalogowanegoUzytkownika);
            } else if (wybor2 == '6') {
                changingData(adresaci, idZalogowanegoUzytkownika);
            } else if (wybor2 == '7') {
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            } else if (wybor2 == '9') {
                idZalogowanegoUzytkownika = 0;
            }
        }
    }
    return 0;
}
