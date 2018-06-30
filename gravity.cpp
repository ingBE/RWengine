#include <iostream>
#include <assert.h>
#include <ctime>
#include "glutInit.h"
#include "precision.h"
#include "core.h"
#include "particle.h"
#include "particleFunc.h"

using namespace RWengine;

Particle particle;
Vector3 position;
Vector3 gravity(0,0,-1.0);
real duration;
clock_t start = 0, end = 0;

void renderScene(void)
{
//    end = clock();
//    duration = ((real)(end - start))/(CLOCKS_PER_SEC*1000.0);
    duration = 0.01;

    position = particle.getPosition();
    particle.addForce( gravity );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glPushMatrix();

    glColor3f( 1.0, 1.0, 1.0 );
    glPointSize( 10.0 );
   
    glBegin(GL_POINTS);
        glVertex3f( position.y, position.z, position.x );
    glEnd();

    glPopMatrix();
    glutSwapBuffers();

    particle.integrate( duration );

//    start = clock();
}

void startKey(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'A':
        case 'a':
            particle.setPosition( 0.0, -2.0, -1.0 );
            particle.setVelocity( 0.0, 1.0, 2.3 );
            break;
    }
}

int main(int argc, char **argv )
{
    particle.setMass( 1.0 );
    particle.setDamping( 0.0 );

    glutInit( argc, argv );
    glutDisplayFunc(renderScene); 

    glutIdleFunc(renderScene);

    glutReshapeFunc(changeSize);

    glutKeyboardFunc(startKey);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
