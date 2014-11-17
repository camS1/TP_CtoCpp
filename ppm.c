
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//https://github.com/camS1/TP_CtoCpp.git


//============================================================================
//                           structure
//============================================================================
//creating structure for a ppm picture.
typedef struct
{
  int heigth;
  int width;
  u_char* data;//to stock the picture.
}img;
 

//============================================================================
//                           Function definitions
//============================================================================
// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(img picture, char*namefile);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(img* picture, char* namefile);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(img * picture);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(img* picture, int factor);



//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])//argc et argv par defaut pas utilise ici.
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  u_char* Newimage = NULL;
  
  int Newwidth=0;
  int Newheight=0;
  //creating a void picture
  printf("%d\n",Newwidth);
  img * image;
  image=(img*)malloc(sizeof(img));
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
  img* image_bw;
  image_bw=(img*)malloc(sizeof(img));
  image_bw->width=Newwidth;
  image_bw->heigth=Newheight;
  u_char* Newimage2= (u_char*) malloc(3 * image_bw->width * image_bw->heigth * sizeof(*Newimage2));
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
  
    
  
  u_char* Newimage_small = NULL;

  img * image_small;
  image_small=(img*)malloc(sizeof(img));
  image_small->width=width_small; 
  image_small->heigth=height_small;
  Newimage_small = (u_char*) malloc(3 * width_small * height_small * sizeof(*Newimage_small));
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



//============================================================================
//                           Function declarations
//============================================================================

void ppm_write_to_file(img picture, char* namefile)// FILE* file)
{
	
  //to open a file
  FILE* file;
  file=fopen(namefile,"w");
  // Write header
  fprintf(file, "P6\n%d %d\n255\n", picture.width, picture.heigth);

  // Write pixels
  fwrite(picture.data, 3, picture.width*picture.heigth, file);
  //to close the file
  fclose(file);
}


//void ppm_read_from_file(int *width, int *height, u_char** data, char*namefile)// FILE* file)
void ppm_read_from_file(img* picture, char* namefile)
{
  //to open a file
  FILE* file;
  file=fopen(namefile,"r");
  // Read file header
  fscanf(file, "P6\n%d %d\n255\n", &picture->width, &picture->heigth);//comment faire??

  // Allocate memory according to width and height
  picture->data = (u_char*) malloc(3 * (picture->width) * (picture->heigth) * sizeof(picture->data));

  // Read the actual image data
  fread(picture->data, 3, (picture->width) * (picture->heigth), file);
  //to close the file
  fclose(file);
}



void ppm_desaturate(img * picture)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < picture->width ; x++)
  {
    for (y = 0 ; y < picture->heigth ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += picture->data[ 3 * (y * picture->width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&picture->data[3 * (y * picture->width + x)], grey_lvl, 3);
    }
  }
}



//void ppm_shrink(u_char** image, int *width, int *height, int factor)
void ppm_shrink(img* picture, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (picture->width) / factor;
  int new_height  = (picture->heigth) / factor;
  
  u_char* new_image = (u_char*) malloc(3 * new_width * new_height * sizeof(*new_image));

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * (picture->width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (picture->width) + dx);

          // Accumulate RGB values
          red   += (picture->data)[i0+delta_i];
          green += (picture->data)[i0+delta_i+1];
          blue  += (picture->data)[i0+delta_i+2];
        }
      }
      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  picture->width  = new_width;
  picture->heigth = new_height;

  // Update image
  free(picture->data);
  picture->data = new_image;
}
