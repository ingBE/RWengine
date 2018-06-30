#include<iostream>
using namespace std;

typedef float real;

namespace RWengine
{
    class Vector3
    {
    public:
        real x;
        real y;
        real z;

    private:
        real pad;

    public:
        Vector3() : x(0), y(0), z(0) {}
        Vector3( real x, real y, real z )
            : x(x), y(y), z(z) {}

        void display() { cout << "( " << x << ", " << y << ", " << z << " )" << endl; }

        void invert()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        real squareMagnitude() const
        {
            return x*x + y*y + z*z;
        }

        Vector3 operator+( Vector3 vector )
        {
            return Vector3( x + vector.x, y + vector.y, z + vector.z );
        }

        Vector3 operator-( Vector3 vector )
        {
            return Vector3( x - vector.x, y - vector.y, z- vector.z );
        }
    };
}

using namespace RWengine;

int main(void)
{
    Vector3 a( 0, 1, 2 );
    Vector3 b( 2, 1, 0 );
    Vector3 c;
    c = a - b;
    c.display();
    return 0;
}
