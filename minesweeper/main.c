#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define maxsize 100

typedef struct{
    int col;
    int row;
    int numofmine;
    int selectrow;
    int selectcol;
}minesweep;

int getnumofmine(minesweep *object);
int getrow(minesweep *object);
int getcol(minesweep *object);
int getselectrow(minesweep *object);
int getselectcol(minesweep *object);


void setrow(minesweep *object,int row);
void setcol(minesweep *object,int col);
void setmine(minesweep *object,int numofmine);
void setselectrow(minesweep *object,int selectrow);
void setselectcol(minesweep *object,int selectcol);

void setmap(int map[][maxsize],int *col,int *row);
void createmine(minesweep *object,int map[][maxsize]);
void setcover(minesweep *object,int cover[][maxsize]);
int setvalue(minesweep *obejct,int map[][maxsize],int row,int col);
void setclue(minesweep *object,int map [][maxsize]);
void reveal(minesweep *object,int map[][maxsize],int cover[][maxsize],int selectrow,int selectcol);
bool checktoreveal(minesweep *object,int map[][maxsize],int cover[][maxsize],int selectrow,int selectcol);

void printmap(minesweep *object,int map[][maxsize],int cover[][maxsize]);
bool lose(minesweep *object,int map[][maxsize],int cover[][maxsize]);
bool win(minesweep *object,int map[][maxsize],int cover[][maxsize]);
void playgame(minesweep *object,int map[][maxsize],int cover[][maxsize]);
void gameover(minesweep *object,int map[][maxsize]);


int main()
{
    int map[maxsize][maxsize];
    int cover[maxsize][maxsize];
    int row,col;
    minesweep object;

    srand(time(0));

    setmap(map,&col,&row);
    setrow(&object,row);
    setcol(&object,col);
    createmine(&object,map);
    setclue(&object,map);
    printmap(&object,map,cover);

    playgame(&object,map,cover);

    return 0;
}

void playgame(minesweep *object,int map[][maxsize],int cover[][maxsize]){
    int round=1,x,y;
    while(((lose(object,map,cover))==false)&&(win(object,map,cover)==false)){

        printf("select the row to reveal:\n");
        scanf("%d",&x);
        printf("select the col to reveal:\n");
        scanf("%d",&y);

        setselectcol(object,y);
        setselectrow(object,x);
        reveal(object,map,cover,x,y);
        while((checktoreveal(object,map,cover,getselectrow(object),getselectcol(object)))==true){
        reveal(object,map,cover,getselectrow(object),getselectcol(object));
        }
        system("cls");
        printmap(object,map,cover);

        printf("Round: %d.\n\n",round);
        round++;
    }
    system("cls");
    gameover(object,map);
    printf("GAME OVER!!!");
    return;

}

//-------------------------------------//
int getnumofmine(minesweep *object){
    return (*object).numofmine;
}

int getrow(minesweep *object){
    return (*object).row;
}

int getcol(minesweep *object){
    return (*object).col;
}
int getselectrow(minesweep *object){
    return (*object).selectrow;
}
int getselectcol(minesweep *object){
    return (*object).selectcol;
}

//------------------------------------//
void setrow(minesweep *object,int row){
    object->row=row;
    return;
}

void setcol(minesweep *object,int col){
    object->col=col;
    return;
}

void setmine(minesweep *object,int numofmine){
    object->numofmine=numofmine;
    return;
}

void setselectrow(minesweep *object,int selectrow){
    object->selectrow=selectrow;
    return;
}

void setselectcol(minesweep *object,int selectcol){
    object->selectcol=selectcol;
    return;
}
//--------------------------------------------------------------//
void setmap(int map[][maxsize],int *col,int *row){
    int i,j;
    printf("enter the col of the map:\n");
    scanf("%d",col);
    printf("enter the row of the map:\n");
    scanf("%d",row);

    for (i=0;i<*row;i++){
        for (j=0;j<*col;j++){
                map[i][j]=0;
            }
    }
    return;
}

void createmine(minesweep *object,int map[][maxsize]){
    int i,numofmine,area,randrow,randcol;

    int row=getrow(object),col=getcol(object);
    area=row*col;

    numofmine=(rand()%(area/4));

    for (i=0;i<numofmine;i++){
            randrow=rand()%(row-1);
            randcol=rand()%(col-1);
            map[randrow][randcol]=-1;
    }
return;
}

void setcover(minesweep *object,int cover[][maxsize]){
    int i,j;
    int row=getrow(object),col=getcol(object);
    for (i=0;i<row;i++){
        for (j=0;j<col;j++){
            cover[i][j]=0;
        }
    }
return;
}

void printmap(minesweep *object,int map[][maxsize],int cover[][maxsize]){
    int i,j,countmine=0;
    int row=getrow(object),col=getcol(object);
    printf("  ");
    for(i=1;i<col+1;i++){
        printf("%d ",i);
    }
    printf("\n");
    for(i=0;i<col+2;i++){
        printf("--");
    }
    printf("\n");
    for (i=0;i<row;i++){
        for (j=0;j<col;j++){
            if(j==0){
                printf("%d|",i+1);
            }
            if(map[i][j]==-1){
            countmine++;
            }
            if(cover[i][j]==0){
                printf("? ");
            }else {
                if(map[i][j]==-1){
                printf("* ");
            }else {
                printf("%d ",map[i][j]);
                }
            }
        }
        printf("\n");
}
printf("the number of mine is %d\n",countmine);
setmine(object,countmine);

return;
}

void reveal(minesweep *object,int map[][maxsize],int cover[][maxsize],int selectrow,int selectcol){
     int i,j;
     cover[selectrow-1][selectcol-1]=1;

     int upcol=selectcol-2,downcol=selectcol,uprow=selectrow-2,downrow=selectrow;

     if(map[selectrow-1][selectcol-1]==0){
        if(upcol<0){
            upcol=selectcol-1;
        }
        if(downcol>getcol(object)){
            downcol=selectcol-1;
        }
        if(uprow<0){
            uprow=selectrow-1;
        }
        if(downrow>getrow(object)){
            downrow=selectrow-1;
        }

        for(i=uprow;i<=downrow;i++){
            for(j=upcol;j<=downcol;j++){
                cover[selectrow-1][selectcol-1]=2;
                if((map[i][j]==0)&&(cover[i][j]==2)){
                    cover[i][j]=2;
                    }else {
                    cover[i][j]=1;
                        }
            //    if((map[i][j]==0)&&(cover[i][j]==1)){
              //      reveal(object,map,cover,i+1,j+1);}

            }
        }
     }
     return;
}

bool checktoreveal(minesweep *object,int map[][maxsize],int cover[][maxsize],int selectrow,int selectcol){
    int i,j,row=getrow(object),col=getcol(object);
    bool flag=false;
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(map[i][j]==0&&cover[i][j]==1){
                flag=true;
                setselectrow(object,i+1);
                setselectcol(object,j+1);
                break;
            }
        }
    }
    return flag;
}

int setvalue(minesweep *object,int map[][maxsize],int row,int col){
    int i,j,counter=0;
    int upcol=col-1,downcol=col+1,uprow=row-1,downrow=row+1;
    if(upcol<0){
        upcol=col;
    }
    if(downcol>getcol(object)){
        downcol=col;
    }
    if(uprow<0){
        uprow=row;
    }
    if(downrow>getrow(object)){
        downrow=row;
    }
    for(i=uprow;i<=downrow;i++){
        for(j=upcol;j<=downcol;j++){
            if(map[i][j]==-1){
                counter++;
            }
        }
    }
    return counter;
}

void setclue(minesweep *object,int map [][maxsize]){
    int i,j,val;
    int row=getrow(object),col=getcol(object);

    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(map[i][j]!=-1){
                val=setvalue(object,map,i,j);
                map[i][j]=val;
            }
        }
    }
return;
}

bool lose(minesweep *object,int map[][maxsize],int cover[][maxsize]){
    int i,j;
    bool flag=false;
    int row=getrow(object),col=getcol(object);
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if((map[i][j]==-1)&&(cover[i][j]>=1)){
                flag=true;
            }
        }
    }
return flag;
}

bool win(minesweep *object,int map[][maxsize],int cover[][maxsize]){
    int i,j;
    bool flag=true;
    int row=getrow(object),col=getcol(object);
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if((map[i][j]!=-1)&&(cover[i][j]==0)){
                flag=false;
            }
        }
    }
return flag;
}

void gameover(minesweep *object,int map[][maxsize]){
    int i,j;
        int row=getrow(object),col=getcol(object);
        for (i=0;i<row;i++){
            for (j=0;j<col;j++){
                    if(map[i][j]==-1){
                         printf("* ");
                    }else{
                        printf("%d ",map[i][j]);
                    }
            }
            printf("\n");
    }
return;
}

