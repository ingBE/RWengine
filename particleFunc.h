using namespace RWengine;

void Particle::integrate( real duration )
{
    if ( inverseMass <= 0.0 ) { return; }

    assert( duration >= 0.0 );

    position += velocity * duration;

    Vector3 resultingAcc = acceleration;
    resultingAcc += forceAccum * inverseMass;

    velocity += resultingAcc * duration;

    clearAccumulator();
}

void Particle::setPosition( const Vector3 position )
{
    Particle::position = position;
}

void Particle::setPosition( const real x, const real y, const real z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

Vector3 Particle::getPosition()
{
    return position;
}

void Particle::setVelocity( const Vector3 velocity )
{
    Particle::velocity = velocity;
}

void Particle::setVelocity( const real x, const real y, const real z)
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

Vector3 Particle::getVelocity()
{
    return velocity;
}

void Particle::setAcceleration( const Vector3 acceleration )
{
    Particle::acceleration = acceleration;
}

void Particle::setAcceleration( const real x, const real y, const real z )
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

Vector3 Particle::getAcceleration()
{
    return acceleration;
}

void Particle::setMass( const real mass )
{
    assert( mass != 0.0 );
    Particle::inverseMass = ((real)1.0)/mass;
}

real Particle::getMass()
{
    return ((real)1.0)/inverseMass;
}

void Particle::setInverseMass( const real inverseMass)
{
    Particle::inverseMass = inverseMass;
}

real Particle::getInverseMass()
{
    return inverseMass;
}

void Particle::clearAccumulator()
{
    forceAccum.clear();
}

void Particle::addForce( const Vector3 force )
{
    forceAccum += force;
}
