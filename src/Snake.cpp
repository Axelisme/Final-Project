#include "Snake.h"

void Snake::draw() {
    for(auto &b:body) {
        b->draw();
    }
}

bool Snake::update() {
    if(isFall) {
        for(auto &b:body){
            b->isFall = true;
            b->update();
        }
        head = body.back()->getPos();
        isFall = false;
        move_direction = NONE;
        return true;
    }
    else if(can_eat_apple) {
        Pos next_pos = Next_Pos();
        Body *origin_head = body.back();
        origin_head->getImg() = Image_body;
        body.push_back(new Body(next_pos,
                                Image_head,
                                move_direction,
                                move_direction));
        can_eat_apple = false;
        return true;
    }
    else if(move_direction!=NONE) {
        Pos next_pos = Next_Pos();
        delete body.front();
        body.pop_front();
        Body *origin_head = body.back();
        origin_head->getImg() = Image_body;
        origin_head->to_dirc = move_direction;
        body.push_back(new Body(next_pos,
                                Image_head,
                                move_direction,
                                move_direction));
        head = next_pos;
        heading = move_direction;
        move_direction = NONE;
        return true;
    }
    else return false;
}

Pos Snake::DIRC_TO_POS(DIRCTION dirc) {
    switch(dirc) {
        case LEFT:  return std::make_pair( 0.,-1.);
        case RIGHT: return std::make_pair( 0., 1.);
        case UP:    return std::make_pair(-1., 0.);
        case DOWN:  return std::make_pair( 1., 0.);
        default:    return std::make_pair( 0., 0.);
    }
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

Snake::Snake(std::vector<Pos>& Poss,ALLEGRO_BITMAP * img_head,
                                    ALLEGRO_BITMAP * img_body) {
    Image_head = img_head;
    Image_body = img_body;

    head = Poss.back();

    DIRCTION from = UP;
    DIRCTION to = UP;
    for(int i=0;i<Poss.size()-1;++i) {
        from = to;
        to = Cal_Dirc(Poss[i],Poss[i+1]);
        body.push_back(new Body(Poss[i],Image_body,from,to));
    }
    body.push_back(new Body(head,Image_head,to,to));
}

Snake::~Snake() {
    for(auto &b:body) {
        delete b;
    }
}

