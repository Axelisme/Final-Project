#include "Snake.h"

void Snake::draw() {
    for(auto &b:body) {
        b->draw();
    }
}

void Snake::Move_all() {
    for(auto &b:body){
        b->move_dirc = move_direction;
        b->update();
    }
    head = body.back()->getPos();
    move_direction = NONE;
}

void Snake::Move_forward() {
    delete body.front();
    body.pop_front();
    Move_extend();
}

void Snake::Move_extend() {
    Pos next_pos = Next_Pos();
    Body *origin_head = body.back();

    origin_head->getImg() = Image_body;
    origin_head->type = BODY;
    origin_head->to_dirc = move_direction;
    head = next_pos;
    heading = move_direction;

    body.push_back(new Body(next_pos,
                            HEAD,
                            Image_head,
                            move_direction,
                            move_direction));
    move_direction = NONE;
}

bool Snake::update() {
    if(isFall) {
        show_msg("Snake fall begin");
        Move_all();
        isFall = false;
        show_msg("Snake fall done");
        return true;
    }
    else if(can_eat_apple) {
        show_msg("Snake eat apple begin");
        Move_extend();
        can_eat_apple = false;
        show_msg("Snake eat apple done");
        return true;
    }
    else if(move_direction!=NONE) {
        show_msg("Snake move begin");
        Move_forward();
        show_msg("Snake move done");
        return true;
    }
    else return false;
}

Pos Snake::Next_Pos() {
    Pos dP = DIRC_TO_POS(move_direction);
    return std::make_pair(head.first+dP.first,head.second+dP.second);
}

DIRCTION Snake::Cal_Dirc(Pos now,Pos next) {
    if(next.first > now.first)   return DOWN;
    if(next.first < now.first)   return UP;
    if(next.second > now.second) return RIGHT;
    if(next.second < now.second) return LEFT;
    return NONE;
}

bool SnakeCanMove(Snake*snake,DIRCTION dirc,Map& map,Map& ob_map) {
    return false;
}

Snake::Snake(std::vector<Pos>& Poss,ALLEGRO_BITMAP * img_head,
                                    ALLEGRO_BITMAP * img_body) {
    show_msg("Create snake begin");
    Image_head = img_head;
    Image_body = img_body;

    head = Poss.back();

    DIRCTION from = UP;
    DIRCTION to = UP;
    for(int i=0;i<Poss.size()-1;++i) {
        from = to;
        to = Cal_Dirc(Poss[i],Poss[i+1]);
        body.push_back(new Body(Poss[i],BODY,Image_body,from,to));
    }
    body.push_back(new Body(head,HEAD,Image_head,to,to));
    show_msg("Create Snake done");
}

Snake::~Snake() {
    show_msg("Delete snake begin");
    for(auto &b:body) {
        delete b;
        b = nullptr;
    }
    show_msg("Delete snake done");
}

