#pragma once

class Score
{
public:
    explicit Score();
    ~Score();
    void calculatePoints(int nLinesCleaned);
    float getSpeedFactor () const;
    int getScore () const;
    int getLevel() const;

private:
    int level;
    int totalPoints;
    float speedFactor;
};
