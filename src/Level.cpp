#include "global.h"
#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>

using Pos=pair<int, int>;

void Level::draw() {

}

// update all object
void Level::update() {}

// process trigered by key
GAME_STATE Level::key_triger(int key) {return GAME_LEVEL;}

// load level
bool Level::load_level(int level_idx) 
{
    char tmp[100];
    sprintf(tmp, "/L%d", level_idx);
    ifstream fin(LEVEL_PATH+tmp);
    if(!fin)
    {
        sprintf(tmp, "Level%d loaded fail, no Level%d's data.", level_idx);
        raise_err(tmp);
        return false;
    }
    int t = 4;
    char data_type[20], path[100];
    int m = 0, n = 0;
    vector <Pos> snake_position;  //snake_posotion {{y1,x1},{y2,y2}}
    vector <Pos> stone_position;  //stone_posotion {{y1,x1},{y2,y2}}
    vector <vector<int>> map_matrix;    //map(high,width)
    while (t--)
    {
        fin >> data_type;
        switch(data_type[0])
        {
            case '1':   //background
                fin >> m;
                while (m--)
                {
                    fin >> path;
                }
            case '2':   //music
                fin >> m;
                while (m--)
                {
                    fin >> path;
                }
            case '3':   //snake
            case '4':   //stone
                fin >> m;
                vector <Pos> tmp_position(m);
                for (int i = 0; i < m; i++)
                {
                    fin >> tmp_position[i].first >> tmp_position[i].second;
                }
                if (data_type[0] == '3') {snake_position = tmp_position;}
                else {stone_position = tmp_position;}
            case '5':   //map
                fin >> m >> n;
                Map tmp_matrix(m,vector<OBJ_TYPE>(n));    //map(high,width)
                int element;
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        fin >> element;
                        tmp_matrix[i][j] = static_cast<OBJ_TYPE>(element);
                    }
                }
                map_matrix = tmp_matrix;

            default:
            sprintf(tmp, "Level%d loaded fail, Level%d's data wrong.", level_idx);
            raise_err(tmp);
            return false;
        }
    }
    return true;
}

// reset
void Level::reset() {}

// constructor and deletor
Level::Level(int i):Interface(MUSIC_PATH+"level_bgm.ogg",IMAGE_PATH+"background.jpg") {}

Level::~Level() {}