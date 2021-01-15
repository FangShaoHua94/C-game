#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

#define dim 50
#define playerrow 24
#define barrierrow 22
#define barrierhp 9
#define moparraysize 1

typedef struct{
    int dir;
    int col;
    bool shoot;

}player;

typedef struct{
    int moprow[moparraysize];
    int row;
    int dir;
    int counter;
}mop;

int getdir(player *x);
int getcol(player *x);
bool getshoot(player *x);
int getmopdir(mop *y);
int getmopcounter(mop *y);
int getmoprow(mop *y);


void setdir(player *x,int dir);
void setcol(player *x,int col);
void setshoot(player *x,bool shoot);
void setmopcounter(mop *y,int counter);
void setmopdir(mop *y,int dir);
void setrow(mop *y,int row);

void setmoprow(mop *y,int firstmoprow);
void setmap(int map[][dim]);
void setplayer(player *x,int map[][dim]);
void setbarrier(int map[][dim]);
void setmop(mop *y,int map[][dim]);
void initiate(player *x,mop *y,int map[][dim]);

void printmap(int map[][dim]);
void testmap(int map[][dim]);
void mopmove(mop *y,int map[][dim]);
void playermove(player *x,int map[][dim]);
void inputmove(player *x,int map[][dim]);
void xbulletmove(player *x,int map[][dim]);
void ybulletmove(mop *y,int map[][dim]);
void shootcannon(player *x,int map[][dim]);
void mopshoot(mop *y,int map[][dim]);

bool lose(player *x,mop *y,int map[][dim]);




int main()
{
    player *x = (player*) malloc(sizeof(player));
    int map[dim][dim];
    mop y;
    int turn=1;

    initiate(x,&y,map);
    printmap(map);
   // testmap(map);

    while((turn<999)&&(lose(x,&y,map)==false)){

        inputmove(x,map);
        system("cls");
        shootcannon(x,map);
         playermove(x,map);

        xbulletmove(x,map);
         mopmove(&y,map);


       //ybulletmove(&y,map);
        printmap(map);
        //testmap(map);
        //printf("TURN: %d\n",turn);

        turn++;
    }

    free(x);
    system("clr");
    printf("GAME OVER.");
    //testmap(map);

    return 0;
}

int getdir(player *x){
    return (*x).dir;
}

int getcol(player *x){
    return (*x).col;
}

int getmopdir(mop *y){
    return (*y).dir;
}

int getmoprow(mop *y){
    return (*y).row;
}

int getmopcounter(mop *y){
    return (*y).counter;
}

bool getshoot(player *x){
    return (*x).shoot;
}

void setdir(player *x,int dir){
    x->dir=dir;
    return;
}

void setcol(player *x,int col){
    x->col=col;
    return;
}

void setshoot(player *x,bool shot){
    x->shoot=shot;
    return;
}

void setmopcounter(mop *y,int counter){
    y->counter=counter;
    return;
}

void setrow(mop *y,int row){
    y->row=row;
    return;
}

void setmopdir(mop *y,int dir){
    y->dir=dir;
    return;
}

void setmoprow(mop *y,int firstmoprow){
    int i,j=firstmoprow;
    for(i=0;i<moparraysize+1;i++){
        (*y).moprow[i]=j;
        j-=2;
    }
    return;
}

void setmap(int map[][dim]){ //blank space=0;fighter=2,mop=1,barrier=1,2,3,4,5,6...;cannon bullet -3,mop bullet -4
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            map[i][j]=0;
        }
    }
    return;
}

void setplayer(player *x,int map[][dim]){
    int col=getcol(x);
    map[playerrow][col]=-2;
    return;
}

void setbarrier(int map[][dim]){  //ooooxxoooxxoooxxoooxxoooo  8+17=25
    int i;
    for(i=0;i<dim;i++){ //4 5 9 10 14 15 19 20
        if(i==4||i==5||i==9||i==10||i==14||i==15||i==19||i==20){
            map[barrierrow][i]=barrierhp;
            }
    }
return;
}

void setmop(mop *y,int map[][dim]){  //oooxoxoxoxoxoxoxoxoxoxooo 10+11+4=25
    int i,j,row1=(*y).moprow[0],row2=(*y).moprow[1],temp=3;
    for(i=0;i<dim;i++){
        for(j=0;j<dim-3;j++){
            if(i==row1||i==row2){
                if(j==temp){
                    map[i][j]=-1;
                    temp+=2;
                }
            }

        }temp=3;
    }
    return;
}
void initiate(player *x,mop *y,int map[][dim]){
    setmap(map);
    setcol(x,12);
    setplayer(x,map);
    setmoprow(y,4);
    setmop(y,map);
    setbarrier(map);
    setmopcounter(y,0);
    setmopdir(y,1);
    setshoot(x,false);
    setrow(y,4);
return;
}

void printmap(int map[][dim]){
    int i,j;
    map[0][0]=0;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            if(map[i][j]==0){
                printf(" ");
            }
            if(map[i][j]==-2){
                printf("!");
            }
            if(map[i][j]==-1){
                printf("T");
            }
            if(map[i][j]>0){
                printf("#");
            }
            if(map[i][j]==-3){
                printf("^");
            }
        }
        printf("|\n");
    }
    printf("---------------------------------\n");
    return;
}

void testmap(int map[][dim]){
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            printf("%d",map[i][j]);
        }
        printf("\n");
    }
    return;
}
 //oooxoxoxoxoxoxoxoxoxoxooo 10+11+4=25
void mopmove(mop *y,int map[][dim]){   //blank space=0;fighter=-2,mop=-1,barrier=1,2,3,4,5,6...;cannon bullet -3,mop bullet -4
    int i,j,mopdir=getmopdir(y),counter=getmopcounter(y),leftlimit=-3,rightlimit=3,moprow=getmoprow(y);

    //move left dir=1

    if(counter==leftlimit||counter==rightlimit){
            for(i=dim;i>0;i--){
                for(j=dim;j>0;j--){
                    if(map[i][j]==-1){
                        map[i][j]=0;
                        map[i+1][j]=-1;
                        }
                    }
                }
        mopdir=mopdir*-1;
        moprow++;
        setrow(y,moprow);
        }

        if(mopdir==1){
            for(i=0;i<dim;i++){
                for(j=0;j<dim;j++){
                    if(map[i][j]==-1){
                        map[i][j]=0;
                        map[i][j-1]=-1;
                    }
                }
            }
        counter--;
        setmopcounter(y,counter);
        setmopdir(y,mopdir);
        }
        //move right dir=-1
        else if(mopdir==-1){
            for(i=dim;i>0;i--){
                for(j=dim;j>0;j--){
                    if(map[i][j]==-1){
                        map[i][j]=0;
                        map[i][j+1]=-1;
                    }
                }
            }
        counter++;
        setmopcounter(y,counter);
        setmopdir(y,mopdir);
        }
    return;
}

void inputmove(player *x,int map[][dim]){
    int i,j,dir;
    int y;

    y=getch();
    if(y==32){
            setshoot(x,true);
      for(i=0;i<dim;i++){
            for(j=0;j<dim;j++){
                if(map[i][j]==-3){
                    setshoot(x,false);
                }
            }
      }

    }else if(y==224){//space 32
    y=getch();  //left 75.right 77.//
    switch(y){
        case 77:
            dir=-1;
            setdir(x,-1);    //-1 right   1 left for dir
            break;

        case 75:
            dir=1;
            setdir(x,1);
            break;
        }
    }



printf("input is %d\n",y);
printf("dir is %d\n",dir);
int z=getdir(x);
printf("z is %d\n",z);
    return;
}

void playermove(player *x,int map[][dim]){
    int dir=getdir(x),j;
    printf("dir is %d\n",dir);

            for(j=0;j<dim;j++){
                if(map[playerrow][j]==-2){
                    if(dir==1){
                        if(j==0){
                            return;
                        }else{
                            map[playerrow][j]=0;
                            map[playerrow][j-1]=-2;
                            return;
                        }
                    }else if (dir==-1){
                        if(j==dim-1){
                            return;
                        }else{
                            map[playerrow][j]=0;
                            map[playerrow][j+1]=-2;
                            return;
                        }
                    }
                }
            }

    return;
}
void shootcannon(player *x,int map[][dim]){
    int i,j;
    bool flag=getshoot(x),z=false;

    if (flag==true){
        printf("shoot true\n");
        for(i=0;i<dim;i++){
            for(j=0;j<dim;j++){
                if(map[i][j]==-2){
                    map[i-1][j]=-3;
                }
            }
        }
        setshoot(x,z);
    }else {
        printf("shoot false\n");
        }
    return;
}

void xbulletmove(player *x,int map[][dim]){
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            if(map[i][j]==-3){
                map[i][j]=0;
                if(map[i-1][j]==0){
                    map[i-1][j]=-3;

                }else{
                    map[i-1][j]=map[i-1][j]-2;
                    if(map[i-1][j]<0){
                        map[i-1][j]=0;
                    }

                }
            }
        }
    }
return;
}

void mopshoot(mop *y,int map[][dim]){
    int i,j;

    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){

        }
    }
}

void ybulletmove(mop *y,int map[][dim]){
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            if(map[i][j]==-4){
                map[i][j]=0;
                if(map[i+1][j]==0){
                    map[i+1][j]=-4;
                    break;
                }else{
                    map[i+1][j]=map[i-1][j]-2;
                    break;
                    }
            }
        }
    }
return;
}

bool lose(player *x,mop *y,int map[][dim]){
    bool flag=true;
    int i,j,moprow=getmoprow(y);
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            if(map[i][j]==-2){
                flag=false;
            }
        }
    }
    if(moprow==24){
        flag=true;
        }
    return flag;
}
