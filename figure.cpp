#include "figure.hpp"
#include<iostream>

CFigure::CFigure()
{
    x=y=0;
    isBlack=isAlive=true;
}

CFigure::CFigure(int aX, int aY, bool aIsBlack)
{
    x=aX;
    y=aY;
    isBlack=aIsBlack;
    isAlive=true;
}

CFigure::~CFigure(){;}

sf::Sprite CFigure::getSprite(){return sprite;}

void CFigure::setSpritePos(){sprite.setPosition(x*64, y*64);}

int CFigure::getX(){return x;}
int CFigure::getY(){return y;}
void CFigure::setXY(int X, int Y){x=X; y=Y;}
bool CFigure::getIsBlack(){return isBlack;}
bool CFigure::getIsAlive(){return isAlive;}
void CFigure::kill(){isAlive=0;}


////////////////////////////PAWN//////////////////////////////////////////////////////

CPawn::CPawn():CFigure(){

    texture.loadFromFile("images/bpawn.png");
    sprite.setTexture(texture);
}

CPawn::CPawn(int aX, int aY, bool aIsBlack):CFigure(aX, aY, aIsBlack)
{

    if(isBlack)texture.loadFromFile("images/bpawn.png");
    else texture.loadFromFile("images/wpawn.png");
    sprite.setTexture(texture);
    name="pawn";
}

CPawn::~CPawn(){;}

bool CPawn::checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn){

    int xOfPawn=figures[indexOfPawn]->getX();
    int yOfPawn=figures[indexOfPawn]->getY();
    for(int i=0;i<32;i++)//odsiewamy ruchy gdzie wchodzimy na pionek w pionie
    {
        if( posX==xOfPawn && figures[i]->getX()==posX && figures[i]->getY()==posY && figures[i]->getIsAlive())return false;
    }
    if(figures[indexOfPawn]->getIsBlack()==1)//jezeli pionek jest czarny
    {
        if(xOfPawn==posX && yOfPawn==1 && (posY==2 || posY==3))//pierwszy ruch tego pionka
        {
            figures[indexOfPawn]->setXY(posX, posY);
            return true;
        }
        if(xOfPawn==posX && yOfPawn!=1 && (posY==yOfPawn+1))//zwyczajny ruch o 1 do przodu inny niz pierwszy
        {
            figures[indexOfPawn]->setXY(posX, posY);
            return true;
        }
        if((xOfPawn==posX-1||xOfPawn==posX+1) && (posY==yOfPawn+1))//chcemy isc na skos
        {
            for(int i=0;i<32;i++)
            {
                if(figures[i]->getX()==posX && figures[i]->getY()==posY && figures[i]->getIsAlive()
                 && figures[i]->getIsBlack()!=figures[indexOfPawn]->getIsBlack())//sprawdzamy czy jest tam zywy przeciwnik
                 {
                    figures[indexOfPawn]->setXY(posX, posY);
                    figures[i]->kill();
                    return true;
                 }
            }
            return false;
        }
    }
    else if(figures[indexOfPawn]->getIsBlack()==0)//jezeli pionek jest bialy
    {
        if(xOfPawn==posX && yOfPawn==6 && (posY==5 || posY==4))//pierwszy ruch tego pionka
        {
            figures[indexOfPawn]->setXY(posX, posY);
            return true;
        }
        if(xOfPawn==posX && yOfPawn!=6 && (posY==yOfPawn-1))//zwyczajny ruch o 1 do przodu inny niz pierwszy
        {
            figures[indexOfPawn]->setXY(posX, posY);
            return true;
        }
        if((xOfPawn==posX-1||xOfPawn==posX+1) && (posY==yOfPawn-1))//chcemy isc na skos
        {
            for(int i=0;i<32;i++)
            {
                if(figures[i]->getX()==posX && figures[i]->getY()==posY && figures[i]->getIsAlive()
                 && figures[i]->getIsBlack()!=figures[indexOfPawn]->getIsBlack())//sprawdzamy czy jest tam zywy przeciwnik
                 {
                    figures[indexOfPawn]->setXY(posX, posY);
                    figures[i]->kill();
                    return true;
                 }
            }
            return false;
        }
    }
    return false;

}

////////////////////////////knight//////////////////////////////////////////////////////

CKnight::CKnight():CFigure(){

    texture.loadFromFile("images/bknight.png");
    sprite.setTexture(texture);
}

CKnight::CKnight(int aX, int aY, bool aIsBlack):CFigure(aX, aY, aIsBlack)
{

    if(isBlack)texture.loadFromFile("images/bknight.png");
    else texture.loadFromFile("images/wknight.png");
    sprite.setTexture(texture);
    name="knight";
}

CKnight::~CKnight(){;}

bool CKnight::checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn){

    int xOfPawn=figures[indexOfPawn]->getX();
    int yOfPawn=figures[indexOfPawn]->getY();
    bool canGo=0;
    if(posY==yOfPawn-2)//w gore
    {
        if(posX==xOfPawn-1)//w lewo
        canGo=1;
        else if(posX==xOfPawn+1)//w prawo
        canGo=1;
    }
    else if(posY==yOfPawn+2)//w dol
    {
        if(posX==xOfPawn-1)//w lewo
        canGo=1;
        else if(posX==xOfPawn+1)//w prawo
        canGo=1;
    }
    else if(posX==xOfPawn+2)
    {
        if(posY==yOfPawn-1)//w lewo
        canGo=1;
        else if(posY==yOfPawn+1)//w prawo
        canGo=1;
    }
    else if(posX==xOfPawn-2)
    {
        if(posY==yOfPawn-1)//w lewo
        canGo=1;
        else if(posY==yOfPawn+1)//w prawo
        canGo=1;
    }

    if(canGo==1)//mozemy isc musimy tylko sprawdzic czy jest tam puste/wrog czy my
    {
        for(int i=0;i<32;i++)
        {
            if(figures[i]->getIsBlack()!=figures[indexOfPawn]->getIsBlack() && figures[i]->getX()==posX && figures[i]->getY()==posY
             && figures[i]->getIsAlive())//wrog tam stoi
             {
                figures[i]->kill();
                figures[indexOfPawn]->setXY(posX, posY);
                return true;
             }
             else if(figures[i]->getIsBlack()==figures[indexOfPawn]->getIsBlack() && figures[i]->getX()==posX && figures[i]->getY()==posY
             && figures[i]->getIsAlive())//my tam stoimy
             {
                return false;
             }
        }
        figures[indexOfPawn]->setXY(posX, posY);
        return true;


    }
    else return false;


}

////////////////////////////bishop//////////////////////////////////////////////////////

CBishop::CBishop():CFigure(){

    texture.loadFromFile("images/bbishop.png");
    sprite.setTexture(texture);
}

CBishop::CBishop(int aX, int aY, bool aIsBlack):CFigure(aX, aY, aIsBlack)
{

    if(isBlack)texture.loadFromFile("images/bbishop.png");
    else texture.loadFromFile("images/wbishop.png");
    sprite.setTexture(texture);
    name="bishop";
}

CBishop::~CBishop(){;}

bool CBishop::checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn){

    int xOfPawn=figures[indexOfPawn]->getX();
    int yOfPawn=figures[indexOfPawn]->getY();
    if(abs(xOfPawn-posX)==abs(yOfPawn-posY))// jak nasz klik jest po skosie, sprawdzimy czy nie ma nic po drodze
    {
        if(posX>xOfPawn)//klik na prawo od bishopa
        {
            if(posY>yOfPawn)//w dol od bishopa
            {
                for(int i=1;i<posX-xOfPawn;i++)
                {
                    for(int j=0;j<32;j++)
                    {
                        if(figures[j]->getIsAlive() && figures[j]->getX()==xOfPawn+i && figures[j]->getY()==yOfPawn+i)return false;
                    }
                }
            }
            if(posY<yOfPawn)//w gore od bishopa
            {
                for(int i=1;i<posX-xOfPawn;i++)
                {
                    for(int j=0;j<32;j++)
                    {
                        if(figures[j]->getIsAlive() && figures[j]->getX()==xOfPawn+i && figures[j]->getY()==yOfPawn-i)return false;
                    }
                }
            }
        }
        else if(posX<xOfPawn)//klik na lewo od bishopa
        {
            if(posY>yOfPawn)//w dol od bishopa
            {
                for(int i=1;i<xOfPawn-posX;i++)
                {
                    for(int j=0;j<32;j++)
                    {
                        if(figures[j]->getIsAlive() && figures[j]->getX()==xOfPawn-i && figures[j]->getY()==yOfPawn+i)return false;
                    }
                }
            }
            if(posY<yOfPawn)//w gore od bishopa
            {
                for(int i=1;i<xOfPawn-posX;i++)
                {
                    for(int j=0;j<32;j++)
                    {
                        if(figures[j]->getIsAlive() && figures[j]->getX()==xOfPawn-i && figures[j]->getY()==yOfPawn-i)return false;
                    }
                }
            }
        }
        //SPRAWDZILISMY ZE NIC NIE MA PODRODZE SPRAWDZMY CO JEST NA POZYCJI DO KTOREJ SZLISMY
        for(int i=0; i<32; i++)
        {
            if(figures[i]->getIsAlive() && figures[i]->getIsBlack()==figures[indexOfPawn]->getIsBlack()
            && figures[i]->getX()==posX &&figures[i]->getY()==posY)//chcemy wejsc na siebie nie pozwalamy
            {
                return false;
            }
            if(figures[i]->getIsAlive() && figures[i]->getIsBlack()!=figures[indexOfPawn]->getIsBlack()
            &&figures[i]->getX()==posX && figures[i]->getY()==posY)//chcemy wejsc na wroga czemu nie
            {
                figures[i]->kill();
                figures[indexOfPawn]->setXY(posX, posY);
                return true;
            }
        }
        figures[indexOfPawn]->setXY(posX, posY);
        return true;
    }
    else return false;
    return false;


}

////////////////////////////tower//////////////////////////////////////////////////////

CTower::CTower():CFigure(){

    texture.loadFromFile("images/btower.png");
    sprite.setTexture(texture);
}

CTower::CTower(int aX, int aY, bool aIsBlack):CFigure(aX, aY, aIsBlack)
{

    if(isBlack)texture.loadFromFile("images/btower.png");
    else texture.loadFromFile("images/wtower.png");
    sprite.setTexture(texture);
    name="tower";
}

CTower::~CTower(){;}

bool CTower::checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn){

    int xOfPawn=figures[indexOfPawn]->getX();
    int yOfPawn=figures[indexOfPawn]->getY();
    if(posX==xOfPawn && posY>yOfPawn)//w dol
    {
        for(int i=1; i<posY-yOfPawn;i++)
        {
            for(int j=0;j<32;j++)
            {
                if(figures[j]->getIsAlive() && figures[j]->getX()==xOfPawn && figures[j]->getY()==yOfPawn+i)return false;
            }
        }
    }
    else if(posX==xOfPawn && posY<yOfPawn)//w gore
    {
        for(int i=1; i<yOfPawn-posY;i++)
        {
            for(int j=0;j<32;j++)
            {
                if(figures[j]->getIsAlive() && figures[j]->getX()==xOfPawn && figures[j]->getY()==yOfPawn-i)return false;
            }
        }
    }
    else if(posY==yOfPawn && posX<xOfPawn)//w lewo
    {
        for(int i=1; i<xOfPawn-posX;i++)
        {
            for(int j=0;j<32;j++)
            {
                if(figures[j]->getIsAlive() && figures[j]->getY()==yOfPawn && figures[j]->getX()==xOfPawn-i)return false;
            }
        }
    }
    else if(posY==yOfPawn && posX>xOfPawn)//w lewo
    {
        for(int i=1; i<posX-xOfPawn;i++)
        {
            for(int j=0;j<32;j++)
            {
                if(figures[j]->getIsAlive() && figures[j]->getY()==yOfPawn && figures[j]->getX()==xOfPawn+i)return false;
            }
        }
    }
    else return false;
    //nic nie ma po drodze sprawdz czy cos jest u celu
    for(int i=0; i<32; i++)
        {
            if(figures[i]->getIsAlive() && figures[i]->getIsBlack()==figures[indexOfPawn]->getIsBlack()
            && figures[i]->getX()==posX &&figures[i]->getY()==posY)//chcemy wejsc na siebie nie pozwalamy
            {
                return false;
            }
            if(figures[i]->getIsAlive() && figures[i]->getIsBlack()!=figures[indexOfPawn]->getIsBlack()
            &&figures[i]->getX()==posX && figures[i]->getY()==posY)//chcemy wejsc na wroga czemu nie
            {
                figures[i]->kill();
                figures[indexOfPawn]->setXY(posX, posY);
                return true;
            }
        }
        figures[indexOfPawn]->setXY(posX, posY);
        return true;

}

////////////////////////////queen//////////////////////////////////////////////////////

CQueen::CQueen():CFigure(){

    texture.loadFromFile("images/bqueen.png");
    sprite.setTexture(texture);
}

CQueen::CQueen(int aX, int aY, bool aIsBlack):CFigure(aX, aY, aIsBlack)
{

    if(isBlack)texture.loadFromFile("images/bqueen.png");
    else texture.loadFromFile("images/wqueen.png");
    sprite.setTexture(texture);
    name="queen";
}

CQueen::~CQueen(){;}

bool CQueen::checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn){

  CTower t;
  CBishop b;
  if(b.checkIfICanMove(figures, posX, posY, indexOfPawn))return true;
  else if(t.checkIfICanMove(figures, posX, posY, indexOfPawn))return true;
  else return false;

}

////////////////////////////king//////////////////////////////////////////////////////

CKing::CKing():CFigure(){

    texture.loadFromFile("images/bking.png");
    sprite.setTexture(texture);
}

CKing::CKing(int aX, int aY, bool aIsBlack):CFigure(aX, aY, aIsBlack)
{

    if(isBlack)texture.loadFromFile("images/bking.png");
    else texture.loadFromFile("images/wking.png");
    sprite.setTexture(texture);
    name="king";
}

CKing::~CKing(){;}

bool CKing::checkIfICanMove(CFigure **figures, int posX, int posY, int indexOfPawn){

    int xOfPawn=figures[indexOfPawn]->getX();
    int yOfPawn=figures[indexOfPawn]->getY();
    bool canGo=0;
    if((xOfPawn==posX || xOfPawn==posX+1 || xOfPawn==posX-1) && (yOfPawn==posY || yOfPawn==posY+1 || yOfPawn==posY-1))
    {
            for(int i=0; i<32; i++)
            {
                if(figures[i]->getIsAlive() && figures[i]->getIsBlack()!=figures[indexOfPawn]->getIsBlack()
                && figures[i]->getX()==posX && figures[i]->getY()==posY)
                {
                    figures[i]->kill();
                    figures[indexOfPawn]->setXY(posX, posY);
                    return true;
                }
                else if(figures[i]->getIsAlive() && figures[i]->getIsBlack()==figures[indexOfPawn]->getIsBlack()
                && figures[i]->getX()==posX && figures[i]->getY()==posY)
                {
                    return false;
                }



            }
            figures[indexOfPawn]->setXY(posX, posY);
                    return true;

    }

    else return false;


}




