#if 1

#include <Windows.h>
#include <iostream>

#include <stdio.h>
#include"include/GL/GL.H"
#include "include/GL/glut.h"
#include "include/GL/GLU.H"
   
#define K_MAT_RED 0
#define K_MAT_GREEN 1
#define K_MAT_BLUE 2
#define K_MAT_YELLOW 3
#define K_MAT_PINK 4

void SetMaterialColor(GLfloat ambient[4], GLfloat diff_use[4])
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

void SetMaterialColor(const int& type)
{
    GLfloat ambien[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diff_use[] = { 0.0, 0.0, 0.0, 1.0 };
    switch (type)
    {
    case K_MAT_RED:
    {
        ambien[0] = 1.0f;
        diff_use[0] = 1.0f;
    }
    break;
    case K_MAT_GREEN:
    {
        ambien[1] = 1.0f;
        diff_use[1] = 1.0f;
    }
    break;
    case K_MAT_BLUE:
    {
        ambien[2] = 1.0f;
        diff_use[2] = 1.0f;
    }
    break;
    case K_MAT_YELLOW:
    {
        ambien[0] = 1.0f;
        ambien[1] = 1.0f;
        diff_use[0] = 1.0f;
        diff_use[1] = 1.0f;
    }
    break;
    case K_MAT_PINK:
    {
        ambien[0] = 1.0f;
        ambien[2] = 1.0f;
        diff_use[0] = 1.0f;
        diff_use[1] = 1.0f;
    }
    break;
    default:
    {
        ambien[0] = 1.0f;
        ambien[1] = 1.0f;
        ambien[2] = 1.0f;
        diff_use[0] = 1.0f;
        diff_use[1] = 1.0f;
        diff_use[2] = 1.0f;
    }
    break;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambien);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
}

GLfloat g_box;

GLfloat g_sphere;

void DrawCoordinate() //vẽ trục tọa độ
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);  //vẽ trục tọa độ x, y z (3 line)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();

    glEnable(GL_LIGHTING); //chiếu sáng
}

GLuint MakeCube() //vẽ hình hộp
{
    GLuint boxDisplay;
    boxDisplay = glGenLists(1);  // Bắt đầ thực hiện Display List__Tạo list đánh theo số, mốc display
                                                         // số 1 ra mốc này, thực hiện để vẽ hlphuong nàysố 1 là vùng nhớ cho hlp? 
    glNewList(boxDisplay, GL_COMPILE);

    glBegin(GL_QUADS);    // Render Đối tượng trong vùng Display List
    // Front Face
    glNormal3f(0.0, 0.0, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Back Face
    glNormal3f(0.0, 0.0, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Top Face
    glNormal3f(0.0, 0.1, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Bottom Face
    glNormal3f(0.0, -1.0, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face
    glNormal3f(1.0, 0.0, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Left Face
    glNormal3f(-1.0, 0.0, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    glEndList();
    return boxDisplay;
}

GLuint MakeBox(const float length, const float width, const float height)
{
    GLuint dp_list;
    dp_list = glGenLists(1);
    glNewList(dp_list, GL_COMPILE);
    float x = length;
    float y = height;
    float z = width;

    //Back
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(x, 0, 0);
    glVertex3f(x, y, 0);
    glVertex3f(0, y, 0);
    glEnd();

    // left
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, z);
    glVertex3f(0, y, z);
    glVertex3f(0, y, 0);
    glEnd();

    //front
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, z);
    glVertex3f(0, y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, 0, z);
    glEnd();

    //// right
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(x, 0, z);
    glVertex3f(x, 0, 0);
    glVertex3f(x, y, 0);
    glVertex3f(x, y, z);
    glEnd();

    //Top
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, y, 0);
    glVertex3f(x, y, 0);
    glVertex3f(x, y, z);
    glVertex3f(0, y, z);

    //Bottom
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(x, 0, 0);
    glVertex3f(x, 0, z);
    glVertex3f(0, 0, z);

    glEnd();

    glEndList();

    return dp_list;
}


void RendenScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();  // 6:40 // đưa về hệ trục tọa độ ban đầu
                                 // khi dùng các phép biến đổi affine,( tịnh tiến, các phép biến đổi) thì thông thg có 2 cách:
  // 1.  Cộng thêm các giá trị y, z— 2.dời trục tọa độ lên theo phép tịnh tiến
  // 2. sau khi rời, vẽ dt, dtg sẽ nằm trên hệ trục tọa độ mới, muốn đẩy về gốc ban đầu loadIdentity

    gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //-------------------------------------------------

    glPushMatrix(); // trc khi thực hiện phép biến đổi affine, lưu hệ trục tọa độ ban đầu vào 1 stack (1 matrix)
    DrawCoordinate();

    SetMaterialColor(K_MAT_RED); // 18:50 //thay đổi màu sắc

    glCallList(g_box);  //gọi hàm g_box
    glPopMatrix(); //lấy ra lại hệ trục gốc

    //-----------------------------------------------------------------------

    glPushMatrix();
    glTranslatef(3.0, 0.0, 0.0);
    SetMaterialColor(K_MAT_YELLOW);
    glCallList(g_sphere);
    glPopMatrix();



    glFlush();
}

void ReShape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio = (float)width / (float)height;
    gluPerspective(45.0, ratio, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


void Init() //tạo ánh sáng
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING); // 9:10
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat ambient[] = { 1.0, 1.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

    GLfloat diff_use[] = { 0.5, 0.5, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    GLfloat shininess = 50.0f;
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

    g_box = MakeCube();  //gọi 5:00 //sau khi vẽ lấy trong displaylist ra
    g_sphere = MakeBox(1,2,3);
}

int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Opengl Study");

    Init(); //hàm chiếu sáng
    glutReshapeFunc(ReShape);
    glutDisplayFunc(RendenScene);

    glutMainLoop();

    return 1;
}



#endif