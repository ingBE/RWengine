#include <GL/glut.h>

int w, h;

void glChangeSize(int width, int height)
{
    w = width; h = height;

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

void exitKey(unsigned char key, int x, int y)
{
    if (key == 27) { exit(0); }
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

void setOrthographicProjection()
{
    // 행렬을 투영모드로 변경합니다.
    glMatrixMode(GL_PROJECTION);
    // 원근투영에 대한 환경변수를 
    // 가지고 있는 이전 행렬을 저장합니다.
    glPushMatrix();
        // 행렬을 초기화합니다.
        glLoadIdentity();
        // 2D 직교투영을 설정합니다.
        gluOrtho2D(0, w, 0, h);
        // y 축을 뒤집습니다.
        glScalef(1, -1, 1);
        // 좌측아래의 원점을 
        // 좌측위로 옮깁니다.
        glTranslatef(0, -h, 0);
    glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString( float x, float y, void *font, char *string)
{
    char *c;
    int x1=x;
    for (c=string; *c != '\0'; c++)
    {
        glRasterPos2f(x1,y);
        glutBitmapCharacter(font, *c);
        x1 = x1 + glutBitmapWidth(font,*c);
    }
}

int frame, time, timebase=0;
char s[60];

void fps()
{

    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000)
    {
        sprintf(s,"FPS:%4.2f",
        frame*1000.0/(time-timebase));
        timebase = time; 
        frame = 0;
    }

    glColor3f(0.0f,1.0f,1.0f);
    glPushMatrix();
        glLoadIdentity();
        setOrthographicProjection();
        renderBitmapString(30,35,GLUT_BITMAP_9_BY_15,s);
    glPopMatrix();
    resetPerspectiveProjection();
}
