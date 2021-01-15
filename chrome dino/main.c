#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <conio.h>

#define col 40
#define row 10
#define heightlimit 3
#define secheightlimit 1

typedef struct{
    bool squat;
    bool falling;
    bool jumping;
    bool doublejump;
}object;


void setmap(int map[row][col]);
void printmap(int map[row][col]);

void setobs(int map[row][col]);
void moveobs(int map[row][col]);

void setdino(int map[row][col]);
void movedino(int map[row][col],object *dino);

bool getsquat(object *dino);
void setsquat(object *dino,bool x);
bool getfalling(object *dino);
void setfalling(object *dino,bool x);
bool getjumping(object *dino);
void setjumping(object *dino,bool x);
bool getdoublejump(object *dino);
void setdoublejump(object *dino,bool x);

void jump(int map[row][col],object *dino);
void doublejump(int map[row][col],object *dino);
void falling(int map[row][col],object *dino);
void squat(int map[row][col],object *dino);
void resetsquat(object *dino,int map[row][col]);

void dinomotion(int map[row][col],object *dino);

void delay(unsigned int mseconds);

int main()
{
    int map[row][col];
    object *dino=(object*)malloc(sizeof(object));

    int i=0,j,k=0;

    srand(time(0));
    setmap(map);
    //setobs(map);
    setdino(map);
    setsquat(dino,false);
    setfalling(dino,false);
    setjumping(dino,false);
    setdoublejump(dino,false);

    printmap(map);
    j=(rand()%8)+6;

    while(i<999){

        delay(500);
        resetsquat(dino,map);
        if(kbhit()){
            movedino(map,dino);
            system("cls");
        }
        dinomotion(map,dino);
        system("cls");
        if(k==j){
           // setobs(map);
            j=(rand()%8)+8;
            k=0;
        }
        moveobs(map);
        printmap(map);
        if(getfalling(dino)==true){
            printf("falling is true\n");
        }
        if(getsquat(dino)==true){
            printf("squat is true\n");
        }
        if(getjumping(dino)==true){
            printf("jumping is true\n");
        }
        if(getdoublejump(dino)==true){
            printf("double jump is true\n");
        }
        i++;
        k++;

    }

    free(dino);
    return 0;
}

bool getsquat(object *dino){
    return (*dino).squat;
}

void setsquat(object *dino,bool x){
    dino->squat=x;
    return;
}

bool getfalling(object *dino){
    return (*dino).falling;
}

void setfalling(object *dino,bool x){
    dino->falling=x;
    return;
}

bool getjumping(object *dino){
    return (*dino).jumping;
}

void setjumping(object *dino,bool x){
    dino->jumping=x;
    return;
}

bool getdoublejump(object *dino){
    return (*dino).doublejump;
}

void setdoublejump(object *dino,bool x){
    dino->doublejump=x;
    return;
}

void setmap(int map[row][col]){
    int i,j;

    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            map[i][j]=0;
        }
    }
    return;
}

void printmap(int map[row][col]){
    int i,j;
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    return;
}

void setobs(int map[row][col]){
    int i,j,size,air;
    size=(rand()%3)+1;
    air=rand()%2;
    if (air==0){
        air=3;
    }

    for(i=row-air;i>=row-air-1;i--){
        for(j=col-1;j>=col-size;j--){
            map[i][j]=1;
        }
    }
return;
}

void moveobs(int map[row][col]){
    int i,j;
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(map[i][j]==1){
                map[i][j]=0;
                if(j-1>=0){
                map[i][j-1]=1;
                }
            }
        }
    }
return;
}

void setdino(int map[row][col]){
    map[7][5]=2;
    map[7][4]=2;
    map[8][5]=2;
    map[8][4]=2;
    map[9][5]=2;
    map[9][4]=2;
    return;
}

void movedino(int map[row][col],object *dino){
    int x;

    x=getch();
    if(x==32){
        if(getjumping(dino)==true){
            setdoublejump(dino,true);
            setjumping(dino,false);
        }else if((getfalling(dino)==false)&&(getdoublejump(dino)==false)){
            setjumping(dino,true);
            }
    }else if (x==224){
        x=getch();
        if(x==80){
            if((getjumping(dino)==true)||(getdoublejump(dino)==true)){
                setjumping(dino,false);
                setdoublejump(dino,false);
                setfalling(dino,true);
            }else if(getsquat(dino)==false){
                setsquat(dino,true);
            }
        }
    }
    return;
}


void resetsquat(object *dino,int map[row][col]){
    setsquat(dino,false);
    map[7][5]=2;
    map[7][4]=2;
    return;
}

void jump(int map[row][col],object *dino){
    bool x=getjumping(dino);
    int i,j;

    if(x==true){
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                if(map[i][j]==2){
                    if(i<heightlimit){
                        setjumping(dino,false);
                        setfalling(dino,true);
                        return;
                    }else{
                    map[i][j]=0;
                    map[i-1][j]=2;
                    }
                }
            }
        }
    }
return;
}

void doublejump(int map[row][col],object *dino){
    bool z=getdoublejump(dino);
    int i,j;

    if(z==true){
      for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                if(map[i][j]==2){
                    if(i+1==secheightlimit){
                        setdoublejump(dino,false);
                        setjumping(dino,false);
                        setfalling(dino,true);
                        return;
                    }else{
                    map[i][j]=0;
                    map[i-1][j]=2;
                    }
                }
            }
        }
    }
return;
}

void falling(int map[row][col],object *dino){
    int i,j;
    bool x=getfalling(dino);

    if(x==true){
        for(i=row-1;i>0;i--){
            for(j=0;j<col;j++){
                if(map[i][j]==2){
                    if(i+1<row){
                        map[i][j]=0;
                        map[i+1][j]=2;
                            }else{
                                setfalling(dino,false);
                                return;
                        }
                    }
                }
            }
        }
return;
}

void squat(int map[row][col],object *dino){
    bool x=getsquat(dino);

    if(x==true){
        map[7][5]=0;
        map[7][4]=0;
    }
return;
}

void dinomotion(int map[row][col],object *dino){
    falling(map,dino);
    jump(map,dino);
    doublejump(map,dino);
    squat(map,dino);
    return;
}

void delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
