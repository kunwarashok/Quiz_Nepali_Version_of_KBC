#include<iostream.h>
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<conio.h>
#include<fstream.h>
#include<time.h>
#define N 20

static unsigned long int scorecount=500;
static int limit_5050=1,limit_skipqn=1,limit_prdctans=1,fail=0;

class quiz
{
int x,y,i;
time_t t;
char question[200],question2[200],op1[50],op2[50],op3[50],op4[50],ans[2],c[2],ch,ch1[2],ch2;
public:
quiz()
{
x=getmaxx();
y=getmaxy();
srand((unsigned) time(&t));
}

void initialize(char que[],char o1[],char o2[],char o3[],char o4[],char an[])
{
strcpy(question,que);
strcpy(op1,o1);
strcpy(op2,o2);
strcpy(op3,o3);
strcpy(op4,o4);
strcpy(ans,an);
}
void displayquestion();
void displayinterface(char []);
};

void quiz::displayinterface(char cond[])
{
//start of 50-50 logic
if(cond[0]=='b')
{
limit_5050=0;
char ca[2];
int i=0,temp[4];
while(1)
{
int n=rand()%4;
for(int j=0; j<i; j++)
{
if(n==temp[j])
break;
}
if(i==j)
{
ca[0]=n+97;
ca[1]='\0';
if(strcmp(ans,ca)!=0)
{
if(ca[0]=='a')
strcpy(op1,"");
else if(ca[0]=='b')
strcpy(op2,"");
else if(ca[0]=='c')
strcpy(op3,"");
else
strcpy(op4,"");
if(i==1)
break;
temp[i]=n;
i++;
}
}
}
}
//end of 50-50 logic

//displaying interface
cleardevice();

rectangle(10,10,x-10,110);
rectangle(10,130,(x/2)-10,170);
rectangle((x/2)+10,130,x-10,170);
rectangle(10,190,(x/2)-10,230);
rectangle((x/2)+10,190,x-10,230);

int l=strlen(question);
int lt=75;
if(l>lt)
{
int i,j=0;
for(i=lt; i<l; i++)
{
question2[j++]=question[i];
}
question[lt]='\0';
question2[j]='\0';
}

outtextxy(20,25,question);
outtextxy(35,40,question2);
outtextxy(20,145,op1);
outtextxy((x/2)+20,145,op2);
outtextxy(20,205,op3);
outtextxy((x/2)+20,205,op4);

outtextxy(x-145,260,"Prize:Rs");
char f[10];
ultoa(scorecount,f,10);
outtextxy(x-75,260,f);

//options for answering
outtextxy(10,260,"a.Direct Answer");

if(limit_5050==1)
outtextxy((x/2)+10,260,"b.50/50 Lifeline");
else
{
setcolor(RED);
outtextxy((x/2)+10,260,"b.50/50 Lifeline");
line((x/2)+10,263,(x/2)+135,263);
setcolor(WHITE);
}

if(limit_skipqn==1)
outtextxy(10,280,"c.Skip Question");
else
{
setcolor(RED);
outtextxy(10,280,"c.Skip Question");
line(10,283,135,283);
setcolor(WHITE);
}

if(limit_prdctans==1)
outtextxy((x/2)+10,280,"d.Predicted Answer");
else
{
setcolor(RED);
outtextxy((x/2)+10,280,"d.Predicted Answer");
line((x/2)+10,283,(x/2)+135,283);
setcolor(WHITE);
}
}

void quiz::displayquestion()
{
top:
char a[2];
a[0]='a';
displayinterface(a);
fflush(stdin);
ch1[0]='a';
if(limit_5050==1 || limit_prdctans==1 || limit_skipqn==1)
{
outtextxy(10,310,"Which Option you want to choose?:");
ch1[0]=getch();
ch1[1]='\0';
outtextxy(273,310,ch1);
}
fflush(stdin);

if((limit_5050==0 && ch1[0]=='b')||(limit_prdctans==0 && ch1[0]=='d')||(limit_skipqn==0 && ch1[0]=='c'))
goto top;

//answer section
//start of skip qn logic
if(ch1[0]=='c')
{
limit_skipqn=0;
displayinterface(a);
return;
}

//end of skip qn logic
if(ch1[0]=='b')
displayinterface(ch1);

//start of predicted logic
int n=rand()%10;
char c[2];
c[0]=(rand()%4)+97;
c[1]='\0';
answeragain:
if(ch1[0]=='d')
{
limit_prdctans=0;
displayinterface(a);
outtextxy(10,310,"Maybe answer is: ");
if(n<4)
outtextxy(145,310,c);
else
outtextxy(145,310,ans);
}
//end of predicted logic
outtextxy((x/2)-75,340,"Enter your answer:");
c[0]=getch();
c[1]='\0';
outtextxy((x/2)+75,340,c);

while(1)
{
fflush(stdin);
ch=getch();
if(ch==13)
break;
if(ch==8)
{
displayinterface(a);
goto answeragain;
}
}
cleardevice();
if((strcmp(ans,c))==0)
{
outtextxy((x/2)-30,(y/2)-50,"Correct!!!");
if(scorecount==16384000)
{
setcolor(GREEN);
outtextxy((x/2)-65,(y/2)-30,"Congratulations!!!");
setcolor(WHITE);
outtextxy((x/2)-85,(y/2)-10,"You have earned: Rs");
char f[10];
ultoa(scorecount,f,10);
outtextxy((x/2)+70,(y/2)-10,f);
outtextxy((x/2)-220,(y/2)+80,"Thanks for playing this game. Please rate us on google play.");
fail=1;
return;
}
scorecount*=2;
}
else
{
outtextxy((x/2)-30,y/2,"Wrong!");
outtextxy((x/2)-80,(y/2)+20,"Correct answer is:");
char answer[50];
if(ans[0]=='a')
strcpy(answer,op1);
else if(ans[0]=='b')
strcpy(answer,op2);
else if(ans[0]=='c')
strcpy(answer,op3);
else
strcpy(answer,op4);
outtextxy((x/2)-70,(y/2)+40,answer);
outtextxy((x/2)-85,(y/2)+70,"You have earned: Rs");
if(scorecount<4000)
scorecount=0;
else if(scorecount<32000)
scorecount=4000;
else if(scorecount<512000)
scorecount=32000;
else if(scorecount<409630)
scorecount=512000;
else
scorecount=409630;

char f[10];
ultoa(scorecount,f,10);
outtextxy((x/2)+70,(y/2)+70,f);
fail=1;
}
}

void play();
void score();
void help();

void main()
{
int gdriver = DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "C:\\TC\\BGI");
errorcode = graphresult();
if (errorcode != grOk)
{
cout<<"Graphics initilization failed!";
getch();
exit(0);
}
//Main code starts here
char ch1[2],ch2;
int x=getmaxx();

while(1)
{
newchoice:
cleardevice();
rectangle((x/2)-100,80,(x/2)+100,110);
outtextxy((x/2)-30,90,"a.PLAY");

rectangle((x/2)-100,130,(x/2)+100,160);
outtextxy((x/2)-30,140,"b.SCORE");

rectangle((x/2)-100,180,(x/2)+100,210);
outtextxy((x/2)-30,190,"c.How to play");

rectangle((x/2)-100,230,(x/2)+100,260);
outtextxy((x/2)-30,240,"d.EXIT");

//outtextxy((x/2)-200,10,"a.Play \t b.Highscore \t c.Exit");
outtextxy((x/2)-90,290,"Enter your choice:");
ch1[0]=getch();
ch1[1]='\0';

outtextxy((x/2)+60,290,ch1);

while(1)
{
fflush(stdin);
ch2=getch();
if(ch2==13)
break;
if(ch2==8)
goto newchoice;
}

switch(ch1[0])
{
case 'a':
	play();
	break;
case 'b':
	score();
	break;
case 'c':
	help();
	break;
default:
	exit(0);
}
}
}

void play()
{
quiz q[N];
char que[200],o1[50],o2[50],o3[50],o4[50],an[3],ch;
int temp[N],i,j=0,n,y=getmaxy();
limit_5050=1,limit_skipqn=1,limit_prdctans=1,fail=0,scorecount=500;

//reading questions from file.
ifstream fquiz;
fquiz.open("quiz.txt");
if(!fquiz)
{
cout<<"Failed to open file!";
exit(1);
}


for(i=0; i<N; i++)
{
fquiz.getline(que,200);
fquiz.getline(o1,50);
fquiz.getline(o2,50);
fquiz.getline(o3,50);
fquiz.getline(o4,50);
fquiz.getline(an,3);
q[i].initialize(que,o1,o2,o3,o4,an);
}
fquiz.close();

//displaying questions in random order.
i=0;
while(1)
{
n=rand()%N;
for(j=0; j<i; j++)
{
if(n==temp[j])
break;
}
if(i==j)
{
q[n].displayquestion();
outtextxy(10,y-10,"Press Enter for Next or Esc to Return to main menu..");
fflush(stdin);
ch=getch();
temp[i]=n;
i++;
if(fail==1)
break;
if(ch==27)
{
if(scorecount<4000)
scorecount=0;
else if(scorecount<32000)
scorecount=4000;
else if(scorecount<512000)
scorecount=32000;
else if(scorecount<409630)
scorecount=512000;
else
scorecount=409630;
break;
}
}
}
}

void score()
{
int x=getmaxx(), y=getmaxy();
unsigned long int hscore;

//reading highscore from file.
fstream fhscore;
fhscore.open("hscore.txt",ios::in|ios::out);
if(!fhscore)
{
cout<<"Failed to open file!";
exit(1);
}

fhscore>>hscore;

cleardevice();
if(scorecount==500)
{
scorecount=0;
}

outtextxy((x/2)-105,(y/2)-30,"Highest Amount Earned: Rs");
char g[10];

if(scorecount>hscore)
{
hscore=scorecount;
fhscore.clear();
fhscore.seekg(0,ios::beg);
fhscore<<hscore;
}

ultoa(hscore,g,10);
outtextxy((x/2)+100,(y/2)-30,g);

outtextxy((x/2)-85,(y/2)+20,"You have earned: Rs");
char f[10];
ultoa(scorecount,f,10);
outtextxy((x/2)+70,(y/2)+20,f);
getch();
}
void help()
{
cleardevice();
int x=getmaxx();
setcolor(YELLOW);
outtextxy((x/2)-70,10,"Quiz Mania");
outtextxy(10,30,"In this game, you have to give answer to maaximum of16 questions.");
outtextxy(10,50,"You must give correct answer to go to next questin.");
outtextxy(10,80," you will have 3 lifelines and direct answer option. you will provide.");
outtextxy(10,110,"your own known answer in the direct option. The skip option skips the current");
outtextxy(10,140,"question.The prediected answer gives 70% right answer 50 50 life line gives");
outtextxy(10,170,"two options including the right answer.Wrong answer terminate the game");
outtextxy(10,200,"each question gives you cash prize rs 500 your main aim to achive 1 core 63");
outtextxy(10,230,"lakhs and 84 thousands.Cash prize is leveled as 0,4000,32000,256000,2048000,");
outtextxy(10,260,"16384000. If the candidate scores as equal tothe cash prize level the ");
outtextxy(10,290,"cash is issued.if then the candidate  gets less  than the leveled prize then");
outtextxy(10,310,"the candidate will get the cash below the nearing cash prize.");
setcolor(WHITE);
getch();
}

