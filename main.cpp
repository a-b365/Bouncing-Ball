#include<glut.h>
#include<cmath>
#include<iostream>
#define PI 3.14159265f

GLfloat ballRadius = 0.2;
GLfloat ballX = 0.0f;
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = 0.007f;
GLfloat xAcceleration = 0.0000f;
GLfloat yAcceleration = -0.0005f;
int refreshMills = 30;
int x1, xa, ya;
int score = 0;
int last_mx = 0, last_my = 0, cur_mx = 0, cur_my = 0;
int arcball_on = false;
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
GLdouble windowWidth = 500;
GLdouble windowHeight = 500;

void color()
{
    if (score <= 5)
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3ub(rand() % 250, rand() % 250, rand() % 250);
}

void balldisp()
{
    glTranslatef(ballX, ballY, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    color();
    glVertex2f(0.0f, 0.0f);
    int numSegments = 100;
    GLfloat angle;
    int i;
    for (i = 0; i <= numSegments; i++)
    {
        angle = i * 2.0f * PI / numSegments;
        glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    }
    glEnd();

    xSpeed += xAcceleration;
    ySpeed += yAcceleration;
    ballX += xSpeed;
    ballY += ySpeed;

    if (ballX > ballXMax)
    {
        xa = ballX;
        ballX = ballXMax;
        xSpeed = -xSpeed;

    }
    else if (ballX < ballXMin)
    {
        xa = ballX;
        ballX = ballXMin;
        xSpeed = -xSpeed;

    }
    if (ballY > ballYMax)
    {
        ya = ballY;
        ballY = ballYMax;
        ySpeed = -ySpeed;

    }
    else if (ballY < ballYMin)
    {
        ya = ballY;
        ballY = ballYMin;
        ySpeed = -ySpeed;

    }
    std::cout<< ballY << std::endl;

    if (ballY <= ballYMin)
    { 
        exit(0);
    }
}

void scoredisp()
{
    int z, j = 0, k = 0;
    z = score;
    glColor3f(1.0, 0.0, 0.0);
    glLoadIdentity();
    glRasterPos2f(-1, 1);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');

    while (z > 9)
    {
        k = z % 10;
        glRasterPos2f(-0.58, 1);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48 + k);
        z /= 10;
        glRasterPos2f(-0.62, 1);
    }
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 48 + z);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    balldisp();
    scoredisp();
    glFlush();
}

void onMotion(int x, int y) {
    if (arcball_on) {
        cur_mx = x;
        cur_my = y;
    }

}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height)
    {
        clipAreaXLeft = -1.0 * aspect;
        clipAreaXRight = 1.0 * aspect;
        clipAreaYBottom = -1.0;
        clipAreaYTop = 1.0;
    }
    else
    {
        clipAreaXLeft = -1.0;
        clipAreaXRight = 1.0;
        clipAreaYBottom = -1.0 / aspect;
        clipAreaYTop = 1.0 / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop + 0.10);
    ballXMin = clipAreaXLeft + ballRadius;
    ballXMax = clipAreaXRight - ballRadius;
    ballYMin = clipAreaYBottom + ballRadius;
    ballYMax = clipAreaYTop - ballRadius;
}

void Timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(refreshMills, Timer, 5);
}

void onMouse(int button, int state, int x, int y) /// I want help here to detect mouse over the ball
{
    cur_mx = x;
    cur_my = y;
    GLfloat X = (-((float)windowWidth / 2) + float(cur_mx)) / (float)windowWidth;
    GLfloat Y = (+((float)windowHeight / 2) - float(cur_my)) / (float)windowHeight;
    ballRadius = float(ballRadius);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        arcball_on = true;
        if ((X >= ballXMin && Y >= ballYMin) && (X >= ballXMin && Y <= ballYMax) &&
            (X <= ballXMax && Y >= ballYMin) && (X <= ballXMax && Y <= ballYMax))
        {
            xSpeed += 0.002;
            ySpeed += 0.02;
        }
    }


    else
    {
        arcball_on = false;
        if ((X >= ballXMin && Y >= ballYMin) && (X >= ballXMin && Y <= ballYMax) &&
            (X <= ballXMax && Y >= ballYMin) && (X <= ballXMax && Y <= ballYMax))
        {
            score += 1;
        }
    }  

}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bouncing Ball");
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPostRedisplay();
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();

}