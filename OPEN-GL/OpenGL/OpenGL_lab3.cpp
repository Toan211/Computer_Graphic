#if 0

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

void Init()  //hàm chiếu sáng 
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat ambient[] = { 2.0, 2.0, 0.0, 1.0 }; // đỏ, xanh dương, xanh lục, Alpha
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    //Chiếu sáng toàn phần cho đối tượng của vật  // bóng //viền

    GLfloat diff_use[] = { 1.0, 0.5, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);
    //Tạo ánh sáng khuếch tán cho đối tượng // màu

    GLfloat specular[] = { 2.0, 1.0, 2.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    //Tạo ánh sáng phản xạ trong đối tượng. // chiếu sáng 

    GLfloat shininess = 50.0f;
    glMateriali(GL_FRONT, GL_SHININESS, shininess);
    //Điều chỉnh cường độ điểm chiếu sáng phản xạ.
}

void DrawCoordinate()
{
    glDisable(GL_LIGHTING); //add this thing

    glBegin(GL_LINES);
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

    glEnable(GL_LIGHTING);  //add this thing
}

void RendenScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5.0, 5.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //gluLookat(eye_x, eye_y, eye_z, model_x, model_y, model_z, up_x, up_y, up_z);
        //Cameral sẽ đặt tại vị trí (5, 5, 15),
        //nhìn thẳng vào điểm có tọa độ O(0, 0, 0) 
        //hướng up cameral là hướng y.

    //ấm trà
    glPushMatrix(); //Cất hệ tọa độ hiện tại vào stack //store present coordinate in stack
    
    DrawCoordinate();
    glTranslatef(-7.0, 0.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);

    SetMaterialColor(K_MAT_PINK);

    glutSolidTeapot(3.0);

    glPopMatrix();// Lấy lại hệ tọa độ cũ // restore original coordinate

    //h nón
    glPushMatrix(); //Cất hệ tọa độ hiện tại vào stack //store present coordinate in stack

    DrawCoordinate();
    // Init(); //add color //this is why we need class 
    // glColor3f(1.0, 0.5, 0.5); //no need this
    glRotatef(45, -1.0, 0.0, 0.0);
    glTranslatef(7.0, 0.0, 0.0);

    SetMaterialColor(K_MAT_RED);

    glutSolidCone(3.0, 6.0, 40, 24); //c rộng đáy//c cao//số điểm (đỉnh)//mặt
    
    glPopMatrix(); 


    glPushMatrix(); //Cất hệ tọa độ hiện tại vào stack //store present coordinate in stack
    
    DrawCoordinate();
    glRotatef(45, 0.0, 1.0, 0.0);
    
    SetMaterialColor(K_MAT_PINK);
    
    glutWireTorus(1.0, 3.0, 30, 30);
    glPopMatrix();// Lấy lại hệ tọa độ cũ // restore original coordinate

    glPushMatrix(); //Cất hệ tọa độ hiện tại vào stack //store present coordinate in stack

    DrawCoordinate();
    glRotatef(-45, 0.0, 1.0, 0.0);
    glutWireTorus(1.0, 3.0, 30, 30);

    glPopMatrix();// Lấy lại hệ tọa độ cũ // restore original coordinate

    glPushMatrix(); //Cất hệ tọa độ hiện tại vào stack //store present coordinate in stack

    DrawCoordinate();
    glRotatef(-90, 0.0, 1.0, 0.0);
    glutSolidTorus(1.0, 5.0, 30, 30);

    glPopMatrix();// Lấy lại hệ tọa độ cũ // restore original coordinate

    glPushMatrix(); //Cất hệ tọa độ hiện tại vào stack //store present coordinate in stack

    DrawCoordinate();
    glRotatef(0, 0.0, 1.0, 0.0);
    glutSolidTorus(1.0, 5.0, 30, 30);

    glPopMatrix();// Lấy lại hệ tọa độ cũ // restore original coordinate

    glPushMatrix(); //Cất hệ tọa độ hiện tại vào stack //store present coordinate in stack

    DrawCoordinate();
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(1.0, 5.0, 30, 30);
    
    SetMaterialColor(K_MAT_BLUE);

    glPopMatrix();// Lấy lại hệ tọa độ cũ // restore original coordinate
    
    glFlush();
}

void ReShape(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio = (float)width / (float)height;
    gluPerspective(45.0, ratio, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //double ko xai dc
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Opengl Lab_3");

    Init();  // hàm chiếu sáng
    glutReshapeFunc(ReShape);
    glutDisplayFunc(RendenScene);

    glutMainLoop();
    
    return 1;
}


#endif