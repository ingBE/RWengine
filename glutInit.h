#include <GL/glut.h>

void glChangeSize(int width, int height)
{
    // 0으로 나누지 못함
    if (height == 0) { height = 1; }
    float ratio = 1.0 * width / height;

    //좌표계 초기화
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, width, height);

    //투시값 변경
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void glutInit( int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowPosition( 100, 30 );
    glutInitWindowSize( 1024, 700 );
    glutCreateWindow( "R A I N W A T E R" );
}

void glCreateCoordinate( float y, float z, float x )
{
    glColor3f( 0.0, 1.0, 0.0 );
    glBegin(GL_LINE_STRIP);
        glVertex3f( -y, 0.0, 0.0 );
        glVertex3f( y, 0.0, 0.0 );
    glEnd();

    glColor3f( 0.0, 1.0, 1.0 );
    glBegin(GL_LINE_STRIP);
        glVertex3f( 0.0, -z, 0.0 );
        glVertex3f( 0.0, z, 0.0 );
    glEnd();

    glColor3f( 1.0, 0.0, 1.0 );
    glBegin(GL_LINE_STRIP);
        glVertex3f( 0.0, 0.0, -x );
        glVertex3f( 0.0, 0.0, x );
    glEnd();
}

void glCreateGround( float x, float y )
{
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
        glVertex3f(-y, 0.0, -x);
        glVertex3f(-y, 0.0, x );
        glVertex3f( y, 0.0, x );
        glVertex3f( y, 0.0, -x);
    glEnd();
}
