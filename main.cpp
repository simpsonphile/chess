#include <iostream>
#include "game.hpp"
#include "figure.hpp"


using namespace std;

int main()
{
    CGame game(652, 532, "szachy");

    while(1)
    {
        game.setPos();//ustawia pozycje sprite w pixelach
        game.draw();//rysuje na mape
        game.display();//wyswietla mape
        game.turn();//tutaj dzieje sie wszystko zwiazane z ruchem
        cout<<game;

        //game.checkIfGameOver();
    }
}
