#include "global.h"
#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>

void Level::draw() {
    Interface::draw();

    for(auto &o:object) {
        o->draw();
    }
    
    snake->draw();
}

inline bool Level::is(Pos pos,OBJ_TYPE T) {
        return map.at(pos.first).at(pos.second) == T;
}

inline bool Level::CanMove(Pos next,DIRCTION dirc) {
    OBJ_TYPE map_next;
    OBJ_TYPE map_next_next;
    switch(dirc)
    {
        case LEFT:
            map_next = map[next.first][next.second-1];
            map_next_next = map[next.first][next.second-2];
        case RIGHT:
            map_next = map[next.first][next.second+1];
            map_next_next = map[next.first][next.second+2];
        case UP:
            map_next = map[next.first-1][next.second];
            map_next_next = map[next.first-2][next.second];
        case DOWN:
            map_next = map[next.first+1][next.second];
            map_next_next = map[next.first+2][next.second];
        case NONE:
            return true;
    }
    if (map_next==BODY || map_next==GROUND || map_next==APPLE)
    {
        return false;
    }
    else if (map_next==STONE && map_next_next!=AIR)
    {
        return false;
    }
    else {return true;}
    return false;
}

// update all object
bool Level::update() {
    if(is(snake->head,END)) return true;

    if((key_lock && ++key_lock_count)%key_lock_num == 0) 
        key_lock = false;
    
    for(auto &ob:object) {
        switch(ob->type) {
            case STONE: {
                Pos pos = ob->getPos();
                int x = pos.second;
                int y = pos.first;
                if(is({y+1,x},AIR)) {
                    ob->move_dirc = DOWN;
                    if(map[y][x]!=STONE) raise_warn("some thing mismatch about map"); 
                    map[y][x] = AIR;
                    ob->update();
                    ob->move_dirc = NONE;
                    map.at(y+1).at(x) = STONE;
                }
                else {
                    ob->move_dirc = NONE;
                }
                break;
            }
            default: raise_warn("try to update unknown type");
        }
    }
    
    snake->isFall = false;
    for(auto &b:snake->body) {
        Pos pos = b->getPos();
        int x = pos.second;
        int y = pos.first;
        if(!is({pos.first+1,pos.second},AIR) && !is({pos.first+1,pos.second},BODY)){
            snake->isFall = true;
            break;
        }
    }
    Pos next = snake->Next_Pos();
    if(snake->isFall || !CanMove(next,snake->move_direction)) 
        snake->move_direction = NONE;
    else {
        if(is(next,APPLE)) {
            snake->can_eat_apple = true;
            map.at(next.first).at(next.second) = BODY;
        }
    }

    snake->update();

    return false;
}

inline DIRCTION Level::KEY_TO_DIRC(int key) {
    switch(key) {
        case ALLEGRO_KEY_LEFT:  return LEFT;
        case ALLEGRO_KEY_RIGHT: return RIGHT;
        case ALLEGRO_KEY_UP:    return UP;
        case ALLEGRO_KEY_DOWN:  return DOWN;
        default :               {
            raise_warn("known key");
            return NONE;}
    }    
}

// process trigered by key
GAME_STATE Level::key_triger(int key) {
    if(key == ALLEGRO_KEY_P) return GAME_MENU; 
    if(key == ALLEGRO_KEY_R) {
        reset();
        return GAME_LEVEL;
    }
    if(key_lock) return GAME_LEVEL;
    snake->move_direction = KEY_TO_DIRC(key);
    return GAME_LEVEL;
}

// load level
bool Level::load_level(int _level_idx) 
{
    level_idx = _level_idx;
    Ground_image = al_load_bitmap((IMAGE_PATH+"/ground.png").c_str());
    Stone_image = al_load_bitmap((IMAGE_PATH+"/stone.png").c_str());
    Apple_image = al_load_bitmap((IMAGE_PATH+"/apple.png").c_str());
    Snake_head_image = al_load_bitmap((IMAGE_PATH+"/snakeHead.png").c_str());
    Snake_body_image = al_load_bitmap((IMAGE_PATH+"/snakeBody.png").c_str());
    End_point_image = al_load_bitmap((IMAGE_PATH+"/end.png").c_str());
    
    char tmp[100];
    sprintf(tmp, "/L%d", level_idx);
    ifstream fin(LEVEL_PATH+tmp);
    if(!fin)
    {
        sprintf(tmp, "Level%d loaded fail, no Level%d's data.", level_idx,level_idx);
        raise_err(tmp);
        return false;
    }
    int t = 4;
    char data_type[20], path[100];
    int m = 0, n = 0;
    while (t--)
    {
        fin >> data_type;
        switch(data_type[0])
        {
            case '1':   //background
            {
                fin >> m;
                while (m--)
                {
                    fin >> path;
                }
            }
            case '2':   //music
            {
                fin >> m;
                while (m--)
                {
                    fin >> path;
                }
            }
            case '3':   //snake
            {
                fin >> m;
                vector <Pos> snake_position_vector(m);  //snake_posotion_vector {{y1,x1},{y2,y2}}
                for (int i = 0; i < m; i++)
                {
                    fin >> snake_position_vector[i].first >> snake_position_vector[i].second;
                }
                snake = new Snake(snake_position_vector,Snake_head_image,
                                                        Snake_body_image);
            }

            case '4':   //stone
            {
                fin >> m;
                Pos stone_position;  //stone_posotion {y1,x1}
                object.reserve(m);
                for (int i = 0; i < m; i++)
                {
                    fin >> stone_position.first >> stone_position.second;
                    Object * temp = new Stone(stone_position,Stone_image);
                    object.emplace_back(temp);
                }
            }
            case '5':   //map
            {
                fin >> m >> n;
                Map map_matrix(m,vector<OBJ_TYPE>(n,AIR));    //map(high,width)
                int element;
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        fin >> element;
                        map_matrix[i][j] = static_cast<OBJ_TYPE>(element);
                    }
                }
                map = map_matrix;
            }
            default:
            sprintf(tmp, "Level%d loaded fail, Level%d's data wrong.", level_idx,level_idx);
            raise_err(tmp);
            return false;
        }
    }
    return true;
}

// print level map
void Level::print_map()
{
    for (auto i:map)
    {
        for (auto j:i)
        {
            switch(j)
            {
                case AIR:
                    cout << "  ";
                case GROUND:
                    cout << "██";
                case HEAD:
                    cout << "▓▓";
                case BODY:
                    cout << "▒▒";
                case END:
                    cout << " ⊠";
                case APPLE:
                    cout << " ⋄";
                case STONE:
                    cout << "░░";
                case EDGE:
                    cout << "▞▞";
            }
        }
        cout << endl;
    }
};

// reset
void Level::reset() {
    load_level(level_idx);
    key_lock = false;
    key_lock_count =0;
}

// constructor and deletor
Level::Level(int i):Interface(MUSIC_PATH+"level_bgm.ogg",IMAGE_PATH+"background.jpg") {
    level_idx = i;
    Ground_image = al_load_bitmap((IMAGE_PATH+"/ground.png").c_str());
    Stone_image = al_load_bitmap((IMAGE_PATH+"/stone.png").c_str());
    Apple_image = al_load_bitmap((IMAGE_PATH+"/apple.png").c_str());
    Snake_head_image = al_load_bitmap((IMAGE_PATH+"/head.png").c_str());
    End_point_image = al_load_bitmap((IMAGE_PATH+"/body.png").c_str());

    key_lock = false;
    key_lock_count =0;
    
    load_level(i);
}

Level::~Level() {
    Interface::~Interface();
    
    al_destroy_bitmap(Ground_image);
    al_destroy_bitmap(Stone_image);
    al_destroy_bitmap(Apple_image);
    al_destroy_bitmap(Snake_head_image);
    al_destroy_bitmap(Snake_body_image);
    al_destroy_bitmap(End_point_image);

    delete snake;
    for(auto &o:object) delete o;
}