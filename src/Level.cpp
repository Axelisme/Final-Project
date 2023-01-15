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

inline bool Level::CanMove(Pos next,DIRCTION dirc) {
    OBJ_TYPE map_next;
    OBJ_TYPE map_next_next;
    switch(dirc)
    {
        case LEFT: {
            map_next = map[next.first][next.second-1];
            map_next_next = map[next.first][next.second-2];
            break;
        }
        case RIGHT: {
            map_next = map[next.first][next.second+1];
            map_next_next = map[next.first][next.second+2];
            break;
        }
        case UP: {
            map_next = map[next.first-1][next.second];
            map_next_next = map[next.first-2][next.second];
            break;
        }
        case DOWN: {
            map_next = map[next.first+1][next.second];
            map_next_next = map[next.first+2][next.second];
            break;
        }
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

bool Level::update() {
    // if reach end
    if(is(snake->head)==END) return false;

    update_key_lock();
    
    // update object
    for(auto &ob:object) {
        if(ob->CanFall) {
            Pos pos = ob->getPos();
            int y = pos.first;
            int x = pos.second;
            if(is({y+1,x})==AIR) {
                set_key_lock();
                ob->move_dirc = DOWN;
                //if(map[y][x]!=STONE) raise_warn("some thing mismatch about map"); 
                map[y][x] = AIR;
                map[y+1][x] = ob->type;
            }
        }
        ob->update();
    }
    
    // snake fall dectection
    snake->isFall = false;
    for(auto &b:snake->body) {
        Pos pos = b->getPos();
        OBJ_TYPE ob_type = is({pos.first+1,pos.second});
        if(ob_type != AIR && ob_type != BODY){
            snake->isFall = true;
            break;
        }
    }

    // snake state set
    Pos next = snake->Next_Pos();
    if(snake->isFall) {  //falling
        show_msg("Snake fall");
        set_key_lock();
        snake->move_direction = NONE;
    }
    else if(CanMove(next,snake->move_direction)) {  //move
        show_msg("Snake move");
        is(next) = BODY;
        is(snake->body.front()->getPos()) = AIR;
    }
    else { 
        snake->move_direction = NONE;
        if(is(next)==APPLE) {  //eat apple
            show_msg("Snake eat apple");
            snake->can_eat_apple = true;
            is(next) = BODY;
        }
    }
    // update snake
    snake->update();

    return true;
}

inline DIRCTION Level::KEY_TO_DIRC(int key) {
    switch(key) {
        case ALLEGRO_KEY_LEFT:  return LEFT;
        case ALLEGRO_KEY_RIGHT: return RIGHT;
        case ALLEGRO_KEY_UP:    return UP;
        case ALLEGRO_KEY_DOWN:  return DOWN;
        default :               {
            raise_warn("known key");
            return NONE;
        }
    }    
}

// process trigered by key
GAME_STATE Level::key_triger(int key) {
    if(key == ALLEGRO_KEY_P) {
        show_msg("Key triger : switch to game menu");
        return GAME_MENU;
    } 
    if(key == ALLEGRO_KEY_R) {
        show_msg("Key triger : reset level");
        level_reset(1);
        return GAME_LEVEL;
    }
    if(key_lock) {
        snake->move_direction = NONE;
    }
    else {
        snake->move_direction = KEY_TO_DIRC(key);
    }
    return GAME_LEVEL;
}

// load level
bool Level::load_level(int _level_idx) 
{
    show_msg("Load level begin");

    show_msg("Set level id");
    level_idx = _level_idx;

    show_msg("Load image begin");
    Ground_image = al_load_bitmap((IMAGE_PATH+"/ground.png").c_str());
    Stone_image = al_load_bitmap((IMAGE_PATH+"/stone.png").c_str());
    Apple_image = al_load_bitmap((IMAGE_PATH+"/apple.png").c_str());
    Snake_head_image = al_load_bitmap((IMAGE_PATH+"/snakeHead.png").c_str());
    Snake_body_image = al_load_bitmap((IMAGE_PATH+"/snakeBody.png").c_str());
    End_point_image = al_load_bitmap((IMAGE_PATH+"/end.png").c_str());
    
    if((Ground_image && Stone_image && Apple_image && Snake_head_image && Snake_body_image && End_point_image) == false) {
        raise_warn("Some image load fail");
    }
    show_msg("Load image done");

    show_msg("Load level file begin");
    char tmp[100];
    sprintf(tmp, "/L%d", level_idx);
    show_msg(std::string("load level: ")+tmp);
    ifstream fin(LEVEL_PATH+tmp);
    if(!fin)
    {
        sprintf(tmp, "Level%d loaded fail, no Level%d's data.", level_idx,level_idx);
        raise_err(tmp);
        return false;
    }
    int t = 5;
    char data_type[20], path[100];
    int m = 0, n = 0;
    while (t--)
    {
        fin >> data_type;
        switch(data_type[0])
        {
            case '1': {  //background
                show_msg("load background");
                fin >> m;
                while (m--)
                {
                    fin >> path;
                }
                break;
            }
            case '2': {  //music
                show_msg("load music");
                fin >> m;
                while (m--)
                {
                    fin >> path;
                }
                break;
            }
            case '3': {  //snake
                show_msg("load snake initial");
                fin >> m;
                vector <Pos> snake_position_vector(m);  //snake_posotion_vector {{y1,x1},{y2,y2}}
                for (int i = 0; i < m; i++)
                {
                    fin >> snake_position_vector[i].first >> snake_position_vector[i].second;
                }
                snake = new Snake(snake_position_vector,Snake_head_image,
                                                        Snake_body_image);
                break;
            }
            case '4': {  //stone
                show_msg("load stone");
                fin >> m;
                Pos stone_position;  //stone_posotion {y1,x1}
                object.reserve(m);
                for (int i = 0; i < m; i++)
                {
                    fin >> stone_position.first >> stone_position.second;
                    Object * temp = new Stone(stone_position,Stone_image);
                    object.emplace_back(temp);
                }
                break;
            }
            case '5': {  //map
                show_msg("load map");
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
                print_map();
            }

            default:
            sprintf(tmp, "Level%d loaded fail, Level%d's data wrong.", level_idx,level_idx);
            raise_err(tmp);
            return false;
        }
    }
    show_msg("load level done");
    return true;
}

// print level map
void Level::print_map()
{
    show_msg("print map begin");
    for (auto i:map)
    {
        for (auto j:i)
        {
            switch(j)
            {
                case AIR:
                    cout << "  ";
                    break;
                case GROUND:
                    cout << "██";
                    break;
                case HEAD:
                    cout << "▓▓";
                    break;
                case BODY:
                    cout << "▒▒";
                    break;
                case END:
                    cout << " ⊠";
                    break;
                case APPLE:
                    cout << " ⋄";
                    break;
                case STONE:
                    cout << "░░";
                    break;
                case EDGE:
                    cout << "▞▞";
                    break;
                default:
                    break;
            }
        }
        cout << endl;
    }
    show_msg("print map done");
};

// reset
void Level::level_reset(int idx) {
    show_msg("Level reset begin");
    destroy_level();
    load_level(idx);
    key_lock = false;
    key_lock_count =0;
    show_msg("Level reset done");
}

void Level::destroy_level() {
    show_msg("level destroy begin");
    Interface::~Interface();
    
    al_destroy_bitmap(Ground_image);
    al_destroy_bitmap(Stone_image);
    al_destroy_bitmap(Apple_image);
    al_destroy_bitmap(Snake_head_image);
    al_destroy_bitmap(Snake_body_image);
    al_destroy_bitmap(End_point_image);

    key_lock = false;
    int key_lock_count = 0;

    delete snake;
    for(auto &o:object) delete o;
    show_msg("level destroy done");
}

// constructor and deletor
Level::Level(int i):Interface(MUSIC_PATH+"level_bgm.ogg",IMAGE_PATH+"background.jpg") {
    show_msg("Create level begin");
    key_lock = false;
    key_lock_count =0;
    
    load_level(i);
    show_msg("Create level done");
}

Level::~Level() {
    show_msg("Delete level begin");
    destroy_level();
    show_msg("Delete level done");
}