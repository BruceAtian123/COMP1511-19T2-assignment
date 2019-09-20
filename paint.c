// Assignment 1 19T2 COMP1511: CS Paint
// paint.c
//
// This program was written by Patrick(Jinming) Dong (z5211275)
// on 23/06/2019
//
// Version 1.0.0 (2019-06-22): Assignment released.

#include <stdio.h>
#include <stdlib.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define DARK 1
#define GREY 2
#define LIGHT 3
#define WHITE 4


// Provided helper functions:
// Print out the canvas.
void printCanvas(int canvas[N_ROWS][N_COLS]);
void drawLine(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int shade);
void drawRectangle(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int shade);
void copyPaste(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int row3, int col3, int shade);
void setBlankCanvas(int canvas[N_ROWS][N_COLS]);
void additiveBrush(int canvas[N_ROWS][N_COLS], int shade_canvas[3][3], int row4, int col4, int row5, int col5);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int main(void) {
    int canvas[N_ROWS][N_COLS];
    int shade_canvas[3][3];

    setBlankCanvas(canvas);

    int instruction;
    int instruction1;
    int row1, col1, row2, col2, row3, col3, row4, col4, row5, col5;
    int shade = BLACK;
    int s1 = BLACK;

    while (scanf("%d", &instruction) == 1){
      if((instruction==1)||(instruction==2)){
	scanf("%d", &row1);
	scanf("%d", &col1);
	scanf("%d", &row2);
	scanf("%d", &col2);
      }
      if(instruction==3){
	scanf("%d", &shade);
	if(shade > 4||shade < 0){
	  shade = WHITE;
	  continue;
	}
      }
      if(instruction==4){
	scanf("%d", &row1);
	scanf("%d", &col1);
	scanf("%d", &row2);
	scanf("%d", &col2);
	scanf("%d", &row3);
	scanf("%d", &col3);
    }
      if(instruction==5){
      for(int r = 0;r<3;r++){
	for(int c = 0;c<3;c++){
	  scanf("%d", &s1);
	  shade_canvas[r][c] = s1;
	}
      }

      scanf("%d", &instruction1);
      if(instruction1 == 1){
	scanf("%d", &row4);
	scanf("%d", &col4);
	scanf("%d", &row5);
	scanf("%d", &col5);
      }
      else if ((row4-1 < 0)||(row4+1 > N_ROWS)||(col4-1 < 0)||(col4+1 > N_COLS)||(row5-1 < 0)||(row5+1 > N_ROWS)||(col5-1 < 0)||(col5+1>N_COLS)){
	continue;
      }
      else{
	continue;
      }
      }
    if (instruction == 1){
      if((row1 >= 0 && row1 < N_ROWS)&&(row2 >= 0 && row2 < N_ROWS)&&(row1 == row2 || col1 == col2)){
	drawLine(canvas, row1, col1, row2, col2, shade);
      }
    }
    if(instruction == 2){
      if((row1 >= 0 && row1 < N_ROWS)&&(row2 >= 0 && row2 < N_ROWS)){
	drawRectangle(canvas, row1, col1, row2, col2, shade);
      }
    }
    if(instruction == 4){
      if((row1 >= 0 && row1 < N_ROWS)&&(row2 >= 0 && row2 < N_ROWS)){
	copyPaste(canvas, row1, col1, row2, col2, row3, col3, shade);
      }
    }
    if(instruction == 5){
      additiveBrush(canvas,shade_canvas,row4,col4,row5,col5);
    }
    printCanvas(canvas);
}

}


// ADD CODE FOR YOUR FUNCTIONS HERE
void drawLine(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int shade) {
  if((row1==row2)&&(col1==col2)){
    canvas[row1][col1] = shade;
  }
  if((row1==row2)&&(col1!=col2)){
    int col = col1<col2?col1:col2;
    int targetcol = col1>col2?col1:col2;
    while(col<targetcol){
      canvas[row1][col] = shade;
      col++;
    }
  }
  if((row1!=row2)&&(col1==col2)){
    int row = row1<row2?row1:row2;
    int targetrow = row1>row2?row1:row2;
    while(row<targetrow){
      canvas[row][col1] = shade;
      row++;
    }
  }
  if(col1!=col2){
  int gradient = (row2-row1)/(col2-col1);
  if((gradient==1)||(gradient==-1)){
      int row = row1<row2?row1:row2;
      int targetrow = row1>row2?row1:row2;
      int col = col1<col2?col1:col2;
      while(row<=targetrow){
	canvas[row][col] = shade;
	row++;
	col++;
      }
    }
  }
  }

void drawRectangle(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int shade){
  if((row1==row2)&&(col1==col2)){
    canvas[row1][col1] = shade;
  }
  else{
    int row = row1<row2?row1:row2;
    int targetrow = row1>row2?row1:row2;
    int col = col1<col2?col1:col2;
    int targetcol = col1>col2?col1:col2;
    
    int r = row;
    while(r<=targetrow){
        int c = col;
        while(c<=targetcol){
            canvas[r][c] = shade;
            c++;
        }
        r++;
    }
  }
}

void copyPaste(int canvas[N_ROWS][N_COLS], int row1, int col1, int row2, int col2, int row3, int col3, int shade){
  int rowlength = abs(row2-row1);
  int collength = abs(col2-col1);
  if((row3+rowlength>0)&&(row3+rowlength<N_ROWS)&&(col3+collength>0)&&(col3+collength<N_COLS)){
  for(int r = row3;r<=row3+rowlength;r++){
    for(int c = col3;c<=col3+collength;c++){
      canvas[r][c] = shade;
    }
  }
  }
}


// Prints the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
//
// You should not need to change the printCanvas function.
void printCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}

void additiveBrush(int canvas[N_ROWS][N_COLS], int shade_canvas[3][3], int row4, int col4, int row5, int col5){
  // Deal with single point
  if((row4==row5)&&(col4==col5)){
    int r = 0;
    int c = 0;
    int startr = row4-1;
    int startc = col4-1;
    while(r<3){
      while(c<3){
	if(canvas[startr][startc]+shade_canvas[r][c]<0){
	  canvas[startr][startc] = 0;
	}
	if(canvas[startr][startc]+shade_canvas[r][c]>4){
	  canvas[startr][startc] = 4;
	}
	else{
	  canvas[startr][startc]+=shade_canvas[r][c];
	}
	c++;
	startc++;
      }
      r++;
      startr++;

      startc = col4-1;
      c = 0;
}
}
    //horizontal line

    if ((row4 == row5) && (col4 != col5)) {
        
        int sc = col4;
        int sr = row4; 
        int ec = col5;
        

        int i = 0; 

        while (sc <= ec) {
            
            while (i < 3) {
            
                canvas[sr - 1][sc + 1] += shade_canvas[i][2];

                //correct the color
                if(canvas[sr - 1][sc + 1] > 4) {
                
                    canvas[sr - 1][sc + 1] = 4;
                }

                if(canvas[sr - 1][sc + 1] < 0) {
                
                    canvas[sr - 1][sc + 1] = 0;
                }

                sr += 1;
                i++;
            }

            sc += 1;
            sr = row4; 
            i = 0; 
        }

        int k = 0;

        sc = col4;
        sr = row4; 

        while (sc <= ec) {
            
            while (k < 3) {
            
                canvas[sr - 1][sc] += shade_canvas[k][1];
                
                //correct the color
                if (canvas[sr - 1][sc] > 4) {
                    
                    canvas[sr - 1][sc] = 4;
                }

                if (canvas[sr - 1][sc] < 0) {
                
                    canvas[sr - 1][sc] = 0;
                }

                sr += 1;
                k++;
            }

            sc += 1;
            sr = row4; 
            k = 0; 

        }

        int h = 0;

        sc = col4;
        sr = row4; 

        while (sc - 1 <= ec - 1) {
            
            while(h < 3) {
            
                canvas[sr - 1][sc - 1] += shade_canvas[h][0];

                //correct the color
                if (canvas[sr - 1][sc - 1] > 4) {
                    
                    canvas[sr - 1][sc - 1] = 4;
                }

                if (canvas[sr - 1][sc - 1] < 0) {
                    
                    canvas[sr - 1][sc - 1] = 0;
                }


                sr += 1;
                h++;
            }

            sc += 1;
            sr = row4; 
            h = 0; 

        }
    }
    
    //veritcal line
    
    if ((col4 == col5) && (row4 != row5)) {
    
        int sc = col4;
        int sr = row4; 
        int er = row5; 

        int i = 0; 

    

        while (sr + 1 <= er + 1) {
            
            while (i < 3) {
            
                canvas[sr + 1][sc - 1] += shade_canvas[2][i];

                if (canvas[sr + 1][sc - 1] > 4) {
                    
                    canvas[sr + 1][sc -1] = 4;
                }

                if (canvas[sr + 1][sc - 1] < 0) {
                    
                    canvas[sr + 1][sc - 1] = 0;
                }

                sc += 1;
                i++;
            }

            sr += 1;
            sc = col4; 
            i = 0; 
        }



        int k = 0;

        sc = col4;
        sr = row4; 

        while (sr <= er) {
            
            while(k < 3) {
            
                canvas[sr][sc - 1] += shade_canvas[1][k];

                //correct the color
                if(canvas[sr][sc - 1] > 4) {
                    
                    canvas[sr][sc -1] = 4;
                }

                if(canvas[sr][sc - 1] < 0) {
                    
                    canvas[sr][sc - 1] = 0;
                }

                sc += 1;
                k++;
            }

            sr += 1;
            sc = col4; 
            k = 0; 
        }

        int h = 0;

        sc = col4;
        sr = row4; 

        while (sr - 1 <= er - 1) {
            
            while (h < 3) {
            
                canvas[sr - 1][sc - 1] += shade_canvas[0][h];


                //correct the color
                if (canvas[sr - 1][sc - 1] > 4) {
                    
                    canvas[sr - 1][sc -1] = 4;
                }

                if (canvas[sr - 1][sc - 1] < 0) {
                    
                    canvas[sr - 1][sc - 1] = 0;
                }

                sc += 1;
                h++;
            }

            sr += 1;
            sc = col4; 
            h = 0; 
        }
    }
}


// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
//
// You should not need to change the setBlankCanvas function.
void setBlankCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}

