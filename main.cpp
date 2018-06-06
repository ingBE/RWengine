#include <iostream>
#include "precision.h"
#include "core.h"
using namespace std;
using namespace RWengine;

int main (void)
{
    Vector3 a( 0, 1, 2 );
    a.invert();
    a.display();
    cout << a.squareMagnitude() << endl;
    return 0;
}
