#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<direct.h>
#include<stdlib.h>
#include "header1.h"

static int x=1;//used for x cursor co-ordinate
int timelimit=30;

#define pos gotoxy(33,x++) /*for cursor movement*/
#define ln  printf(".......................");
//.......................................................................................................................................................................
 COORD coord={0,0};
 
void gotoxy(int x,int y)//function to set the cursor position
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//.......................................................................................................................................................................
void delay(unsigned int mseconds)//function for delay
{
    clock_t goal=mseconds+clock();
    while(goal>clock());
}
//.............................................................................................................................................................................
void setcolor(int ForgC) //function to change color
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
 }



//****************************************************************************************************************************************************************************
int menu(char name[])
{
    int choice;
    printf("\n\nHello %s\n\n",name);
    printf("MENU:\n");
    printf("1.START TYPING\n2.PROGRESS CARD\n3.RULES\n4.ABOUT US\n5.EXIT\n\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
            starttyping(name);
            break;
        case 2:
            progresscard(name);
            break;
        case 3:
            rules(name);
            break;
        case 4:
            aboutus(name);
            break;
        case 5:
            endgame();
            break;
        default:
            printf("\nWrong choice- enter again:\n");
            menu(name);
            return 0;
    }
    return 1;
}

void starttyping(char name[])
{
    
	sett(name);
	time_t t;
	time(&t);
	x=1;
	system("cls");
	pos;
	setcolor(12) ;
	printf("welcome to typing tutor ");
	setcolor(10) ;
	pos;
	printf("%s",ctime(&t));
	
	pos;
	ln pos;

    int score=0,level=1,mode=100,count=0;
	clock_t begin;int time_spent,speed;
	int wrong=0;
	int total=0;
	float accuracy;
	int r,letter;
    char ch;
	delay(1000);

	system("cls");
	srand(time(NULL)) ; //initilizes random function and seed with time
	x=2;
	pos;
	setcolor(7);
	printf("#select the Mode#");pos;
	ln
	pos;
	printf("1.Easy mode#");
	pos;
	printf("2.Normal mode#");
	pos;
	printf("3.hard mode#");
	pos;
	scanf("%d",&level);
	
		begin=clock();
		int flag=1;
		while(flag)
		{       system("cls");
			time_spent=(int)(clock()-begin)/CLOCKS_PER_SEC;

			if(time_spent>=timelimit)
			{
				flag=0;
				break;
			}
			if(level==1)    //only uppercase alphabet
	     			r=rand()%26+65;
	    		if(level==2)    //uppercase and lowercase alphabets
				r=rand()%58+65;
	    		if(level==3)    //alphabets including numbers and special characters
				r=rand()%94+33;
			gotoxy(20,8);
			printf("....Type the following character....\t\ttime_spent=%d sec\n\t\t score= %d",time_spent,score);
			gotoxy(36,11) ;
			printf(" %c",r);//prints random character

			letter=getch();

			if(letter!=r)
			{
				setcolor(10);
				printf("\nWrong Input");
				wrong+=1;
				total+=1;
				setcolor(7);
				score=score-10;
			}
			else
			{   
                count++;
				total+=1;
				score=score+10;
			}
            gotoxy(37,9);
			    if(level==1)
					delay(400);
				if(level==2)
					delay(200);
				if(level==3)
					delay(100);

		}
		gotoxy(26,x);
		delay(400);
		
		++x;
		pos;
		speed=(count*60)/time_spent ;
		accuracy = ((float)count/(float)total)*100;

		setcolor(11);
		printf("Times up !session ended!");
		pos;
		
		printf("Ratings for your typing (out of 5 stars)\n");
		pos;setcolor(12);
		if(speed>=60)
			printf("*****");
		else if(speed>45)
			printf("****");
		else if(speed>35)
			printf("***");
		else if(speed>25)
			printf("**");
		else
			printf("*");
		
		pos;setcolor(11);
		printf("Total score is :%d",score);
		pos;
		printf("Your net speed=%d letter per minute",speed);
		pos;
		printf("Accuracy = %0.2f",accuracy);
		++x;
    setcolor(7);	
    printf("\nDo you want to save this session?\n1.yes    2.no\n");
    int choice1;
    scanf("%d",&choice1);
    if(choice1==1)
    {
	    update_progresscard(name,level,score,speed,accuracy);
        printf("Progress report saved.");
    }
	else
		printf("Not saved");
	system("cls");
    menu(name);
}

void update_progresscard(char name[],int level,int score,int speed,float accuracy)
{
    FILE *fp;
	fp=fopen("file.txt","a");
	
	if(fp==NULL)
		printf("error in opening file");
	fprintf(fp,"\nname=%s   level=%d    score=%d    speed=%d    accuracy=%0.2f",name,level,score,speed,accuracy);
	fclose(fp);
	
	printf("progress card updated\n");

}

void progresscard(char name[])
{
   int ch;
	FILE *fp;
	
	setcolor(11);
	printf("\t\t\t....PROGRESS REPORT....\n");

	fp=fopen("file.txt","r");
	while((ch=fgetc(fp))!=EOF)
	{
        
        printf("%c",ch);
	}
	getch();
	setcolor(7);
    menu(name);
}

void rules(char name[])
{
    printf("Rules are as follows:\n1) Enter your name as player name\n2) The application has three modes of difficulty i.e., easy,normal and hard.\n3) The user will have to choose one of the above options.\n4) The first,i.e.,the easy mode has all the letters in upper case.So,the user will have to type only upper case letters in this mode.\n5) The second,i.e.,the normal mode comprises of both upper and lower case.\n6) The difficult mode includes both the upper and lower case including special characters.\n7) Characters are displayed and you have to type them as fast as you can..\n8) Avoid incorrect typing otherwise game will be over..\n");


    menu(name);
}

void aboutus(char name[])
{
    printf("About us:\nHeyy guys.Do you know your typing speed???\nHere we are  with an amazing application which helps you double your typing speed.\nThis is a platform where you can learn keyboarding in a fun way.\nYou can test your wpm(words per minute),speed and accuracy here.\n\n\nTeam members:\n1)Jeffrey S Varghese\n2)J Arvind Reddy\n3)Jagruthi K J\n");

    menu(name);
}

void endgame()
{
    system("cls");
    printf("exit\n");
    printf("Thank you!!\n");
	printf("Team mates:\n)Jeffrey S Varghese\n2)J Arvind Reddy\n3)Jagruthi K J\n");
}

void sett(char name[])  //set time limit
{
	int ch;
	system("cls");
	//rectangle(0,0,70,15);
	setcolor(11);
	x=5;
	pos;
	printf("Set the time limit for game in minute::");
	pos;
	ln
	pos;
	printf("press 0 for half minute") ;pos;
	printf("press 1 for 1 minute"); pos;
	printf("press 2 for 2 minute");pos;
	scanf("%d",&ch);
	switch(ch)
	{
		case 0:timelimit=30;break;
		case 1:timelimit=60;break;
		case 2:timelimit=120;break;
		default:menu(name);
	}
}