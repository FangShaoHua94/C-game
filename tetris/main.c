#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>



#define boardrow 21
#define boardcol 10
#define nexts 4

void setmap(int map[boardrow][boardcol]);  // moving tile=1 . blank tile=0 .  fixed tile=2.   bottom limit=-1
void printmap(int map[boardrow][boardcol]);


void square(int nextshape[nexts][nexts]);
void tshape(int nextshape[nexts][nexts]);
void stick(int nextshape[nexts][nexts]);
void z1shape(int nextshape[nexts][nexts]);
void z2shape(int nextshape[nexts][nexts]);
void l1shape(int nextshape[nexts][nexts]);
void l2shape(int nextshape[nexts][nexts]);

void setnextshape(int nextshape[nexts][nexts]);
void generatenextshape(int nextshape[nexts][nexts]);
void printnextshape(int nextshape[nexts][nexts]);

void inputshape(int map[boardrow][boardcol],int nextshape[nexts][nexts]);
void automove(int map[boardrow][boardcol]);
void input(int map[boardrow][boardcol]);
void rotate(int map[boardrow][boardcol]);
void chngtofix(int map[boardrow][boardcol]);

void moveleft(int map[boardrow][boardcol]);
void moveright(int map[boardrow][boardcol]);
void movedown(int map[boardrow][boardcol]);


void delay(unsigned int mseconds);





int main()
{
    int map[boardrow][boardcol];
    int nextshape[nexts][nexts];
    int i=0;


    srand(time(0));
    setmap(map);
    printmap(map);
    printf("---------\n");

    setnextshape(nextshape);
    generatenextshape(nextshape);
    printnextshape(nextshape);
    printf("---------\n");

    inputshape(map,nextshape);
    printmap(map);
    printf("---------\n");

    while(i<9999){
        delay(1000);
        system("cls");
        automove(map);
        printmap(map);
    i++;
    }



    return 0;
}

void setmap(int map[boardrow][boardcol]){
    int i,j,k;
    for(i=0;i<boardrow;i++){
        for(j=0;j<boardcol;j++){
            map[i][j]=0;
        }
    }
    for(k=0;k<boardcol;k++){
        map[boardrow-1][k]=-1;
    }
    return;
}

void printmap(int map[boardrow][boardcol]){
    int i,j;
        for(i=0;i<boardrow;i++){
            for(j=0;j<boardcol;j++){
                printf("%d ",map[i][j]);
            }
            printf("\t aaaaa");
            printf("\n");
        }
        return;
}


void square(int nextshape[nexts][nexts]){
    int i,j;
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            nextshape[i][j]=1;
        }
    }
    return;
}

void tshape(int nextshape[nexts][nexts]){
    int i,j;
    for(i=0;i<2;i++){
        for(j=0;j<3;j++){
            nextshape[1][j]=1;
        }
    }
    nextshape[0][1]=1;
    return;
}

void stick(int nextshape[nexts][nexts]){
        int i,j;
        for(i=0;i<4;i++){
            for(j=0;j<1;j++){
                nextshape[i][j]=1;
            }
        }
        return;
}

void z1shape(int nextshape[nexts][nexts]){
        int i,j;
        for(i=0;i<2;i++){
            for(j=0;j<3;j++){
                nextshape[i][j]=1;
            }
        }
        nextshape[0][2]=0;
        nextshape[1][0]=0;
        return;
}

void z2shape(int nextshape[nexts][nexts]){
        int i,j;
        for(i=0;i<2;i++){
            for(j=0;j<3;j++){
                nextshape[i][j]=1;
            }
        }
        nextshape[0][0]=0;
        nextshape[1][2]=0;
        return;
}

void l1shape(int nextshape[nexts][nexts]){
     int i,j;
        for(i=0;i<3;i++){
            for(j=0;j<2;j++){
                nextshape[i][j]=1;
            }
        }
        nextshape[0][0]=0;
        nextshape[1][0]=0;
        return;
}

void l2shape(int nextshape[nexts][nexts]){
     int i,j;
        for(i=0;i<3;i++){
            for(j=0;j<2;j++){
                nextshape[i][j]=1;
            }
        }
        nextshape[0][1]=0;
        nextshape[1][1]=0;
        return;
}

void setnextshape(int nextshape[nexts][nexts]){
        int i,j;
        for(i=0;i<nexts;i++){
            for(j=0;j<nexts;j++){
                nextshape[i][j]=0;
            }
        }
        return;
}


void generatenextshape(int nextshape[nexts][nexts]){
    int shape;
    shape=rand()%7;

    switch (shape){
    case 0:  //sqaure
        square(nextshape);
        break;
    case 1:  //tshape
        tshape(nextshape);
        break;
    case 2:    //stick
        stick(nextshape);
        break;
    case 3:  // z1shape
        z1shape(nextshape);
        break;
    case 4:  // z2shape
        z2shape(nextshape);
        break;
    case 5:// l1shape
        l1shape(nextshape);
        break;
    case 6: // l2shape
        l2shape(nextshape);
        break;
    }
return;
}

void printnextshape(int nextshape[nexts][nexts]){
        int i,j;
        for(i=0;i<nexts;i++){
            for(j=0;j<nexts;j++){
                printf("%d ",nextshape[i][j]);
            }
            printf("\n");
        }
        return;
}

void inputshape(int map[boardrow][boardcol],int nextshape[nexts][nexts]){
    int i,j;
    for(i=0;i<nexts;i++){
        for(j=0;j<nexts;j++){
            map[i][j]=nextshape[i][j];
        }
    }
    return;
}

void automove(int map[boardrow][boardcol]){
    int i,j;
    for(i=boardrow;i>=0;i--){
        for(j=boardcol;j>=0;j--){
            if(map[i][j]==1){
                if(map[i+1][j]==-1 ||map[i+1][j]==2 ){
                    goto end;
                }else{
                    map[i][j]=0;
                    map[i+1][j]=1;
                }
            }
        }
    }
    end:
    return;
}

void delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void input(int map[boardrow][boardcol]){
    int y;

    y=getch();
    if(y==32){
       // rotate(map);
    }else if (y==224){
        y=getch();//up 72.left 75.right 77.down 80.//
        switch (y){
    case 75:
      //  moveleft(map);
        break;
    case 77:
      //  moveright(map);
        break;
    case 80:
      //  movedown(map);
        break;
        }
    }
    return;
}

void chngtofix(int map[boardrow][boardcol]){
    int i,j;
    for(i=0;i<boardrow;i++){
        for(j=0;j<boardcol;j++){
            if(map[i][j]==1){
                map[i][j]=2;
            }
        }
    }
    return;
}

void moveleft(int map[boardrow][boardcol]){

}
void moveright(int map[boardrow][boardcol]);
void movedown(int map[boardrow][boardcol]);
