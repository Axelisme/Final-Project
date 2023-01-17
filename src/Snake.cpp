#include "Snake.h"

void Snake::draw() {
    for(auto &b:body) {
        b->window_x = head.second - window_width/2;
        b->window_y = head.first - window_height/2;
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
    Move_extend();
    Shorten();
}

void Snake::Move_extend() {
    Pos next_pos = Next_Pos();
    Body *origin_head = body.back();

    origin_head->type = BODY;
    origin_head->to_dirc = move_direction;
    head = next_pos;
    heading = move_direction;

    body.push_back(new Body(next_pos,
                            HEAD,
                            Image_head,
                            Image_body_straight,
                            Image_body_turn,
                            move_direction,
                            move_direction));
    move_direction = NONE;
}

void Snake::Shorten() {
    show_msg("snake shorten begin");
    delete body.front();
    body.pop_front();
    if(body.empty()) {
        isDied = true;
        return;
    }
    Body * NewTail = body.front();
    NewTail->image_body_straight = Image_tail;
    NewTail->from_dirc = NewTail->to_dirc;
    show_msg("snake shorten end");
}

bool Snake::update() {
    if(isDied) return false;
    else if(isFall) {
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

Snake::Snake(std::vector<Pos>& Poss,ALLEGRO_BITMAP * img_head,
                                    ALLEGRO_BITMAP * img_body_straight,
                                    ALLEGRO_BITMAP * img_body_turn,
                                    ALLEGRO_BITMAP * img_tail) {
    show_msg("Create snake begin");
    Image_head = img_head;
    Image_body_straight = img_body_straight;
    Image_body_turn = img_body_turn;
    Image_tail = img_tail;

    move_direction = NONE;
    isFall = false;
    can_eat_apple = false;
    isDied = false;

    DIRCTION from = UP;
    DIRCTION to = POS_TO_DIRC(Poss[0],Poss[1]);
    body.push_back(new Body(Poss.front(),BODY,Image_head,
                                              Image_tail,
                                              Image_body_turn,
                                              to,to));
    for(int i=1;i<Poss.size()-1;++i) {
        from = to;
        to = POS_TO_DIRC(Poss[i],Poss[i+1]);
        body.push_back(new Body(Poss[i],BODY,Image_head,
                                             Image_body_straight,
                                             Image_body_turn,
                                             from,to));
    }
    head = Poss.back();
    heading = to;
    body.push_back(new Body(head,HEAD,Image_head,
                                      Image_body_straight,
                                      Image_body_turn,
                                      to,to));
    
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

