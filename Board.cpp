#include <iostream>
#include "saper.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

Board::Board() // konstruktor calej planszy, musze go opracowac
{

}

void Board::deploy_mines(int n, bool random) // metoda rozmieszczajaca miny na planszy
{
    srand(time(NULL));
    bool is_bomb = true;
    if (n > M*N)
    {
        cout << "Nie mozna zainicjowac gry, bo chcesz rozmiescic wiecej min, niz jest pol!\n";
        getch();
        exit(0);
    }
    else if (is_bomb && random)
    {
        while (is_bomb && n > 0)
        {
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (!T[i][j].mine && n > 0 && rand() % 29 == 0) // ustawilem modulo 29,
                    {                                               // poniewaz jest to liczba pierwsza, nie za mala, nie za duza
                        T[i][j].place_mine();                       // i rozmiesci miny bardziej losowo na planszy
                        n--;
                    }
                }
            }
        }
    }
    else if (!random)
    {
        int j = 0;
        for (int i = 0; i < M; i++)
        {
            T[i][j].place_mine();
            j++;
        }
    }
}

bool Board::has_Mine(int x, int y) // metoda sprawdzajaca czy na zadanym polu znajduje sie mina
{
    if (T[x][y].mine)
    {
        return true;
    }
    return false;
}

int Board::count_mines(int x, int y) // metoda zliczajaca miny w poblizu odkrytego pola
{
    int near = 0;
    int edge_x = 0;
    int edge_y = 0;
    int edge_x_max = 3;
    int edge_y_max = 3;

    if (x == 0)
    {
        edge_x = 1;
    }
    if (y == 0)
    {
        edge_y = 1;
    }
    if (x == M - 1)
    {
        edge_x_max = 2;
    }
    if (y == N - 1)
    {
        edge_y_max = 2;
    }
    //stosuje oddzielne instrukcje warunkowe if, poniewaz warunki sa rozlaczne,
    //musza byc sprawdzane kazdorazowo

    for (int pomoc1 = edge_x; pomoc1 < edge_x_max; pomoc1++)
	{
		for (int pomoc2 = edge_y; pomoc2 < edge_y_max; pomoc2++)
		{
			if (has_Mine(x - 1 + pomoc1, y - 1 + pomoc2)) near++;
		}
	}
	return near;
}

void Board::reveal(int x, int y) // metoda odkrywajaca szereg pol na planszy
{
    T[x][y].uncover();

    if (!count_mines(x, y))
	{
		int x_min = 0;
		int y_min = 0;
		int x_max = 3;
		int y_max = 3;
		if (x == 0) // pierwsza krawedz x
		{
			x_min = 1;
		}
		if (y == 0) // pierwsza krawedz y
		{
			y_min = 1;
		}
		if (x == M - 1) // ostatnia krawedz x
		{
			x_max = 2;
		}
		if (y == N - 1) // ostatnia krawedz y
		{
			y_max = 2;
		}
		for (int i = x_min; i < x_max; i++)
		{
			for (int j = y_min; j < y_max; j++)
			{
				if (T[x - 1 + i][y - 1 + j].is_covered()) reveal(x - 1 + i, y - 1 + j); // rekurencyjnie wywolywana metoda reveal
			}                                                                           // gdy sa puste pola, kolega mi pomogl z tym
		}                                                                               // mialem z odkrywaniem pol ogromny problem
	}
}

void Board::display() // metoda wyswietlajaca wszystkie pola zgodnie z zasadami gry
{
    cout << "     ";
    for (int i = 0; i < N; i++)
    {
        cout << i << "  ";
    }
    cout << "\n";
    for (int j = 0; j < M; j++)
        {
            cout << endl << j << "   ";
            for (int k = 0; k < N; k++)
            {
                if (!T[j][k].covered && T[j][k].mine) cout << "[x]";
                else if (T[j][k].covered && T[j][k].flag) cout << "[?]";
                     else if (!T[j][k].covered && count_mines(j, k) == 0) cout << "[ ]";
                          else if (!T[j][k].covered && count_mines(j, k) != 0) cout << "[" << count_mines(j, k) << "]";
                               else if (T[j][k].covered && !T[j][k].flag) cout << "[.]";
            }
        }
}

void Board::modify_flag(int x, int y) // metoda wywolujaca metode klasy Field, ktora dynamicznie
{                                        // (w trakcie dzialania programu) ukrywa/zakrywa zadane pole przez uzytkownika
	T[x][y].change_flag();
}

bool Board::whether_hidden(int x, int y) // metoda wywolujaca metode klasy Field, ktora zwraca wartosc logiczna zakrycia/odkrycia pola
{
	return T[x][y].is_covered();
}

void Board::play(Board b1) // metoda realizujaca gre
{
    int x, y;
    int mina = 0, hidden;
    char choice;
    bool victory = false;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (b1.has_Mine(i, j)) mina++;
        }
    }

    do
    {
        system("CLS");
        b1.display();
        hidden = 0;

        cout << "\n\nMozliwe akcje do wykonania:\n";
        cout << "1.Odkrycie pola\n2.Zakrycie pola flaga lub odkrycie flagi\n\n";
        cout << "Co chcesz zrobic? Wpisz numer: ";
        cin >> choice;

        system("CLS");
        b1.display();

        switch (choice)
        {
        case '1':
            {
                do
                {
                    cout << "\n\nPodaj wspolrzedna X: ";

                    while (!(cin >> y))
                    {
                        cout << "To nie jest liczba! Podaj jeszcze raz wartosc osi odcietych (OX): ";
                        cin.clear(); // czyszcze flage bledu strumienia wejsciowego command in (cin)
                        cin.sync(); // synchronizuje strumien wejsciowy command in przed wprowadzeniem wartosci
                    }

                    cout << "Podaj wspolrzedna Y: ";

                    while (!(cin >> x))
                    {
                        cout << "To nie jest liczba! Podaj jeszcze raz wartosc osi rzednych (OY): ";
                        cin.clear(); // czyszcze flage bledu strumienia wejsciowego command in (cin)
                        cin.sync(); // synchronizuje strumien wejsciowy command in (cin) przed wprowadzeniem wartosci
                    }

                    if (x < 0 || x > M || y < 0 || y > N) cout << "Nie ma takich wspolrzednych! Podaj je jeszcze raz";
                }
                while (x < 0 || x > M || y < 0 || y > N);

                b1.reveal(x, y);

                if (b1.has_Mine(x, y))
                {
                    system("CLS");
                    b1.display();
                    cout << "\n\nNiestety, ale trafiles na mine, przegrales! :(\n";
                    cout << "Wcisnij [ENTER] jesli chcesz zagrac ponownie lub klawisz [ESC]\n";
                    cout << "by skonczyc dzialanie programu\n";

                    if (getch() == 13)
                    {
                        system("CLS");
                        return;
                    }
                    else exit(0);
                }
                else break;
            }
        case '2':
            {
                do
                {
                    cout << "\n\nPodaj wspolrzedna X: ";

                    while (!(cin >> y))
                    {
                        cout << "To nie jest liczba! Podaj jeszcze raz wartosc osi odcietych (OX): ";
                        cin.clear(); // czyszcze flage bledu strumienia wejsciowego command in (cin)
                        cin.sync(); // synchronizuje strumien wejsciowy command in przed wprowadzeniem wartosci
                    }

                    cout << "Podaj wspolrzedna Y: ";

                    while (!(cin >> x))
                    {
                        cout << "To nie jest liczba! Podaj jeszcze raz wartosc osi rzednych (OY): ";
                        cin.clear(); // czyszcze flage bledu strumienia wejsciowego command in (cin)
                        cin.sync(); // synchronizuje strumien wejsciowy command in (cin) przed wprowadzeniem wartosci
                    }

                    if (x < 0 || x > M || y < 0 || y > N) cout << "Nie ma takich wspolrzednych! Podaj je jeszcze raz";
                }
                while (x < 0 || x > M || y < 0 || y > N);

                b1.modify_flag(x, y);
                break;
            }
        default:
            {
                cout << "\n\nNie ma takiej pozycji! Kliknij [ENTER] by wrocic do menu gry\n";
                cin.sync();
                cin.get();
                break;
            }
        }

        for (int i = 0; i < M; i++) // obliczanie ilosci zakrytych pol
		{
			for (int j = 0; j < N; j++)
			{
				if (b1.whether_hidden(i, j)) hidden++;
			}
		}

		if (mina == hidden) // jesli tyle samo min co zakrytych pol to koniec gry
		{
			victory = true;
		}
    }
    while (!victory);

    if (victory)
    {
        system("CLS");
        b1.display();
        cout << "\n\nGratulacje, zwyciezyles! :)\n";
        cout << "Wcisnij [ENTER] jesli chcesz zagrac ponownie lub klawisz [ESC]\n";
        cout << "by skonczyc dzialanie programu\n";

        if (getch() == 13)
        {
            system("CLS");
            return;
        }
        else exit(0);
    }
	else b1.display();
}
