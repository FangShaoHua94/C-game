#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define maxsize 100


void setmap(int map[][maxsize],int *col,int *row);
void printmap(int map[][maxsize],int *col,int *row,int cover[][maxsize]);
void setcover(int cover[][maxsize],int *col,int *row);
void setship(int map[][maxsize],int *col,int *row);
void selecttile(int map[][maxsize],int *col,int *row,int cover[][maxsize]);
bool endgame(int map[][maxsize],int *col,int *row);
void testprint(int map[][maxsize],int *col,int *row);


int main()
{
    int map[maxsize][maxsize];
    int cover[maxsize][maxsize];
    int row,col,turn=0;
    srand(time(0));

    setmap(map,&col,&row);
    setcover(cover,&col,&row);
    setship(map,&col,&row);
    system("cls");
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    printmap(map,&col,&row,cover);

    //testprint(map,&col,&row);
    while(endgame(map,&col,&row)!=true){

        selecttile(map,&col,&row,cover);
        system("cls");
        printf("  0 1 2 3 4 5 6 7 8 9\n");
        printmap(map,&col,&row,cover);
        //printf("--------------------\n");
        //testprint(map,&col,&row);

        turn++;
    }
    printmap(map,&col,&row,cover);
    printf("GAME OVER\n");
    printf("number of turn used=%d\n",turn);
return 0;
}

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

void printmap(int map[][maxsize],int *col,int *row,int cover[][maxsize]){
    int i,j;
    for (i=0;i<*row;i++){
        printf("%d ",i);
        for(j=0;j<*col;j++){
           if(cover[i][j]==1){
            printf("O ");
           }else{
               if(map[i][j]==3){
                printf("@ ");
               }
                else {
                    printf("# ");
                }
               }
        //   printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    //printf("-----------------cover\n");
    //for (i=0;i<*row;i++){
      //  for (j=0;j<*col;j++){
         //       printf("%d ",cover[i][j]);
        //    }
     //   printf("\n");
  //  }
    return;
}

void setcover(int cover[][maxsize],int *col,int *row){
    int i,j;
    for (i=0;i<*row;i++){
        for (j=0;j<*col;j++){
                cover[i][j]=1;
            }
    }
    return;

}

void setship(int map[][maxsize],int *col,int *row){
    int numberofship=(rand()%(*col));
    int i,x,y,dir,k,sizeofship;
    bool overlap=false;

    for(k=0;k<numberofship;k++){

    sizeofship=(rand()%3)+2;
    x=rand()%(*row);
    y=rand()%(*col);
    dir=rand()%2;
   // printf("number of ship is %d\n",numberofship);
   // printf("the dir is %d \n",dir);
   // printf("size of ship is %d\n",sizeofship);
   // printf("x is %d, y is %d\n",x,y);
   // printf("-------------------------------------------------\n");

    if(dir==1){               //horizontal//
        for(i=y;i<y+sizeofship;i++){
            if((map[x][i]==2)||(i>(*row))){
                overlap=true;
            }
        }
        if(overlap==false){
            for(i=y;i<y+sizeofship;i++){
                map[x][i]=2;
                }
        }
        overlap=false;
    }

    if(dir==0){               //vertical//
        for(i=x;i<x+sizeofship;i++){
            if((map[i][y]==2)||(i>(*col))){
                overlap=true;
            }
        }
        if(overlap==false){
            for(i=x;i<x+sizeofship;i++){
                map[i][y]=2;
                }
        }
        overlap=false;
    }

    }
    return;
}

void selecttile(int map[][maxsize],int *col,int *row,int cover[][maxsize]){
    int selectrow,selectcol;
    printf("enter the row to bomb:\n");
    scanf("%d",&selectrow);
    printf("enter the col to bomb:\n");
    scanf("%d",&selectcol);

    cover[selectrow][selectcol]=-1;

    if(map[selectrow][selectcol]==2){
        map[selectrow][selectcol]=3;
    }else{
        map[selectrow][selectcol]=4;
        }
    return;
}

bool endgame(int map[][maxsize],int *col,int *row){
    int i,j;
    bool win=true;
     for (i=0;i<*row;i++){
        for (j=0;j<*col;j++){
                if(map[i][j]==2){
                    win=false;
                }
            }
    }
    return win;
}

void testprint(int map[][maxsize],int *col,int *row){
    int i,j;
    for (i=0;i<*row;i++){
        for (j=0;j<*col;j++){
                printf("%d ",map[i][j]);
                }
                printf("\n");
            }
            return;
}
