#include "block.h"

using namespace std;
// This is the constructor. It runs when a *value* of type Block is created.
// ie. with `Block my_block(Block::l_piece, true)`
Block::Block(Block::Shape shape, bool mirror) {
    // The members are just accessible by their name.
    switch (shape) {
        case straight:
            cells = array<array<char,4>,4> {{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}};
            break;
        case l_piece:
            cells = array<array<char,4>,4> {{{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}};
            break;
        case squiggley:
            cells = array<array<char,4>,4> {{{0,0,0,0},{0,1,1,0},{0,0,1,1},{0,0,0,0}}};
            break;
        case square:
            cells = array<array<char,4>,4> {{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}};
            break;
    }
    if (mirror) { //Do something to get the other version of l_piece and squiggley 
    }
}

// These are other methods, they run with my_block.flip()
// You can probably call them from each other, ah.
// There's an automagically created this pointer.
// So flip could call `this->shift(1,1)` if it also needed to shift.
void Block::flip(){
}

int Block::shift(int dx, int dy) {
    return 0;
}

int Block::getX() {
    return x;
}

int Block::getY() {
    return y;
}


string Block::toString() {
    return string("abc");
}

