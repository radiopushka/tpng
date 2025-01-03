#include "curses/curses.c"
#include <stdlib.h>
#include <string.h>
#include "png.c"

int main(int argn,char* argv[]){

   if(argn<2){
    printf("please provide a PNG file\n");
    return -1;
  }


  unsigned char* matrix;
  unsigned char* matrix_end;
  int width,height,bytes;
  int status=read_png_file(argv[1],&width,&height,&bytes,&matrix,&matrix_end);

  if(status==-1){
    return -1;
  }

  int scalex=1;
  



  int twidth,theight;
  
  term_size(&twidth,&theight);

  if(width>twidth){
    scalex=width/twidth+2;
  }

  int scaley=scalex*2;

  printf("image:\n");

  unsigned char* start;
  int col_counter=0;
  int row_counter=0;
  int count=0;
  int width_count=0;
  for(start = matrix ; start < matrix_end; start=start+bytes){
    if((width_count<twidth) && (col_counter%scalex == 0) && (row_counter%scaley == 0)){
      
      fpixel(*start,*(start+1),*(start+2));
      width_count++;

    }
    count++;
    col_counter++;
    if(col_counter>=width){
      width_count=0;
      if(row_counter%scaley == 0){
        fclear();
        printf("\n");
      }
      row_counter++;
      col_counter=0;
    }
  }

  
  free(matrix);
  fclear();
  printf("\n");
  printf("%d pixels %d %d\n",count,width,height);

  

  return 0;
}
