#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#define max 40
#define inversespeed 1000

typedef struct{
    int length;
    int score;
    int currentdirection;
    int targetrow;
    int targetcol;
    int headrow;
    int headcol;
    int newdirection;

}game;

int getlength(game *snake);
int getscore(game *snake);
int getcurrentdirection(game *snake);
int getnewdirection(game *snake);
int gettargetrow(game *snake);
int gettargetcol(game *snake);
int getheadcol(game *snake);
int getheadrow(game *snake);



void setlength(game *snake,int length);
void setscore(game *snake,int score);
void sethead(game *snake,int map[][max],int dim);
void setmap(int map[][max],int dim);
void setdirection(game *snake,int dir);
void resetdir(game *snake);
void setsnake(game *snake,int map[][max],int dim);
void settargetpos(game *snake,int dir);
void initiate(game *snake,int map[][max],int dim);


bool checkfood(game *snake,int map[][max],int dim);
void generatefood(game *snake,int map[][max],int dim);
void printmap(game *snake,int map[][max],int dim);

bool eatfood(game *snake,int map[][max],int dim);
void move(game *snake,int map[][max],int dim);

int inputdirection(game *snake);
bool lose(game *snake,int map[][max],int dim);
void delay(unsigned int mseconds);


int main()                    //snake>0,food=-1,blank=0;//  //1=up,-1=down,2=right,-2=left//
{
    game snake;
    int map[max][max];
    int dim,turn,i=0,inputdir,j;

    srand(time(0));
    printf("enter the dimension of the map.\n");
    scanf("%d",&dim);

    initiate(&snake,map,dim);

    printf("enter the number of turn.\n");
    scanf("%d",&turn);
    system("cls");

    generatefood(&snake,map,dim);
    printmap(&snake,map,dim);
    for(j=0;j<dim;j++){
        printf("--");
        }
    printf("\n");


    while(i<turn){

    printf("TURN : %d | SCORE : %d\n",i,getscore(&snake));

    resetdir(&snake);
    generatefood(&snake,map,dim);
    sethead(&snake,map,dim);
    delay(inversespeed);
    if(kbhit()){
    inputdir=inputdirection(&snake);

    settargetpos(&snake,inputdir);

   } else{            //if no dir is input, then delay and execute next step.

    settargetpos(&snake,getcurrentdirection(&snake));
   }

    if(lose(&snake,map,dim)==false){
    move(&snake,map,dim);
    generatefood(&snake,map,dim);
    system("cls");
    printmap(&snake,map,dim);
    sethead(&snake,map,dim);
    for(j=0;j<dim;j++){
    printf("--");
    }
    printf("\n");
    i++;
    }else{i=turn;
    }
    }


    printf("GAME OVER!\nTOTAL SCORE: %d",getscore(&snake));

    delay(10000);

    return 0;
}

int getlength(game *snake){
    return (*snake).length;
}

int getscore(game *snake){
    return (*snake).score;
}

int getcurrentdirection(game *snake){
    return (*snake).currentdirection;
}

int getnewdirection(game *snake){
    return (*snake).newdirection;
}

int gettargetrow(game *snake){
    return (*snake).targetrow;
}

int gettargetcol(game *snake){
    return (*snake).targetcol;
}

int getheadcol(game *snake){
    return (*snake).headcol;
}

int getheadrow(game *snake){
    return (*snake).headrow;
}


void setmap(int map[][max],int dim){
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            map[i][j]=0;
        }
    }
return;
}

void resetdir(game *snake){
    int currentdir=getcurrentdirection(snake),newdir=getnewdirection(snake);
    if((currentdir)==((-1)*(newdir))){
        return;
    }else {
    snake->currentdirection=snake->newdirection;
    }
    return;
}

void setlength(game *snake,int length){
    snake->length=length;
    return;
}

void setscore(game *snake,int score){
    snake->score=score;
    return;
}

void setdirection(game *snake,int dir){
    snake->newdirection=dir;
    return;
}

void sethead(game *snake,int map[][max],int dim){
    int i,j,maxval=0,hrow,hcol;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
             if(map[i][j]>maxval){
                maxval=map[i][j];
                hrow=i;
                hcol=j;
            }
        }
    }
    snake->headrow=hrow;
    snake->headcol=hcol;
    return;
}



void initiate(game *snake,int map[][max],int dim){
    snake->currentdirection=2;
    setlength(snake,3);
    setmap(map,dim);
    setsnake(snake,map,dim);
    sethead(snake,map,dim);
    setdirection(snake,2);
    setscore(snake,0);
    settargetpos(snake,getcurrentdirection(snake));

    return;
}
//snake>0,food=-1,blank=0;//  //1=up,-1=down,2=right,-2=left//
void settargetpos(game *snake,int dir){
     int trow,tcol,currentdir=getcurrentdirection(snake);
     trow=((*snake).headrow);
     tcol=((*snake).headcol);

     if(abs(dir)==abs(currentdir)){
        switch(currentdir){
        case 1:
            trow--;
            break;
        case -1:
            trow++;
            break;
        case 2:
            tcol++;
            break;
        case -2:
            tcol--;
            break;
        }

    }else {
        switch(dir){
        case 1:
            trow--;
            break;
        case -1:
            trow++;
            break;
        case 2:
            tcol++;
            break;
        case -2:
            tcol--;
            break;
        }
    }
    snake->targetcol=tcol;
    snake->targetrow=trow;

    return;
}

void setsnake(game *snake,int map[][max],int dim){
    int length=getlength(snake),i=0,j;
    for(j=0;j<length;j++){
        map[i][j]=j+1;
    }
return;
}

bool checkfood(game *snake,int map[][max],int dim){
    int i,j;
    bool flag=false;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            if(map[i][j]==-1){
                flag=true;
            }
        }
    }
    return flag;
}

void generatefood(game *snake,int map[][max],int dim){
    int foodcol,foodrow;

    if(checkfood(snake,map,dim)==false){
        foodcol=rand()%dim;
        foodrow=rand()%dim;
        while(map[foodrow][foodcol]>0){
            foodcol=rand()%dim;
            foodrow=rand()%dim;
        }
        map[foodrow][foodcol]=-1;
    }
    return;
}

int inputdirection(game *snake){
    int dir;
    int y;

    y=getch();
    y=getch();
      //up 72.left 75.right 77.down 80.//


    switch(y){
        case 72:
            dir=1;

            break;

        case 80:
            dir=-1;

            break;

        case 75:
            dir=-2;

            break;

        case 77:
            dir=2;

            break;
        }


    setdirection(snake,dir);
    return dir;
}

void move(game *snake,int map[][max],int dim){
    int i,j,tcol=gettargetcol(snake),trow=gettargetrow(snake);

    if(eatfood(snake,map,dim)==true){
        map[trow][tcol]=getlength(snake);
    }else {
         for(i=0;i<dim;i++){
            for(j=0;j<dim;j++){
                if(map[i][j]>0){
                map[i][j]=map[i][j]-1;
                map[trow][tcol]=getlength(snake);
                    }
                }
            }
        }

    return;
}

bool eatfood(game *snake,int map[][max],int dim){
    int tcol=gettargetcol(snake),trow=gettargetrow(snake),score=getscore(snake),length=getlength(snake);
    bool flag=false;
    if(map[trow][tcol]==-1){
        flag=true;
        score++;
        length++;
    }
    setscore(snake,score);
    setlength(snake,length);
    return flag;
}

void printmap(game *snake,int map[][max],int dim){
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            if(map[i][j]==0){
                printf("  ");
            }
            if(map[i][j]==-1){
                printf("o ");
            }
            if(map[i][j]>0){
                    if(map[i][j]==getlength(snake)){
                        printf("@ ");
                    }else{
                        printf("X ");
                        }

            }
            if(j==dim-1){
            printf("|");
        }
        }
        printf("\n");
    }
return;
}

bool lose(game *snake,int map[][max],int dim){
    bool flag=false;
    int tcol=gettargetcol(snake),trow=gettargetrow(snake);

            if((tcol>=dim)||(tcol<0)||(trow>=dim)||(trow<0)){
                flag=true;
            }

            if((map[trow][tcol]>=1)&&(map[trow][tcol]!=-1)){
                flag=true;
            }
    return flag;
}

void delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
