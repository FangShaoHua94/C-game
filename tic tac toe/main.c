#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define dim 3


void readmap(int map[][dim]);
void printmap(int map[][dim]);
void p1selectcell(int map[][dim]);
void p2selectcell(int map[][dim]);
bool gameover(int map[][dim]);

int main()
{
    int map[dim][dim];
    readmap(map);
    printmap(map);
    while(gameover(map)==false){

    p1selectcell(map);
    system("cls");
    printmap(map);
    if(gameover(map)==true){
        break;
    }

    p2selectcell(map);
    printmap(map);

    }
    printf("game over!");
    return 0;
}

void readmap(int map[][dim]){
    int i,j;
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            map[i][j]=0;
        }
    }

return;
}

void printmap(int map[][dim]){
    int i,j;
      for(i = 0; i < dim; i++) {
        for(j = 0; j < dim; j++) {
            if(map[i][j]==0){
                printf("| ");
            }else if (map[i][j]==1){
            printf("|O");
            }else {
            printf("|X");
            }

            }
        printf("|\n");
    }
return;
}

void p1selectcell(int map[][dim]){
    int row,col;
    printf("player 1 select cell. enter row and column:\n");
    scanf("%d%d",&row,&col);
    if(map[row][col]==0){
    map[row][col]=1;
    }else{
    printf("the cell is taken.\n");
    p1selectcell(map);
    }
    return;
}

void p2selectcell(int map[][dim]){
    int row,col;
    printf("player 2 select cell. enter row and column:\n");
    scanf("%d%d",&row,&col);
    if(map[row][col]==0){
    map[row][col]=2;
    }else{
    printf("the cell is taken.\n");
    p2selectcell(map);
    }
    return;
}

bool gameover(int map[][dim]){
    int i,j,x=0,y=2;
    bool flag=true;
    for(i=0;i<dim+1;i++){  //full board
        for(j=0;j<dim+1;j++){
            if(map[i][j]==0){
                flag=false;
            }
        }
    }

    for(i=0;i<3;i++){     //row win
        if((map[i][0]!=0)&&(map[i][0]==map[i][1])&&(map[i][0]==map[i][2])){
            flag=true;
        }
    }

    for(i=0;i<3;i++){    //col win
        if((map[0][i]!=0)&&(map[0][i]==map[1][i])&&(map[0][i]==map[2][i])){
            flag=true;
        }
    }

    if((map[x][x]!=0)&&(map[x][x]==map[x+1][x+1])&&(map[x][x]==map[x+2][x+2])){  //diagoanl win
        flag=true;
    }

    if((map[y-1][y-1]!=0)&&(map[y-2][y]==map[y-1][y-1])&&(map[y-1][y-1]==map[y][y-2])){  //diagoanl win
        flag=true;
    }

    return flag;
}
