
#if 0

// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>

#include"include/GL/GL.H"
#include "include/GL/glut.h"
#include "include/GL/GLU.H"
//lq toi opengl

void Init() //xoa man hinh
{
    glClearColor(1.0, 0.0, 0.0, 0.0);
    //xoa mau?
    //vi la double nen chay tu 0->1
    //so cuoi cung la do trong suot
}


void ReShape(int width, int height) //thiet lap che do view (che do ban dau?)
{
    glViewport(0, 0, width, height); //toa do x,y , c dai, rong cua so

    glMatrixMode(GL_PROJECTION); //ma tran chieu

    glLoadIdentity(); //ma tran don vi

    glOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, -10.0); //tim hieu sau

    glMatrixMode(GL_MODELVIEW); //vao view
}


void RenderScene() //VE  1 THU gi do (ve doi tuong)
{
    glutWireTeapot(4.0); // ve am tra

    //glutSolidTeapot(4.0) //ve mat am tra-->chua chieu sang nen ko thay mat
    //glutWireSphere(4.0, 200, 5); //dat radius, mat, stack??? //dang day, hinh cau
    //it mat qua se ko tron, it stack cung vay

    //hinh non: cone
    //hinh banh xe???: torus 
    //hinh cau: sphere
    //dang duong: wire
    //dang mat:solid
    //co ham ve duong thang, doan thang

    glutSwapBuffers();//day buffer tam len buffer chinh

    glFlush(); //xoa bo dem
}


int main()
{
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

//khoi tao che do hien thi single
    // displaymode… hien thi mau ve RGB
        //may se chay nhanh hon 
            //neu co card do hoa (neu xai glut_single)

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //single ko xai dc

    //su ly cham, dung double buffer-->ve tren buffer tam

    glutInitWindowSize(500, 500);
    //mo cua so ve 500px 500px

    glutInitWindowPosition(100, 100);
    // vi tri x:100 y:100

    glutCreateWindow("Opengl Testing");
    //ten cua so
    Init();
    //khoi tao.
    //xoa man hinh vs mau la mau do

    glutReshapeFunc(ReShape);
    //dc goi thong qua ham, thiet lap moi truong ve

    glutDisplayFunc(RenderScene);
    // goi ham render de ve doi tuong

    glutMainLoop();
    //lap ham main de ve

    return 1;
}

#endif