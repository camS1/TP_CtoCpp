
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
  img image;
  image.ppm_read_from_file("gargouille.ppm");
  Newwidth=image.Getwidth();
  Newheight=image.Getheigth();
  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gagouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  /*int width_bw  = width;
  int height_bw = height;
  u_char* image_bw = (u_char*) malloc(3 * width * height * sizeof(*image_bw));*/
  //creating a void picture
  
  img image_bw = img(image);
  //image_bw.img(image);
  //image_bw.width=Newwidth;
  //image_bw.heigth=Newheight;
  //u_char* Newimage2= (u_char*) malloc(3 * image_bw->width * image_bw->heigth * sizeof(*Newimage2));
  //u_char * Newimage2= new u_char [3 * image_bw.width * image_bw.heigth ]; 
  //image_bw.data=Newimage2;
  memcpy(image_bw.GetData(), image.GetData(), 3 * image_bw.Getwidth() * image_bw.Getheigth() * sizeof(*image_bw.GetData()));

  // Desaturate image_bw
  image_bw.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  //FILE* ppm_output = fopen("gargouille_BW.ppm", "wb");
  image_bw.ppm_write_to_file("gargouille_BW.ppm");
  //fclose(ppm_output);

  // Free the desaturated image
  free(image_bw.GetData());
  

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  int width_small  = Newwidth;
  int height_small = Newheight;
  
  
  img image_small=img(image);
  //image_small.img(height_small,width_small);
  //image_small.width=width_small; 
  //image_small.heigth=height_small;
  //Newimage_small = (u_char*) malloc(3 * width_small * height_small * sizeof(*Newimage_small));
  //u_char * Newimage_small= new u_char [3 * width_small * height_small]; 
  //image_small.data=Newimage_small;
  
  memcpy(image_small.GetData(), image.GetData(), 3 * image_small.Getwidth() * image_small.Getheigth() * sizeof(*image_small.GetData()));
  
  // Shrink image_small size 2-fold
  image_small.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  //ppm_output = fopen("gargouille_small.ppm", "wb");
  image_small.ppm_write_to_file("gargouille_small.ppm");
  //fclose(ppm_output););

  return 0;
}



