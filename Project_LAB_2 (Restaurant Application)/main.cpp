/// Tema 15: Restaurant
#include <bits/stdc++.h>

using namespace std;

/// vom avea o clasa abstracta
class Meniu
{
protected:
    double pret;
public:
    virtual void afisare_pret() = 0; /// functie virtuala pura
    Meniu();
    Meniu(double);
    Meniu(const Meniu &);
    virtual ~Meniu();
    virtual void set_price(double);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Client
{
    int nr_client;
    string comanda; /// ce comanda clientul
    double nota_total; ///per client
public:
    Client(int nr_client = 0, double nota_total = 0, string comanda = "");
    Client(Client&);
    ~Client();
    friend ostream& operator<<(ostream &gout,  const Client &client);
    friend istream& operator>>(istream &fin, Client &client);
    Client operator=(const Client&);
    int get_nr_client();
    double  get_nota_total();
    string get_comanda();
    void set_nr_client(int);
    void set_comanda(string);
    void adauga_la_comanda(string);
    void adauga_la_nota_total(double);
    void adauga_comanda_si_pret(string, double);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Masa
{
    Client *masa_de_clienti; /// vector de "clienti"
    int capacitate_masa;
    int numar_clienti;
    static int index_masa;
    static int index_client_de_la_masa;
public:
    Masa(int numar_clienti = 0, int capacitate_masa = 8);
    Masa(const Masa&);
    ~Masa();
    friend ostream& operator<<(ostream &gout, const Masa &table);
    friend istream& operator>>(istream &fin, Masa &table);
    Masa operator=(const Masa&);
    void adauga_client_la_masa();
    double nota_total_pe_masa();
    double nota_total_pe_un_client(int);
    void adauga_comanda_la_client(int, string);
    void adauga_pret_la_client(int, double);
    void adauga_comanda_si_pret_la_client(int, string, double);
    int numar_clienti_de_la_o_masa();
    int get_capacitate_masa();
    static void incrementare_index_masa();
    static int obtine_index_masa();
    static void incrementare_index_client();
    static int obtine_index_client();
    static void reset_index_client();
    void afiseaza_nota_total_pe_masa();
    void afiseaza_nota_total_pe_un_client(int);
    Masa *memorare_afisare_n_obiecte();
};
int Masa::index_masa = 0;
int Masa::index_client_de_la_masa = 0;
void Masa::incrementare_index_masa()
{
    ++index_masa;
}
int Masa::obtine_index_masa()
{
    return index_masa;
}
void Masa::incrementare_index_client()
{
    ++index_client_de_la_masa;
}
int Masa::obtine_index_client()
{
    return index_client_de_la_masa;
}
void Masa::reset_index_client()
{
    index_client_de_la_masa = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Ciorba:public Meniu
{
    string tip_ciorba;
    bool smantana, ardei;
public:
    Ciorba(double pret = 6, string tip_ciorba = "legume", bool smantana = false, bool ardei = false);
    Ciorba(const Ciorba&);
    virtual ~Ciorba()
    {
        tip_ciorba = "";
        smantana = false;
        ardei = false;
    }
    void afisare_pret();
    void set_price(double);
    double get_price();
    string get_tip_ciorba();
    void set_tip_ciorba(string, bool, bool);
    Ciorba operator=(const Ciorba &);
    friend ostream& operator<<(ostream &gout, Ciorba &ciorba);
    friend istream& operator>>(istream &fin, Ciorba &ciorba);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Fel_principal:public Meniu
{
    string carne;
    string fel_carne;
public:
    Fel_principal(double pret = 23, string carne = "pui", string fel_carne = "frigarui");
    Fel_principal(const Fel_principal&);
    virtual ~Fel_principal()
    {
        carne = "";
        fel_carne = "";
    }
    virtual void afisare_pret();
    virtual void set_price(double cost)
    {
        if(carne == "pui"  and fel_carne == "tocana")
            cost += 23;
        else
            if(carne == "vita" and fel_carne == "chateaubrian")
                cost += 30;
            else
                if(carne == "vita" and fel_carne == "stroganoff")
                    cost += 35;
                else
                if(carne == "vita" and fel_carne == "file")
                    cost += 40;

        Meniu::set_price(cost);
    }
    virtual double get_price();
    string get_tip_carne();
    void set_tip_carne(string, string);
    Fel_principal operator=(const Fel_principal&);
    friend ostream& operator<<(ostream &gout, Fel_principal &tip);
    friend istream& operator>>(istream &fin, Fel_principal &tip);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Garnitura:public Fel_principal
{
    string leguma, tip_garnitura;
public:
    Garnitura(double pret = 27, string carne = "pui", string fel_carne = "frigarui", string leguma = "cartofi", string tip_garnitura = "prajiti");
    Garnitura(const Garnitura&);
    ~Garnitura();
    void afisare_pret()
    {
        cout << pret;
    }
    void set_price(double cost)
    {
        if(leguma == "cartofi" and tip_garnitura == "piure")
            cost += 4;
        else
            if(leguma == "orez" and tip_garnitura == "sarbesc")
                cost += 6;
        Meniu::set_price(cost);
    }
    double get_price();
    string get_tip_garnitura();
    void set_tip_garnitura(string, string);
    Garnitura operator=(const Garnitura&);
    friend ostream& operator<<(ostream &gout, Garnitura &garnitura);
    friend istream& operator>>(istream &fin, Garnitura &garnitura);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Desert:public Meniu
{
    string tip_desert;
    int numar_cupe;
public:
    Desert(double pret = 5, string tip_desert = "inghetata", int numar_cupe = 0);
    Desert(const Desert&);
    ~Desert();
    void afisare_pret() override
    {
        cout << pret;
    }
    void set_price(double cost) override
    {
        if(tip_desert == "inghetata" && numar_cupe == 3)
            Meniu::set_price(cost + 3.5);
        else
            if(tip_desert == "inghetata" && numar_cupe == 4)
                Meniu::set_price(cost + 5);
            else
                if(tip_desert == "inghetata" && numar_cupe == 5)
                    Meniu::set_price(cost + 6.7);
                else
                    Meniu::set_price(cost);
    }
    virtual double get_price();
    string get_tip();
    void set_tip_desert(string, int);
    Desert operator=(const Desert&);
    friend ostream& operator<<(ostream &gout, Desert &desert);
    friend istream& operator>>(istream &fin, Desert &desert);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vin_varsat:virtual public Meniu
{
    string tip_vin;
    double cantitate; // in ml
public:
    Vin_varsat(double pret = 17, string tip_vin = "rosu", double cantitate = 100);
    Vin_varsat(const Vin_varsat&);
    ~Vin_varsat();
    virtual void afisare_pret()
    {
        cout << pret;
    }
    virtual void set_price(double cost)
    {
        if (tip_vin == "rosu")
            cost += (cantitate / 10);
        else
            cost += (cantitate / 15);
        Meniu::set_price(cost);
    }
    virtual double get_price();
    string get_tip_vin_varsat();
    void set_tip_vin_varsat(string, double);
    Vin_varsat operator=(const Vin_varsat&);
    friend ostream& operator<<(ostream &gout, Vin_varsat &vin);
    friend istream& operator>>(istream &fin, Vin_varsat &vin);

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vin_la_sticla:virtual public Meniu
{
    string denumire;
    int an;
public:
    Vin_la_sticla(double pret = 25, string denumire = "Castel Bolovanu", int an = 2004);
    Vin_la_sticla(const Vin_la_sticla&);
    ~Vin_la_sticla();
    virtual void afisare_pret()
    {
        cout<<pret;
    }

    virtual void set_price(double cost)
    {

        if(denumire == "Bordeaux")
            cost += 20;
        else
            cost += 10;

        Meniu::set_price(cost);
    }
    virtual double get_price();
    string get_tip_vin_la_sticla();
    void set_tip_vin_la_sticla(string, int);
    Vin_la_sticla operator=(const Vin_la_sticla&);
    friend ostream& operator<<(ostream &gout, Vin_la_sticla &vin);
    friend istream& operator>>(istream &fin, Vin_la_sticla &vin);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Bere_la_sticla: virtual public Meniu
{
    string denumire;
    bool alcool;
public:
    Bere_la_sticla(double pret = 15, string denumire = "Timisoreana", bool alcool = true);
    Bere_la_sticla(const Bere_la_sticla&);
    ~Bere_la_sticla();
    virtual void afisare_pret()
    {
        cout<<pret;
    }
    virtual void set_price(double cost)
    {
        if(denumire == "Ursus")
            cost += 3;
        else
            if(denumire == "Tuborg")
                cost += 5;
            else
                if(denumire == "Heineken")
                    cost += 7;
        Meniu::set_price(cost);
    }
    virtual double get_price();
    string get_tip_bere_la_sticla();
    void set_tip_bere_la_sticla(string, bool);
    Bere_la_sticla operator=(const Bere_la_sticla&);
    friend ostream& operator<<(ostream &gout, Bere_la_sticla &bere);
    friend istream& operator>>(istream &fin, Bere_la_sticla &bere);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Apa:virtual public Meniu
{
    string denumire;
public:
    Apa(double pret = 20, string denumire = "Borsec");
    Apa(const Apa&);
    ~Apa();
    void afisare_pret()
    {
        cout << pret;
    }
    virtual void set_price(double cost)
    {
        if (denumire == "Dorna")
            cost += 2;
        else
            cost += 3;
        Meniu::set_price(cost);
    }
    virtual double get_price();
    string get_tip_apa();
    void set_tip_apa(string);
    Apa operator=(const Apa &);
    friend ostream& operator<<(ostream &gout, Apa &apa);
    friend istream& operator>>(istream &fin, Apa &apa);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Bauturi:public Vin_varsat, public Vin_la_sticla, public Bere_la_sticla, public Apa
{
    double mediu_price;
public:
    Bauturi(double pret = 6.5);
    Bauturi(const Bauturi&);
    ~Bauturi();
    void set_price(double cost)
    {
        mediu_price = cost;
    }
    void afisare_pret()
    {
        cout << pret;
    }
    virtual void calculeaza_pret_mediu();
    Bauturi operator=(const Bauturi&);
    friend ostream& operator<<(ostream &gout, Bauturi&);
    friend istream& operator>>(istream &fin, Bauturi&);
};


/// =============================================================================================================================
void dialog_interactiv()
{
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << "                                     BINE ATI VENIT IN RESTAURANT!                              \n";
    cout << "------------------------------------------------------------------------------------------------\n";
    cout << '\n';

    bool client_adaugat_deja_la_masa = false;
    int numar_mese, numar_clienti, numar_client_de_la_masa;
    cout << "Introduceti numarul de mese din restaurantul dumneavoastra: ";
    cin >> numar_mese;
    cout << "\n----------------------------------------------------------------------------------------\n\n";
    for (int i = 1 ; i <= numar_mese ; ++i)
    {
        Masa table;
        table.incrementare_index_masa();
        int numar_masa_din_restaurant = table.obtine_index_masa();
        string sir, comanda;
        double pret;
        table.reset_index_client();
        cin >> table;
        cout << "Pentru masa cu numarul " << numar_masa_din_restaurant << " introduceti numarul de clienti care sosesc: ";
        cin >> numar_clienti;
        while (table.get_capacitate_masa() < numar_clienti)
        {
            cout << "Masa este prea mica pentru numarul de clienti.\n";
            cout << "Dati alt numar de clienti: ";
            cin >> numar_clienti;
        }
        for (int j = 1 ; j <= numar_clienti ; ++j)
        {
            if(client_adaugat_deja_la_masa == false)
            {
                table.adauga_client_la_masa();
                table.incrementare_index_client();
                numar_client_de_la_masa = table.obtine_index_client();
            }
            cout << "Detalii despre comanda clientului " << numar_client_de_la_masa << " (scrieti cu litere mici, doar marca produselor cu majuscula)" << '\n';
            cout << "Doriti ceva de baut?(da / nu): ";
            cin >> sir;
            if (sir == "da")
            {
                cout << "Doriti vin, bere sau apa?: ";
                cin >> sir;
                string tip, culoare;
                double nr;
                int n;
                if (sir == "vin")
                {
                    cout << "Doriti la pahar(varsat) sau la sticla?(pahar / sticla): ";
                    cin >> tip;
                    if (tip == "pahar")
                    {
                        Vin_varsat vin_la_pahar;
                        cout << "Cati ml ati dori?: ";
                        cin >> nr;

                        try
                        {
                            vin_la_pahar.set_tip_vin_varsat(culoare, nr);
                        }
                        catch(double x)
                        {
                            while (nr != 100)
                            {
                                cout << "Nu avem cantitatea asta! Dispunem doar de 100 ml!!)\n";
                                cout << "Cati ml ati dori?: ";
                                cin >> nr;
                            }

                        }

                        cout << "Ce culoare?(rosu / alb): ";
                        cin >> culoare;
                        vin_la_pahar.set_tip_vin_varsat(culoare, nr);
                        if (culoare == "rosu")
                            vin_la_pahar.set_price(13);
                        else
                            vin_la_pahar.set_price(11);
                        comanda = sir + " la " + tip + " " + culoare;
                        table.adauga_comanda_la_client(j , comanda);
                        pret = vin_la_pahar.get_price();
                        table.adauga_pret_la_client(j , pret);
                    }
                    else
                        if (tip == "sticla")
                        {
                            Bauturi o;
                            Vin_la_sticla *sticla = &o; // upcasting
                            cout << "Ce firma ati dori?(Bordeaux / Castel Bolovanu): ";
                            cin.get();
                            getline(cin, culoare);
                            cout << "Din ce an sa fie?(1996 / 2004): ";
                            cin >> n;
                            sticla->set_tip_vin_la_sticla(culoare, n);
                            sticla->Vin_la_sticla::set_price(45);
                            pret = sticla->get_price();
                            comanda = sir + " la " + tip + " de tip " + culoare + " din anul " + to_string(n);
                            table.adauga_comanda_la_client(j , comanda);
                            table.adauga_pret_la_client(j , pret);
                        }
                        else
                            cout << "Imi pare rau, dar nu avem in meniu!\n";
                }
                else
                    if (sir == "bere")
                    {
                        string s1, s2;
                        bool alcool;
                        Meniu *bere = new Bere_la_sticla; // upcasting
                        Bere_la_sticla *o = dynamic_cast <Bere_la_sticla*> (bere);  // downcasting
                        cout << "De la ce firma?(Tuborg / Heineken / Timisoreana / Guinness): ";
                        cin >> s1;
                        cout << "Doriti cu alcool sau fara?(cu / fara): ";
                        cin >> s2;
                        if (s2 == "cu")
                        {
                            alcool = true;
                            comanda = sir + " " + s1 + " " + "cu alcool";
                        }
                        else
                        {
                            alcool = false;
                            comanda = sir + " " + s1 + " " + "fara alcool";
                        }
                        o->set_tip_bere_la_sticla(s1, alcool);
                        o->set_price(8);
                        table.adauga_comanda_la_client(j , comanda);
                        pret = o->get_price();
                        table.adauga_pret_la_client(j , pret);

                    }
                    else
                        if (sir == "apa")
                        {
                            Apa *ob = new Bauturi;                          // upcasting
                            Bauturi *a = dynamic_cast<Bauturi*>(ob);        // downcasting cu dynamic_cast(am functii virtuale in clasa
                                                                            // de baza "Apa")
                            string fel_apa;
                            cout << "De la ce firma?(Dorna / Borsec / Aqua_Carpatica): ";
                            cin >> fel_apa;
                            a->set_tip_apa(fel_apa);
                            a->Apa::set_price(4);
                            comanda = sir + " " + fel_apa;
                            pret = a->Apa::get_price();
                            table.adauga_comanda_la_client(j , comanda);
                            table.adauga_pret_la_client(j , pret);

                        }
            }

            cout << "Doriti, poate, si ceva de mancare?(da / nu): ";
            cin >> sir;
            if (sir == "da")
            {
                cout << "Doriti ciorba?: ";
                cin >> sir;
                if (sir == "da")
                {
                    string s1, s2, s3;
                    bool smantana, ardei;
                    cout << "Ce fel de ciorba?(legume / ciuperci / burta): ";
                    cin >> s1;
                    Ciorba obiect;
                    if (s1 == "legume" or s1 == "ciuperci" or s1 == "burta")
                    {
                        comanda = "ciorba de " +  s1;
                        cout << "Cu sau fara smantana?(cu / fara): ";
                        cin >> s2;
                        if(s2 == "cu")
                        {
                            smantana = true;
                            comanda += " cu smantana";
                        }
                        else
                            smantana = false;

                        cout << "Cu sau fara ardei?(cu / fara): ";
                        cin >> s3;
                        if(s3 == "cu")
                        {
                            ardei = true;
                            comanda += " cu ardei";
                        }
                        else
                            ardei = false;

                        obiect.set_tip_ciorba(s1, smantana, ardei);
                        obiect.set_price(23.5);
                        pret = obiect.get_price();
                        table.adauga_comanda_la_client(j , comanda);
                        table.adauga_pret_la_client(j , pret);
                    }
                    else
                        cout << "Nu exista acest tip de ciorba in meniu!\n";

                }

                cout << "Doriti fel principal?: ";
                cin >> sir;
                string s1, s2, s3;
                if (sir == "da")
                {
                    Fel_principal princ;
                    cout << "Doriti carne de pui sau vita?(pui / vita): ";
                    cin >> s1;
                    if (s1 == "pui")
                    {
                        cout << "Doriti frigarui sau tocana?: ";
                        cin >> s2;
                        comanda = s2 + " de pui";
                        princ.set_tip_carne(s1, s2);
                        princ.set_price(27.6);
                        pret = princ.get_price();
                        table.adauga_comanda_la_client(j , comanda);
                        table.adauga_pret_la_client(j , pret);
                    }
                    else
                        if (s1 == "vita")
                        {
                             cout<<"Doriti vita Chateaubriand, Stroganoff sau File?: ";
                             cin >> s2;
                             s3 = "";
                             if (s2 == "Chateaubriand")
                             {
                                 cout << "Doriti sa fie frageda sau in sange?(frageda / in sange): ";
                                 cin.get();
                                 getline(cin, s3);
                                 if (s3 == "frageda")
                                    princ.set_price(53.7);
                                 else
                                    princ.set_price(63.2);
                             }
                             else
                                princ.set_price(47);

                             comanda = s1 + " " + s2 + " " + s3;
                             princ.set_tip_carne(s1, s2);
                             pret = princ.get_price();
                             table.adauga_comanda_la_client(j , comanda);
                             table.adauga_pret_la_client(j , pret);

                        }
                        else
                            cout << "Nu avem alt fel de carne!\n";

                    cout << "Doriti si garnitura la felul principal?: ";
                    cin >> s1;
                    if (s1 == "da")
                    {
                        Garnitura garni;
                        cout << "Doriti orez sau cartofi?: ";
                        cin >> s2;
                        if (s2 == "cartofi")
                        {
                            cout << "Doriti prajiti sau piure?: ";
                            cin >> s3;
                        }
                        else
                            if (s2 == "orez")
                                s3 = "sarbesc";
                        garni.set_tip_garnitura(s2, s3);
                        comanda = s2 + " " + s3;
                        Fel_principal *obiect = &garni; // upcasting cu virtual
                        obiect->set_price(8.4);
                        pret = obiect->get_price();
                        table.adauga_comanda_la_client(j , comanda);
                        table.adauga_pret_la_client(j , pret);
                    }

                }
                cout << "Doriti si desert?: ";
                cin >>sir;
                if (sir == "da")
                {
                    string s1;
                    int numar_cupe = 0;
                    Desert obiect;
                    cout << "Doriti inghetata sau tort krantz?(inghetata / tort krantz): ";
                    cin.get();
                    getline(cin, s1);
                    if (s1 == "inghetata")
                    {
                        cout << "Cate cupe ati dori?: ";
                        cin >> numar_cupe;
                        try
                        {
                            obiect.set_tip_desert("inghetata", numar_cupe);
                        }
                        catch(int a)
                        {
                            while (numar_cupe < 3 or numar_cupe > 5)
                            {
                                cout << "Avem doar intre 3 si 5 cupe!\n";
                                cout << "Cate cupe ati dori?: ";
                                cin >> numar_cupe;
                            }
                        }
                        catch(...)
                        {
                            cout << "Numar cupe incorect!\n";
                        }
                        comanda = "inghetata cu " + to_string(numar_cupe) + " cupe";
                        obiect.set_price(2.8);
                        pret = numar_cupe * obiect.get_price();
                        table.adauga_comanda_la_client(j , comanda);
                        table.adauga_pret_la_client(j , pret);
                    }
                    else
                        if (s1 == "tort krantz")
                        {
                            comanda = s1;
                            obiect.set_price(10);
                            pret = obiect.get_price();
                            table.adauga_comanda_la_client(j , comanda);
                            table.adauga_pret_la_client(j , pret);
                        }
                        else
                            cout << "Nu avem acest desert in meniu!\n";
                }
            }
        client_adaugat_deja_la_masa = false;
        if (numar_clienti < table.get_capacitate_masa())
        {
            string client_nou;
            cout << "Doriti sa mai vina un client la aceasta masa?: ";
            cin >> client_nou;
            if (client_nou == "da")
            {
                table.adauga_client_la_masa();
                table.incrementare_index_client();
                numar_client_de_la_masa = table.obtine_index_client();
                ++numar_clienti;
                client_adaugat_deja_la_masa = true;
                if (numar_clienti == table.get_capacitate_masa())
                    cout << "\nMasa este full! Nu mai incap clienti la aceasta masa!!\n\n";
            }
        }

        }

        cout << '\n';
        bool ok = true;
        int optiune;
        while(ok)
        {
            cout << "Doriti sa afisez nota pe un client sau pe toata masa? (0 - exit optiune nota, 1 - toata masa, 2 - un anumit client): ";
            cin >> optiune;
            switch(optiune)
            {
            case 1:
                cout << table << '\n';
                table.afiseaza_nota_total_pe_masa();
                cout << '\n';
                break;
            case 2:
                int nr_client;
                cout << "Dati numar client: ";
                cin >> nr_client;
                table.afiseaza_nota_total_pe_un_client(nr_client);
                cout << '\n';
                break;
            case 0:
                ok = false;
                cout << "La revedere!! :)\n";
                break;
            default:
                cout << "Optiune invalida! Dati alta optiune!\n\n";
                break;
            }
        }
        if (i != numar_mese)
                cout << "\n                                        NEW TABLE                                         \n";
        cout << "\n------------------------------------------------------------------------------------------\n\n";
    }
    cout << "                  =======      SFARSITUL PROGRAMULUI      =======                    \n";
}
/// =============================================================================================================================


int main()
{
    // =================
    dialog_interactiv();
    // =================

    return 0;
}

///Meniu      ------------------------------------------------------------------------------------------------------
Meniu::Meniu():pret(0){}
Meniu::Meniu(double new_price):pret(new_price) {}
Meniu::Meniu(const Meniu &o)
{
    pret = o.pret;
}
Meniu::~Meniu()
{
    pret = 0;
}
void Meniu::set_price(double new_cost)
{
    pret = new_cost;
}


///Client      ------------------------------------------------------------------------------------------------------
Client::Client(int nr_client_nou, double total_nou, string comanda_nou):nr_client(nr_client_nou), nota_total(total_nou), comanda(comanda_nou)
{

}
Client::Client(Client &o)
{
    nr_client = o.nr_client;
    nota_total = o.nota_total;
    comanda = o.comanda;
}
Client::~Client()
{
    nota_total = 0;
    comanda.clear();
}
ostream& operator<<(ostream &gout, const Client &client1)
{
    gout << "Clientul cu numarul " << client1.nr_client << " aveti de platit " << client1.nota_total
            << " lei pentru comanda: " << client1.comanda;
    return gout;
}
istream& operator>>(istream &fin, Client &client1)
{
    cout << "Dati numar client: ";
    fin >> client1.nr_client;
    cout << "Dati comanda clientului: ";
    fin.get();
    getline(fin, client1.comanda);
    return fin;
}

Client Client::operator=(const Client &o)
{
    if(this != &o)
    {
        nr_client = o.nr_client;
        comanda = o.comanda;
        nota_total = o.nota_total;
    }
    return *this;
}
int Client::get_nr_client()
{
    return nr_client;
}
double Client::get_nota_total()
{
    return nota_total;
}
string Client::get_comanda()
{
    return comanda;
}
void Client::set_comanda(string sir)
{
    this->comanda = sir;
}
void Client::set_nr_client(int numar)           /// Am folosit si cateva this-uri prin aceasta parte
{
    this->nr_client = numar;
}
void Client::adauga_la_comanda(string produs)
{
    if(this->get_comanda() != "")
        comanda = this->get_comanda() + ", " + produs;
    else
        comanda = produs ;
}
void Client::adauga_la_nota_total(double price)
{
    this->nota_total = this->get_nota_total() + price;
}
void Client::adauga_comanda_si_pret(string produs, double price)
{
    if(this->get_comanda() != "")
        comanda = this->get_comanda() + ", " + produs;
    else
        comanda = produs ;
    this->nota_total = this->get_nota_total() + price;
}


///Masa      ------------------------------------------------------------------------------------------------------
Masa::Masa(int clients_number, int table_capacity): numar_clienti(clients_number), capacitate_masa(table_capacity)
{
    masa_de_clienti = new Client[table_capacity + 1];
}

Masa::Masa(const Masa &o): masa_de_clienti(o.masa_de_clienti)
{
    capacitate_masa = o.capacitate_masa;
    numar_clienti = o.numar_clienti;
    masa_de_clienti = new Client[capacitate_masa + 1];
    for (int i = 1 ; i <= capacitate_masa ; ++i)
        masa_de_clienti[i] = o.masa_de_clienti[i];
}
Masa::~Masa()
{
    delete []masa_de_clienti;
    this->capacitate_masa = 0;
    this->numar_clienti = 0;
}

Masa Masa::operator=(const Masa &o)
{
    if(this != &o)
    {
        numar_clienti = o.numar_clienti;
        capacitate_masa = o.capacitate_masa;
        masa_de_clienti = new Client[capacitate_masa + 1];
        for (int i = 1 ; i <= capacitate_masa ; ++i)
            masa_de_clienti[i] = o.masa_de_clienti[i];
    }
    return *this;
}
ostream& operator<<(ostream &gout, const Masa &table)
{
    gout << "La masa sunt ocupate " << table.numar_clienti << " locuri din " << table.capacitate_masa << " locuri totale.\n";
    gout << "Detalii fiecare client: \n";
    for (int i = 1 ; i <= table.numar_clienti ; ++i)
        cout << table.masa_de_clienti[i] << '\n';
    //gout << "Clientul cu namr"
    return gout;
}
istream& operator>>(istream &fin, Masa &table)
{
    string sir;
    cout << "Introduceti capacitatea mesei: ";
    fin >> table.capacitate_masa;

    return fin;
}
void Masa::adauga_client_la_masa()
{
    if(numar_clienti + 1 <= capacitate_masa)
    {
        ++numar_clienti;
        masa_de_clienti[numar_clienti].set_nr_client(numar_clienti);
    }

}
void Masa::adauga_comanda_la_client(int nr_client, string s)
{
    if(nr_client <= capacitate_masa)
        masa_de_clienti[nr_client].adauga_la_comanda(s);
}
void Masa::adauga_pret_la_client(int nr_client, double pret)
{
    if(nr_client <= capacitate_masa)
        masa_de_clienti[nr_client].adauga_la_nota_total(pret);
}
void Masa::adauga_comanda_si_pret_la_client(int nr_client, string s, double pret)
{
    if(nr_client <= capacitate_masa)
        {
            masa_de_clienti[nr_client].adauga_la_comanda(s);
            masa_de_clienti[nr_client].adauga_la_nota_total(pret);
        }
}
double Masa::nota_total_pe_un_client(int nr_client)
{
    if (nr_client <= capacitate_masa)
        return masa_de_clienti[nr_client].get_nota_total();
}
double Masa::nota_total_pe_masa()
{
    double total = 0;
    for (int i = 1 ; i <= numar_clienti ; ++i)
        total += masa_de_clienti[i].get_nota_total();
    return total;
}
void Masa::afiseaza_nota_total_pe_un_client(int nr_client)
{
    cout << masa_de_clienti[nr_client] << '\n';
}
void Masa::afiseaza_nota_total_pe_masa()
{
    cout << "Totalul pe aceasta masa este: " << nota_total_pe_masa();
    cout << " lei.\n";
}
int Masa::numar_clienti_de_la_o_masa()
{
    return this->numar_clienti;
}
int Masa::get_capacitate_masa()
{
    return this->capacitate_masa;
}
Masa* Masa::memorare_afisare_n_obiecte()
{
    int numar_mese;
    cout << "Dati numarul de mese: ";
    cin >> numar_mese;
    Masa a[numar_mese];
    for (int i = 1 ; i <= numar_mese ; ++i)
        cin >> a[i];
    cout << '\n';
    for(int i = 1 ; i <= numar_mese ; ++i)
        cout << a[i];
    return a;
}


///Ciorba      ------------------------------------------------------------------------------------------------------
Ciorba::Ciorba(double pret, string tip_ciorba1, bool smantana1, bool ardei1):Meniu(pret),tip_ciorba(tip_ciorba1),smantana(smantana1), ardei(ardei1)
{

}
Ciorba::Ciorba(const Ciorba &o)
{
    pret = o.pret;
    tip_ciorba = o.tip_ciorba;
    smantana = o.smantana;
    ardei = o.ardei;
}

void Ciorba::afisare_pret()
{
    cout << pret;
}
void Ciorba::set_price(double price)
{
    if (tip_ciorba == "burta")
        price += 8;
    else
        if (tip_ciorba == "ciuperci")
            price += 6;
    if(smantana)
        price += 3;
    if(ardei)
        price += 1.5;

    Meniu::set_price(price);
}
void Ciorba::set_tip_ciorba(string tip, bool smantana, bool ardei)
{
    tip_ciorba = tip;
    this->smantana = smantana;
    this->ardei = ardei;
    Ciorba::set_price(0);
}
double Ciorba::get_price()
{
    return pret;
}

string Ciorba::get_tip_ciorba()
{
    return tip_ciorba;
}

Ciorba Ciorba::operator=(const Ciorba &o)
{
    if(this!=&o)
    {

        pret = o.pret;
        tip_ciorba = o.tip_ciorba;
        smantana = o.smantana;
        ardei = o.ardei;
    }
    return *this;
}

ostream& operator<<(ostream &gout, Ciorba &ciorba)
{
    gout<<"Pentru ciorba de "<<ciorba.tip_ciorba;
    if(ciorba.smantana == true)
        cout<<" cu smantana, ";
    if(ciorba.ardei == true)
        cout<<" cu ardei,  ";
    cout<<"Pretul este de: ";
    gout<<ciorba.pret << " lei.";
    cout<<"\n";
    return gout;
}

istream& operator>>(istream &fin, Ciorba &ciorba)
{
    cout<<"Dati tipul de ciorba: ";
    fin>>ciorba.tip_ciorba;
    string s;
    cout<<"Doriti cu smantana?: ";
    fin>>s;
    if(s=="da")
        ciorba.smantana = true;
    else
        ciorba.smantana = false;

    cout<<"Doriti cu ardei?: ";
    fin>>s;
    if(s=="da")
        ciorba.ardei = true;
    else
        ciorba.ardei = false;

    cout<<"Dati pretul: ";
    double pr;
    fin>>pr;
    ciorba.set_price(pr);
    return fin;
}


///Fel_principal      ------------------------------------------------------------------------------------------------------
Fel_principal::Fel_principal(double pret, string carne, string tip):Meniu(pret), carne(carne), fel_carne(tip)
{

}
Fel_principal::Fel_principal(const Fel_principal &o)
{
    pret = o.pret;
    carne = o.carne;
    fel_carne = o.fel_carne;
}
void Fel_principal::afisare_pret()
{
    cout << pret;
}
double Fel_principal::get_price()
{
    return pret;
}
void Fel_principal::set_tip_carne(string carne1, string tip)
{
    this->carne = carne1;
    this->fel_carne = tip;
}
string Fel_principal::get_tip_carne()
{
    return carne + " " + this->fel_carne;
}
Fel_principal Fel_principal::operator=(const Fel_principal &o)
{
    if(this != &o)
    {
        pret = o.pret;
        carne = o.carne;
        fel_carne = o.fel_carne;
    }
    return *this;
}
ostream& operator<<(ostream &gout, Fel_principal &fel)
{
    gout << "Pentru preparatul din carne de " << fel.carne << " de tipul " << fel.fel_carne << '\n';
    gout << "Pretul este de " << fel.pret << " lei.\n";
    return gout;
}
istream& operator>>(istream &fin, Fel_principal &fel)
{
    cout << "Dati tipul de carne: ";
    fin >> fel.carne;
    cout << "Alegeti sortimentul carnii: ";
    fin >> fel.fel_carne;

    cout << "Dati pretul pentru carne: ";
    double pr;
    fin >> pr;
    fel.set_price(pr);
    return fin;
}


///Garnitura      ------------------------------------------------------------------------------------------------------
Garnitura::Garnitura(double pret, string carne, string tip_carne, string leguma, string tip_garni):
Fel_principal(pret, carne, tip_carne), leguma(leguma), tip_garnitura(tip_garni)
{

}
Garnitura::Garnitura(const Garnitura &o)
{
    pret = o.pret;
    leguma = o.leguma;
    tip_garnitura = o.tip_garnitura;
}
Garnitura::~Garnitura()
{
    leguma = "";
    tip_garnitura = "";
}
void Garnitura::set_tip_garnitura(string leguma, string nume)
{
    leguma = leguma;
    tip_garnitura = nume;
}
double Garnitura::get_price()
{
    return pret;
}
string Garnitura::get_tip_garnitura()
{
    return leguma + " " + tip_garnitura;
}
Garnitura Garnitura::operator=(const Garnitura &o)
{
    if(this!=&o)
    {
        this->Fel_principal::operator=(o);
        pret = o.pret;
        leguma = o.leguma;
        tip_garnitura = o.tip_garnitura;
    }
    return *this;
}

ostream& operator<<(ostream &gout, Garnitura &garnitura)
{
    gout<<"pt garnitura "<<garnitura.leguma<<" cu denumirea "<<garnitura.tip_garnitura;
    gout<<" pretul este ";
    gout<<garnitura.pret;
    gout<<"\n";
    return gout;
}

istream& operator>>(istream &fin, Garnitura &garnitura)
{
    cout<<"dati din ce vreti garnitura:\n ";
    fin>>garnitura.leguma;
    cout<<"dati modul de perparare:\n";
    fin>>garnitura.tip_garnitura;

    cout<<"dati pretul: ";
    double pr;
    fin>>pr;
    garnitura.set_price(pr);
    return  fin;
}


///Desert      ------------------------------------------------------------------------------------------------------
Desert::Desert(double pret, string tip_desert, int nr_cupe):Meniu(pret),tip_desert(tip_desert),numar_cupe(nr_cupe)
{

}
Desert::Desert(const Desert &o)
{
    pret = o.pret;
    tip_desert = o.tip_desert;
    numar_cupe = o.numar_cupe;
}
Desert::~Desert()
{
    tip_desert = "";
    numar_cupe = 0;
}

void Desert::set_tip_desert(string tip, int nr_cupe)
{
    this->tip_desert  = tip;
    this->numar_cupe = nr_cupe;
    if(tip_desert == "inghetata" and (nr_cupe < 3 or nr_cupe >5))
        throw 0;

}
double Desert::get_price()
{
    return pret;
}

string Desert::get_tip()
{
    return tip_desert;
}

Desert Desert::operator=(const Desert &o)
{
    if(this!=&o)
    {
        pret = o.pret;
        tip_desert = o.tip_desert;
        numar_cupe = o.numar_cupe;
    }
    return *this;
}

ostream& operator<<(ostream &gout, Desert &desert)
{
    gout<<"pt desertul "<<desert.tip_desert<<" pretul este ";
    gout<<desert.pret;
    if(desert.tip_desert == "inghetata")
        gout<<" si nr de cupe este "<<desert.numar_cupe;
    return gout;
}

istream& operator>>(istream &fin, Desert &desert)
{
    cout<<"dati tipul de desert:\n ";
    fin>>desert.tip_desert;
    if(desert.tip_desert == "inghetata")
    {
        cout<<"dati numar cupe: ";
        fin>>desert.numar_cupe;
    }
    cout<<"dati pretul: ";
    double pr;
    fin>>pr;
    desert.set_price(pr);
    return  fin;
}


///Vin_varsat      ------------------------------------------------------------------------------------------------------
Vin_varsat::Vin_varsat(double pret, string tip_vin1, double cantitate1):Meniu(pret),tip_vin(tip_vin1),cantitate(cantitate1)
{

}
Vin_varsat::Vin_varsat(const Vin_varsat &o)
{
    pret = o.pret;
    tip_vin = o.tip_vin;
    cantitate = o.cantitate;
}
Vin_varsat::~Vin_varsat()
{
    cantitate = 0;
    tip_vin = "";
}
void Vin_varsat::set_tip_vin_varsat(string tip_vin, double nr)
{
    this->tip_vin = tip_vin;
    this->cantitate = nr;
    if(nr != 100)
        throw nr;
}

double Vin_varsat::get_price()
{
    return pret;
}

string Vin_varsat::get_tip_vin_varsat()
{
    return tip_vin;
}

Vin_varsat Vin_varsat::operator=(const Vin_varsat &o)
{
    if(this != &o)
    {
        pret = o.pret;
        tip_vin = o.tip_vin;
        cantitate = o.cantitate;
    }
    return *this;
}

ostream& operator<<(ostream &gout, Vin_varsat &vin)
{
    gout<<"pt vinul varsat "<<vin.tip_vin<<vin.cantitate<<" mililitri";
    gout<<" pretul este ";
    gout<<vin.pret;
    gout<<"\n";
    return gout;
}

istream& operator>>(istream &fin, Vin_varsat &vin)
{
    cout<<"dati ce tip_vin de vin varsat doriti:\n ";
    fin>>vin.tip_vin;
    cout<<"dati cantitatea:\n";
    fin>>vin.cantitate;

    cout<<"dati pretul: ";
    double pr;
    fin>>pr;
    vin.set_price(pr);
    return  fin;
}


///Vin_la_sticla       -----------------------------------------------------------------------------------------------
Vin_la_sticla::Vin_la_sticla(double pret, string denumire1, int an1):Meniu(pret),denumire(denumire1),an(an1)
{

}
Vin_la_sticla::Vin_la_sticla(const Vin_la_sticla &o)
{
    pret = o.pret;
    denumire = o.denumire;
    an = o.an;
}
Vin_la_sticla::~Vin_la_sticla()
{
    denumire = "";
    an = 0;
}
void Vin_la_sticla::set_tip_vin_la_sticla(string denumire, int an)
{
    this->denumire = denumire;
    this->an = an;
}
double Vin_la_sticla::get_price()
{
    return pret;
}

string Vin_la_sticla::get_tip_vin_la_sticla()
{
    return denumire;
}

Vin_la_sticla Vin_la_sticla::operator=(const Vin_la_sticla &o)
{
    if(this != &o)
    {
        pret = o.pret;
        denumire = o.denumire;
        an = o.an;
    }
    return *this;
}

ostream& operator<<(ostream &gout, Vin_la_sticla &vin)
{
    gout<<"pt vinul la sticla "<<vin.denumire <<" din anul "<<vin.an;
    gout<<" pretul este ";
    gout<<vin.pret;
    gout<<"\n";
    return gout;
}

istream& operator>>(istream &fin, Vin_la_sticla &vin)
{
    cout<<"dati ce marca de vin la sticla doriti:\n ";
    fin>>vin.denumire;
    cout<<"dati anul de productie:\n";
    fin>>vin.an;

    cout<<"dati pretul: ";
    double pr;
    fin>>pr;
    vin.set_price(pr);
    return  fin;
}


///Bere_la_sticla           ----------------------------------------------------------------------------------------------------------
Bere_la_sticla::Bere_la_sticla(double pret, string denumire1, bool alcool1):Meniu(pret),denumire(denumire1),alcool(alcool1)
{

}
Bere_la_sticla::Bere_la_sticla(const Bere_la_sticla &o)
{
    pret = o.pret;
    denumire = o.denumire;
    alcool = o.alcool;
}

Bere_la_sticla::~Bere_la_sticla()
{
    denumire = "";
    alcool = false;
}

void Bere_la_sticla::set_tip_bere_la_sticla(string denumire, bool alcool)
{
    this->denumire = denumire;
    this->alcool = alcool;

}
double Bere_la_sticla::get_price()
{
    return pret;
}
string Bere_la_sticla::get_tip_bere_la_sticla()
{
    return denumire;
}
Bere_la_sticla Bere_la_sticla::operator=(const Bere_la_sticla &o)
{
    if(this!=&o)
    {
        pret = o.pret;
        denumire = o.denumire;
        alcool = o.alcool;
    }
    return *this;
}

ostream& operator<<(ostream &gout, Bere_la_sticla &bere)
{
    gout<<"pt berea la sticla "<<bere.denumire;
    if(bere.alcool == true)
        gout<<" cu alcool";
    else
        cout<<" fara alcool";
    gout<<" pretul este ";
    gout<<bere.pret;
    gout<<"\n";
    return gout;
}

istream& operator>>(istream &fin, Bere_la_sticla &bere)
{
    cout<<"dati ce marca de bere la sticla doriti:\n ";
    fin>>bere.denumire;

    string s;
    cout<<"doriti cu alcool?:\n";
    fin>>s;
    if(s=="da")
        bere.alcool = true;
    else
        bere.alcool = false;
    cout<<"dati pretul: ";
    double pr;
    fin>>pr;
    bere.set_price(pr);
    return  fin;
}


///Apa            ----------------------------------------------------------------------------------------------------------
Apa::Apa(double pret, string denumire1):Meniu(pret),denumire(denumire1)
{

}
Apa::Apa(const Apa &o)
{
    pret = o.pret;
    denumire = o.denumire;
}
Apa::~Apa()
{
    denumire = "";
}
void Apa::set_tip_apa(string denumire)
{
    this->denumire = denumire;
}
double Apa::get_price()
{
    return pret;
}
string Apa::get_tip_apa()
{
    return denumire;
}
Apa Apa::operator=(const Apa &o)
{
    if(this!=&o)
    {
        pret = o.pret;
        denumire = o.denumire;
    }
    return *this;
}
ostream& operator<<(ostream &gout, Apa &apa)
{
    gout<<"pt sticla de apa"<<apa.denumire;
    gout<<" pretul este ";
    gout<<apa.pret;
    gout<<"\n";
    return gout;
}
istream& operator>>(istream &fin, Apa &apa)
{
    cout<<"dati ce marca de apa la sticla doriti:\n ";
    fin>>apa.denumire;
    cout<<"dati pretul: ";
    double pr;
    fin>>pr;
    apa.set_price(pr);
    return  fin;
}


///Bauturi    Mostenire Multipla   -----------------------------------------------------------------------------------------------------------------------
Bauturi::Bauturi(double pret):mediu_price(pret)
{

}
Bauturi::Bauturi(const Bauturi &o)
{
    pret = o.pret;
    mediu_price = o.mediu_price;
}
Bauturi::~Bauturi()
{
    mediu_price = 0;
}
void Bauturi::calculeaza_pret_mediu()
{
    cout << this->mediu_price;
}
Bauturi Bauturi::operator=(const Bauturi &o)
{
    if(this!=&o)
    {
        this->Vin_la_sticla::operator=(o);
        this->Vin_varsat::operator=(o);
        this->Bere_la_sticla::operator=(o);
        pret = o.pret;
        mediu_price = o.mediu_price;
    }
    return *this;
}
ostream& operator<<(ostream &gout, Bauturi &b)
{
    gout<<"pretul mediu al bauturilor este "<<b.mediu_price;
    gout<<"\n";
    return gout;
}

istream& operator>>(istream &fin, Bauturi &b)
{
    cout<<"dati pretul mediu al bauturilor:\n ";
    fin>>b.mediu_price;
    return  fin;
}
