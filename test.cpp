#include <iostream>
#include "item.h"

using namespace std;

int main() {
    item a("helmet", 1);
    item b("helmet", 1);

    if(b >= a) {
        std::cout << "True.\n";
    }

    return 0;
}
