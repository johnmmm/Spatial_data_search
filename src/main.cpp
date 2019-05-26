#include "GPTree.h"

int main()
{
    GPTree new_tree;
    new_tree.test_cmake();

    new_tree.init();
    new_tree.read();
    // new_tree.load();
    new_tree.build_tree();
    new_tree.save();

    return 0;
}