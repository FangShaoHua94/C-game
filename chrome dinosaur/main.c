#include <stdio.h>
#include <stdlib.h>


#define dim 30

void setmap(int map[][dim]);
void printmap(int map[][dim]);

int main()
{
    int map[dim][dim];
    setmap(map);
    printmap(map);
    return 0;
}

void setmap(int map[][dim]){
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
    for(i=0;i<dim;i++){
        for(j=0;j<dim;j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
return;
}
