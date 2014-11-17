
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
  img image_bw = img(image);
  memcpy(image_bw.GetData(), image.GetData(), 3 * image_bw.Getwidth() * image_bw.Getheigth() * sizeof(*image_bw.GetData()));

  // Desaturate image_bw
  image_bw.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  image_bw.ppm_write_to_file("gargouille_BW.ppm");

  // delete the desaturated image
  delete(image_bw.GetData());
  

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  int width_small  = Newwidth;
  int height_small = Newheight;
  img image_small=img(image);
  memcpy(image_small.GetData(), image.GetData(), 3 * image_small.Getwidth() * image_small.Getheigth() * sizeof(*image_small.GetData()));
  
  // Shrink image_small size 2-fold
  image_small.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  image_small.ppm_write_to_file("gargouille_small.ppm");

  return 0;
}



