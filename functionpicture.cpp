#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <assert.h>
#include"functionpicture.h"
#include <string.h>


//============================================================================
//                           Function declarations
//============================================================================

void ppm_write_to_file(img picture, const char * namefile)// FILE* file)
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


//void ppm_read_from_file(int *width, int *height, const u_char * ** data, const char *namefile)// FILE* file)
void ppm_read_from_file(img* picture, const char * namefile)
{
  //to open a file
  FILE* file;
  file=fopen(namefile,"r");
  // Read file header
  fscanf(file, "P6\n%d %d\n255\n", &picture->width, &picture->heigth);//comment faire??

  // Allocate memory according to data.
  //picture->data = (u_char *) malloc(3 * (picture->width) * (picture->heigth) * sizeof(picture->data));
	picture->data= new u_char [3 * (picture->width) * (picture->heigth)]; 

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



//void ppm_shrink(const u_char * ** image, int *width, int *height, int factor)
void ppm_shrink(img* picture, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (picture->width) / factor;
  int new_height  = (picture->heigth) / factor;
  
  //u_char *new_image = (u_char *) malloc(3 * new_width * new_height * sizeof(*new_image));
	u_char* new_image= new u_char [3 * new_width * new_height ]; 

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
