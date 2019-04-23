// C code to implement basic
// transformations in OPENGL
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include<string.h>



//#include<glut.h>

#include<iostream>//for strlen

#include<stdlib.h>

#include <stdio.h>



#include <math.h>

#include <string.h>



#define ESCAPE 27

int lane=0;

int pause=0;

int a[100];
GLdouble dist[100];

GLint window;

GLint window2;

GLint Xsize=1000;

GLint Ysize=800;

float i,theta;

GLint nml=0,day=1;



char name3[]="3D BALL GAME";



GLfloat xt=0.0,yt=0.0,zt=-1.2,xw=0.0;

GLfloat xs=1.0,ys=1.0,zs=1.0;

GLfloat xangle=15.0,yangle=-85.0,zangle=0.0,angle=0.0;



GLfloat r=0,g=0,b=1;

GLint light=1;

int count=1,flg=1;

int view=0;

int flag1=1,aflag=1;

int flag2=0,wheelflag=1;   //to switch fog effect

GLUquadricObj *t;



void mouse(int button, int state, int x, int y)
{
    
    
    if (pause==1 && button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        
        glClearColor(0.0 ,0.0 ,0.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glScissor(x,690-y,800,500);
        glEnable(GL_SCISSOR_TEST);
        glutPostRedisplay();
    }
    
    
}

static void SpecialKeyFunc( int Key, int x, int y );



GLvoid Transform(GLfloat Width, GLfloat Height)

{
    
    glViewport(0, 0, Width, Height);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    gluPerspective(45.0,Width/Height,0.1,100.0);
    
    glMatrixMode(GL_MODELVIEW);
    
}
GLvoid check(GLdouble xw)

{
    
    GLdouble m1=0;
    
    
    
    for(int i=1;i<100;i=i+3)
        
    {
        
        m1=dist[i]+xw-1.4;
        
        GLdouble x1=(lane-a[i])*(0.33);
        
        if(sqrt((m1*m1)+(x1*x1))<0.3)
            
        {
            
            
            
            flag1=0;
            pause=1;
            
        }
        
    }
    
    return;
    
}




GLvoid InitGL(GLfloat Width, GLfloat Height)

{
    
    
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glLineWidth(2.0);              /* Add line width,   ditto */
    
    Transform( Width, Height ); /* Perform the transformation */
    
    t=gluNewQuadric();
    
    gluQuadricDrawStyle(t, GLU_FILL);
    
    glEnable(GL_LIGHTING);
    
    glEnable(GL_LIGHT0);
    
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    
    GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    
    GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };
    
    
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);   //track lights
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);   // objects lights
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);    //objects lights
    
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    
    
}

void init()

{
    
    glClearColor(0,0,0,0);
    
    glPointSize(5.0);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    glOrtho(0.0,900.0,0.0,600.0,50.0,-50.0);
    
    if(pause==0)
        
        glutPostRedisplay();
    
}

void display_string(int x, int y, char *string, int font)

{
    
    int len,i;
    glDisable(GL_LIGHTING);
    
    glColor3f(1.0f,1.0f,1.0f);
    
    glRasterPos2f(x, y);
    
    len = (int) strlen(string);
    
    for (i = 0; i < len; i++) {
        
        if(font==1)
            
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
        
        if(font==2)
            
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
        
        if(font==3)
            
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
        
        if(font==4)
            
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
        
    }
    
    
    
}



void display1(void)

{
    glClearColor(0.8,0.33,0,1.0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    display_string(335,500,name3,1);
    
    display_string(390+10,470,"HELP",2);
    
    display_string(10,340,"KEYBOARD",2);
    
    display_string(10,310,"X-Y KEYS FOR ROTATION IN CORRESPONDING DIRECTION",3);
    
    display_string(10,280,"U TO MOVE CAMERA",3);
    
    display_string(10,250,"USE LEFT ARROW(<-) AND RIGHT ARROW(->) TO MOVE BALL",3);
    
    display_string(10,220,"ESCAPE TO EXIT",3);
    
    display_string(250,150,"PRESS SPACE BAR TO ENTER",2);
    
    display_string(10,450,"MOUSE",2);
    
    display_string(10,420,"PRESS RIGHT BUTTON FOR MENU",3);
    
    display_string(10,390,"PRESS LEFT BUTTON FOR CLIPPING WHILE PAUSED",3);
    
    glutPostRedisplay();
    
    glutSwapBuffers();
    
    
    
}



GLvoid DrawGLScene()

{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(view==0)
        
    {
        
        init();
        
        display1();
        
    }
    
    else
        
    {
        
        if(count==1)
            
            InitGL(Xsize,Ysize);
        
        if(aflag==1)/* Initialize our window. */
            
            glClearColor(1,1,1,1);
        
        else
            
            glClearColor(0.1,0.1,0.1,0);
        
        glPushMatrix();
        
        glLoadIdentity();
        
        glTranslatef(-1.0,0.0,-3.5);
        
        glRotatef(xangle,1.0,0.0,0.0);
        
        glRotatef(yangle,0.0,1.0,0.0);
        
        glRotatef(zangle,0.0,0.0,1.0);
        
        glTranslatef(xt,yt,zt);
        
        glScalef(xs,ys,zs);
        
        glEnable(GL_COLOR_MATERIAL);
        
        
        
        if(flag2==1)
            
        {
            
            GLfloat fogcolour[4]={1.0,1.0,1.0,1.0};
            
            
            
            glFogfv(GL_FOG_COLOR,fogcolour);
            
            glFogf(GL_FOG_DENSITY,0.1);
            
            glFogi(GL_FOG_MODE,GL_EXP);
            
            glFogf(GL_FOG_START,3.0);
            
            glFogf(GL_FOG_END,100.0);
            
            glHint(GL_FOG_HINT, GL_FASTEST);
            
            glEnable(GL_FOG);
            
        }
        
        if(flag2==0)
            
        {
            
            glDisable(GL_FOG);
            
        }
        
        glBegin(GL_QUADS);
        
        glPushMatrix();
        
        glTranslatef(xw,0,0);
        
        glColor3f(0.34,0.47,0.7);
        
        glVertex3f(-100,0.1,-100);
        
        glVertex3f(-100,0.1,-0.02);         //Side View
        
        glVertex3f(100,0.1,-0.02);
        
        glVertex3f(100,0.1,-100);
        
        
        glColor3f(2.55,2.55,2.55);
        
        glVertex3f(-100,0.1,-0.02);
        
        glVertex3f(-100,0.1,0.01);         //Track1
        
        glVertex3f(100,0.1,0.01);
        
        glVertex3f(100,0.1,-0.02);
        
        glColor3f(2.04,0.85,0);
        
        glVertex3f(-100,0.1,0.01);
        
        glVertex3f(-100,0.1,0.32);
        
        glVertex3f(100,0.1,0.32);
        
        glVertex3f(100,0.1,0.01);
        
        
        glColor3f(2.55,2.55,2.55);
        
        glVertex3f(-100,0.1,0.32);       //track2
        
        glVertex3f(-100,0.1,0.35);
        
        glVertex3f(100,0.1,0.35);
        
        glVertex3f(100,0.1,0.32);
        
        glColor3f(2.04,0.85,0);
        
        glVertex3f(-100,0.1,0.35);
        
        glVertex3f(-100,0.1,0.65);
        
        glVertex3f(100,0.1,0.65);
        
        glVertex3f(100,0.1,0.35);
        
        
        
        glColor3f(2.55,2.55,2.55);
        
        glVertex3f(-100,0.1,0.65);
        
        glVertex3f(-100,0.1,0.68);         //track3
        
        glVertex3f(100,0.1,0.68);
        
        glVertex3f(100,0.1,0.65);
        
        glColor3f(2.55,2.55,2.55);
        
        glVertex3f(-100,0.1,0.99);
        
        glVertex3f(-100,0.1,1.02);
        
        glVertex3f(100,0.1,1.02);
        
        glVertex3f(100,0.1,0.99);
        
        glColor3f(2.04,0.85,0);
        
        glVertex3f(-100,0.1,0.68);
        
        glVertex3f(-100,0.1,0.99);
        
        glVertex3f(100,0.1,0.99);
        
        glVertex3f(100,0.1,0.68);
        
        
        
        glColor3f(0.34,0.47,0.7);
        
        glVertex3f(-100,0.1,1.02);
        
        glVertex3f(-100,0.1,100);         //Side View2
        
        glVertex3f(100,0.1,100);
        
        glVertex3f(100,0.1,1.02);
        
        glPopMatrix();
        
        glEnd();
        
        
        
        if(wheelflag)
            
        {
            
            glPushMatrix();
            
            glTranslatef(xw,0,0);
            
            if(xw>70)
                
            {
                
                xw=1;
                
            }
            
            
            
            glColor3f(0.52,0.50,0.51);
            
            for(int j=1;j<100;j=j+3)
                
            {
                
                int k1=a[j];
                
                glTranslatef((-1)*j, 0.25, 0.2);
                
                glTranslatef(0, 0, k1*0.33);
                
                gluSphere(t,0.15,50,50);
                
                glTranslatef(0, 0, (-1)*k1*0.33);
                
                glTranslatef(j, -0.25, -0.2);
                
            }
            
            check(xw);
            
            
            
          glPopMatrix();
            
        }
        
        //
        
        
        
        //************IGNITION SYSTEM
        
        glPushMatrix();
        
        glColor3f(0.20,0.53,0.47);
        
        glTranslatef(1.4,0.25,0.2);
        
        glTranslatef(0, 0, lane*0.33);
        
        gluSphere(t,0.15,50,50);
        
        glTranslatef(0, 0, (-1)*lane*0.33);
        
        glPopMatrix();
        
        
        
        glPopMatrix();
        
        glEnable(GL_DEPTH_TEST);
        
        //automatic increment
        
        if(wheelflag && pause==0)
            
        {
            
            angle+=5;
            
            xw+=0.05;
            
            
            
            glutPostRedisplay();
            
        }
        
        if(pause==0)
            
            glutPostRedisplay();
        
        glutSwapBuffers();
        
    }
    
}



void NormalKey(GLubyte key, GLint x, GLint y)

{
    
    switch ( key )    {
            
        case ESCAPE : printf("escape pressed. exit.\n");
            
            glutDestroyWindow(window);
            
            exit(0);
            
            break;
            
            
            
        case ' ':view=1;
            
            DrawGLScene();
            
            break;
            
            
            
        case 'y':
            if(pause==1)
                xangle = xangle<30? xangle+5.0: xangle;
            
            glutPostRedisplay();
            
            break;
            
            
            
        case 'Y':
            if(pause==1)
                xangle = xangle>5? xangle-5.0: xangle;
            
            glutPostRedisplay();
            
            break;
            
            
            
        case 'x':
            
            if(pause==1)
                
                yangle = yangle<-70? yangle+5.0: yangle;
            
            glutPostRedisplay();
            
            break;
            
            
            
        case 'X':
            
            if(pause==1)
                
                yangle = yangle>-100? yangle-5.0: yangle;
            
            
            
            glutPostRedisplay();
            
            break;
            
            
        case 'u':                          /* Move up */
            if(pause==1)
                yt = yt<0.6? yt+0.2: yt;
            
            glutPostRedisplay();
            
            break;
            
            
            
        case 'U':
            if(pause==1)/* Move down */
                yt = yt>-0.8? yt-0.2: yt;
            
            glutPostRedisplay();
            
            break;
            
            
            
        case 'P':
            
            flag1=0;
            
            pause=1;
            
            if(pause==1)
                
                glutPostRedisplay();
            
            break;
            
        case 'R':
            
            flag1=1;
            
            wheelflag=1;
            
            pause=0;
            
            glutPostRedisplay();
            
            break;
            
            
            
            
            
        default:
            
            break;
            
    }
    
    
    
}



static void SpecialKeyFunc( int Key, int x, int y )

{
    
    switch ( Key ) {
            
        case GLUT_KEY_UP:
            
            if(!wheelflag)
                
                xt += 0.2;
            
            if(wheelflag)
                
            {
                
                angle+=5;
                
                xw+=0.2;
                
            }
            
            if(pause==0)
                
                glutPostRedisplay();
            
            break;
            
            
            
        case GLUT_KEY_LEFT:
            
            
            
            if(wheelflag)
                
            {
                
                if(lane<2)
                    
                    lane=lane+1;
                
            }
            
            if(pause==0)
                
                glutPostRedisplay();
            
            break;
            
        case GLUT_KEY_RIGHT:
            
            
            
            if(wheelflag)
                
            {
                
                if(lane>0)
                    
                    lane=lane-1;
                
            }
            
            if(pause==0)
                
                glutPostRedisplay();
            
            break;
            
        default:
            
            
            
            
            
            ;
            
    }
    
}



void myMenu(int id)

{
    
    if(id==12)
        
    {
        
        aflag=1;
        
        day=1;
        
        glClearColor(1,1,1,1);
        
        glDisable(GL_FOG);
        
        glutPostRedisplay();
        
    }
    
    if(id==19)
        
    { flag1=0;
        
        //    wheelflag=1;
        
        pause=1;
        
        if(pause==0)
            
            glutPostRedisplay();
        
    }
    
    if(id==20)
        
    { flag1=1;
        
        wheelflag=1;
        
        pause=0;
        
        glDisable(GL_SCISSOR_TEST);
        glutPostRedisplay();
        
        
        if(pause==0)
            
            glutPostRedisplay();
        
    }
    
    if(id==13)
        
    {
        
        aflag=0;
        
        
        flag2=2;
        
        
        GLfloat fogcolour[4]={0,0,0,0.2};
        
        
        
        glFogfv(GL_FOG_COLOR,fogcolour);
        
        glFogf(GL_FOG_DENSITY,0.04);
        
        glFogi(GL_FOG_MODE,GL_EXP);
        
        glHint(GL_FOG_HINT, GL_FASTEST);
        
        glEnable(GL_FOG);
        
        glutPostRedisplay();
        
    }
    
    
    if(id==14)
    {
        view=0;
        xw=0;
        pause=0;
        for(int i=0;i<100;i++)
        {
            a[i]=rand()%3;
        }
        
        for(int i=0;i<30;i++)
        {
            a[69+i]=a[i];
        }
        glDisable(GL_SCISSOR_TEST);
        
        glutPostRedisplay();
    }
    
    
}




int main(int argc, char **argv)

{
    glutInit(&argc, argv);
    //INITIALIZE THE LOCATIONS WHERE THE BALLS WHICH ARE COMMING ARE TO BE PLACED
    for(int i=0;i<100;i++)
    {
        
        a[i]=rand()%3;
    
    }
    for(int i=0;i<100;i++)
    {  dist[i]=(-1)*i;
        
        }
    
    for(int i=0;i<30;i++)
    {
         a[69+i]=a[i];
        
    }
    
   
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH);
    
    glutInitWindowSize(1000,800);
    
    glutInitWindowPosition(50,50);
    
    glutCreateWindow("3D BALL GAME");
    
    glutDisplayFunc(DrawGLScene);
    
    glutKeyboardFunc(NormalKey);
    
    glutSpecialFunc( SpecialKeyFunc );
    
    InitGL(Xsize,Ysize);
    
    glutCreateMenu(myMenu);
    
    glutAddMenuEntry("PAUSE", 19);
    
    glutAddMenuEntry("RESUME", 20);
    
    glutAddMenuEntry("daymode",12);
    
    glutAddMenuEntry("Night mode",13);
    
    glutAddMenuEntry("Restart",14);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMouseFunc(mouse);
    
    
    glutMainLoop();
    
    return 1;
    
}
