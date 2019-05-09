#include <iostream>
#include <assert.h>
#include "../glutInit.h"
#include "../precision.h"
#include "../core.h"
#include "../particle.h"
#include "../particleFunc.h"

using namespace RWengine;

Particle particle;
Vector3 position;
Vector3 gravity( 0, 0, -9.8 );
real duration;

int mouse_x, mouse_y;
float phi = M_PI - 0.6947382762, theta = M_PI_2, d_phi = 0, d_theta = 0;
Vector3 d_camera;
Vector3 camera( 5, -2, 1 );
Vector3 cameraLook;

void lookAtVector3()
{
    Vector3 look = camera + cameraLook;
    glLoadIdentity();
    gluLookAt( camera.y, camera.z, camera.x, look.y, look.z, look.x, 0.0, 1.0, 0.0 );
}

void move( float phi, float theta )
{
    d_camera = Vector3( sinf(theta)*cosf(phi), sinf(theta)*sinf(phi), cosf(theta) );
}

void stop()
{ d_camera = Vector3( 0, 0, 0 ); }

void cameraMove( float speed )
{
    cameraLook = Vector3( sinf(theta)*cosf(phi), sinf(theta)*sinf(phi), cosf(theta) );

    phi = phi + d_phi;
    theta = theta + d_theta;

    camera += d_camera * speed;

    lookAtVector3();
}

void changeSize(int width, int height)
{
    glChangeSize( width, height );
    lookAtVector3();
}

int start=0, end=0;
//int a=0, b=0;

void renderScene(void)
{
    //  현실과 비슷한지 측정
    //  실제로는 ( -4.285, 5.000, 0.000) 1.429sec
    
/*    if (particle.getPosition().z <= 0.0 and particle.getPosition().z > -0.15 and particle.getPosition().x != 0)
    {
        b = glutGet(GLUT_ELAPSED_TIME);
        particle.getPosition().display();
        std::cout << (float)(b-a)/1000 << "sec" << std::endl << std::endl;
    }
*/    

    start = end; end=glutGet(GLUT_ELAPSED_TIME);
    duration = (float)(end-start)/1000.0;

    cameraMove(0.01);

    position = particle.getPosition();
    particle.addForce( gravity * particle.getMass() );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glPushMatrix();

    glCreateCoordinate( 100.0, 100.0, 100.0 );
    glColor3f( 0.0, 0.0, 0.0 );
    for ( float i=-100; i<=100; i++)
    {
        glBegin(GL_LINE_STRIP);
            glVertex3f( -100, 0.0, i );
            glVertex3f( 100, 0.0, i );
        glEnd();
    }
    for ( float i=-100; i<=100; i++)
    {
        glBegin(GL_LINE_STRIP);
            glVertex3f( i, 0.0, -100 );
            glVertex3f( i, 0.0, 100 );
        glEnd();
    }
    glCreateGround( 100, 100 );

    glColor3f( 1.0, 0.5, 0.0 );

    glTranslatef( position.y, position.z, position.x );
    glutSolidSphere( 0.075, 50, 50 );

    glPopMatrix();

    fps();

    glutSwapBuffers();

    if ( particle.position.z < 0 ) { particle.velocity.z = -particle.velocity.z; }
    particle.integrate( duration );
}


void mouseMotion( int x, int y )
{
    if ( 0 < x < w and 0 < y < h )
    {
        d_phi = (float)(x - mouse_x) * 0.0003;
        d_theta = (float)(mouse_y - y) * 0.0003;

        mouse_x = x;
        mouse_y = y;
    }
}

void mousePassiveMotion( int x, int y )
{
    if ( 0 < x < w and 0 < y < h )
    {
        d_phi = 0.0f;
        d_theta = 0.0f;

        mouse_x = x;
        mouse_y = y;
    }
}

void pressKey(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 13:
            particle.setPosition( 0.0, 0.0, 10.0 );
            particle.setVelocity( 1.0, 0.0, 0.0 );
//            a = glutGet(GLUT_ELAPSED_TIME);
            break;
        case 'w':
            move( phi, theta );
            break;
        case 's':
            move( phi + M_PI, M_PI - theta );
            break;
        case 'a':
            move( phi + M_PI_2, M_PI_2 );
            break;
        case 'd':
            move( phi - M_PI_2, M_PI_2 );
            break;
        case 32:
            move( 0, 0 );
            break;
        case 'c':
            move( 0, M_PI );
            break;
        case 27:
            exit(0);
    }
}

void releaseKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'w':
        case 's':
        case 'a':
        case 'd':
        case 32:
        case 'c':
            stop();
    }
}

int main(int argc, char **argv )
{
    particle.setMass( 1.0 );

    glutInit( argc, argv );
    glutReshapeFunc(changeSize);
    glutDisplayFunc(renderScene); 

    glutIdleFunc(renderScene);

    glutReshapeFunc(changeSize);

    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKeys);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mousePassiveMotion);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
