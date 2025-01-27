#include "Score.h"

Score::Score()
{
    level = 0;
    totalPoints = 0;
    speedFactor = 1.0;
}

Score::~Score()
{

}

void Score::calculatePoints(int nLinesCleaned){
    int p = 0; //new points
    if(nLinesCleaned == 1) p = 40;
    else if (nLinesCleaned == 2) p = 100;
    else if (nLinesCleaned == 3) p = 300;
    else if (nLinesCleaned == 4) p = 1200;
    
    totalPoints += p * (level + 1);
    if (p != 0) level += 1;
    if (level > 2 && level < 15) speedFactor = 0.5;
    else if (level >= 15) speedFactor = 0.25;

};

float Score::getSpeedFactor() const{
    return speedFactor;
}

int Score::getScore() const{
    return totalPoints;
}
int Score::getLevel() const{
    return level;
}