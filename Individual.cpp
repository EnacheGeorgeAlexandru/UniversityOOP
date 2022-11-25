#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <windows.h>

class Individ {
    int i;
    char tip;
    int varsta;
    double energie;
    bool viu;

    void hraneste();
    void inmulteste(std::vector<Individ*>& vectorIndivizi);
    void ataca(std::vector<Individ*>& vectorIndivizi);
    void imbatraneste();
    void moare();
public:
    Individ();
    Individ(int pozitia = -1, char tipul = ' ');
    Individ(const Individ& object);
    Individ& operator=(const Individ& object);
    ~Individ();
    void actualizare(std::vector<Individ*>& vectorIndivizi);
    bool esteViu() const;
    void omoara();
    int getPozitie() const;
    char getTip() const;
    int getVarsta() const;
    double getEnergie() const;
    void setPozitie(const int pozitieP);
    void setTip(const char tipP);
    void setVarsta(const int varstaP);
    void setEnergie(const double energieP);

    friend std::istream& operator>>(std::istream& in, Individ& ob);
    friend std::ostream& operator<<(std::ostream& out, Individ& ob);
};

class Solution {
    int dimensiune = 0;
    std::vector<Individ*> vectorIndivizi;
public:
    Solution(int dimensiune);
    ~Solution();

    void bucla();
    void afisareMeniu() const;
    bool inputValid(int nr) const;
    int pozitiiLibere() const;
    void citire();
    void afisare() const;
    void actualizare();
    void esteViu() const;
    void getTip() const;
};

void Individ::hraneste()
{
    int min = 1;
    int max = 10;
    srand(time(0));
    int randNum = rand() % (max - min + 1) + min;
    energie = energie + randNum;
}

void Individ::inmulteste(std::vector<Individ*>& vectorIndivizi)
{
    if (i-1 >= 0)
        if (vectorIndivizi[i-1] == nullptr)
        {
            vectorIndivizi[i-1] = new Individ(i-1, tip);
            vectorIndivizi[i-1]->setEnergie(2 * energie);
            std::cout << "Individul de la pozitia " << i << " a creat un alt individ de acelasi tip la pozitia " << i-1 << '\n';
        }
    if (i+1 <  int(vectorIndivizi.size()))
        if (vectorIndivizi[i+1] == nullptr)
        {
            vectorIndivizi[i+1] = new Individ(i+1, tip);
            vectorIndivizi[i+1]->setEnergie(2 * energie);
            std::cout << "Individul de la pozitia " << i << " a creeat un alt individ de acelasi tip la pozitia " << i+1 << '\n';
        }
}

void Individ::ataca(std::vector<Individ*>& vectorIndivizi)
{
    if (i-1 >= 0)
        if (vectorIndivizi[i-1]->getTip() != tip)
            if (energie > vectorIndivizi[i-1]->getEnergie())
            {
                energie = energie - vectorIndivizi[i-1]->getEnergie();
                vectorIndivizi[i-1]->omoara();
                std::cout << "Individul de la pozitia " << i << " a atacat cu succes individul de la pozitia " << i-1 << '\n';
            }
    if (i+1 < int(vectorIndivizi.size()))
        if (vectorIndivizi[i+1]->getTip() != tip)
            if (energie > vectorIndivizi[i+1]->getEnergie())
            {
                energie = energie - vectorIndivizi[i+1]->getEnergie();
                vectorIndivizi[i+1]->omoara();
                std::cout << "Individul de la pozitia " << i << " a atacat cu succes individul de la pozitia " << i+1 << '\n';
            }
}

void Individ::imbatraneste()
{
    varsta += 1;
    energie -= 1;
    if (varsta == 100 || energie <= 0)
        moare();
}

void Individ::moare()
{
    viu = false;
    std::cout <<"Individul de la pozitia " << i << " a murit\n";
}

Individ::Individ(){};

Individ::Individ(int pozitia, char tipul) : i{ pozitia }, tip{ tipul }, varsta{ 0 }, energie{ 100 }, viu{ true } {}

Individ::Individ(const Individ& object)
{
    i = object.i;
    tip = object.tip;
    varsta = object.varsta;
    energie = object.energie;
    viu = object.viu;
}

Individ& Individ::operator=(const Individ& object)
{
    if(this == &object)
        return *this;
    i = object.i;
    tip = object.tip;
    varsta = object.varsta;
    energie = object.energie;
    viu = object.viu;
    return *this;
}

Individ::~Individ(){}

void Individ::actualizare(std::vector<Individ*>& vectorIndivizi)
{
    if(viu)
    {
        hraneste();
        inmulteste(vectorIndivizi);
        ataca(vectorIndivizi);
        imbatraneste();
    }
    else
        std::cout << "Individul de la pozitia " << i << " nu poate fi actualizat deoarece nu este viu.\n";

}

bool Individ::esteViu() const
{
    return viu;
}

void Individ::omoara()
{
    moare();
}

int Individ::getPozitie() const
{
    return i;
}

char Individ::getTip() const
{
    return tip;
}

int Individ::getVarsta() const
{
    return varsta;
}

double Individ::getEnergie() const
{
    return energie;
}

void Individ::setPozitie(const int pozitieP)
{
    i = pozitieP;
}
void Individ::setTip(const char tipP)
{
    tip = tipP;
}
void Individ::setVarsta(const int varstaP)
{
    varsta = varstaP;
}
void Individ::setEnergie(const double energieP)
{
    energie = energieP;
}

std::istream& operator>>(std::istream& in, Individ& ob)
{
    std::cout << "Introduceti pozitia individului:\n";
    in >> ob.i;
    std::cout << "Introduceti tipul individului:\n";
    in >> ob.tip;
    return in;
}

std::ostream& operator<<(std::ostream& out, Individ& ob)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorCode;
    if (ob.getTip() == '+')
        colorCode = 6;
    if (ob.getTip() == '0')
        colorCode = 13;
    SetConsoleTextAttribute(hConsole, colorCode);
    out << "        ~~~ \n       ";
    if (ob.esteViu())
        out << "(^_^) \n";
    else out << "(x_x) \n";
    out << "     ___ || ____ \n     --   ";
    out << ob.tip;
    out << "   -- \n    * -  ";
    SetConsoleTextAttribute(hConsole, 12);
    out << ob.energie;
    SetConsoleTextAttribute(hConsole, colorCode);
    out << "  - * \n   *   -  ";
    SetConsoleTextAttribute(hConsole, 10);
    out << ob.varsta;
    SetConsoleTextAttribute(hConsole, colorCode);
    out << "  -   * \n   *    - ";
    SetConsoleTextAttribute(hConsole, 9);
    out << ob.i;
    SetConsoleTextAttribute(hConsole, colorCode);
    out << " -    * \n         ** \n        *  * \n       *    * \n      *      * \n    **        ** \n\n";
    SetConsoleTextAttribute(hConsole, 15);
    return out;
}

Solution::Solution(int dimensiune) : dimensiune{ dimensiune }
{
    vectorIndivizi.resize(dimensiune, nullptr);
}

Solution::~Solution()
{
    for (auto& itr : vectorIndivizi) {
        delete itr;
        itr = nullptr;
    }
}

void Solution::bucla()
{
    std::string comanda;
    afisareMeniu();
    while (true)
    {
        std::cout << "\nIntroduceti comanda:\n";
        std::cin >> comanda;
        if (comanda == "stop")
            break;
        if (comanda == "citire")
            citire();
        if (comanda == "afisare")
            afisare();
        if (comanda == "actualizare")
            actualizare();
        if (comanda == "viu")
            esteViu();
        if (comanda == "tip")
            getTip();
        if (comanda == "meniu")
            afisareMeniu();
    }
}

void Solution::afisareMeniu() const
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "Pentru fiecare individ ";
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "energia ";
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << "este afisata cu ";
    SetConsoleTextAttribute(hConsole, 12);
    std::cout << "rosu, ";
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "varsta ";
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << "este afisata cu ";
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "verde, ";
    SetConsoleTextAttribute(hConsole, 9);
    std::cout << "pozitia ";
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << "este afisata cu ";
    SetConsoleTextAttribute(hConsole, 9);
    std::cout << "albastru, ";
    SetConsoleTextAttribute(hConsole, 15);
    std::cout << "iar tipul are aceeasi culoare ca si individul.\n";
    std::cout << "Comenzile disponibile:\n"
        << "-> citire\n"
        << "-> afisare\n"
        << "-> actualizare\n"
        << "-> viu\n"
        << "-> tip\n"
        << "-> meniu\n"
        << "-> stop\n";
}

bool Solution::inputValid(int nr) const
{
    if (nr < 0 || nr > dimensiune-1)
    {
        std::cout << "Numarul este in afara vectorului\n";
        return false;
    }
    if (vectorIndivizi[nr] == nullptr)
    {
        std::cout << "Nu exista un individ la acea pozitie\n";
        return false;
    }
    return true;
}

int Solution::pozitiiLibere() const
{
    int contorPoz = 0;
    for(auto i: vectorIndivizi)
        if(i == nullptr)
            contorPoz++;
    return contorPoz;
}
void Solution::citire()
{
    Individ* manPtr = nullptr;
    int nrIndivizi;
    std::cout << "Introduceti numarul de indivizi pe care doriti sa ii cititi:\n";
    std::cin >> nrIndivizi;
    while(nrIndivizi > pozitiiLibere() )
    {
        std::cout << "Puteti introduce maxim " << pozitiiLibere() << " de indivizi. Introduceti numarul de indivizi:\n";
        std::cin >> nrIndivizi;
    }
    for (int i = 0; i < nrIndivizi; i++)
    {
        manPtr = new Individ(-1,' ');
        std::cin >> *manPtr;
        while (vectorIndivizi[manPtr->getPozitie()] != nullptr || manPtr->getPozitie() < 0 || manPtr->getPozitie() > int(vectorIndivizi.size())-1)
        {
            std::cout << "Pozitia " << manPtr->getPozitie() << " nu este valida, introduceti alta pozitie:\n";
            int temp;
            std::cin >> temp;
            manPtr->setPozitie(temp);
        }
        while(manPtr->getTip() != '+' && manPtr->getTip() != '0')
        {
            std::cout << "Tipul individului poate sa fie numai + sau 0. Introduceti tipul:\n";
            char temp;
            std::cin >> temp;
            manPtr->setTip(temp);
        }
        vectorIndivizi[manPtr->getPozitie()] = manPtr;
    }
}

void Solution::afisare() const
{
    for (const auto j : vectorIndivizi)
        if (j != nullptr)
            std::cout << *j << '\n';
}

void Solution::actualizare()
{
    int nr;
    std::cout << "Introduceti pozitia individului pe care doriti sa il actualizati:\n";
    std::cin >> nr;
    if (inputValid(nr))
        vectorIndivizi[nr]->actualizare(vectorIndivizi);
}

void Solution::esteViu() const
{
    std::cout << "Introduceti numarul individului:\n";
    int nr;
    std::cin >> nr;
    if (inputValid(nr))
    {
        if (vectorIndivizi[nr]->esteViu())
            std::cout << "Este viu\n";
        else std::cout << "Nu este viu\n";
    }
}

void Solution::getTip() const
{
    std::cout << "Introduceti numarul individului:\n";
    int nr;
    std::cin >> nr;
    if (inputValid(nr))
        std::cout << "Tipul individului de la pozitia " << nr << " este: " << vectorIndivizi[nr]->getTip() << "\n";
}

int main()
{
    Solution sln{ 30 };
    sln.bucla();
}
