/*

	TIC TAC TOE PROGRAM IN WINBGIM GRAPHICS
	BY KADUM KOMUT
	
	Flow of the program
	1.Getting the player name input
	2.Setting up the graphic window in the TicTacToe Constructor
	3.Run the start function - The intro of the game
	4.Run the draw function - the draw function sets up the drawBackground,drawBoard and drawTextBoard
	5.Loop through the draw function with while loop
	6.Check for each mouse click for win.
	7.If it satisfies the checkWin() logic, go to end() function else invoke the draw function and end the program.
	8.End() exits from the program.

*/

#include<graphics.h>
#include<windows.h>
#include<iostream>
#include<string.h>
//main board in which the operations and win logic will be performed
int board[9] = {0,0,0,0,0,0,0,0,0};
//player turns
int playerTurn=1;
//for mouse click
//allowing mouse to click on possible boxes but not all
int hitBoard[9] = {0,1,2,3,4,5,6,7,8};
//coordinates of the boxes starting from the first box till end
int left[9] =   {240,400,560,240,400,560,240,400,560};
int top[9]  =   {140,140,140,300,300,300,460,460,460};
int right[9] =  {340,500,660,340,500,660,340,500,660};
int bottom[9] = {240,240,240,400,400,400,560,560,560};
//getting both the player details
class player
{
	public:
		char firstPlayer[20],secondPlayer[20];
		player()
		{
			std::cout<<"Enter The first player name\n";
			std::cin>>firstPlayer;
			std::cout<<"\nEnter the Second player name\n";
			std::cin>>secondPlayer;
		}
};
//tic tac toe class
class TicTacToe
{
	private:
		//width and height of the screen
		DWORD width,height;
	public:
		TicTacToe()
		{
			width=GetSystemMetrics(SM_CXSCREEN);
	        height=GetSystemMetrics(SM_CYSCREEN);
	        initwindow(width,height,"Number Puzzle Program");
		}
		void start();
		void draw(player);
		void drawBackground();
		void drawBoard();
		void drawTextBoard();
		int checkWin(int);
		int mouseHitBox(int,int,int,int,int,int,int);
		void end(int,player);
		void gameDraw();
};
//if there is a draw
void TicTacToe::gameDraw()
{
	cleardevice();
	drawBackground();
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
	outtextxy((width/2)-540,height/2,"GAME WAS DRAW - Press Enter to exit the game");
	getch();
	exit(0);
}
//drawing the background
void TicTacToe::drawBackground()
{
	setcolor(BLUE);
    setfillstyle(SOLID_FILL,GREEN);
    rectangle(0,0,width,height);
    floodfill(2,2,GREEN);
}
//drawing the rectangle boxes
void TicTacToe::drawBoard()
{
  for(int i=0;i<9;i++)
  {
     setcolor(WHITE);
     rectangle(left[i],top[i],right[i],bottom[i]);
  }
}
//setting up the text in the board simultaneously as the board
void TicTacToe::drawTextBoard()
{
   char a[10];
   settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
   for(int i=0;i<9;i++)
   {
   	 char ch;
	 if(board[i]==0)
	  continue;
	 if(board[i]==1)
	   ch='x';
	 else if(board[i]==2)
	   ch='o'; 
	sprintf(a,"%c",ch);
	setcolor(WHITE);
	outtextxy(left[i]+40,top[i]+40,a);
   }
}
//start function to show the intro of the game
void TicTacToe::start()
{
	int i,j;
    setcolor(WHITE);
    for(i=0;i<(width/2)-270;i++)
    {
       cleardevice();
       setcolor(i);
       rectangle(0,0,639,479);
       setcolor(WHITE);
       settextstyle(SANS_SERIF_FONT,HORIZ_DIR,8);
       outtextxy(i,(height/2)-140,"TIC TAC TOE");
  	   //delay(1);
    }
    setcolor(RED);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
    outtextxy((width/2)-200,height/2,"USE THE LEFT MOUSE TO CLICK");
    delay(2000);
    outtextxy((width/2)-350,(height/2)+40,"ClICK ON THE WINDOW AND PRESS ENTER KEY TO START");
    getch();
}
//main part of the program
void TicTacToe::draw(player p)
{
	//x=mouseXPosition  y=mouseYPosition
    //button=mouseClick
    //temp=swapping
    //win=checkWin()
    //hit=if there is a hit
    int i,x,y,hit,temp,win,turns=0;
    char t[5];
    char player[20];
    strcpy(player,p.firstPlayer);
	//drawing the initial things
	drawBackground();
	drawBoard();
	drawTextBoard();
    //Run until the user presses any key
    while(!kbhit())
    {
    	settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
    	outtextxy(800,150,player);
    	outtextxy(800,200,"'s TURN");
    	if(turns==9){
    		gameDraw();
		}
	    //if there is a mouse click from the user
	   if(ismouseclick(WM_LBUTTONDOWN))
	   {
	   	 getmouseclick(WM_LBUTTONDOWN,x,y);
	   	 for(i=0;i<9;i++)
	   	 {
	   	 	if(hitBoard[i]==-1) continue;
			hit = mouseHitBox(mousex(),mousey(),left[hitBoard[i]],top[hitBoard[i]],100,100,hitBoard[i]);
			if(hit!=-1)
			{
				//increasing the turns to see the game draw logic
				//if there is no box to hit and the game went draw
				turns++;
				//Insert the board with players turn input
				//if player turn=1 - x
				//if player turn=2 - o
				board[hit]=playerTurn;
				//add the hitBoard with -1 so that the for loop doesnot have to 
				hitBoard[hit]=-1;
				//checking win logic
				win=checkWin(playerTurn);
				if(win==1){
					end(1,p);
				}
				if(win==2){
					end(2,p);
				}
				//exchange the player turn
				playerTurn=(playerTurn==1)?2:1;
				//changing the players name;
				if(playerTurn==1)
				   strcpy(player,p.firstPlayer);
				else
				   strcpy(player,p.secondPlayer);
				//re setup the functions to draw on the screen
				cleardevice();
				drawBackground();
				drawBoard();
				drawTextBoard();
				break;
			}
		 }
	   }//end of if there is a mouse click
    }//outer while loop
}
//checking for the mouse to hit the boxes
int TicTacToe:: mouseHitBox(int px,int py,int rx,int ry,int rw,int rh,int userMouseHitPosition)
{
  if(px>=rx&&px<=rx+rw&&py>=ry&&py<=ry+rh)
  {
    return userMouseHitPosition;
  }
  return -1;
}
//win logic for tic tac toe
int TicTacToe::checkWin(int p)
{
	if(p==1)
	{
		if(board[0]==1&&board[1]==1&&board[2]==1)
		   return 1;
		if(board[3]==1&&board[4]==1&&board[5]==1)
		   return 1;
		if(board[6]==1&&board[7]==1&&board[8]==1)
		   return 1;
		if(board[0]==1&&board[3]==1&&board[6]==1)
		   return 1;
		if(board[1]==1&&board[4]==1&&board[7]==1)
		   return 1;
		if(board[2]==1&&board[5]==1&&board[8]==1)
		   return 1;
		if(board[0]==1&&board[4]==1&&board[8]==1)
		   return 1;
		if(board[2]==1&&board[4]==1&&board[6]==1)
		   return 1;      
	}
	else if(p==2)
	{
		if(board[0]==2&&board[1]==2&&board[2]==2)
		   return 2;
		if(board[3]==2&&board[4]==2&&board[5]==2)
		   return 2;
		if(board[6]==2&&board[7]==2&&board[8]==2)
		   return 2;
		if(board[0]==2&&board[3]==2&&board[6]==2)
		   return 2;
		if(board[1]==2&&board[4]==2&&board[7]==2)
		   return 2;
		if(board[2]==2&&board[5]==2&&board[8]==2)
		   return 2;
		if(board[0]==2&&board[4]==2&&board[8]==2)
		   return 2;
		if(board[2]==2&&board[4]==2&&board[6]==2)
		   return 2;
	}
	return 0;
}
//winning logic
void TicTacToe::end(int winner,player p)
{
	char t[5];
	cleardevice();
	if(winner==1)
	{
		outtextxy((width/2)-210,height/2,p.firstPlayer);
	    outtextxy((width/2)-180,(height/2)+100,"Wins");
	}else
	{
		outtextxy((width/2)-210,height/2,p.secondPlayer);
	    outtextxy((width/2)-180,(height/2)+100,"Wins");
	}
	getch();
	exit(0);
}
int main()
{
	player p;
	TicTacToe t;
    t.start();
    t.draw(p);
	getch();
	closegraph();
	return 0;
}
