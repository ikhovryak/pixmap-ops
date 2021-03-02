#include "ppm_image.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{

}

ppm_image::ppm_image(int w, int h) 
{
    
}

ppm_image::ppm_image(const ppm_image& orig)
{
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   // todo: your code here

   return *this;   
}

ppm_image::~ppm_image()
{
}

bool ppm_image::load(const std::string& filename)
{
    ifstream file(filename);
    if (!file) // true if the file is valid
    {
        cout << "Cannot load file: " << filename << endl;
        return false;
    }
    string header;
    file >> header;
    file >> this->w;
    file >> this->h;

    string second_header;
    file >> second_header;

    // create the pixels array
    this->image = new ppm_pixel*[h];
    for (int i = 0; i < h; ++i) {
        this->image[i] = new ppm_pixel[w];
    }
    

    // populate pixels array
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            int red;
            int green;
            int blue;
            file >> red;
            file >> green;
            file >> blue;
            cout << i<<" "<< j<<" "<<red << " " << green << " " << blue << "\n";
            this->image[i][j] = ppm_pixel{ red, green, blue };
        }
    }

    //debugging to see if it works
    /*
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            cout << this->image[i][j].r << " "<< this->image[i][j].g << " "<< this->image[i][j].b<<"\n";
        }
    }

    cout << "hello";
    */
    return true;
}

bool ppm_image::save(const std::string& filename) const
{
    ofstream file;
    file.open(filename);
    file << "P3\n";
    file << this->w << " " << this->h << "\n";
    file << "255\n";
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            file << this->image[i][j].r << "\n" << this->image[i][j].g << "\n" << this->image[i][j].b << "\n";
        }
    }
    file.close();
    return true;
}

 ppm_image ppm_image::resize(int w, int h) const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
    ppm_image result;
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::grayscale() const
{
   ppm_image result;
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
   return ppm_pixel{ 0,0,0 };
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
}

int ppm_image::height() const
{
   return this->h;
}

int ppm_image::width() const
{
   return this->w;
}
