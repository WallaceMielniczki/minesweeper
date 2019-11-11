#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show(char **camp, int size, int gameover){
    printf("+");
    for (int i = 0; i < size; ++i){
        printf(" %i", i);
    }
    printf("\n");

    for (int i = 1; i < size+1; ++i){
        
        printf("%i", i-1);
        for (int j = 1; j < size+1; ++j){
           
            if(gameover){
                printf(" %c", camp[i][j]);
            }else {
                if(camp[i][j] == '*'){
                    printf(" .");
                }else {
                    printf(" %c", camp[i][j]);
                }
            }
        }
        printf("\n");
    }
}

char **allocate_matrix(int size){
    char **v = (char**)malloc((sizeof(char*)*size)+1);
    for (int i = 0; i < size; ++i){
        v[i] = (char*)malloc((sizeof(char)*size)+1);
        v[i][size] = '\0';
    }

    v[size] = '\0';
    return v;
}

void ini(char **camp, int size){
    srand((unsigned) time(NULL));

    for (int i = 0; i < size+2; ++i){
        for (int j = 0; j < size+2; ++j){
            if(i>0 && i < size+1 && j > 0 && j < size+1){
                camp[i][j] = '.';
            }else {
                camp[i][j] = '#';
            }
        }
    }
   
    for(int i=0; i<size;){
        int pos_i = rand()%size+2;
        int pos_j = rand()%size+2;
        
        if(camp[pos_i][pos_j] == '.'){
            camp[pos_i][pos_j] = '*';
            i++;
        }
    }
}

int count_bombs(int l, int c, char **camp){
    int bombs = 0;
    for (int i = l-1; i <= l+1; ++i){
        for (int j = c-1; j <= c+1; ++j){
            if(camp[i][j] == '*'){
                bombs++;
            }
        }
    }

    return bombs;
}

int count_filled(char **camp, int size){

    int counter = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if(camp[i][j]-48 >= 0 && camp[i][j]-48 <= 9){
                counter++;
            }
        }
    }

    return counter;
}

void hint(char **camp, int l, int c){

    int continua;

    do{
        for (int i = l-1; i <= l+1; ++i){
            for (int j = c-1; j <= c+1; ++j){
                continua = 0;
                if(camp[i][j] != '#'){
                    if(count_bombs(i, j, camp) == 0 && camp[i][j] < 48 || camp[i][j] > 57){
                        continua = 1;
                        camp[i][j] = '0';
                        hint(camp, i, j);
                    }else {
                        camp[i][j] = count_bombs(i, j, camp)+48;
                    }
                }
            }
        }
    }while(continua);
}

int main()
{   

    printf("=========================================================\n");
    printf("=                                                       =\n");
    printf("=                      MINESWEEPER                      =\n");
    printf("=                                                       =\n");
    printf("=========================================================\n\n");
   
    int size;
    int gameover = 0;
    
    printf("DIGITE A ÁREA DO CAMPO: ");
    scanf("%i", &size);
    printf("\n");

    char **camp = allocate_matrix(size+2);

    ini(camp, size);
    show(camp, size, gameover);
   
    while(!gameover){

        int x;
        int y;

        printf("\nDIGITE A LINHA: ");
        scanf("%i", &y);

        printf("DIGITE A COLUNA: ");
        scanf("%i", &x);

        system("clear");
       
        if(camp[y+1][x+1] == '*'){

            gameover = 1;
        }else {

            int bombs = count_bombs(y+1, x+1, camp);
            
            if(bombs == 0){
                hint(camp, y+1, x+1);

            }else {

                camp[y+1][x+1] = bombs;
            }
        }

        if(count_filled(camp, size+2) == (size*size)-size){
            gameover = 2;
        }

        show(camp, size, gameover);
    }

    switch(gameover){
        case 1:
            printf("\nGAMEOVER!\n");
            break;

        case 2:
            printf("\nYOU WINS\n");
            break;
    }

    return 0;
}