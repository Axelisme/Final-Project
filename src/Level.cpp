#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>

void Level::draw_map() {
    float window_x = window_center.second - window_width/2;
    float window_y = (MAP_HEIGHT-SEE_MAP_HEIGHT)/2;
    for(int i=0;i<map.size();++i) {
        for(int j=0;j<map[0].size();++j){
            if(j<window_x || j>window_x+window_width || i<window_y || i>window_y+window_height) continue;
            ALLEGRO_BITMAP * img;
            switch(ground_map[i][j]) {
                case AIR : 
                case EDGE : continue;
                case GROUND: {
                    img = Ground_image;
                    break;
                }
                case END: {
                    img = End_point_image;
                    break;
                }
                case APPLE: {
                    img = Apple_image;
                    break;
                }
                case SPIKE:{
                    img = Spike_image;
                    break;
                }
                default: {
                    raise_warn("wrong object type while write map");
                    img = nullptr;
                }
            }
            if(img==nullptr) {
                raise_warn("try to draw null object in ground map"); 
                return;
            }

            al_draw_scaled_bitmap(img,
                                  0,0,
                                  al_get_bitmap_width(img) ,al_get_bitmap_height(img),
                                  CHUNK_WIDTH *(j -window_x - 1.5),
                                  CHUNK_HEIGHT*(i -window_y - 1.5),
                                  3*CHUNK_WIDTH,3*CHUNK_HEIGHT,
                                  0
                                 );
        }
    }
}

void Level::draw() {
    window_center = snake->head;
    Interface::draw();

    draw_map();

    for(auto &o:object) {
        o->window_x = window_center.second - window_width/2;
        o->window_y = (MAP_HEIGHT-SEE_MAP_HEIGHT)/2;
        o->draw();
    }
    
    snake->draw();
}

bool Level::CanMove(Pos now,OBJ_TYPE T,DIRCTION dirc) {
    if(dirc == NONE) return false;
    const Pos dP = DIRC_TO_POS(dirc);
    const Pos next = {now.first+dP.first,now.second+dP.second};
    const Pos next_next = {next.first+dP.first,next.second+dP.second};
    OBJ_TYPE NT = is(next,map);
    OBJ_TYPE NNT = is(next_next,map);

    switch(NT) {
        case HEAD:
        case BODY:
        case GROUND: 
        case APPLE: return false;
        case EDGE: 
        case AIR:
        case END:   return true;
        case STONE: {
            if(NNT==AIR || NNT==EDGE || NNT == END) return true;
            else return false;
        }
        default:{
            raise_warn("unknown type in map");
            return false;
        }
    }
}

bool Level::update() {
    // if reach end
    if(is(snake->head,ground_map)==END){
        level_stat = NEXT;
        return false;
    }

    // update key lock
    update_key_lock();

    bool draw = false;
    // object state set
    for(auto it=object.begin();it!=object.end();++it) {
        if((*it)->type == STONE) {
            Pos _pos = (*it)->getPos();
            if(is(_pos,ground_map)==EDGE) {
                is(_pos,ob_map) = AIR;
                delete *it;
                object.erase(it);
                draw = true;
            }
            if(CanMove((*it)->getPos(),STONE,Gravity)) {
                set_key_lock();
                (*it)->move_dirc = Gravity;
                draw = true;
            }
        }
    }
    
    // snake fall dectection
    snake->isFall = true;
    for(auto &b:snake->body) {
        Pos pos = b->getPos();
        const Pos dP = DIRC_TO_POS(Gravity);
        const Pos next = {pos.first+dP.first,pos.second+dP.second};
        if(is(pos,ground_map)==EDGE) {
            snake->isFall = false;
            level_stat = RESTART;
            return true;
        }
        if(!CanMove(pos,b->type,Gravity) && is(next,snake_map)!=BODY && is(next,snake_map)!=HEAD){
            snake->isFall = false;
            break;
        }
    }

    // snake state set
    Pos next = snake->Next_Pos();
    if(snake->isFall) {  //falling
        show_msg("Snake fall");
        snake->move_direction = Gravity;
        set_key_lock();
        draw = true;
    }
    else if(snake->move_direction==NONE) {}
    else if(is(next,map)==APPLE) {  //eat apple
        show_msg("Snake eat apple");
        snake->can_eat_apple = true;
        is(next,map) = AIR;
        is(next,ground_map) = AIR;
        draw = true;
    }
    else if(CanMove(snake->head,HEAD,snake->move_direction)) {  //move
        show_msg("Snake move");
        if(is(next,map)==STONE) {
            for(auto &ob:object) {
                if(ob->getPos() == next) ob->move_dirc = snake->move_direction;
            }
        }
        set_key_lock();
        draw = true;
    }
    else {
        show_msg("Snake can't move because obstacle");
        snake->move_direction = NONE;
        draw = true;
    }

    // delete all object to temp map
    for(const auto &b:snake->body) {
        is(b->getPos(),snake_map) = AIR;
        is(b->getPos(),map) = AIR;
    }
    for(const auto &o:object) {
        is(o->getPos(),ob_map) = AIR;
        is(o->getPos(),map) = AIR;
    }

    // update snake
    snake->update();
    
    // update object
    for(auto &o:object) {
        o->update();
    }

    // load all object to temp map
    for(const auto &b:snake->body) {
        is(b->getPos(),snake_map) = b->type;
        is(b->getPos(),map) = b->type;
    }
    for(const auto &o:object) {
        is(o->getPos(),ob_map) = o->type;
        is(o->getPos(),map) = o->type;
    }

    if(draw && Show) print_map();

    return true;
}

inline DIRCTION Level::KEY_TO_DIRC(int key) {
    switch(key) {
        case ALLEGRO_KEY_LEFT:  return LEFT;
        case ALLEGRO_KEY_RIGHT: return RIGHT;
        case ALLEGRO_KEY_UP:    return UP;
        case ALLEGRO_KEY_DOWN:  return DOWN;
        default :               {
            raise_warn("Unknown key");
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
    if(key == ALLEGRO_KEY_N) {
        show_msg("Key triger : jump to next level");
        level_stat = NEXT;
        return GAME_LEVEL;
    } 
    if(key == ALLEGRO_KEY_Q) {
        show_msg("Key triger : quit game");
        return GAME_TERMINATE;
    } 
    if(key == ALLEGRO_KEY_R) {
        show_msg("Key triger : reset level");
        level_stat = RESTART;
        return GAME_LEVEL;
    }
    if(key_lock) {
        show_msg("Key triger : key lock");
        snake->move_direction = NONE;
    }
    else {
        show_msg("Key triger : move");
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
    Snake_body_straight_image = al_load_bitmap((IMAGE_PATH+"/snakeBody_straight.png").c_str());
    Snake_body_turn_image = al_load_bitmap((IMAGE_PATH+"/snakeBody_turn.png").c_str());
    Snake_tail_image = al_load_bitmap((IMAGE_PATH+"/snakeTail.png").c_str());
    End_point_image = al_load_bitmap((IMAGE_PATH+"/end.png").c_str());
    Buttom_image = al_load_bitmap((IMAGE_PATH+"/buttom.png").c_str());
    Spike_image = al_load_bitmap((IMAGE_PATH+"/spike.png").c_str());
    
    if((Ground_image && 
        Stone_image && 
        Apple_image && 
        Snake_head_image && 
        Snake_body_straight_image && 
        Snake_body_turn_image &&
        Snake_tail_image &&
        End_point_image &&
        Buttom_image && 
        Spike_image) == false) {
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
        fin.close();
        return false;
    }
    int t = 6;
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
                                                        Snake_body_straight_image,
                                                        Snake_body_turn_image,
                                                        Snake_tail_image);
                break;
            }
            case '4': {  //stone
                show_msg("load stone");
                fin >> m;
                Pos stone_position;  //stone_posotion {y1,x1}
                for (int i = 0; i < m; i++)
                {
                    fin >> stone_position.first >> stone_position.second;
                    Object * temp = new Stone(stone_position,Stone_image);
                    object.emplace_back(temp);
                }
                break;
            }
            case '5': {  //button
                show_msg("load button");
                fin >> m;
                Pos button_position;  //button_posotion {y1,x1}
                for (int i = 0; i < m; i++)
                {
                    fin >> button_position.first >> button_position.second >> path;
                    switch (path[1])
                    {
                    case 'h':{   //Short
                        /* code */
                        break;}
                    case 'p':{   //Spike
                        Pos spike_position;  //spike_posotion {y1,x1}
                        fin >> n;
                        while (n--)
                        {
                            fin >> spike_position.first >> spike_position.second;
                        }
                        
                        break;}
                    case 'r':{   //Grave
                        /* code */
                        break;}
                    default:
                        break;
                    }
                }
                break;
            }
            case '6': {  //map
                show_msg("load map");
                fin >> m >> n;
                mapw = n;
                maph = m;
                map.resize(m,std::vector<OBJ_TYPE>(n,AIR));
                ground_map = map;
                ob_map = map;
                snake_map = map;
                int element;
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        fin >> element;
                        OBJ_TYPE typ = static_cast<OBJ_TYPE>(element);
                        switch(typ) {
                            case EDGE:
                            case AIR:
                            case GROUND:
                            case END:
                            case APPLE:
                            case SPIKE: {
                                ground_map[i][j] = typ;
                                map[i][j] = typ;
                                break;
                            }
                            case HEAD:
                            case BODY: {
                                snake_map[i][j] = typ;
                                map[i][j] = typ;
                            }
                            case STONE:
                            case BUTTON: {
                                ob_map[i][j] = typ;
                                map[i][j] = typ;
                                break;
                            }
                            default: {
                                raise_warn("Unknown type when load level");
                                map[i][j] = typ;
                                break;
                            }
                        }
                    }
                }
                break;
            }

            default: {
                sprintf(tmp, "Level%d loaded fail, Level%d's data wrong.", level_idx,level_idx);
                raise_err(tmp);
                fin.clear();
                fin.close();
                return false;
            }
        }
    }
    show_msg("load level done");
    fin.clear();
    fin.close();
    print_map();
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
                case STONE:
                    cout << "░░";
                    break;
                case GROUND:
                    cout << "██";
                    break;
                case END:
                    cout << " ⊠";
                    break;
                case APPLE:
                    cout << " ⋄";
                    break;
                case EDGE:
                    cout << "▞▞";
                    break;
                case SPIKE:
                    cout << "||";
                    break;
                case BUTTON:
                    cout << " ▂";
                    break;
                case BODY:
                    cout << "▒▒";
                    break;
                case HEAD:
                    cout << "▓▓";
                    break;
                default:
                    cout << "**";
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
    key_lock = false;
    key_lock_count =0;
    load_level(idx);
    show_msg("Level reset done");
}

void Level::destroy_level() {
    show_msg("level destroy begin");
    Interface::~Interface();
    
    al_destroy_bitmap(Ground_image);
    al_destroy_bitmap(Stone_image);
    al_destroy_bitmap(Apple_image);
    al_destroy_bitmap(Snake_head_image);
    al_destroy_bitmap(Snake_body_straight_image);
    al_destroy_bitmap(Snake_body_turn_image);
    al_destroy_bitmap(End_point_image);
    al_destroy_bitmap(Buttom_image);
    al_destroy_bitmap(Spike_image);
    al_destroy_bitmap(Snake_tail_image);
    Ground_image = nullptr;
    Stone_image = nullptr;
    Apple_image = nullptr;
    Snake_head_image = nullptr;
    Snake_body_straight_image = nullptr;
    Snake_body_turn_image = nullptr;
    Snake_tail_image = nullptr;
    End_point_image = nullptr;
    Buttom_image = nullptr;
    Spike_image = nullptr;

    key_lock = false;
    int key_lock_count = 0;

    delete snake;
    for(auto &o:object) {
        delete o;
        o = nullptr;    
    }
    show_msg("level destroy done");
}

// constructor and deletor
Level::Level(int i):
       Interface(MUSIC_PATH+"/level_bgm.ogg",IMAGE_PATH+"/background.png") 
{
    show_msg("Create level begin");
    key_lock = false;
    key_lock_count =0;
    level_stat = KEEP;
    load_level(i);
    show_msg("Create level done");
}

Level::~Level() {
    show_msg("Delete level begin");
    destroy_level();
    show_msg("Delete level done");
}