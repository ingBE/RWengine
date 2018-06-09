#include <iostream>
#include <assert.h>
#include "precision.h"
#include "core.h"
#include "particle.h"

using namespace std;
using namespace RWengine;

void Particle::integrate( real duration )
{
    if ( inverseMass <= 0 ) { return; }

    assert( duration > 0 );

    position += velocity * duration;
    velocity += acceleration * duration;

    velocity *= real_pow( damping, duration );
}

int main(void)
{
    return 0;
}
