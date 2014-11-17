
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"functionpicture.h"


//https://github.com/camS1/TP_CtoCpp.git


//============================================================================
//                                  Main
//============================================================================
int main(int argc, const char* argv[])//argc et argv par defaut pas utilise ici.
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  u_char* Newimage = NULL;
  
  int Newwidth=0;
  int Newheight=0;
  //creating a void picture
  printf("%d\n",Newwidth);
  //img * image;
  //image=(img*)malloc(sizeof(img));
  img * image= new img; 
  ppm_read_from_file(image,"gargouille.ppm");
  Newwidth=image->width;
  Newheight=image->heigth;
  printf("%d\n",Newwidth);
  getchar();
  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gagouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  /*int width_bw  = width;
  int height_bw = height;
  u_char* image_bw = (u_char*) malloc(3 * width * height * sizeof(*image_bw));*/
  //creating a void picture
  //img* image_bw;
  //image_bw=(img*)malloc(sizeof(img));
  img * image_bw= new img; 
  image_bw->width=Newwidth;
  image_bw->heigth=Newheight;
  //u_char* Newimage2= (u_char*) malloc(3 * image_bw->width * image_bw->heigth * sizeof(*Newimage2));
  u_char * Newimage2= new u_char [3 * image_bw->width * image_bw->heigth ]; 
  image_bw->data=Newimage2;
  memcpy(image_bw->data, image->data, 3 * image_bw->width * image_bw->heigth * sizeof(*image_bw->data));

  // Desaturate image_bw
  ppm_desaturate(image_bw);

  // Write the desaturated image into "gargouille_BW.ppm"
  //FILE* ppm_output = fopen("gargouille_BW.ppm", "wb");
  ppm_write_to_file(*image_bw,"gargouille_BW.ppm");
  //fclose(ppm_output);

  // Free the desaturated image
  free(image_bw->data);
  

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  int width_small  = Newwidth;
  int height_small = Newheight;
  
    
  
  //u_char* Newimage_small = NULL;

  //img * image_small;
  //image_small=(img*)malloc(sizeof(img));
  img * image_small= new img; 
  image_small->width=width_small; 
  image_small->heigth=height_small;
  //Newimage_small = (u_char*) malloc(3 * width_small * height_small * sizeof(*Newimage_small));
  u_char * Newimage_small= new u_char [3 * width_small * height_small]; 
  image_small->data=Newimage_small;
  
  memcpy(image_small->data, image->data, 3 * image_small->width * image_small->heigth * sizeof(*image_small->data));
  
  // Shrink image_small size 2-fold
  ppm_shrink(image_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  //ppm_output = fopen("gargouille_small.ppm", "wb");
  ppm_write_to_file(*image_small,"gargouille_small.ppm");
  //fclose(ppm_output););

  return 0;
}



