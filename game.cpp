#include "game.hpp"


CGame::CGame(int aWidth, int aHeight, string aTitle){

    width=aWidth;
    height=aHeight;
    title=aTitle;
    blackTurn=pawnIsChoosed=0;
    window.create(sf::VideoMode(width, height), title);
    texture.loadFromFile("images/board.png");
    selectedT.loadFromFile("images/selected.png");
    sprite.setTexture(texture);
    selectedS.setTexture(selectedT);
    indexOfMoves=0;
    figures=new CFigure*[32];
    for(int i=0; i<8; i++)
    {
        CPawn *p=new CPawn(0+i, 1, true);
        figures[i]=p;
        p=new CPawn(0+i, 6, false);
        figures[8+i]=p;
    }
    CKnight *p=new CKnight(1,0,true);
    figures[16]=p;
    p=new CKnight(1,7,false);
    figures[17]=p;
    p=new CKnight(6,0,true);
    figures[18]=p;
    p=new CKnight(6,7,false);
    figures[19]=p;
    CBishop *b;
    b=new CBishop(2,0,true);
    figures[20]=b;
    b=new CBishop(5,0,true);
    figures[21]=b;
    b=new CBishop(2,7,false);
    figures[22]=b;
    b=new CBishop(5,7,false);
    figures[23]=b;
    CTower *t=new CTower(0,0,true);
    figures[24]=t;
    t=new CTower(7,0,true);
    figures[25]=t;
    t=new CTower(0,7,false);
    figures[26]=t;
    t=new CTower(7,7,false);
    figures[27]=t;
    CQueen *q=new CQueen(3,0,true);
    figures[28]=q;
    q=new CQueen(4,7,false);
    figures[29]=q;
    CKing *k=new CKing(4,0,true);
    figures[30]=k;
    k=new CKing(3,7,false);
    figures[31]=k;

}

ostream & operator<< (ostream &wyjscie, const CGame &s) {
   return wyjscie<<s.moves[s.indexOfMoves-1]<<endl;
 }

CGame::~CGame(){

delete[] figures;

}

void CGame::setPos()
{
    for(int i=0; i<32; i++)
    {
        figures[i]->setSpritePos();
    }

}

void CGame::draw(){

    window.clear();
    window.draw(sprite);
    for(int i=0;i<32;i++){
        if(figures[i]->getIsAlive())window.draw(figures[i]->getSprite());
    }
}

void CGame::display(){

    window.display();
}

void CGame::turn()
{
    //getMove() zwraca falsz jak wybrales swoj pionek
    //zwraca true jak sie ruszyles pionkiem falsz jak sie nie udalo ruszyc pionkiem
    while(true)
    {
        bool leaveWhile=getMove();
        if(leaveWhile==true)break;
    }

    blackTurn=!blackTurn;
}

bool CGame::getMove()
{
    while(1)
    {
        sf::Event event;
        int x=-10; int y=-10;
        while( window.pollEvent( event ))
        {
            if(event.type == sf::Event::Closed)window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)window.close();
            if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                x=event.mouseButton.x;
                y=event.mouseButton.y;
                x=x/64;
                y=y/64;
                for(int i=0;i<32;i++)//sprawdza czy wybrales swoj pionek
                {
                    if(figures[i]->getIsAlive() && figures[i]->getIsBlack()==blackTurn && figures[i]->getX()==x && figures[i]->getY()==y)
                    {
                        draw();
                        selectPawn(x, y);
                        return false;
                    }
                }
                //jak tu doszedl to nie wybrales swojego pionka trzeba sprawdzic czy jest wybrany
                if(pawnIsChoosed)
                {
                    pawnIsChoosed=!pawnIsChoosed;
                    draw();
                    display();
                    //jak twoj pionek jesy wybrany i klikneles teraz cos innego to trzeba sprawdzic czy mozna sie tam ruszyc
                    for(int i=0;i<32;i++)//szukamy pionka ktorego wczesniej wybrales
                    {
                        if(figures[i]->getIsAlive() && figures[i]->getX()==xOfSelectedPawn && figures[i]->getY()==yOfSelectedPawn)
                        {
                            if(figures[i]->checkIfICanMove(figures, x, y, i))
                            {
                                addMove(xOfSelectedPawn, yOfSelectedPawn, x, y, figures[i]->name);

                                return true;
                            }
                            else return false;

                        }

                    }
                }
            }
        }
    }
}

int CGame::selectPawn(int aX, int aY)
{
    selectedS.setPosition(aX*64, aY*64);
    window.draw(selectedS);
    window.display();
    xOfSelectedPawn=aX;
    yOfSelectedPawn=aY;
    pawnIsChoosed=1;
}

bool CGame::checkForGameOver(){;}

void CGame::addMove(int fromX, int fromY, int x, int y, string nameOfPawn)
{
    string a;
    a="player ";
    if(blackTurn)a+="black ";
    else a+="white ";
    a+="moved ";
    a+=nameOfPawn;
    a+=" from ";
    for(int i=0; i<8; i++)
    {
        char temp='A'+i;
        if(fromX==i)a+=temp;
    }
    for(int i=0; i<8; i++)
    {
        char temp='1'+i;
        if(fromY==i)a+=temp;
    }
    a+=" to ";
    for(int i=0; i<8; i++)
    {
        char temp='A'+i;
        if(x==i)a+=temp;
    }
    for(int i=0; i<8; i++)
    {
        char temp='1'+i;
        if(y==i)a+=temp;
    }


    moves[indexOfMoves]=a;
    indexOfMoves++;

}











