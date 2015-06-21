/*
 *  3D Objects
 *
 *  Demonstrates how to draw objects in 3D.
 *
 *  Key bindings:
 *  m/M        Cycle through different sets of objects
 *  a          Toggle axes
 *  arrows     Change view angle
 *  0          Reset view angle
 *  ESC        Exit
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

double dim=5.0;
double asp=1;
double fov=55;
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
double zh=0;      //  Rotation of teapot
int axes=0;       //  Display axes
int mode=0;//  What to display

//  Cosine and Sine in degrees
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
    char    buf[LEN];
    char*   ch=buf;
    va_list args;
    //  Turn the parameters into a character string
    va_start(args,format);
    vsnprintf(buf,LEN,format,args);
    va_end(args);
    //  Display the characters one at a time at the current raster position
    while (*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}


static void Project()
{
    //  Tell OpenGL we want to manipulate the projection matrix
    glMatrixMode(GL_PROJECTION);
    //  Undo previous transformations
    glLoadIdentity();
    //  Perspective transformation
    if (mode)
        gluPerspective(fov,asp,dim/4,4*dim);
    //  Orthogonal projection
    else
        glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
    //  Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
    //  Undo previous transformations
    glLoadIdentity();
}




static void Vertex(double th,double ph)
{
    glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
    glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}





static void sphere2(double x,double y,double z,double r)
{
    const int d=5;
    int th,ph;
    
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(x,y,z);
    glScaled(r,r,r);
    
    //  Latitude bands
    for (ph=-90;ph<90;ph+=d)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=d)
        {
            Vertex(th,ph);
            Vertex(th,ph+d);
        }
        glEnd();
    }
    
    //  Undo transformations
    glPopMatrix();
}








/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimentions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void house(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    glColor3f(0.556863,.137255,.137255);
    glVertex3f(-1,-1, 1);
    glVertex3f(+1,-1, 1);
    glVertex3f(+1,+1, 1);
    glVertex3f(-1,+1, 1);
    //  Back
    glColor3f(0.556863,.137255,.137255);
    glVertex3f(+1,-1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,+1,-1);
    glVertex3f(+1,+1,-1);
    //  Right
    glColor3f(0.556863,.137255,.137255);
    glVertex3f(+1,-1,+1);
    glVertex3f(+1,-1,-1);
    glVertex3f(+1,+1,-1);
    glVertex3f(+1,+1,+1);
    //  Left
    glColor3f(0.556863,.137255,.137255);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,+1);
    glVertex3f(-1,+1,+1);
    glVertex3f(-1,+1,-1);
    //  Top
   glColor3f(0.556863,.137255,.137255);
    glVertex3f(-1,+1,+1);
    glVertex3f(+1,+1,+1);
    glVertex3f(+1,+1,-1);
    glVertex3f(-1,+1,-1);
    //  Bottom
    glColor3f(0.556863,.137255,.137255);
    glVertex3f(-1,-1,-1);
    glVertex3f(+1,-1,-1);
    glVertex3f(+1,-1,+1);
    glVertex3f(-1,-1,+1);
    //  End
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glColor3f(0.65,0.5, 0.39);
    glVertex3f(+1, +1, -1);
    glVertex3f(-1, +1, -1);
    glVertex3f(0,3,0);
 
    glColor3f(0.65,0.5, 0.39);
    glVertex3f(+1, +1, +1);
    glVertex3f(-1, +1, +1);
    glVertex3f(0,3,0);
    
    glColor3f(0.65,0.5, 0.39);
    glVertex3f(+1, +1, -1);
    glVertex3f(+1, +1, +1);
    glVertex3f(0,3,0);
    
    glColor3f(0.65,0.5, 0.39);
    glVertex3f(-1, +1, -1);
    glVertex3f(-1, +1, +1);
    glVertex3f(0,3,0);
    
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(.75, .75, .75);
    glVertex3f(-3, -1, -1);
    glVertex3f(+3, -1, -1);
    glVertex3f(+3, -1, -2);
    glVertex3f(-3, -1, -2);
    
    
    glColor3f(.75, .75, .75);
    glVertex3f(-3, -1, +1);
    glVertex3f(+3, -1, +1);
    glVertex3f(+3, -1, +2);
    glVertex3f(-3, -1, +2);
    
    
    
    glColor3f(.13, .37, .31);
    glVertex3f(-1, -1, +1);
    glVertex3f(-1, -1, -1);
    glVertex3f(+3, -1, -1);
    glVertex3f(+3, -1, +1);
    
    
    glColor3f(.13, .37, .31);
    glVertex3f(+1, -1, +1);
    glVertex3f(+1, -1, -1);
    glVertex3f(-3, -1, -1);
    glVertex3f(-3, -1, +1);
    
    glEnd();
    
    
    
    //  Undo transformations
    glPopMatrix();
}

/*
 *  Draw vertex in polar coordinates
 */
/*
 *  Draw a sphere (version 1)
 *     at (x,y,z)
 *     radius (r)
 */
static void SolidPlane(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{
    // Dimensions used to size airplane
    const double wid=0.05;
    const double nose=+0.50;
    const double cone= 0.20;
    const double wing= 0.00;
    const double strk=-0.20;
    const double tail=-0.50;
    //  Unit vector in direction of flght
    double D0 = sqrt(dx*dx+dy*dy+dz*dz);
    double X0 = dx/D0;
    double Y0 = dy/D0;
    double Z0 = dz/D0;
    //  Unit vector in "up" direction
    double D1 = sqrt(ux*ux+uy*uy+uz*uz);
    double X1 = ux/D1;
    double Y1 = uy/D1;
    double Z1 = uz/D1;
    //  Cross product gives the third vector
    double X2 = Y0*Z1-Y1*Z0;
    double Y2 = Z0*X1-Z1*X0;
    double Z2 = X0*Y1-X1*Y0;
    //  Rotation matrix
    double mat[16];
    mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
    mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
    mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
    mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;
    
    //  Save current transforms
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x,y,z);
    glMultMatrixd(mat);
    //  Nose (4 sided)
    glColor3f(0,0,1);
    glBegin(GL_TRIANGLES);
    glVertex3d(nose, 0.0, 0.0);
    glVertex3d(cone, wid, wid);
    glVertex3d(cone,-wid, wid);
    
    glVertex3d(nose, 0.0, 0.0);
    glVertex3d(cone, wid,-wid);
    glVertex3d(cone,-wid,-wid);
    
    glVertex3d(nose, 0.0, 0.0);
    glVertex3d(cone, wid, wid);
    glVertex3d(cone, wid,-wid);
    
    glVertex3d(nose, 0.0, 0.0);
    glVertex3d(cone,-wid, wid);
    glVertex3d(cone,-wid,-wid);
    glEnd();
    //  Fuselage (square tube)
    glBegin(GL_QUADS);
    glVertex3d(cone, wid, wid);
    glVertex3d(cone,-wid, wid);
    glVertex3d(tail,-wid, wid);
    glVertex3d(tail, wid, wid);
    
    glVertex3d(cone, wid,-wid);
    glVertex3d(cone,-wid,-wid);
    glVertex3d(tail,-wid,-wid);
    glVertex3d(tail, wid,-wid);
    
    glVertex3d(cone, wid, wid);
    glVertex3d(cone, wid,-wid);
    glVertex3d(tail, wid,-wid);
    glVertex3d(tail, wid, wid);
    
    glVertex3d(cone,-wid, wid);
    glVertex3d(cone,-wid,-wid);
    glVertex3d(tail,-wid,-wid);
    glVertex3d(tail,-wid, wid);
    
    glVertex3d(tail,-wid, wid);
    glVertex3d(tail, wid, wid);
    glVertex3d(tail, wid,-wid);
    glVertex3d(tail,-wid,-wid);
    glEnd();
    //  Wings (plane triangles)
    glColor3f(1,1,0);
    glBegin(GL_TRIANGLES);
    glVertex3d(wing, 0.0, wid);
    glVertex3d(tail, 0.0, wid);
    glVertex3d(tail, 0.0, 0.5);
    
    glVertex3d(wing, 0.0,-wid);
    glVertex3d(tail, 0.0,-wid);
    glVertex3d(tail, 0.0,-0.5);
    glEnd();
    //  Vertical tail (plane triangle)
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex3d(strk, 0.0, 0.0);
    glVertex3d(tail, 0.3, 0.0);
    glVertex3d(tail, 0.0, 0.0);
    glEnd();
    //  Undo transformations
    glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{

    const double len=1.5;  //  Length of axes
    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);
    //  Undo previous transformations
    glLoadIdentity();
    //  Set view angle
    //  Decide what to draw
    if (mode)
    {
        double Ex = -2*dim*Sin(th)*Cos(ph);
        double Ey = +2*dim        *Sin(ph);
        double Ez = +2*dim*Cos(th)*Cos(ph);
        gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
        
    }
    
    
    else
    {
        glRotatef(ph,1,0,0);
        glRotatef(th,0,1,0);
    }
    
            
            
    SolidPlane( 0, 2, 0 , 1,0,0 , 0, 1,0);
    house(0,0,0 , 0.3,0.3,0.3, 0);
    house(1,0,0 , 0.3,0.3,0.3,  0);
    house(-1.7,.2,0 , 0.3,0.5,0.3,  0);
    sphere2(-3,0,0, .2);
    
    //  White
    glColor3f(1,1,1);
    //  Draw axes
    if (axes)
    {
        glBegin(GL_LINES);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(len,0.0,0.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(0.0,len,0.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(0.0,0.0,len);
        glEnd();
        //  Label axes
        glRasterPos3d(len,0.0,0.0);
        Print("X");
        glRasterPos3d(0.0,len,0.0);
        Print("Y");
        glRasterPos3d(0.0,0.0,len);
        Print("Z");
    }
    //  Five pixels from the lower left corner of the window
    glWindowPos2i(5,5);
    //  Print the text string
    Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");
    glFlush();
    //  Make the rendered scene visible
    glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
    //  Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
        th += 5;
    //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLUT_KEY_LEFT)
        th -= 5;
    //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP)
        ph += 5;
    //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)
        ph -= 5;
    
    else if (key==GLUT_KEY_PAGE_UP)
        dim +=0.1;
    
    else if (key==GLUT_KEY_PAGE_DOWN && dim>1)
        dim-=0.1;
        
    //  Keep angles to +/-360 degrees
    th %= 360;
    ph %= 360;
    //  Tell GLUT it is necessary to redisplay the scene
    
    Project();
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
    //  Exit on ESC
    if (ch == 27)
        exit(0);
    //  Reset view angle
    else if (ch == '0')
        th = ph = 0;
    //  Toggle axes
    else if (ch == 'a' || ch == 'A')
        axes = 1-axes;
    //  Switch display mode
    else if (ch == 'm'|| ch=='M')
        mode = 1-mode;
    else if (ch == '-' && ch>1)
        fov--;
    else if (ch=='+' && ch<179)
        fov++;
    Project();
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
    //  Ratio of the width to the height of the window
    asp = (height>0) ? (double)width/height : 1;
    //  Set the viewport to the entire window
    glViewport(0,0, width,height);
    //  Tell OpenGL we want to manipulate the projection matrix
    Project();
}

/*
 *  GLUT calls this toutine when there is nothing else to do
 */

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
    //  Initialize GLUT and process user parameters
    glutInit(&argc,argv);
    //  Request double buffered, true color window with Z buffering at 600x600
    glutInitWindowSize(600,600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    //  Create the window
    glutCreateWindow("Projections");
    //  Tell GLUT to call "idle" when there is nothing else to do
    //  Tell GLUT to call "display" when the scene should be drawn
    glutDisplayFunc(display);
    //  Tell GLUT to call "reshape" when the window is resized
    glutReshapeFunc(reshape);
    //  Tell GLUT to call "special" when an arrow key is pressed
    glutSpecialFunc(special);
    //  Tell GLUT to call "key" when a key is pressed
    glutKeyboardFunc(key);
    //  Pass control to GLUT so it can interact with the user
    glutMainLoop();
    return 0;
}

