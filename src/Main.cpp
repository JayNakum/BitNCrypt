
#include "BitNCrypt.h"

int main(int argc, char** argv)
{
    // Start the system
    // pass the argument count and arguments values
    BitNCrypt* sys = new BitNCrypt(argc, argv);
    // free the memory
    delete sys;
}
