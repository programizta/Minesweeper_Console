#include <iostream>
#define N 10
#define M 10

using namespace std;

class Field
{
    bool covered;   //mialem problem z hermetyzacja danych, czyli z dostepem
    bool flag;      // do tych prywatnych zmiennych
    bool mine;
    friend class Board;   //udalo mi sie uzyskac do nich dostep poprzez przyjazn klas

public:

    Field();
    void place_mine();
    bool is_mine();
    void uncover();
    bool is_covered();
    void place_flag();
    void change_flag();
    bool is_flag();
};

class Board
{
    Field T[M][N]; //nie wiem jak ustawic pozadane rozmiary planszy M*N

public:

    Board();
    void deploy_mines(int n, bool random);
    bool has_Mine(int x, int y);
    int count_mines(int x, int y);
    void reveal(int x, int y);
    void display();
    void modify_flag(int x, int y);
    bool whether_hidden(int x, int y);
    void play(Board b1);
};
