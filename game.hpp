#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include "figure.hpp"
#include<string>
#include<iostream>
#include<unistd.h>
using namespace std;
class CGame{

    public:
    CGame(int, int, string);
    friend ostream & operator<< (ostream &wyjscie, const CGame &s);
    ~CGame();
    void display();
    void draw();
    void setPos();
    void turn();
    int selectPawn(int, int);//pobiera wybor pinonka
    int xOfSelectedPawn;
    int yOfSelectedPawn;
    bool getMove();//po wybraniu pionka czeka na ruch
    CFigure **figures;//wszystkie pinonki
    bool checkForGameOver();
    void addMove(int fromX, int fromY, int destX, int destY, string nameOfPawn);
    string moves[1000];
    int indexOfMoves;
    private:
    int width, height;
    string title;
    sf::RenderWindow window;
    sf::Texture texture, selectedT;
    sf::Sprite sprite, selectedS;
    bool blackTurn, pawnIsChoosed;

};


#endif // GAME_HPP_INCLUDED
