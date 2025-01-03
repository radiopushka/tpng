#include <stdio.h>
#include <sys/ioctl.h>

void mvprint(int x,int y,char* string){
  printf("\033[%d;%dH%s",x,y,string);
}
void mvmove(int x,int y){
  printf("\033[%d;%dH",x,y);
}
void clear(){
  printf("\033c");
}
void refresh(){
  fflush(stdout);
}

void nocurs(){
  printf("\e[?25l");
}
void curs(){
  printf("\e[?25h");
}
void fpixel(unsigned char r,unsigned char g,unsigned char b){
  printf("\x1b[48;2;%d;%d;%dm ",r,g,b);
}
void fbg(unsigned char r,unsigned char g,unsigned char b){
  printf("\x1b[48;2;%d;%d;%dm",r,g,b);
}
void ffg(unsigned char r,unsigned char g,unsigned char b){
  printf("\x1b[38;2;%d;%d;%dm",r,g,b);
}
void fclear(){
  printf("\x1b[0m");
}

void term_size(int* width,int* height){
  struct winsize winf;
  int w;
  int h;
  ioctl(0, TIOCGWINSZ, &winf);
  h=winf.ws_row;
  w=winf.ws_col;
  if(h<1){
    h=30;
  }
  if(w<1){
    w=100;
  }
  *width=w;
  *height=h;
}


