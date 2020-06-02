// Some simple unit tests. Feel free to replace this with a testing
// framework if you are aware of one.

#include <iostream>
#include "block.h"
using namespace std;

// Lazy globals for tests because slack.
int test_ct = 0;
int pass_ct = 0;

void expect(bool test, const string message);

int main() {

    Block block = Block(Block::straight);
    expect(block.getX() == 0 &&  block.getY() == 0, "Initial position.");

    block.shift(0,1);
    expect(block.getX() == 0 &&  block.getY() == 1, "Shift.");
    string test_string_1 = " +  \n"\
                           " +  \n"\
                           " +  \n"\
                           " +  ";

    expect(block.toString() == test_string_1, "To string."); 
    

    cout << pass_ct << "/" << test_ct << "tests passed" << '\n';
}


void expect(bool test, const string message) {
    if (test) {
        cout << "Test " << ++test_ct << " passed." << '\n'; 
        ++pass_ct;
    }
    else {
        cout << "Test " << ++test_ct << " failed." << '\n' << message << '\n';
    }
}

