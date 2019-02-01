#include <iostream>
#include "saper.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Field::Field() // konstruktor pojedynczego pola
{
    mine = false;
    covered = true;
    flag = false;
}

void Field::place_mine() // metoda ustawiajaca mine
{
    mine = true;
}

bool Field::is_mine() // metoda sprawdzajaca wartosc logiczna miny na pojedynczym polu
{
    if (mine) return true;
    return false;
}

void Field::uncover() // metoda ukrywajaca pojedyncze pole
{
    covered = false;
}

bool Field::is_covered() // metoda zwracajaca wartosc logiczna zakrycia pola
{
    return covered;
}

void Field::place_flag() // metoda zakrywajaca pojedyncze pole
{
    flag = true;
}

void Field::change_flag() // metoda zmieniajaca wartosc logiczna zakrycia/odkrycia pola
{
    if (flag) flag = false;
    else flag = true;
}
