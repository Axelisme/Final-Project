#include "global.h"
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
        isFall = false;
    }
    else if(can_eat_apple) {
        Pos next_pos = Next_Pos();
        if(next_pos == head) {
            raise_warn("find apple in head?");
            return true;
        }
        Body *origin_head = *body.rbegin();
        origin_head->type = BODY;
        body.emplace_back(new Body(next_pos,HEAD));
        
    }
}

void Snake::EatApple(Pos pos) {

}

Pos Snake::Next_Pos() {

}

BODY_DIRCTION Snake::Body_Dirc(int) {

}

Snake::Snake(std::vector<Pos>&,ALLEGRO_BITMAP * img_head,ALLEGRO_BITMAP * img_body) {

}

