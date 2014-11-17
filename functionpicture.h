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
