#include <assert.h>
#include "precision.h"
#include "core.h"
#include "particle.h"

using namespace RWengine;

void Particle::integrate( real duration )
{
    if ( inverseMass <= 0.0 ) { return; }

    assert( duration > 0.0 );

    position += velocity * duration;

    Vector3 resultingAcc = acceleration;
    resultingAcc += forceAccum * inverseMass;

    velocity += resultingAcc * duration;

    clearAccumulator();
}

void Particle::setPositon( const Vector3 positon )
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

void Particle::setVelocity( const Vector3 velosity )
{
    Partcle::velosity = velosity;
}

void Particle::setVelosity( const real x, const real y, const real z)
{
    velosity.x = x;
    velosity.y = y;
    velosity.z = z;
}

Vector3 Particle::getVelosity()
{
    real velosity;
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

void Particle::setDamping( const real damping )
{
    Particle::damping = damping;
}

real Particle::getDamping()
{
    return damping;
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
