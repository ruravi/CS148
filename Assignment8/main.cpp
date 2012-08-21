//
//  main.cpp
//  Assignment8
//
//  Created by Rukmani RaviSundaram on 11/30/11.
//  Copyright 2011 stanford. All rights reserved.
//

#include <iostream>
#include "st.h"
#include "stgl.h"
#include "stglut.h"
#include <stdlib.h>
#include "STImage.h"
#include "fstream.h"
#include "Scene.h"


#define WIN_WIDTH  512
#define WIN_HEIGHT 512

float glWindowSizeX;
float glWindowSizeY;

//Globals
std::string scenefile;


void display (void)
{
    /** Create Scene, This will parse the scenefile and start off the rendering process
     */
    
    printf("Display function \n");
    Scene myScene = Scene(scenefile);
    float width = myScene.imgWidth;
    float height = myScene.imgHeight;
    
    glWindowSizeX = width;
    glWindowSizeY = height;
    
    gluOrtho2D(0., glWindowSizeX, 0., glWindowSizeY);
    glViewport(0., 0., glWindowSizeX, glWindowSizeY);
    glutReshapeWindow(glWindowSizeX, glWindowSizeY);
    
    for (float i = 0; i < width; i++) {
        for (float j = 0; j < height; j++) {
            myScene.RenderScene(i, j);
        }
    }
    /* Perform Reflection now after all pixels havebeen rendered */
    
    myScene.DrawScene();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glWindowSizeX = w;
    glWindowSizeY = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glutPostRedisplay();
}


static void usage( void ) {
    printf("Usage: \n");
    printf("Assignment8 Filename \n");
    exit(-1);
}

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // quit
        case 'Q':
        case 'q':
            exit(0);
            break;
    }
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("CS148 Rukmani RaviSundaram Assignment 8");
    
    if (argc < 2) {
        usage();
    }
    
    scenefile = std::string(argv[1]);
    
    glWindowSizeX = WIN_WIDTH;
    glWindowSizeY = WIN_HEIGHT;
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;

}

