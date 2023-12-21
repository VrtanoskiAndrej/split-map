#include "split_map.hpp"

int main(int argc, char const *argv[])
{
    split_map<int, int> map;
    map.put(0, 1);
    map.print();
    return 0;
}
