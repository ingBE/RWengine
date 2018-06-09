#include <cmath>

namespace RWengine
{
    class Vector3
    {
    public:
        real x;
        real y;
        real z;

    private:
        real pad; // 4 워드 최적화

    public:
        Vector3() : x(0), y(0), z(0) {}
        Vector3( const real x, const real y, const real z )
            : x(x), y(y), z(z) {}

        void display() { std::cout << "( " << x << ", " << y << ", " << z << " )" << std::endl; }

        // function
        
        void invert()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        real magnitude() const
        {
            return sqrt( x*x + y*y + z*z );
        }

        real squareMagnitude() const
        {
            return x*x + y*y + z*z;
        }

        void normalize()
        {
            real l = magnitude();
            if ( l > 0 )
            {
                (*this) *= ((real)1/l);
            }
        }

        void makeOrthonormalBasis( Vector3 *a, Vector3 *b, Vector3 *c )
        {
            a->normalize();
            (*c) = (*a) % (*b);
            if ( c->magnitude() == (real)0 ) { return; }
            c->normalize();
            (*b) = (*c) % (*a);
        }

        // operator

        Vector3 operator+( const Vector3 vector ) const
        {
            return Vector3( x + vector.x, y + vector.y, z + vector.z );
        }

        Vector3 operator-( const Vector3 vector ) const
        {
            return Vector3( x - vector.x, y - vector.y, z - vector.z );
        }

        Vector3 operator*( const real number ) const // scala product
        {
            return Vector3( x * number, y * number, z * number );
        }

        real operator*( const Vector3 vector ) const
        {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        Vector3 operator%( const Vector3 vector ) const // vector product
        {
            return Vector3( y*vector.z - z*vector.y, z*vector.x - x*vector.z, x*vector.y - y*vector.x );
        }

        void operator+=( const Vector3 vector )
        {
            x += vector.x;
            y += vector.y;
            z += vector.z;
        }

        void operator-=( const Vector3 vector )
        {
            x -= vector.x;
            y -= vector.y;
            z -= vector.z;
        }

        void operator*=( const real number )
        {
            x *= number;
            y *= number;
            z *= number;
        }

        void operator%=( const Vector3 vector )
        {
            (*this) = (*this) % vector;
        } 
    };
}
