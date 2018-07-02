#include <iostream>
#include <assert.h>
#include "../glutInit.h"
#include "../precision.h"
#include "../core.h"
#include "../particle.h"
#include "../particleFunc.h"

using namespace RWengine;

Particle sun;
Particle earth;
Vector3 sun_position;
Vector3 earth_position;
real g = 1.0;
real duration;

Vector3 gravity( Particle p1, Particle p2 )
{
    Vector3 r;
    r = p2.getPosition() - p1.getPosition();

    real m1 = p1.getMass(), m2 = p2.getMass();

    real sqr = r.squareMagnitude();
    r.normalize();
    //r.invert();

    return r*((g*m1*m2)/sqr);
}

float x = 0.0, y = 0.0, z = 15.0;
float lx = 0.0, ly = 0.01, lz = -30.0;

void changeSize(int width, int height)
{
    glChangeSize( width, height );
    gluLookAt( y, z, x, y+ly, z+lz, x+lx, 0.0,1.0,0.0);
}

int start=0, end=0;
int a=0, b=0;

void renderScene(void)
{
    start = end; end=glutGet(GLUT_ELAPSED_TIME);
    duration = (float)(end-start)/1000.0;

    sun_position = sun.getPosition();
    earth_position = earth.getPosition();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glPushMatrix();
        glCreateCoordinate( 100.0, 100.0, 100.0 );
        glColor3f( 1.0, 1.0, 0.0 );
        glTranslatef( sun_position.y, sun_position.z, sun_position.x );
        glutSolidSphere( 0.1, 50, 50 );
    glPopMatrix();

    glPushMatrix();
        glColor3f( 0.0, 1.0, 0.0 );
        glTranslatef( earth_position.y, earth_position.z, earth_position.x );
        glutSolidSphere( 0.05, 50, 50 );
    glPopMatrix();

    fps();

    glutSwapBuffers();

    sun.addForce( gravity( sun, earth ) );
    earth.addForce( gravity( earth, sun ) );
    /*
    if ( (b-a) % 100 == 0 ) 
    {
        sun.getVelocity().display(); 
        //earth.getVelocity().display();
        a = b;
    }
    b = end;
    */
    sun.integrate( duration );
    earth.integrate( duration );
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
            x = 0.0, y = 0.0, z = 15.0;
            lx = 0.0, ly = 0.01, lz = -30.0;
            glLoadIdentity();
            gluLookAt(y,z,x,y+ly,z+lz,x+lx,0.0,1.0,0.0);
            break;
        case 27:
            //std::cout << (float)end/1000 << "s" << std::endl;
            //sun.getPosition().display();
            exit(0);
    }
}

int main(int argc, char **argv )
{
    sun.setPosition( 0.0, 0.0, 0.0 );
    sun.setVelocity( 0.045, 0.0, 0.0 );
    sun.setMass( 100.0 );
    earth.setPosition( 0.0, 5.0, 0.0 );
    earth.setVelocity( -4.5, 0.0, 0.0 );
    earth.setMass( 1.0 );

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
