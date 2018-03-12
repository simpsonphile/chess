#ifndef FIGURE_HPP_INCLUDED
#define FIGURE_HPP_INCLUDED
#include<SFML/Graphics.hpp>
#include<string>
#include <cstdlib>
using namespace std;

class CFigure{

    public:
    CFigure();
    CFigure(int aX, int aY, bool aIsBlack);
    ~CFigure();
    void setXY(int, int);
    int getX();
    int getY();
    bool getIsBlack();
    bool getIsAlive();
    void kill();
    sf::Sprite getSprite();
    void setSpritePos();
    virtual bool checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn)=0;
    string name;


    protected:
    int x, y;
    bool isBlack, isAlive;
    sf::Texture texture;
    sf::Sprite sprite;
};

class CPawn: public CFigure{

    public:
    CPawn();
    CPawn(int aX, int aY, bool aIsBlack);
    ~CPawn();
    virtual bool checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn);

};

class CKnight: public CFigure{

    public:
    CKnight();
    CKnight(int aX, int aY, bool aIsBlack);
    ~CKnight();
    virtual bool checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn);

};

class CBishop: public CFigure{

    public:
    CBishop();
    CBishop(int aX, int aY, bool aIsBlack);
    ~CBishop();
    virtual bool checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn);

};

class CTower: public CFigure{

    public:
    CTower();
    CTower(int aX, int aY, bool aIsBlack);
    ~CTower();
    virtual bool checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn);

};

class CQueen: public CFigure {

    public:
    CQueen();
    CQueen(int aX, int aY, bool aIsBlack);
    ~CQueen();
    virtual bool checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn);

};

class CKing: public CFigure{

    public:
    CKing();
    CKing(int aX, int aY, bool aIsBlack);
    ~CKing();
    virtual bool checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn);

};



#endif // FIGURE_HPP_INCLUDED
