#include <iostream>
#include <windows.h>
#include<conio.h> //klavye buffer tutmasý ve iþlemesi için getch.
#include<dos.h> //delay sleep vs için
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define MINX 2
#define MINY 2
#define MAXX 30
#define MAXY 22
using namespace std;
bool gameover;
int ch = 32;
const int mapWidth = 30;
const int mapHeight = 20;
int level=1;
int totalWin=0;
bool startGame=false;
int BarSlider[2] = {21,11};
int Ball[2] = {20,15};
int bricks[15][2] = {
						{2,1},{2,7},{2,13},{2,19},{2,25},
					  	{4,1},{4,7},{4,13},{4,19},{4,25},
					  	{6,1},{6,7},{6,13},{6,19},{6,25}
					};
int totalBricks;
int visibleBricks[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int score;
int dir = 1;
int lose = 0;
int win = 0;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void Setup()
{
    gameover=false;
    score = 0;

}
void level1(){
    totalBricks=10;
    Ball[0] = 22;
    Ball[1] = 12;
    BarSlider[0] = 21;
    BarSlider[1] = 11;
    for( int i=0; i<10; i++){
		 visibleBricks[i] = 1;
}
}
void level2(){
    totalBricks=15;
     Ball[0] = 22;
    Ball[1] = 12;
    BarSlider[0] = 21;
    BarSlider[1] = 11;
    for( int i=0; i<15; i++){
		 visibleBricks[i] = 1;
}
}
void level3(){
    totalBricks=10;
      Ball[0] = 22;
    Ball[1] = 12;
    BarSlider[0] = 21;
    BarSlider[1] = 11;
    for( int i=0; i<5; i++){
		 visibleBricks[i] = 1;
}
     for( int i=10; i<15; i++){
		 visibleBricks[i] = 1;
}
}
void level4(){
    totalBricks=15;
     Ball[0] = 20;
    Ball[1] = 12;
    BarSlider[0] = 21;
    BarSlider[1] = 11;
    for( int i=0; i<15; i++){
		 visibleBricks[i] = 1;
}
}
void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void drawFrameHorizontal(int width){
    for (int i=0;i<width+2;i++){
        cout << "_";
    }
    cout << endl;
}
void drawFrameVertical(int width,int height){
   for (int i=0;i<height;i++){

        for (int j=0;j<=width+2;j++){

            if(j==0 || j==width+1)
                cout<<"|";
            else
                cout<<" ";
    }
    cout << endl;
    }
}
void drawFrames(int width,int height){
    drawFrameHorizontal(width);
    drawFrameVertical(width,height);
    drawFrameHorizontal(width);
}
void Draw(int width,int height)
{
    system("cls");//system clear
    drawFrames(width,height);
}
void drawBricks(){

	for( int i=0; i<15; i++){
		if( visibleBricks[i] == 1 ){
			gotoxy(bricks[i][1], bricks[i][0]);
			cout<<"|####|";
		}
	}
}
void drawBall(){

    gotoxy(Ball[1], Ball[0]);
    cout<<"0";
    gotoxy(BarSlider[1],BarSlider[0]);
		cout<<"±±±±±±±±";
}

void ballHitSlider(){
	if( Ball[1]>=BarSlider[1] && Ball[1]<=BarSlider[1]+8){
		if( Ball[0] == BarSlider[0]-1 ){
			if( dir == 3 )
				dir = 2;
			else if( dir == 4 )
				dir = 1;
		}
	}
}
void ballHitBrick(){
	for( int i=0; i<15; i++){
		if(visibleBricks[i]==1){
			if( Ball[1]>=bricks[i][1] && Ball[1]<=bricks[i][1]+6){
				if( Ball[0] == bricks[i][0] ){
					visibleBricks[i] = 0;
					totalBricks--;
				}
			}
		}
	}
}

void RKT_slider(){

    gotoxy(BarSlider[1],BarSlider[0]);
		cout<<"±±±±±±±±";



		}

void play(){

	if(level==1)
        {level1();}
	else if(level==2)
        {level2();}
    else if(level==3)
        {level3();}
    else if(level==4)
        {level4();}

    Draw(mapWidth,mapHeight);



	while(1){
        system("cls");
        drawBall();
        drawBricks();
       char keybord;

        if(kbhit())
        {
            keybord = getch();
            switch(keybord)
            {
            case 'd':
            case 'D':
                if(BarSlider[1] > 2){
					BarSlider[1] = BarSlider[1]-2;
					}
                break;
            case 'a':
            case 'A':
                if(BarSlider[1] <= 22)
                    {
					BarSlider[1] = BarSlider[1]+2;
                    }
                break;
            }
        }

		if(startGame){

        {
            RKT_slider();
			if( dir == 1){
				Ball[0] = Ball[0] - 1;
				Ball[1] = Ball[1] + 2;
				if( Ball[1] > MAXX ){
					dir = 2;
				}
				else if( Ball[0] < MINY ){
					dir = 4;
				}
			}
			else if( dir == 2) {
				Ball[0] = Ball[0] - 1;
				Ball[1] = Ball[1] - 2;
				if( Ball[0] < MINY ){
					dir = 3;
				}
				else if( Ball[1] < MINX  ){
					dir = 1;
				}
			}
			else if( dir == 3) {
				Ball[0] = Ball[0] + 1;
				Ball[1] = Ball[1] - 2;

				if( Ball[0] > MAXY ){
					lose = 1;
					break;
				}
				else if( Ball[1] < MINX  ){
					dir = 4;
				}
			}
			else if( dir == 4) {
				Ball[0] = Ball[0] + 1;
				Ball[1] = Ball[1] + 2;
				if( Ball[1] > MAXX ){
					dir = 3;
				}
				else if( Ball[0] > MAXY ){
					lose = 1;
					break;
				}
			}
            ballHitSlider();
		}
            ballHitBrick();
            if( totalBricks == 0){
                if (level==4){

                    win=1;
                    level=1;
                    break;
                }
			else{
                level++;
                break;
			}
		}

		Sleep(30);
		}
        }
    if( lose == 1){
		system("cls");

		gotoxy(10,5); cout<<" --------------------- ";
		gotoxy(10,6); cout<<" |     YOU LOSE      | ";
		gotoxy(10,7); cout<<" --------------------- ";

		gotoxy(10,9); cout<<"Press any key to go back to Menu.";
		_getch();
		lose =0;
	}

	if( win == 1){
		system("cls");
		gotoxy(10,5); cout<<" --------------------- ";
		gotoxy(10,6); cout<<" |     YOU WIN       | ";
		gotoxy(10,7); cout<<" --------------------- ";

		gotoxy(10,9); cout<<"Press any key to go back to Menu.";
		_getch();
		totalWin++;
		win =0;
	}

        }

int main()
{
    do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- ";
		gotoxy(10,6); cout<<" |     BRICK BREAKER      | ";
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();

		if( op=='1') play();
		else if( op=='2') exit(0);

	}while(1);

    cout<<endl<<endl;
    return 0;
}


