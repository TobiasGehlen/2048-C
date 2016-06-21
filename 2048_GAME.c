#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void show_game (int game[][4], int *score){
  int i, j;
  printf("\tScore: %d\n", *score);
  for (i=0; i<4; i++){
    for (j=0; j<4; j++)
      printf("%5d", game[i][j]);
    printf("\n");
  }
  printf("\n");
}

void start_game (int game[][4]) {
  srand(time(NULL));
  int e = rand()%16;
  int i, j, t;
  i = e/4;
  j = e%4;
  for (t=0; t<2; t++){
    while (game[i][j] != 0){
      e = rand()%16;
      i = e/4;
      j = e%4;
    }
    game[i][j]=2;
  }
}

void new_element(int game[][4]) {
  srand(time(NULL));
  int e = rand()%16;
  int i, j;
  i = e/4;
  j = e%4;
  while (game[i][j] != 0){
    e = rand()%16;
    i = e/4;
    j = e%4;
  }
  srand(time(NULL));
  int k = rand()%18;
  if(k>6) game[i][j]=2;
  else    game[i][j]=4;
}

int move_right (int game[][4]){
  int i, j, b, k=0;
  for (i=0; i<4; i++){
    for (j=3; j>0; j--){
      if ((game[i][j]) == 0){
        if (j>1) b = (j-1);
        else if (j==1) b=j;
        while ((game[i][b]) == 0 && b>0) b--;
        if ((game[i][b]) != 0){
          game [i][j] = game[i][b];
          game [i][b] = 0;
          k++;
        }
      }
    }
  }
  return k;
}

int move_left (int game[][4]){
  int i, j, b, k=0;
  for (i=0; i<4; i++){
    for (j=0; j<3; j++){
      if ((game[i][j]) == 0){
        if (j<2) b = (j+1);
        else if (j==2) b=j;
        while ((game[i][b]) == 0 && b<3) b++;
        if ((game[i][b]) != 0){
          game [i][j] = game[i][b];
          game [i][b] = 0;
          k++;
        }
      }
    }
  }
  return k;
}

int move_up (int game[][4]){
  int i, j, b, k=0;
  for (j=0; j<4; j++){
    for (i=0; i<3; i++){
      if ((game[i][j]) == 0){
        if (i<2) b = (i+1);
        else if (i=2) b = i;
        while ((game[b][j]) == 0 && b<3) b++;
        if ((game[b][j]) != 0){
          game [i][j] = game[b][j];
          game [b][j] = 0;
          k++;
        }
      }
    }
  }
  return k;
}

int move_down (int game[][4]){
  int i, j, b, k=0;
  for (j=0; j<4; j++){
    for (i=3; i>0; i--){
      if ((game[i][j]) == 0){
        if (i>1) b = (i-1);
        else if (i=1) b = i;
        while ((game[b][j]) == 0 && b>0) b--;
        if ((game[b][j]) != 0){
          game [i][j] = game[b][j];
          game [b][j] = 0;
          k++;
        }
      }
    }
  }
  return k;
}

int add_right (int game[][4], int *score){
  int i, j, k=0;
  for (i=3; i>=0; i--){
    for (j=3; j>=1; j--){
      if ((game[i][(j-1)]) == (game[i][j])){
        if ((game[i][(j-1)]) != 0 && (game[i][j]) != 0){
          game[i][j] += game[i][(j-1)];
          game[i][(j-1)] = 0;
          *score += game[i][j];
          k++;
        }
      }
    }
  }
  return k;
}

int add_left (int game[][4], int *score){
  int i, j, k=0;
  for (i=0; i<4; i++){
    for (j=0 ;j<3; j++){
      if ((game[i][(j+1)]) == (game[i][j])){
        if ((game[i][(j+1)]) != 0 && (game[i][j]) != 0){
          game[i][j] += game[i][(j+1)];
          game[i][(j+1)] = 0;
          *score += game[i][j];
          k++;
        }
      }
    }
  }
  return k;
}

int add_up (int game[][4], int *score){
  int i, j, k=0;
  for (j=0; j<4; j++){
    for (i=0; i<3; i++){
      if ((game[i][j]) == (game[(i+1)][j])){
        if ((game[i][j]) != 0 && (game[(i+1)][j]) != 0){
          game[i][j] += game[(i+1)][j];
          game[(i+1)][j] = 0;
          *score += game[i][j];
          k++;
        }
      }
    }
  }
  return k;
}

int add_down (int game[][4], int *score){
  int i, j, k=0;
  for (j=0; j<4; j++){
    for (i=3; i>0; i--){
      if ((game[i][j]) == (game[(i-1)][j])){
        if ((game[i][j]) != 0 && (game[(i-1)][j]) != 0){
          game[i][j] += game[(i-1)][j];
          game[(i-1)][j] = 0;
          *score += game[i][j];
          k++;
        }
      }
    }
  }
  return k;
}

int won_or_lost (int game[][4]){
  int i, j, v=-1;
  for (i=0; i<4; i++){
    for (j=0; j<4; j++)
      if ((game[i][j]) == 2048) v = 1;
  }
  for (i=0; i<4; i++){
    for (j=0; j<4; j++)
      if ((game[i][j])==0) v=0;
  }
  if (v!=0){
    for (i=0; i<4; i++){
      for(j=0; j<3; j++)
        if ((game[i][j])==(game[i][(j+1)])) v = 0;
    }
    for (j=0; j<4; j++){
      for(i=0; i<3; i++)
        if ((game[i][j])==(game[(i+1)][j])) v = 0;
    }
  }
  return v;
}

int main() {
  int board[4][4]={{0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0}};
  int win=0, k=0, *score;
  score = malloc (sizeof(int));
  *score = 0;
  char move;
  printf("\nUse 'w, a, s, d' to move and 'q' to quit\n\n");
  start_game (board);
  show_game(board, score);
  while (win != (-1) && win!= (1)){
      k = 0;
      scanf("%c", &move);
      if (move == 'd' || move == 'D') {
        printf("Move right\n");
        k += move_right(board);
        k += add_right(board, score);
        k += move_right(board);
        if (k>0) new_element(board);
        show_game(board, score);
      }
      else if (move == 'a' || move == 'A') {
        printf("Move left\n");
        k += move_left(board);
        k += add_left(board, score);
        k += move_left(board);
        if (k>0) new_element(board);
        show_game(board, score);
      }
      else if (move == 'w' || move == 'W') {
        printf("Move up\n");
        k += move_up(board);
        k += add_up(board, score);
        k += move_up(board);
        if (k>0) new_element(board);
        show_game(board, score);
      }
      else if (move == 's' || move == 'S') {
        printf("Move down\n");
        k += move_down(board);
        k += add_down(board, score);
        k += move_down(board);
        if (k>0) new_element(board);
        show_game(board, score);
      }
      else if (move == 'q' || move == 'Q') {
        printf("QUIT\n\nFinal Score: %d\n\n", *score);
        return 0;
      }
      win = won_or_lost(board);
  }
  if     ((won_or_lost(board)) == ( 1)) printf("YOU WON!\n\n");
  else if((won_or_lost(board)) == (-1)) printf("YOU LOST\n\n");
  else if((won_or_lost(board)) == ( 0)) return 0;

  return 0;
}
