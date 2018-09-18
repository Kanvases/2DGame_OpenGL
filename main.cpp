//
//  main.cpp
//  Mid_assignment
//
//  Created by 张帆 on 29/03/2018.
//  Copyright ? 2018 nil. All rights reserved.
//

#include <GL/GLUT.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#define N 10
using namespace std;
float theta = 0.0;

typedef struct Points{
    float x;
    float y;
    float size;
}Points;
typedef struct mapPoint{
    Points p[N*10];
    int length;
}mapPoint;

int randX(int m, int n);
mapPoint randomPoint();
void drawMap();
void ball();
void GetKeyBoard(GLint key,int x,int y);
void GameOver();

float ox = -100, oy = 0;
mapPoint mp = randomPoint();
int loadIndex = 0;
int gameState = 0; //0:playing 1:over
int gameRank = 1;
int living = 3;


int randX(int m, int n){
    return rand()%(n-m+1)+m;
}
mapPoint randomPoint(){
    mapPoint mp;
    mp.length = 0;
    srand((int)time(0));
    for(int i = 0; i<N*gameRank; i++){
        mp.p[i].x = randX(50*i,50*(i+1))+100;
        mp.p[i].y = rand()%480 - 240;
        mp.p[i].size = rand()%10+3;
        mp.length ++;
    }
    return mp;
}

void Init(){
    glClearColor(0.0f,0.0f,0.2f,0.0f);
    
}
void Reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(double)w/2, (double)w/2, -(double)h/2, (double)h/2, -500, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ball(){
    glBegin(GL_POLYGON);
    for(float i =0;i < 2*3.14; i+=0.2093){
        glColor3f(0.1*gameRank, 0.1*gameRank, 0.3*gameRank);
        glVertex2f(20*cos(i)+ox,20*sin(i)+oy);
    }
    glEnd();
    if(pow(ox - mp.p[loadIndex].x,2) + pow(oy - mp.p[loadIndex].y,2) < 400 ||
       pow(ox - mp.p[loadIndex-1].x,2) + pow(oy - mp.p[loadIndex-1].y,2) < 400||
       pow(ox - mp.p[loadIndex+1].x,2) + pow(oy - mp.p[loadIndex+1].y,2) < 400){
        if(gameState==0 && ox>50){
            gameState = 1;
        }
        
    }
}

void drawMap(){
    if (mp.p[loadIndex].x < ox){
        loadIndex ++;
    }
    for(int i = loadIndex-5<0?0:loadIndex-5; i< loadIndex+5;i++){
        glPointSize(mp.p[i].size+5);
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(mp.p[i].x,mp.p[i].y);
        glEnd();
        glBegin(GL_POLYGON);
        for(float j =0;j < 2*3.14; j+=0.5){
            glColor3f(1.0, 1.0, 1.0);
            glVertex2f(mp.p[i].size*cos(j)+mp.p[i].x,mp.p[i].size*sin(j)+mp.p[i].y);
        }
        glEnd();
    }
}

void GameOver(){
    glClearColor(0.0, 0.1, 0.2+0.2*abs(sin(theta)),0.0f);
    glLoadIdentity();
    ox = 0;
    oy = 0;
    loadIndex = 0;
    gameState = 0;
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    if(oy < -290){
        living --;
		cout << "碰到障碍物！ 生命值-1" << endl;
        if(living == 0){
            glutDestroyWindow(glutGetWindow());
            cout << "游戏结束" <<endl;
			system("pause");
            exit(0);
        }
        GameOver();
    }else{
        ball();
        drawMap();
        glFlush();
    }
    
}
void GetKeyBoard(GLint key,int x,int y){
    if(key == GLUT_KEY_UP){
        oy += 30+gameRank*0.3;
        glutPostRedisplay();
    }
}
void itFalling(int id){
    glClearColor(0.0, 0.1, 0.2+0.2*abs(sin(theta)),0.0f);
    theta += 0.03;
    if(gameState == 1){
        oy -= 20;
    }else{
        oy -= 5+0.1*gameRank;
        ox += 5+(0.3)*gameRank*gameRank;
        if(ox > N*50*gameRank){
            
            glLoadIdentity();
            ox = 0;
            oy = 0;
            loadIndex = 0;
            gameRank++;
            cout << "晋级！现在等级" << gameRank << endl;
            mp = randomPoint();
        }
        glTranslated(-5-(0.3)*gameRank*gameRank, 0, 0);
    }
    glutPostRedisplay();
    glutTimerFunc(100*(-0.1)*gameRank+100,itFalling,1);
}
int main(int argc, char * argv[]) {
	cout << "欢迎游玩～\n在游戏中请用【方向上键】控制小球飞起，并躲避星星。\n你有三条命。\n按回车开始。" << endl;
    living =3;
    cin.get();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("GAME");
    Init();
    glutSpecialFunc(GetKeyBoard);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(Reshape);
    glutTimerFunc(100*(-0.1)*gameRank+100,itFalling,1);
    glutMainLoop();
    return 0;
}
