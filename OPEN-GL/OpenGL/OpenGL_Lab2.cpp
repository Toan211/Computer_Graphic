#if 0

#include <Windows.h>
#include <iostream>

#include <stdio.h>
#include"include/GL/GL.H"
#include "include/GL/glut.h"
#include "include/GL/GLU.H"

void Init() //xoa man hinh
{
    glClearColor(1.0, 0.0, 0.0, 0.0);
    //xoa mau?
    //vi la double nen chay tu 0->1
    //so cuoi cung la do trong suot
}


void DrawCoodinate() //vẽ 2 hệ truc td (dg màu xanh vs đỏ) (nhìn cho dễ)
{
    glColor3f(1.0, 0.0, 0.0); //dg màu đỏ
    glBegin(GL_LINES);
    glVertex3f(100.0, 0.0, 0.0);
    glVertex3f(-100.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0); //dg màu xanh lá
    glBegin(GL_LINES);
    glVertex3f(0.0, 100.0, 0.0);
    glVertex3f(0.0, -100.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0); // dg màu xanh lục
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 100.0);
    glVertex3f(0.0, 0.0, -100.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
}

#if 0

void OnTimer(int Time)
{
    switch (Time)
    {
    case 0:
        break;
    case 1:
        {

            glRotatef(1, 0.0, 1.0, 0.0);
            break;
        }
        
        
    default:
        {}
    }
}

void Rotate()
{
    
    glRotatef(1, 0.0, 1.0, 0.0);
}

#endif

void RenderScene() //ve các dt 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //xóa mh
    glLoadIdentity(); //load hệ trc td gốc
    gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //thông số góc q sat
    

 //----------------------bd từ đây

    DrawCoodinate(); //vẽ hệ trục td
    glPushMatrix();     
    
    glTranslatef(0.25, 0.0, 0.0);     // Dời trục sang gốc mới để có hệ tọa độ mới
                                     // O doi qua 0.2 0 0 
                                     //ko hieu sao phai la so 0.2 thay vi 2

    //  tại sao trans thì nó quay luôn? nó có quay 1 chút
    // mh dời hệ trục td (mắt) chứ ko phải dời hình, nên hình quay 

    


    //trc khi quay, vòi ở đằng sau, tay cầm đằng trc
    glRotatef(90, 0.0, 1.0, 0.0);  //quay x: nó theo chiều... đỉnh đầu?
                                    //quay y: theo chiều ngang
                                    //quay z: chiều thẳng đứng 
    

    glColor3f(1.0, 0.0, 0.5);
    
    glutWireTeapot(0.1); //b kính 

    glPopMatrix();

 //----------------------kt ở đây
    

    DrawCoodinate(); 
    glPushMatrix();      

    glTranslatef(-0.25, 0.0, 0.0);     
    
    //trc khi quay, h nón có đỉnh hướng vào tầm nhìn
    glRotatef(90, 0.0, 0.0, 1.0);   //quay x: nó theo chiều dọc
                                    //quay y: theo chiều ngang
                                    //quay z: ??? ko quay?
    glColor3f(1.0, 0.5, 0.5);

    glutWireCone(0.05, 0.2, 40, 24); //c rộng đáy//c cao//số điểm (đỉnh)//mặt
    //h nón
    glPopMatrix();
    
//-------------------------kt lần 2

    glPushMatrix();

    glTranslatef(0.0, 0.0, 0.0);

    glRotatef(90, 0.0, 1.0, 0.0); //quay z ??? ko quay?
                                  //quay y nó hướng lên trời
                                  //quay x nó hướng ngang      

    glColor3f(1.0, 0.8, 0.3); 

    glutWireTorus(0.03, 0.07, 40, 60); //c rong b xe//bkinh?(tới giữa h tròn r phình to)//...
    //b xe
    glPopMatrix();

//--------------------------kt lần 3

    glutSwapBuffers();

    glFlush();



}

void ReShape(int width, int height) // tinh chỉnh lại mp tọa độ, chiếu,…
{
    if (height == 0)
    {
        height = 1;
    }

    float ratio = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, ratio, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


int main()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //ca single lan double deu xai dc
    glutInitWindowSize(1200, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL-Lab-02");

    glutReshapeFunc(ReShape);

    glutDisplayFunc(RenderScene);
    glutMainLoop();
   
    return 1;
}

#endif
