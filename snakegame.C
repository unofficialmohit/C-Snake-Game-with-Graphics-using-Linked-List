#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
char *sname[100],key;	//sname is used for name of player,key is used to read key entered
int score1,level=1,speed=60,maxx,maxy,n=0;

struct loc	//structure for location
{
	int x,y;
};

struct snake	//structure for snake length and direction
{
	struct loc sloc;
	struct snake *link;
	char dir;
};

struct game_data	//structure for score and food
{
	int score;
	int no_food;

};
struct game_data gd={0,0};	



struct limit		//structure to limit playable area
{
	int lx1,ly1,lx2,ly2;
};

struct limit l={50,50,600,400};

struct food	 	//structure to generate food on screen
{
	struct loc floc;
	int number;
};

void draw_board()	//Basic UI function for main menu
{
maxx=getmaxx();	//to get max value of x coordinate 
maxy=getmaxy();	//to get max value of y coordinate 
setcolor(WHITE);
rectangle(0,0,maxx,maxy);  //to draw rectangle on screen
rectangle(8,8,maxx-8,maxy-8);
rectangle(maxx-130,38,maxx-133,maxy-8);
rectangle(maxx-130,70,maxx-9,73);
setfillstyle(9,2);	//formating fill style 
floodfill(6,6,WHITE);	//to fill a specfic area
rectangle(8,35,maxx-8,38);
setfillstyle(SOLID_FILL,12);
bar(9,9,maxx-9,34);
settextstyle(0,0,2);
setcolor(9);
outtextxy(maxx/2-150,16,"S N A K E  G A M E");
setcolor(YELLOW);
settextstyle(2,0,4);
settextstyle(2,0,4);
setcolor(3);
outtextxy(maxx-120,40, "Panjab University");
outtextxy(maxx-100,50, "Chandigarh");
settextstyle(2,0,5);
outtextxy(maxx-115,310, "Developed By");
setcolor(2);
settextstyle(2,0,4);
outtextxy(maxx-90, 330, "MOHIT");
setcolor(10);
outtextxy(maxx-105, 350, "MCA 2nd Sem");
outtextxy(maxx-100, 370, "Guided By");
outtextxy(maxx-120, 390, "Mrs. Shyamla Devi");
}

//Funtion to move snake around the area
void game1(struct snake *head,struct food *f)
{
int ch;
struct snake *temp,pre,nxt;
temp=head;
speed=60;
level=1;
gd.no_food=0;
gd.score=0;
while(key!='p')
{

if(head->sloc.x==l.lx1||head->sloc.x==l.lx2||head->sloc.y==l.ly1||head->sloc.y==l.ly2)
{
loss_game(gd.score);
}
if(head->sloc.x>=f->floc.x-5&&head->sloc.x<=f->floc.x+5&&head->sloc.y>=f->floc.y-5&&head->sloc.y<=f->floc.y+5)
{
temp=head;
f->floc.x=60+random(430);
f->floc.y=60+random(330);
gd.score+=100;	//increment in score
gd.no_food+=1;	//increment in food
n=n+1;
//if(gd.no_food%15==0)
if(gd.score%1500==0)
{
if(speed>10)
{
speed=speed-10;
delay(2);
settextstyle(1,0,6);
outtextxy(180,200,"NEXT LEVEL");
settextstyle(1,0,2);
outtextxy(180,260,"Press any key to continue");
delay(2);
getch();
}
}
if(gd.no_food%15==0)
{
level=level+1;	//increment in level
}
while(temp->link!=NULL){temp=temp->link;}
temp->link=(struct snake *)malloc(sizeof(struct snake));
temp->link->link=NULL;
temp->link->sloc.x= temp->sloc.x;
temp->link->sloc.y= temp->sloc.y;
temp->link->dir=temp->dir;
n=0;
}    
settextstyle(2,0,4);
outtextxy(maxx-200,17, "Your Score:");
gotoxy(66,2);
printf("%d",gd.score);
outtextxy(maxx-300,17,"Speed :");
gotoxy(50,2);
printf("%d",70-speed);
outtextxy(maxx-400,17,"Level :");
gotoxy(38,2);
printf("%d",level);
outtextxy(maxx-550,17,"Food Collected :");
gotoxy(26,2);
printf("%d",gd.no_food);
settextstyle(3,0,4);
outtextxy(maxx-510,maxy-65,"THE SNAKE GAME USING LL");
switch(key)
{
case 'a':
if(head->dir!='d')
{
head->dir='a';
head->sloc.x-=2; }
else
{
key=head->dir;
}
break;
case 'w':
if(head->dir!='s')
{
head->dir='w';
head->sloc.y-=2; }
else
{
key=head->dir;
}
break;
case 'd':
if(head->dir!='a')
{
head->dir='d';
head->sloc.x+=2;
}
else
{
key=head->dir;
}
break;
case 's':
if(head->dir!='w')
{
head->dir='s';
head->sloc.y+=2;
}
else
{
key=head->dir;
}
break;
}
draw(head,f);
temp=head;
pre=*temp;
while(temp->link!=NULL)
{
nxt.sloc.x=temp->link->sloc.x;
nxt.sloc.y=temp->link->sloc.y;
nxt.dir=temp->link->dir;
temp->link->sloc.x=pre.sloc.x;
temp->link->sloc.y=pre.sloc.y;
temp->link->dir=pre.dir;
temp=temp->link;
pre=nxt;
}
}
}

//function to draw snake and other info during gameplay
draw(struct snake *head,struct food *f)
{
struct snake *temp;
temp=head;
rectangle(50,50,600,400);
rectangle(45,45,605,405);
setfillstyle(9,13);
bar(temp->sloc.x-6,temp->sloc.y-6,temp->sloc.x+6,temp->sloc.y+6);
temp=temp->link;
setfillstyle(9,2);
while(temp->link!=NULL)
{
bar(temp->sloc.x-5,temp->sloc.y-5,temp->sloc.x+5,temp->sloc.y+5);
temp=temp->link;
}
bar(temp->sloc.x-5,temp->sloc.y-5,temp->sloc.x+5,temp->sloc.y+5);
circle(f->floc.x-2,f->floc.y-2,5);
circle(f->floc.x+2,f->floc.y+2,5);
circle(f->floc.x-2,f->floc.y+2,5);
circle(f->floc.x+2,f->floc.y-2,5);
delay(speed);
while(!kbhit()){goto e;}
key=getche();
e:
cleardevice();
return 0;
}

void help() //function to display instructions
{
char *str[]={"1:-Make Snake Long By Eating Food.",
"2:-Move Snake By Using These Keys:-",
" * A :- Move Left",
" * D :- Move Right",
" * W :- Move Up",
" * S :- Move Down",
"NOTE 1 :- Do not touch snake to boundries.",
"If you do this then result is GAME OVER.",
"NOTE 2 :- Speed will not go above 60",
"Have Fun Playing Snake Game"};
int y=120,i;
setcolor(WHITE);
settextstyle(3,0,4);
rectangle(50,40,590,100);
outtextxy(230,50,"Instructions");
setfillstyle(SOLID_FILL,RED);
bar3d(50,100,590,430,0,5);
settextstyle(0,0,1);
setcolor(YELLOW);
for(i=0;i<10;i++)
{
outtextxy(70,y,str[i]);
delay(700);
y=y+25;
}
getch();
cleardevice();
fflush(stdin);
main();
}

//function to save score in a file
void sethigh(int s,char *sname)
{
FILE *fp;
fp=fopen("snake.txt","a");
if(!fp)
printf("ERROR");
fprintf(fp,"\n%s \t\t %d",sname,s);
fclose(fp);
}
void showhigh()
{
char buffer[100];
int y=8;
FILE *fp1;
setcolor(WHITE);
settextstyle(3,0,4);
rectangle(50,40,590,100);
outtextxy(230,50,"SCORES");
setfillstyle(SOLID_FILL,RED);
bar3d(50,100,590,430,0,5);
settextstyle(0,0,1);
setcolor(YELLOW);
fp1=fopen("snake.txt","r");
while(!feof(fp1))
{
if(feof(fp1))
break;
else
{
fgets(buffer,100,fp1);
gotoxy(28,y);
y=y+1;
printf("%s",buffer); }}
fclose(fp1);
getch();
cleardevice();
main();
}

//function to get player name 
//to call other funtion after entering name
void game(void)
{
struct snake *s;
struct food f;
cleardevice();
outtextxy(140,100,"ENTER PLAYER NAME");
draw_board();
gotoxy(28,11);
setcolor(YELLOW);
rectangle(140,140,370,200);
scanf("%s",&sname);
cleardevice();
s=(struct snake *)malloc(sizeof(struct snake));
s->dir='w';
s->link=NULL;
s->sloc.x= s->sloc.y=300;
f.floc.x=150+random(250);
f.floc.y=150+random(250);
draw_board();
game1(s,&f);
}

//function to display game over on screen 
//and call another function to save score in file
int loss_game(int score)
{
settextstyle(1,0,6);
setcolor(RED);
outtextxy(180,200,"GAME OVER");
settextstyle(1,0,2);
outtextxy(180,260,"Press any key to continue");
sethigh(score,sname);
getch();
cleardevice();
main();
return 0;
}

//main funtion, it contain main menu screen
//New Game,Help,Score,Exit 
int main()
{

int gd=DETECT,gm;
int cursor_y = 130;
char ch;
int x;
initgraph(&gd,&gm,"c:\\tc\\bgi");
maxx=getmaxx();
maxy=getmaxy();
while(1)
{
draw_board();
settextstyle(8,0,6);
setcolor(YELLOW);
settextstyle(3,0,3);
rectangle(160,125,390,163);
outtextxy(200,130,"New Game");
rectangle(160,167,390,201);
outtextxy(200,170,"Help");
rectangle(160,205,390,247);
outtextxy(200,210,"Score");
rectangle(160,243,390,287);
outtextxy(200,250,"Exit");
setcolor(RED);
outtextxy(170,cursor_y,"->");
setcolor(WHITE);
settextstyle(3,0,3);
outtextxy(90,350,"<<<WELCOME TO SNAKE GAME>>>");
x=0;
if(x==0){
ch = getch();
cleardevice();
if(ch == 13) 
{
if(cursor_y==250) exit(0);
else if(cursor_y==130) game();
else if(cursor_y==170) help();
else if(cursor_y==210) showhigh();
}
}
//setcolor(WHITE);
if(ch==80) {cursor_y+=40;
if(cursor_y > 250) {cursor_y=130;}
}
if(ch==72) {cursor_y-=40;
if(cursor_y < 130) {cursor_y=250;}
}
}
}