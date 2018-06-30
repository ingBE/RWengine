#include <GL/glut.h>

void changeSize(int width, int height)
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
    gluLookAt(0.0,0.0,5.0, 0.0,0.0,-1.0, 0.0,1.0,0.0);
}

void glutInit( int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowPosition( 100, 30 );
    glutInitWindowSize( 1024, 700 );
    glutCreateWindow( "R A I N W A T E R" );
    glutReshapeFunc(changeSize);
}
