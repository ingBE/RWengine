namespace RWengine
{
    class Particle
    {
    public:
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
        real damping;
        real inverseMass;
        Vector3 forceAccum;

    public:
        void integrate( real duration );
        void setPosition( const Vector3 position );
        void setPosition( const real x, const real y, const real z );
        Vector3 getPosition();
        void setVelocity( const Vector3 velocity );
        void setVelocity( const real x, const real y, const real z );
        Vector3 getVelocity();
        void setAcceleration( const Vector3 acceleration );
        void setAcceleration( const real x, const real y, const real z );
        Vector3 getAcceleration();
        void setDamping( const real dmaping );
        real getDamping();
        void setMass( const real mass );
        real getMass();
        void setInverseMass( const real inverseMass );
        real getInverseMass();
        void clearAccumulator();
        void addForce( const Vector3 force );
    };
}
