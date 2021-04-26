#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>



GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0, Calpha= 360.0, C_hr_alpha=360.0;
GLboolean bRotate = false, fRotate= true, cRotate= true, xz_rotate=false,l_on=true;
const int width = 1000;
const int height = 1000;
GLboolean amb=true, spec=true, dif=true;


bool l_on1 = false;
bool l_on2 = false;
bool l_on3 = false;



double spt_cutoff=40;


GLfloat eyeX = 5;
GLfloat eyeY = 15;
GLfloat eyeZ = -30;

GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;

static GLfloat v_Cube[8][3] =
{
    {0.0, 0.0, 0.0},
    {2.0, 0.0, 0.0},
    {0.0, 2.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 2.0, 0.0},
    {0.0, 2.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 2.0, 2.0}
};


static GLubyte quadIndices[6][4] =
{
    {1, 4, 7, 6},
    {7, 4, 2, 5},
    {3, 5, 2, 0},
    {3, 6, 7, 5},
    {0, 2, 4, 1},
    {1, 6, 3, 0}
};



static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void cube(GLfloat colr1, GLfloat colr2, GLfloat colr3)
{



    GLfloat cube_no[] = {0, 0, 0, 1.0};
    GLfloat cube_amb[] = {colr1*0.3,colr2*0.3,colr3*0.3,1};
    GLfloat cube_dif[] = {colr1,colr2,colr3,1};
    GLfloat cube_spec[] = {1,1,1,1};
    GLfloat cube_sh[] = {10};


    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, cube_sh);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_Cube[quadIndices[i][0]][0], v_Cube[quadIndices[i][0]][1], v_Cube[quadIndices[i][0]][2],
                    v_Cube[quadIndices[i][1]][0], v_Cube[quadIndices[i][1]][1], v_Cube[quadIndices[i][1]][2],
                    v_Cube[quadIndices[i][2]][0], v_Cube[quadIndices[i][2]][1], v_Cube[quadIndices[i][2]][2]);
        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_Cube[quadIndices[i][j]][0]);
        }

    }
    glEnd();


}
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, width / ar);

}

void flooor()
{

    glPushMatrix();

    glScalef(50,1,50);
    glTranslatef(-1,-1,-1);
    cube(0.663, 0.663, 0.663);
    glPopMatrix();


}
void table()
{

    GLfloat table_width =5;
    GLfloat table_height = 3, table_length = 1;

    GLfloat leg_width=0.6, leg_height= 0.8, leg_length=8;

    glPushMatrix();
    glScalef(table_width,table_length, table_height); //base
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((table_width-leg_width)/2+2.2,(table_length-leg_length)/2-5,(table_height-leg_length)/2+0.5); //leg1
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((table_width-leg_width)/2-6.5,(table_length-leg_length)/2-5,(table_height-leg_length)/2+0.5); //leg2
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((table_width-leg_width)/2-6.5,(table_length-leg_length)/2-5,(table_height-leg_length)/2+4.5); //leg3
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((table_width-leg_width)/2+2.1,(table_length-leg_length)/2-5,(table_height-leg_length)/2+4.5); //leg3
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();




}

void chair()
{

    glPushMatrix();

    GLfloat chair_width =3;
    GLfloat chair_height = 3, chair_length = 1;

    GLfloat leg_width=0.6, leg_height= 0.8, leg_length=4;


    glPushMatrix();  //upper_base

    glTranslatef((chair_width-leg_width)/2-1.1,(chair_length-leg_length)/2+7,(chair_height-leg_length)/2-2);
    glScalef(chair_width,chair_length*4.5, chair_height/6);
    glTranslatef(-1,-1,-1);
    cube(0.627, 0.322, 0.176);
    glPopMatrix();



    glPushMatrix();
    glScalef(chair_width,chair_length, chair_height); //base
    glTranslatef(-1,-1,-1);
    cube(0.722, 0.525, 0.043);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((chair_width-leg_width)/2+1.125,(chair_length-leg_length)/2-3,(chair_height-leg_length)/2-1.6); //leg1
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((chair_width-leg_width)/2-3.5,(chair_length-leg_length)/2-3,(chair_height-leg_length)/2+2.6); //leg2
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();



    glPushMatrix();
    glTranslatef((chair_width-leg_width)/2+1.1,(chair_length-leg_length)/2-3,(chair_height-leg_length)/2+2.5); //leg3
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((chair_width-leg_width)/2-3.4,(chair_length-leg_length)/2-3,(chair_height-leg_length)/2-1.6); //leg4
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();

    glPopMatrix();



}

void full_set()
{
    glPushMatrix();
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,-3,-8);
    chair();
    glPopMatrix();

}

void nine_full_set_chair_table()
{
    glPushMatrix();

    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,0);
    full_set();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(0,0,20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-20);
    full_set();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-15,0,20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,-20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,20);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,-20);
    full_set();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-15,0,0);
    full_set();
    glPopMatrix();



}
void almari()
{
    glPushMatrix();

    GLfloat almari_height =15, almari_width= 8, almari_length= 5;


    glPushMatrix();  //main_box
    glScalef(almari_width,almari_height, almari_length);
    glTranslatef(-1,-1,-1);
    cube(0.294, 0.000, 0.510);
    glPopMatrix();

    glPushMatrix(); // almari_line
    glTranslatef(0.4,0,4.1);
    glScalef(almari_width/45,(almari_height-.5), almari_length/5.5);
    glTranslatef(-1,-1,-1);
    cube(1.000, 0.000, 1.000);
    glPopMatrix();

    glPushMatrix(); // almari_handel_right
    glTranslatef(1.5,5,4.5);
    glScalef(almari_width/25,almari_height/15, almari_length/5.5);
    glTranslatef(-1,-1,-1);
    cube(0.957, 0.643, 0.376);
    glPopMatrix();

    glPushMatrix(); // almari_handel_left
    glTranslatef(-0.6,5,4.5);
    glScalef(almari_width/25,almari_height/15, almari_length/5.5);
    glTranslatef(-1,-1,-1);
    cube(0.957, 0.643, 0.376);
    glPopMatrix();

    glPopMatrix();


}


void wall(GLfloat col1,GLfloat col2,GLfloat col3)
{
    glPushMatrix();
    glScalef(50,1,50);
    glTranslatef(-1,-1,-1);
    cube(col1, col2, col3);
    glPopMatrix();


}




void fan_leg()
{
    glPushMatrix();
    glScalef(5,0.01113,2);
    glTranslatef(-1,-1,-1);
    cube(0.392, 0.584, 0.929);
    glPopMatrix();
}

void fan_face()
{
    glPushMatrix();
    glScalef(1.5,0.2,1.5);
    glTranslatef(-1,-1,-1);
    cube(1.000, 1.000, 1.000);
    glPopMatrix();


}

void fan_stand()
{
    glPushMatrix();
    glTranslatef(0,3.5,0);
    glScalef(0.3,6,0.3);
    glTranslatef(-1,-1,-1);
    cube(0.627, 0.322, 0.176);
    glPopMatrix();
}
void fan_set()
{
    glPushMatrix();
    glPushMatrix();
    fan_face();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6,0,0); //leg1
    fan_leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6,0,0); //leg2
    fan_leg();
    glPopMatrix();




    glPushMatrix();

    glRotatef(90,0,1,0);
    glTranslatef(6,0,0); //leg3
    fan_leg();
    glPopMatrix();


    glPushMatrix();

    glRotatef(90,0,1,0);
    glTranslatef(-6,0,0); //leg4
    fan_leg();
    glPopMatrix();
}

void fan()
{


    glPushMatrix();
    glRotatef(alpha,0,1,0);
    fan_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.5,0);
    fan_stand();
    glPopMatrix();

}

void clock()
{
    glPushMatrix();

    glPushMatrix(); //clk_leg1

    glScalef(1.5,1,1);
    glTranslatef(-.5,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix(); //clk_leg2
    glRotatef( C_hr_alpha,0, 1, 0.0 );
    glScalef(1.5,1,1);
    glTranslatef(0.8,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix(); //clk_leg3
    glRotatef( Calpha,0, 1, 0.0 );
    glRotatef(90,0,1,0);
    glScalef(1.5,1,1);
    glTranslatef(0.8,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();



    glScalef(4,0.2,3.5);
    glTranslatef(-1,-1,-1);
    cube(0.000, 0.000, 0.804);

    glPopMatrix();

}
void door()
{

    glPushMatrix(); // door_lock

    glTranslatef(44,2,13);
    glRotatef(90,0,1,0);
    glTranslatef(-0.6,5,4.5);
    glScalef(0.40,1.5, 0.5/5.5);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();  //door
    glTranslatef(49,6,20);
    glRotatef(90,0,1,0);
    glScalef(8,15,.5);
    glTranslatef(-1,-1,-1);
    cube(0.647, 0.165, 0.165);
    glPopMatrix();

}
void room()
{
    glPushMatrix();//front wall
    glTranslatef(0,0,45);
    glRotatef(270,1,0,0);

    glPushMatrix();//light front side
    glTranslatef(3,2,36);
    glRotatef(90,1,0,0);
    glScalef(12,.8,0.8);
    glTranslatef(-1,-1,-1);
    cube(1.000, 0.843, 0.000); //light
    glPopMatrix();

    glPushMatrix();  //blackboard
    glTranslatef(0,1,18);
    glScalef(30,0.5,8);
    glTranslatef(-1,-1,-1);
    cube(0.000, 0.000, 0.000);
    glPopMatrix();

    glPushMatrix();//clock
    glPushMatrix();
    glTranslatef(3,1,31);
    clock();
    glPopMatrix();
    glPopMatrix();
    wall(1.000, 1.000, 0.878);
    glPopMatrix();   // front wall end




    glPushMatrix();
    glTranslatef(0.0,0,-50);
    glRotatef(90,1,0,0);
    wall(0.863, 0.863, 0.8630); //back  wall
    glPopMatrix();

    glPushMatrix();//left side  wall start

    glPushMatrix();//light right side
    glTranslatef(42,30,-5);
    glRotatef(90,0,1,0);
    glScalef(12,1,0.8);
    glTranslatef(-1,-1,-1);
    cube(1.000, 0.843, 0.000); //light
    glPopMatrix();

    glPushMatrix();
    door();
    glPopMatrix();

    glTranslatef(50.0,0,-1);
    glRotatef(90,0,0,1);
    wall(1.000, 0.894, 0.882);
    glPopMatrix();//left side  wall


    glPushMatrix(); //right side wall start

    glPushMatrix();//light right side

    glTranslatef(-42,30,-5);
    glRotatef(90,0,1,0);
    glScalef(12,1,0.8);
    glTranslatef(-1,-1,-1);
    cube(1.000, 0.843, 0.000); //light
    glPopMatrix();

    glTranslatef(-50.0,0,-1);
    glRotatef(90,0,0,1);
    wall(1.000, 0.894, 0.882);
    glPopMatrix();//right side  wall


    glPushMatrix();

    glPushMatrix(); //top wall fan
    glScalef(0.8,1,1);
    glTranslatef(-5,30,0);
    fan();
    glPopMatrix();


    glTranslatef(0,40,-5);
    glRotatef(90,0,1,0);
    wall(0.663, 0.663, 0.663); //top  wall
    glPopMatrix();

    glPushMatrix();//floor
    glTranslatef(0,-10,0);
    glPushMatrix();// teacher floor
    glTranslatef(-40,2,25);
    glScaled(40,1,10);
    cube(0.647, 0.165, 0.165);
    glPopMatrix();
    flooor();
    glPopMatrix();

}


void classRoom()
{
    glPushMatrix();
    room();
    glPopMatrix();

    glPushMatrix();   //teachers desk
    glScalef(1.5,1,1);
    glRotatef(180,0,1,0);
    glTranslatef(15,4,-30);
    full_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,-5);
    glScalef(1.2,1,1.2);
    nine_full_set_chair_table();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.2,1.4,1);
    glTranslatef(-35,0,10);
    glRotatef(90,0,1,0);
    almari();
    glPopMatrix();

}


/*

 glPushMatrix();
    glPopMatrix();

*/

void light()
{

    //light

    GLfloat l_amb[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat l_dif[] = {0.961, 0.871, 0.702};
    GLfloat l_spec[] = {0.2,0.2,0.2,1};
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_pos1[] = {20,20,20,1.0}; //front side light
    GLfloat l_pos2[] = {44,30,-5,1.0}; //right side
    GLfloat l_pos3[] = {10,60,-30,1.0}; //left side



    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    if(l_on1)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT0,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos1);



    // glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spt_cut);



    if(l_on2)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT1,GL_SPECULAR,l_no);

    }
    glLightfv(GL_LIGHT1,GL_POSITION,l_pos2);



    if(l_on3)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_spec);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
        }

    }
    else
    {
        glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        glLightfv(GL_LIGHT2,GL_SPECULAR,l_no);
    }

    glLightfv(GL_LIGHT2,GL_POSITION,l_pos3);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    GLfloat spt_ct[] = {spt_cutoff};
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0); //eyeX,eyeY,eyeZ //5,10,-20
    //glViewport(0, 0, width, height);




    /*

    */
    glRotatef(theta, axis_x,axis_y,0);

    light();
    classRoom();

    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'R':
    case 'r':
        bRotate = !bRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case 'f':   //fan
    case 'F':
        fRotate = !fRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case '+': //zoom in
        eyeZ++;
        lookZ++;
        break;
    case '-': //zoom out
        eyeZ--;
        lookZ--;
        break;
    case '*': //zoom up
        eyeY++;
        lookY++;
        break;
    case '/': //zoom down
        eyeY--;
        lookY--;
        break;

    case 'x':
        eyeX++;
        lookX++;
        break;
    case 'z':
        eyeX--;
        lookX--;
        break;



    case '1': //light
        l_on1=!l_on1;
        break;
    case '2':
        l_on2=!l_on2;
        break;
    case '3':
        l_on3=!l_on3;
        break;

    case 'a':  //poperties of light
        amb= !amb;
        break;
    case 's':
        spec =!spec;
        break;
    case 'd':
        dif=!dif;
        break;








    case 27:	// Escape key
        exit(1);

    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }


    if (fRotate == true)
    {
        alpha += 0.8;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if (cRotate == true)  //for clock
    {
        Calpha -= 0.075;
        C_hr_alpha -=0.009;
        if(Calpha < 1.0)
            Calpha = 360.0;
        if(C_hr_alpha < 1.0)
            C_hr_alpha = 360.0;
    }

    glutPostRedisplay();

}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(height, width);
    glutCreateWindow("ClassRoom");

    glutReshapeFunc(resize);

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    printf("Use '1' to on/off light  from the front side.\n");
    printf("Use '2' to on/off light  from the right side.\n");
    printf("Use '3' to on/off spot light from the left side.\n");

    printf("Use 'a' to on/off the light ambient property for all lights.\n");
    printf("Use 'd' to on/off the light diffuse property for all lights.\n");
    printf("Use 's' to on/off the light Specular property for all lights.\n");

    printf("Use 'r' to rotate the scene. \n");
    printf("Use 'f' to on/off the fan.\n");

    printf("Use '+' to zoom in and '-' to zoom out.\n");
    printf("Use '*' to look up, '/' to look down, 'z' to look right, and 'x' to look left.\n");



    glutMainLoop();



    return 0;
}
