#include "block.h"
#include <iostream>
#include <string>

using namespace std;
/*
// This is a class definition, I copied it here so I don't have to switch back and forth.
// It defines a new type of thing or collection of data.
// Much like a struct.
// It also defines a namespace.
// So there can be things that are part of the block class/namespace that are accessed with
// Block:: from outside it, or are just available from inside it.
// The non-static members are particular to an *instance* of Block.
class Block{
  // These are only available inside Block, so only the functions defined inside the Block{....} can see them.
  private:
    bool cells[4][4];
    int x;
    int y;
  // Could have public variables too. Stuff outside can change those.
  public:
    // An enum, basically one of four values.
    enum Shape {
        l_piece,
        straight,
        squiggley,
        square
    };
    // This is a special method called a constructor.
    // Even though it looks weird, like a function call, it's a function declaration like the others below.
    Block(Block::Shape shape, bool mirror);
    void flip();
    int shift(int dx, int dy);
    string toString();
    int getX();
    // There's no reason you have to have a declaration and not a definition inside the block. Any of the above
    // functions could have their body here.
    int getY() {
        return y;
    }
};
*/

// This is the constructor. It runs when a *value* of type Block is created.
// ie. with `Block my_block(Block::l_piece, true)`
Block::Block(Block::Shape shape, bool mirror) {
    // The members are just accessible by their name.
    switch (shape) {
        case straight:
            cells = { {0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}};
            break;
        case l_piece:
            cells = { {0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}};
            break;
        case squiggley:
            cells = { {0,0,0,0},{0,1,1,0},{0,0,1,1},{0,0,0,0}};
            break;
        case square:
            cells = { {0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}};
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

