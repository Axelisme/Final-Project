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

inline bool Level::CanMove(MOVE_DIRCTION dirc) {
    return true;
}

// update all object
bool Level::update() {
    if(is(snake->head,END)) return true;

    if((key_lock && ++key_lock_count)%key_lock_num == 0) 
        key_lock = false;
    
    for(auto &ob:object) {
        switch(ob->type) {
            case STONE: {
                int x = int(ob->getx());
                int y = int(ob->gety());
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
        int x = b->getx();
        int y = b->gety();
        if(!is({y+1,x},AIR) && !is({y+1,x},BODY)){
            snake->isFall = true;
            break;
        }
    }
    if(snake->isFall || !CanMove(snake->move_direction)) 
        snake->move_direction = NONE;
    else {
        Pos next = snake->Next_Pos();
        if(is(next,APPLE)) snake->next_apple = true;
    }

    snake->update();

    return false;
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
    vector <Pos> snake_position_vector(m);  //snake_posotion_vector {{y1,x1},{y2,y2}}
    Pos stone_position;  //stone_posotion {y1,x1}
    Map map_matrix(m,vector<OBJ_TYPE>(n));    //map(high,width)
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
                fin >> m;
                for (int i = 0; i < m; i++)
                {
                    fin >> snake_position_vector[i].first >> snake_position_vector[i].second;
                }
                snake = new Snake(snake_position_vector,Snake_head_image,Snake_body_image);   //TODO
                
            case '4':   //stone
                fin >> m;
                object.reserve(m);
                for (int i = 0; i < m; i++)
                {
                    fin >> stone_position.first >> stone_position.second;
                    Object * temp = new Stone(stone_position.first,stone_position.second,Stone_image);
                    object.emplace_back(temp); //TODO
                }
            case '5':   //map
                fin >> m >> n;
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