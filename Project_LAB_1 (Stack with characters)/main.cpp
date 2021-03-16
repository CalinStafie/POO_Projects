///Tema 4. Clasa ”Stiva_de_caractere” (implementata dinamic)

#include <bits/stdc++.h>

using namespace std;

//clasa Nod{ char info; Nod *next; }
class Nod
{
    //datele membre
    char info;
    Nod* next;

 public:
    //constructor de initializare fara niciun parametru
    Nod();

    //constructor de initializare cu un parametru pentru informatie
    Nod(char);

    //set-ari pentru informatie si *next
    void set_info(char);
    void set_next(Nod *);

    //get-ari pentru informatie si *next
    char get_info();
    Nod *get_next();

    //destructor
    ~Nod();
};

Nod::Nod()
{
    info = '\0';
    next = NULL;
}
Nod::Nod(char caracter)
{
    this->info = caracter;
    this->next = NULL;
}
void Nod::set_info(char caracter)
{
    this->info = caracter;
}
void Nod::set_next(Nod *urmator_element)
{
    this->next = urmator_element;
}
char Nod::get_info()
{
    return this->info;
}
Nod* Nod::get_next()
{
    return this->next;
}
Nod::~Nod()
{
    if(next != NULL)
        delete next;
}


//clasa Stiva_de_caractere
class Stiva_de_caractere
{
    //date membre
    Nod* varf_stiva;

public:
    //constructor de initializare (face varful stivei = NULL)
    Stiva_de_caractere();

    //constructor de copiere
    Stiva_de_caractere(Stiva_de_caractere& stack1);

    //destructor
    ~Stiva_de_caractere();

    //getari si setari pentru varful stivei
    Nod* get_varf();
    void set_varf(Nod*);

    //parcurgere toata stiva;
    void parcurgere();

    //metodele: push, pop, top, isempty
    void push(char);
    void pop();
    void top();
    bool isempty();

    //supraincarcarea operatorilor << si >>
    friend ostream& operator<<(ostream &gout, Stiva_de_caractere &stiva);
    friend istream& operator>>(istream &fin, Stiva_de_caractere &stiva);

    //metoda pentru inversarea unui sir
    string inversare_sir_cu_stiva(string&);

    //supraincarcarea operatorului -
    Stiva_de_caractere operator-(Stiva_de_caractere&);

    //citire afisare si memorare
    void citire_memorare_afisare();

    //metoda pentru afisare stiva de jos pana la varf
    void parcurgere_de_jos_in_sus();
};

Stiva_de_caractere::Stiva_de_caractere()
{
    varf_stiva = NULL;
}

Stiva_de_caractere::Stiva_de_caractere(Stiva_de_caractere& stack1)
{
    this->varf_stiva = stack1.get_varf();
    cout << "Stiva a fost copiata cu succes!" << '\n';
}

Stiva_de_caractere::~Stiva_de_caractere()
{
    while (varf_stiva != NULL)
    {
        Nod *p = varf_stiva;
        varf_stiva = varf_stiva->get_next();
        delete p;
    }
    delete varf_stiva;
    //cout << "Stiva a fost stearsa cu succes!"<<'\n';
}

Nod* Stiva_de_caractere::get_varf()
{
    return this->varf_stiva;
}

void Stiva_de_caractere::set_varf(Nod* varf_nou)
{
    this->varf_stiva = varf_nou;
}

void Stiva_de_caractere::parcurgere()
{
    if (varf_stiva == NULL)
    {
        cout << "Stiva este vida!"<<'\n';
        return;
    }

    Nod *p = varf_stiva;
    while (p != NULL)
    {
        cout<<p->get_info();
        p = p->get_next();
    }
    cout<<'\n';
}

void Stiva_de_caractere::push(char caracter)
{
    if(isempty())
    {
        Nod* q = new Nod();
        q->set_info(caracter);
        varf_stiva = q;
        delete q;
    }
    else
    {
        Nod* p = new Nod();
        p ->set_info(caracter);
        p ->set_next(varf_stiva);
        varf_stiva = p;
        delete p;

    }
}

void Stiva_de_caractere::pop()
{
    if(isempty())
        cout << "Stiva este vida!"<<'\n';
    else
    {
        Nod* p = varf_stiva;
        varf_stiva = varf_stiva->get_next();
        delete p;
    }

}


void Stiva_de_caractere::top()
{
    if(isempty())
        cout << "Stiva este vida!"<<'\n';
    else
        cout << varf_stiva->get_info()<<'\n';
}

bool Stiva_de_caractere::isempty()
{
    if (varf_stiva == NULL)
        return 1;
    return 0;
}

ostream& operator<<(ostream& gout, Stiva_de_caractere& stiva)
{
    while(!stiva.isempty())
    {
        gout << stiva.get_varf() ->get_info();
        stiva.pop();
    }
    gout<<'\n';
    return gout;
}

istream& operator>>(istream &fin, Stiva_de_caractere &stiva)
{
    string sir;
    cout << "Dati caracterele: ";
    getline(cin, sir);

    for(int i=0;i < sir.length();++i)
        stiva.push(sir[i]);

    return fin;
}

string Stiva_de_caractere::inversare_sir_cu_stiva(string& s)
{
    for(int i=0;s[i];++i)
        push(s[i]);
    s.clear();
    while(!isempty())
    {
        s.push_back(get_varf() ->get_info());
        pop();
    }
    return s;
}

Stiva_de_caractere Stiva_de_caractere::operator-(Stiva_de_caractere &stiva2)
{
    Stiva_de_caractere diferenta;
    while(!stiva2.isempty() and !this->isempty())
        if(this->get_varf() != NULL and stiva2.get_varf() != NULL)
            {
                if(this->get_varf()->get_info() > stiva2.get_varf()->get_info())
                {
                    diferenta.push(this->get_varf()->get_info());
                    this->pop();
                    stiva2.pop();
                }
                else
                {
                    diferenta.push(stiva2.get_varf()->get_info());
                    this->pop();
                    stiva2.pop();
                }
            }
    return diferenta;

}

void Stiva_de_caractere::parcurgere_de_jos_in_sus()
{
    Stiva_de_caractere rasturnata;
    if (varf_stiva == NULL)
    {
        cout << "Stiva este vida!"<<'\n';
        return;
    }

    Nod *p = varf_stiva;
    while (p != NULL)
    {
        rasturnata.push(p->get_info());
        p = p->get_next();
    }
    delete p;

    Nod *q = rasturnata.get_varf();
    while (q != NULL)
    {
        cout<<q->get_info();
        q = q->get_next();
    }
    cout<<'\n';
}

void Stiva_de_caractere::citire_memorare_afisare()
{
    int numar_stive;
    cout<<"Dati numarul de stive: ";
    cin>>numar_stive;
    cin.get();
    Stiva_de_caractere a[numar_stive+1];
    for(int i=0;i<numar_stive;++i)
        cin>>a[i];
    cout<<'\n';
    cout << "Optiuni afisare n obiecte: " << '\n';
    cout << "1 - Afisare cu ajutorul operatorului << (WARNING: Acest operator va sterge tot continutul fiecarei stive in timpul afisarii.)" << '\n';
    cout << "2 - Afisare cu metoda parcurgere (nu sterge elementele stivelor)" << '\n';
    cout << "3 - Afisare cu metoda parcurgere_de_jos_in_sus (afiseaza elementele from bottom to top)" << '\n';
    cout << "4 - Nu afisa nimic, doar salvam cele n stive (obiecte)" << '\n';
    int option_writing;
    cout << "Introduceti optiunea pentru afisare: ";
    cin >> option_writing;
    switch(option_writing)
    {
    case 1:
        {
            for(int i=0;i<numar_stive;++i)
                    cout << a[i];
            break;
        }
    case 2:
        {
            for(int i=0;i<numar_stive;++i)
                    a[i].parcurgere();
            break;
        }
    case 3:
        {
            for(int i=0;i<numar_stive;++i)
                    a[i].parcurgere_de_jos_in_sus();
            break;
        }
    case 4:
        {
            break;
        }

    }

}


void menu()
{
    cout << "Aveti urmatoarele optiuni din care puteti alege: " << '\n';
    cout << "1 - Creare obiect stiva_de_caractere (aici se vor verifica si constructorii de intializare si destructor)" << '\n';
    cout << "2 - Testare constructor de copiere" << '\n';
    cout << "3 - Parcurgere stiva (normal)" << '\n';
    cout << "4 - Parcurgere stiva (de jos in sus)" << '\n';
    cout << "5 - Meniu - Metode push, pop, top, isempty" << '\n';
    cout << "6 - Supraincarcare operator << " << '\n';
    cout << "7 - Supraincarcare operator >> " << '\n';
    cout << "8 - Inversare sir de caractere utilizand stiva" << '\n';
    cout << "9 - Supraincarcare operator -" << '\n';
    cout << "10 - Citirea, memorarea si afisarea a n obiecte citite de la tastatura" << '\n';
    cout << "0 - Iesire din program (EXIT)" << '\n';


    int optiune;
    bool loop = true;
    while(loop)
    {
        cout << '\n';
        cout << "Dati optiunea dumneavoastra: ";
        cin >> optiune;
        cin.get();
        switch(optiune)
        {

        case 0:
            {
                loop = false;
                cout << "Programul s-a incheiat cu succes!" << '\n';
                cout << "Puteti sa mai luati exemple si lucruri din comentariile din main :)" << '\n';
                break;
            }

        case 1:
            {
                Stiva_de_caractere stiva;
                /// am comentat acest cout de mai jos din destructor ca sa nu apara de fiecare data la distrugerea unui obiect
                /// puteti decomenta in destructor cout-ul respectiv pentru a afisa un mesaj de fiecare data cand este distrus un obiect
                cout << "Stiva a fost creata si stearsa cu succes!"<<'\n';
                break;
            }

        case 2:
            {
                /// nu am mai facut optiunea si cu set si get deoarece aceasta optiune face cam acelasi lucru ca o combinatie de set si get
                /// pentru un exemplu mai concret aveti in main un exemplu de comenzi pentru set si get
                Stiva_de_caractere stiva;
                stiva.push('T');
                stiva.push('S');
                stiva.push('E');
                stiva.push('T');
                Stiva_de_caractere copie(stiva);
                cout << copie;
                break;
            }
        case 3:
            {
                Stiva_de_caractere stack;
                cin >> stack;
                cout << "Stiva parcursa normal este: ";
                stack.parcurgere();
                break;
            }
        case 4:
            {

                Stiva_de_caractere stack;
                cin >> stack;
                cout << "Stiva parcursa de jos in sus este: ";
                stack.parcurgere_de_jos_in_sus();
                break;
            }
        case 5:
            {
                cout << "Alegeti metoda:" << '\n';
                cout << "1 - push" << '\n';
                cout << "2 - pop" << '\n';
                cout << "3 - top" << '\n';
                cout << "4 - isempty" << '\n';
                cout << "5 - afisati stiva curenta" << '\n';
                cout << "Apasati orice cifra mai mare decat 5 (e de preferat si 0) pentru a parasi meniul de metode!" << '\n';
                cout << '\n';

                int metoda;
                Stiva_de_caractere stiva_de_lucru;
                bool ok = true;
                while(ok)
                {
                    cout << "Dati metoda(push, pop, top, isempty, afisare, exit): ";
                    cin >> metoda;
                    switch(metoda)
                    {
                    case 1:
                        {
                            cout<<"Dati caracter care sa fie inserat in stiva: ";
                            char c;
                            cin >> c;
                            stiva_de_lucru.push(c);
                            cout << '\n';
                            break;
                        }
                    case 2:
                        {
                            if (!stiva_de_lucru.isempty())
                                cout << "Elementul din varful stivei a fost eliminat!" << '\n';
                            stiva_de_lucru.pop();
                            cout << '\n';
                            break;
                        }
                    case 3:
                        {
                            if (!stiva_de_lucru.isempty())
                                cout << "Elementul din varful stivei este: ";
                            stiva_de_lucru.top();
                            cout << '\n';
                            break;
                        }
                    case 4:
                        {
                            if (stiva_de_lucru.isempty())
                                cout << "Stiva este vida!" << '\n';
                            else
                                cout << "Stiva NU este vida!" << '\n';
                            cout << '\n';
                            break;
                        }
                    case 5:
                        {
                            if (!stiva_de_lucru.isempty())
                                cout << "Stiva curenta are componenta: ";
                            stiva_de_lucru.parcurgere();
                            cout << '\n';
                            break;
                        }
                    default:
                        {
                            ok = false;
                            cout << "Am iesit din meniul cu metode!" << '\n';
                        }
                    }
                }
                break;
            }
        case 6:
            {
                Stiva_de_caractere stiva;
                cin >> stiva;
                cout << stiva;
                cout << "S-a realizat supraincarcarea operatorului << (afisare + golire stiva )!";
                cout << '\n';
                break;
            }
        case 7:
            {
                Stiva_de_caractere stiva;
                cin >> stiva;
                cout << stiva;
                cout << "S-a realizat supraincarcarea operatorului >> (realizata prin push-uri succesive)!";
                cout << '\n';
                break;
            }
        case 8:
            {
                cout << "Dati sirul care vreti sa fie inversat: ";
                string sir;
                Stiva_de_caractere stiva_aux;
                getline(cin, sir);
                cout << "Sirul inversat este: ";
                cout << stiva_aux.inversare_sir_cu_stiva(sir) << '\n';
                break;
            }
        case 9:
            {
                Stiva_de_caractere stiva_A, stiva_B, stiva_C, stiva_copie;

                cout << "Stiva_A: " << '\n';
                cin >> stiva_A;

                cout << "Stiva_B: " << '\n';
                cin >> stiva_B;

                stiva_C = stiva_A - stiva_B;
                stiva_copie = stiva_C;
                // Stiva_de_caractere stiva_copie"(stiva_C);
                cout << "S-a realizat supraincarcarea operatorului - si componenta stivei rezultat (Stiva_C, de sus in jos) este: ";
                cout << stiva_C;
                cout << "Stiva_C afisata de jos in sus (from bottom to top): ";
                stiva_copie.parcurgere_de_jos_in_sus();
                break;
            }
        case 10:
            {
                Stiva_de_caractere st;
                st.citire_memorare_afisare();
                break;
            }
        }
    }
}


int main()
{
    menu();
/*
    Stiva_de_caractere stiva;
    stiva.push('c');
    stiva.push('a');
    stiva.push('l');

    Stiva_de_caractere stiva2;
    stiva2.push('x');
    stiva2.push('2');
    stiva2.push('y');

    stiva.parcurgere_de_jos_in_sus();

    stiva.set_varf(stiva2.get_varf());
    cout << stiva;
/*
    Nod A('d');
    Nod b('p');
    A.set_info('c');
    Nod *a = new Nod();
    a->set_info('a');
    A.set_next(a);
    //cout<<a->get_info()<<"\n";
*/
/*
Stiva_de_caractere st;
    st.push('c');
    st.push('a');
    //st.pop();
    //st.pop();
    //st.pop();
    //st.top();
    st.push('f');
    //st.pop();
    st.push('x');
    //cout<<st;
    //st.parcurgere();
    /*cout<<st;
    st.parcurgere();


    string sir;
    getline(cin, sir);

    Stiva_de_caractere aux;
    cout << aux.inversare_sir_cu_stiva(sir) << '\n';

    Stiva_de_caractere st1;
    cin>>st1;
    cout<<st1;*/
/*
    Stiva_de_caractere S5,S4,S3;
    S3.push('E');
    S3.push('X');
    S3.push('A');
    S3.push('M');
    S3.push('E');
    S3.push('N');

    S4.push('P');
    S4.push('O');
    S4.push('O');
    S4.push('L');
    S4.push('A');
    S4.push('B');
    S4.push('O');
    S4.push('R');
    S4.push('A');
    S4.push('T');
    S4.push('O');
    S4.push('R');
     /*S3.parcurgere();
     S3.parcurgere_de_jos_in_sus();

     S4.parcurgere();
     S4.parcurgere_de_jos_in_sus();
    //cin>>S3;
    //cin>>S4;
     S5 = S3- S4;
     cout<<"Supraincarcare operator -: ";

     S5.parcurgere();
     S5.parcurgere_de_jos_in_sus();

     st.parcurgere();
     st.parcurgere_de_jos_in_sus();
     cout<<S5;

    Stiva_de_caractere X;
    X.citire_memorare_afisare();*/

//    Stiva_de_caractere stiva(S3);
  //  cout<<stiva;
    return 0;
}
