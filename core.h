cyclone/core.h

namespace cyclone {

    class Vector3
    {
    public:
        real x;
        real y;
        real z;

    private:
        /** 4 워드 최적화*/
        real pad;

    public:
        Vector3() : x(0), y(0), z(0) {}
        Vecotr3(const real x, const real y, const real z)
            : x(x), y(y), z(z) {}

        void invert()
        {
            x = -x;
            y = -y;
            z = -z;
        }

        real magnitude() const
        {
            return real_sqrt(x*x+y*y+z*z);
        }

        real squareMagnitude() const
        {
            return x*x+y*y+z*z;
        }

        void normalize()
        {
            real l = magnitude();
            if (l > 0)
            {
                (*this) *= ((real)1)/l;
            }
        }
    };
}
