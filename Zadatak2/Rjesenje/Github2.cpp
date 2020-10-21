#include<iostream>
using namespace std;
const char* crt = "\n----------------------------------------------\n";
char* AlocirajNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)
        return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
            
    }
    Datum(const Datum& datum) {
        _dan = new int(*datum._dan);
        _mjesec = new int(*datum._mjesec);
        _godina = new int(*datum._godina);
    }
    Datum& operator=(const Datum& datum) {
        if (this != &datum) {
            delete _dan;
            delete _mjesec;
            delete _godina;
            _dan = new int(*datum._dan);
            _mjesec = new int(*datum._mjesec);
            _godina = new int(*datum._godina);
        }
        return *this;
    }
    ~Datum() {
        delete _dan;
        _dan = nullptr;
        delete _mjesec;
        _mjesec = nullptr;
        delete _godina;
        _godina = nullptr;

    }
    friend ostream& operator <<(ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "  " << *obj._mjesec << "  " << *obj._godina;
        return COUT;
    }
    int SumaDana() {
        return *_dan + *_mjesec * 30 + *_godina * 365;
    }
};
template <class T>
class Kolekcija {
    T* _niz;
    int _trenutno;
public:
    Kolekcija() :_trenutno(0), _niz(nullptr) {}
    ~Kolekcija() { delete[]_niz; _niz = nullptr; _trenutno = 0; }
    Kolekcija(const Kolekcija& kolekcija) {
        _trenutno = kolekcija._trenutno;
        _niz = new T[kolekcija._trenutno];
        for (int i = 0; i < kolekcija._trenutno; i++)
        {
            _niz[i] = kolekcija._niz[i];
        }
    }
    Kolekcija& operator=(const Kolekcija& kolekcija) {
        if (this != kolekcija) {
            delete[] _niz;
            _trenutno = kolekcija._trenutno;
            _niz = new T[kolekcija._trenutno];
            for (int i = 0; i < kolekcija._trenutno; i++)
            {
                _niz[i] = kolekcija._niz[i];
            }
        }
        return *this;
    }
    T* GetNiz() { return _niz; }
    int GetTrenutno() { return _trenutno; };
    //IMPLEMENTIRATI POTREBNE FUNKCIJE)
    void Add(T var) {
        T* temp = new T[_trenutno + 1];
        for (int i = 0; i < _trenutno; i++)
        {
            temp[i] = _niz[i];
        }
        temp[_trenutno] = var;
        delete[] _niz;
        _niz = temp;
        _trenutno++;
    }
    friend ostream& operator<<<>(ostream& COUT, const Kolekcija<T>& objekat);
    T& operator[](int i) {
        return _niz[i];
    }
};
template <class T>
ostream& operator<<<>(ostream& COUT, const Kolekcija<T>& objekat) {
    for (int i = 0; i < objekat._trenutno; i++)
    {
        COUT << objekat._niz[i] << endl;
    }
    return COUT;
}
class Usluga {
    char* _naziv;
    double _cijena;//cijena usluge je izrazena po danu koristenja
public:
    Usluga() :_naziv(nullptr), _cijena(0) {}
    Usluga(const char* naziv, double cijena) :_cijena(cijena) {
        _naziv = AlocirajNizKaraktera(naziv);
    }
    Usluga(const Usluga& usluga) {
        _naziv = new char[strlen(usluga._naziv) + 1];
        strcpy_s(_naziv, strlen(usluga._naziv) + 1, usluga._naziv);
        _cijena = usluga._cijena;
    }
    Usluga& operator=(const Usluga& usluga) {
        if (this != &usluga) {
            delete[] _naziv;
            _naziv = new char[strlen(usluga._naziv) + 1];
            strcpy_s(_naziv, strlen(usluga._naziv) + 1, usluga._naziv);
            _cijena = usluga._cijena;
        }
        return *this;
    }
    ~Usluga() {
        delete _naziv;
        _naziv = nullptr;
    }
    double GetCijena() { return _cijena; }
    const char* GetNaziv() { return _naziv; }
    friend ostream& operator<<(ostream& COUT, const Usluga& obj);
    bool operator==(const Usluga& usluga) {
        if (strcmp(_naziv, usluga._naziv) == 0 && _cijena == usluga._cijena)
            return true;
        return false;
    }
};
ostream& operator<<(ostream& COUT, const Usluga& obj) {
    COUT << obj._naziv << " -> \t\t" << obj._cijena << "KM" << endl;
    return COUT;
}
class Rezervacije {
    static int _rezervacijeIDBrojac;
    const int _rezervacijaID;//broj rezervacija se krece od 160000
    Datum _rezervacijaOD;
    Datum _rezervacijaDO;
    double _cijenaPoDanu;//cijena osnovnih usluga koja ne ukljucuje dodatne usluge
    Kolekcija<Usluga>_dodatneUsluge;//dodatne usluge mogu biti:sauna,sportski tereni,kuglanje,masaza
public:
    //implementirati potrebne funkcije
    Rezervacije(Datum rezervacijaOD, Datum rezervacijaDO, double cijenaPoDanu) :
        _rezervacijaOD(rezervacijaOD), _rezervacijaDO(rezervacijaDO), _rezervacijaID(_rezervacijeIDBrojac++) {
        _cijenaPoDanu = cijenaPoDanu;
    }
    bool operator+=(const Usluga& usluga) {
        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
        {
            if (_dodatneUsluge[i] == usluga)
                return false;
        }
        _dodatneUsluge.Add(usluga);
    }
    void PrintRacun() {
        cout << crt;
        cout << "R.ID:" << _rezervacijaID << endl;
        cout << "OD: " << _rezervacijaOD << endl;
        cout << "DO: " << _rezervacijaDO;
        cout << crt;
        cout << "DODATNE USLUGE :";
        cout << crt;

        int brojDana = _rezervacijaDO.SumaDana() - _rezervacijaOD.SumaDana();
        double osnovne = brojDana * _cijenaPoDanu;
        double dodatne = 0;

        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
        {
            double cijena = _dodatneUsluge[i].GetCijena();
            cout << _dodatneUsluge[i].GetNaziv() << "->\t\t\t" << cijena << " KM" << endl;
            dodatne += cijena;
        }
        dodatne *= brojDana;

        cout << crt;
        cout << "Osnovne usluge->\t\t" << osnovne << " KM" << endl;
        cout << crt;
        cout << "Dodatne usluge->\t\t" << dodatne << " KM" << endl;
        cout << crt;
        cout << "Ukupno->\t\t\t" << osnovne + dodatne << " KM" << endl;
        cout << crt;
    }
    Usluga* operator[](const char* naziv) {
        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
        {
            if (strcmp(naziv, _dodatneUsluge[i].GetNaziv()) == 0)
                return &_dodatneUsluge[i];
        }
        return nullptr;
    }
    Kolekcija<Usluga> operator()(int OD, int DO) {
        Kolekcija<Usluga> k;
        for (int i = 0; i < _dodatneUsluge.GetTrenutno(); i++)
        {
            if (_dodatneUsluge[i].GetCijena() >= OD && _dodatneUsluge[i].GetCijena() <= DO)
                k.Add(_dodatneUsluge[i]);
        }
        return k;
    }
};

int Rezervacije::_rezervacijeIDBrojac = 160000;

void main() {

    cout << crt << "TRAJANJE ISPITA -> 90 MINUTA" << crt;
    Kolekcija<int>brojevi;
    for (int i = 0; i < 15; i++)
    {
        brojevi.Add(i);
    }
    cout << brojevi << crt;
    //u okviru klase Usluga implementirati MOVE konstruktor
    Usluga Parking("Parking", 5), Dorucak("Dorucak", 10), Rucak("Rucak", 15), Veseraj("Veseraj", 10);

    //rezervacijaOD,rezervacijaDO,cijenaPoDanu
    Rezervacije rezervacija(Datum(25, 10, 2018), Datum(30, 10, 2018), 59.9);

    //dodaje novu uslugu u rezervaciju. onemoguciti ponavljanje usluga
    if (rezervacija += Parking)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Dorucak)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Rucak)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Veseraj)
        cout << "Usluga uspjesno dodana!" << endl;
    if (rezervacija += Dorucak)
        cout << "Usluga vec postoji!" << endl;

    /*prikazuje racun formatiran na nacin prikazan na slici. prilikom izracunavanja iznosa
    koristiti cijene osnovnih i dodatnih usluga ,kao i broj dana za koje je napravljena  rezervacija
    (napomena: duzina trajanja rezervacije je maksimalno 30 dana)*/
    rezervacija.PrintRacun();
    //vraca pokazivac na uskugu sa proslijedenim nazivom
    Usluga* p = rezervacija["Dorucak"];
    if (p != nullptr)
        cout << *p << crt;
    //vraca sve dodatne usluge koje imaju cijenu u opsegu vrijednosti parametara
    Kolekcija<Usluga>uslugePoCijeni = rezervacija(8, 12);
    for (int i = 0; i < uslugePoCijeni.GetTrenutno(); i++)
        cout << uslugePoCijeni[i] << crt;
    cin.get();

    system("pause");
}

/*
--------------------------------------
R.ID:160000
OD:25 10 2018
DO:30 10 2018
--------------------------------------
DODATNE USLUGE:
--------------------------------------
Parking->                   5 KM
Dorucak->                  10 KM
Rucak->                    15 KM
Veseraj->                  10 KM
--------------------------------------
Osnovne usluge->           299.5 KM
--------------------------------------
Dodatne usluge->           200 KM
--------------------------------------
Ukupno->                   499.5 KM
--------------------------------------

*/