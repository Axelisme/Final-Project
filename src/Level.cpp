#include "global.h"
#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>

using Pos=pair<int, int>;

void Level::draw() {
    Interface::draw();

    for(auto &o:object) {
        o->draw();
    }
    
    snake->draw();
}

inline bool Level::is(int _y,int _x,OBJ_TYPE T) {
        return map.at(_y).at(_x) == T;
}

// update all object
bool Level::update() {
    bool tmp = false;
    if((key_lock && ++key_lock_count)%key_lock_num == 0) {
        key_lock = false;
        tmp = true;
    }
    
    for(auto &ob:object) {
        switch(ob->type) {
            case STONE: {
                int x = int(ob->getx());
                int y = int(ob->gety());
                if(is(y+1,x,AIR)) {
                    ob->move_dirc = DOWN;
                    if(map[y][x]!=STONE) raise_warn("some thing mismatch about map"); 
                    map[y][x] = AIR;
                    ob->update();
                    ob->move_dirc = NONE;
                    map.at(y+1).at(x) = STONE;
                    tmp = true;
                }
                else {
                    ob->move_dirc = NONE;
                }
                break;
            }
            default: raise_warn("try to update unknown type");
        }
    }
    
     
    for(auto &b:snake->body) {
        int x = b->getx();
        int y = b->gety();
        if(is(y,x,AIR)){}
    }
    


    return tmp;
}

// process trigered by key
GAME_STATE Level::key_triger(int key) {
    if(key == ALLEGRO_KEY_P) return GAME_MENU; 
    if(key == ALLEGRO_KEY_R) {
        reset();
        return GAME_LEVEL;
    }
    if(key_lock) return GAME_LEVEL;
    if(key>=ALLEGRO_KEY_LEFT && key <= ALLEGRO_KEY_DOWN) {
        snake->move_direction = static_cast<MOVE_DIRCTION> (key - ALLEGRO_KEY_LEFT);
        return GAME_LEVEL;
    }
    else {
        raise_warn("Unknown key");
        return GAME_LEVEL;
    }
}

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
Level::Level(int i):Interface(MUSIC_PATH+"level_bgm.ogg",IMAGE_PATH+"background.jpg") {
    level_idx = i;
    Ground_image = al_load_bitmap((IMAGE_PATH+"/ground.png").c_str());
    Stone_image = al_load_bitmap((IMAGE_PATH+"/stone.png").c_str());
    Apple_image = al_load_bitmap((IMAGE_PATH+"/apple.png").c_str());
    Snake_head_image = al_load_bitmap((IMAGE_PATH+"/head.png").c_str());
    Snake_body_image = al_load_bitmap((IMAGE_PATH+"/body.png").c_str());

    key_lock = false;
    key_lock_count =0;
    
    load_level(i);
}

Level::~Level() {
    al_destroy_bitmap(Ground_image);
    al_destroy_bitmap(Stone_image);
    al_destroy_bitmap(Apple_image);
    al_destroy_bitmap(Snake_head_image);
    al_destroy_bitmap(Snake_body_image);

    delete snake;
    for(auto &o:object) delete o;
}