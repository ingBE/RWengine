#include <iostream>
#include <assert.h>
#include "../glutInit.h"
#include "../precision.h"
#include "../core.h"
#include "../particle.h"
#include "../particleFunc.h"

using namespace RWengine;

// 카메라의 위치
float x = 5, y = -2, z = 1;

// 카메라의 시선
float lx = -6, ly = 5, lz = 0;

Particle particle;
Vector3 position;
Vector3 gravity( 0, 0, -9.8 );
real duration;

void changeSize(int width, int height)
{
    glChangeSize( width, height );
    gluLookAt( y, z, x, y+ly, z+lz, x+lx, 0.0,1.0,0.0);
}

void renderScene(void)
{
    duration = 0.005;

    position = particle.getPosition();
    particle.addForce( gravity );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glPushMatrix();

    glCreateCoordinate( 100.0, 100.0, 100.0 );
    glCreateGround( 100, 100 );

    glColor3f( 1.0, 0.5, 0.0 );

    glTranslatef( position.y, position.z, position.x );
    glutSolidSphere( 0.05, 50, 50 );

    glPopMatrix();

    glutSwapBuffers();

    particle.integrate( duration );
}

void startKey(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '1':
            x = 5, y = -2, z = 1;
            lx = -6, ly = 5, lz = 0;
            glLoadIdentity();
            gluLookAt(y,z,x,y+ly,z+lz,x+lx,0.0,1.0,0.0);
            break;
        case '2':
            x = 5, y = 5, z = 1;
            lx = -6, ly = -2, lz = 0;
            glLoadIdentity();
            gluLookAt(y,z,x,y+ly,z+lz,x+lx,0.0,1.0,0.0);
            break;
        case '3':
            x = 5.0, y = 8.0, z = 0.0;
            lx = -7.0, ly = -6.0, lz = 0.0;
            glLoadIdentity();
            gluLookAt(y,z,x,y+ly,z+lz,x+lx,0.0,1.0,0.0);
            break;
        case 'A':
        case 'a':
            particle.setPosition( 0.0, 0.0, 0.0 );
            particle.setVelocity( -3.0, 3.5, 7.0 );
            break;
    }
}

int main(int argc, char **argv )
{
    particle.setMass( 1.0 );
    particle.setDamping( 0.0 );

    glutInit( argc, argv );
    glutReshapeFunc(changeSize);
    glutDisplayFunc(renderScene); 

    glutIdleFunc(renderScene);

    glutReshapeFunc(changeSize);

    glutKeyboardFunc(startKey);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
