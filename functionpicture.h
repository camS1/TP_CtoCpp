//============================================================================
//                           structure
//============================================================================
//creating a class for a ppm picture.

class img
{
  public : 
  	img(void);
		img(const img& tocopy);//constructer by copy
  	int Getheigth(void) const;
  	int Getwidth(void) const;
  	u_char* GetData(void) const;
		void Setheigth(float Newheight);
		void Setwidth(float Newwidth);
		void ppm_write_to_file(const char * namefile);//to write a picture in a file namefile
		void ppm_read_from_file( const char * namefile);//to read a picture from a file namefile
		void ppm_desaturate();//to desaturate a picture
		void ppm_shrink(int factor);//to shrink a picture
		//no use of getters.

  private : 
    int heigth;
  	int width;
  	u_char* data;//to stock the picture.
	
};


//============================================================================
//                           Function definitions
//============================================================================
// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(img picture, const char*namefile);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(img* picture, const char* namefile);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(img * picture);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(img* picture, int factor);
