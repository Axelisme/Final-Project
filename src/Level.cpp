#include "Level.h"

LEVEL::LEVEL(const int level) {
    char buffer[50];

    setLevel(level);
}

LEVEL::~LEVEL()
{
    for(int i=0;i < NumOfGrid;i++)
    {
        levelMap[i].roadPoint = false;
    }
}

void
LEVEL::setLevel(const int level)
{
    char buffer[50];
    FILE *file;

    sprintf(buffer, "../../data/LEVEL%d.txt", level);
    file = fopen(buffer, "r");

    this->level = level;
    this->road_grid.clear();

    for(int i = 0; i < NumOfGrid; i++)
    {
        this->levelMap[i].roadPoint = false;
    }

    int err = fscanf(file, "%s", buffer);
    if(err == EOF) exit(1);
    Monster_MAX = atoi(buffer);

    for(int i=0; i < Num_MonsterType; i++)
    {
        int err = fscanf(file, "%s", buffer);
        if(err == EOF) exit(1);
        MonsterNum[i] = atoi(buffer);
    }

    while(fscanf(file, "%s", buffer) != EOF) {
        this->levelMap[atoi(buffer)].roadPoint = true;
        road_grid.push_back(atoi(buffer));
    }

    fclose(file);
}
