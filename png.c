
#include <png.h>

/*unsigned int reverse_int(unsigned int input){
  unsigned int out=0;
  for(unsigned int i=0;i<32;i++){
    out=(out<<1)|((input>>i)&1);
    printf("%d\n",out);
    
  }
return out;
}*/




unsigned int _reverse_endian(unsigned int input){
  unsigned int out=((input&255)<<24)|(((input>>8)&255)<<16)|(((input>>16)&255)<<8)|((input>>24)&255);
  return out;
}


int read_png_file(char* file,int* width,int* height,int* bytes_per_pixel,unsigned char** buffer_pointer,unsigned char** buffer_end_pointer){
 
unsigned char png_header[] = {137, 80, 78, 71, 13, 10, 26, 10};


  FILE* im=fopen(file,"rb");
  if(!im){
    printf("unable to open file\n");
    return -1;
  }

  //obtain image dimensions
  char header[17];
  int ret=fread(header,sizeof(char),16,im);
  if(ret<16){
    printf("not a png file\n");
    return -1;

  }

  if(memcmp(header,png_header,8)!=0){
    printf("not a png file\n");
    return -1;
  }

  unsigned int obw,obh;


  if(fread(&obw,sizeof(int),1,im)<1){
    printf("not a png file\n");
    return -1;

  }
  if(fread(&obh,sizeof(int),1,im)<1){
    printf("not a png file\n");
    return -1;

  }

  *width=_reverse_endian(obw);
  *height=_reverse_endian(obh);


  rewind(im);

  

  png_structp png=png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png){
    printf("png error\n");
    return -1;
  }

  png_infop info = png_create_info_struct(png);
  if(!info){
    printf("png info error\n");
    return -1;
  }

  if(setjmp(png_jmpbuf(png))){
    printf("fault\n");
    return -1;
  }

  png_init_io(png, im);
  png_read_info(png, info);
  
  *bytes_per_pixel=3;
  int color_type = png_get_color_type(png, info);
  if(color_type == PNG_COLOR_TYPE_PALETTE){
    png_set_palette_to_rgb(png);
    *bytes_per_pixel=4;
  }

  if(color_type == PNG_COLOR_TYPE_GRAY ||color_type == PNG_COLOR_TYPE_GRAY_ALPHA){
    png_set_gray_to_rgb(png);
  }

  png_read_update_info(png, info);


  if(color_type==PNG_COLOR_TYPE_RGB_ALPHA ){
    *bytes_per_pixel=4;
  }

  size_t msize=png_get_rowbytes(png,info)*(*height);
  size_t chunk_size=png_get_rowbytes(png,info);
  unsigned char* matrix=malloc(msize*sizeof(char));

  png_bytep* rows=malloc(sizeof(png_bytep)*(*height));
  int i;
  for(i=0;i<*height;i++){
    rows[i]=(png_byte*)(matrix+(i*chunk_size));
  }
  *buffer_end_pointer=matrix+msize;
  
  png_read_image(png, rows);
  fclose(im);
  png_destroy_read_struct(&png, &info, NULL);

  *buffer_pointer=matrix;
  free(rows);

  return 1;
}


