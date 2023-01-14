#include "global.h"
#include "Level.h"

// update all object
void Level::update() {}

// process trigered by key
GAME_STATE Level::key_triger(int key) {return GAME_LEVEL;}

// load level
bool Level::load_level(int) {return true;}

// reset
void Level::reset() {}

// constructor and deletor
Level::Level(int i) {}
Level::~Level() {}