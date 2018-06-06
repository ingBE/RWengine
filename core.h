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
        
        // 함수
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
        
        // 연산자  
        Vector3 operator+( Vector3 vector )
        {
            return Vector3( x + vector.x, y + vector.y, z + vector.z );
        }
        
        Vector3 operator-( Vector3 vector )
        {
            return Vector3( x - vector.x, y - vector.y, z - vector.z );
        }
    };
}
