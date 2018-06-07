#include <iostream>
#include "precision.h"
#include "core.h"
using namespace std;
using namespace RWengine;

int main(void)
{
    Vector3 a( 1, 1, 0 );
    Vector3 b( 0, 0, 6 );
    Vector3 c;
    a.makeOrthonormalBasis( a, b, c );
    a.display();
    b.display();
    c.display();
    return 0;
}
