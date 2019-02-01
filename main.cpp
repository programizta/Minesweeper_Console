#include <iostream>
#include <cstdlib>
#include "saper.h"

using namespace std;

main()
{
    beginning:
    int bombs;

    do
    {
        cout << "Ile chcesz bomb rozmiescic? Podaj ich ilosc: ";

        while (!(cin >> bombs)) // dopoki strumien zglasza blad, dopoty wprowadzane sa bledne dane
        {
            cout << "To nie jest liczba! Wprowadz jeszcze raz ilosc bomb do rozmieszczenia: ";
            cin.clear();
            cin.sync();
        }

        if (bombs > M*N) cout << "Wprowadz ilosc min jeszcze raz, bo chcesz rozlokowac ich wiecej, niz jest pol!\n";
        else if (bombs < 0) cout << "Chcesz rozmiescic ujemna ilosc bomb? Na pewno? Jeszcze raz podaj ich wartosc\n";
    }
    while (bombs > M*N || bombs < 0);

    Board b1;
    b1.deploy_mines(bombs, true);
    b1.count_mines(0, 0);
    b1.play(b1);
    goto beginning;

    cin.get();
    return 0;
}
