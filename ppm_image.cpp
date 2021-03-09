#include "ppm_image.h"
#include <string>
#include <fstream>
#include <iostream>
#include <math.h> 
using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{

}

ppm_image::ppm_image(int width, int height) 
{
    this->h = height;
    this->w = width;
}

ppm_image::ppm_image(const ppm_image& orig)
{
    if (&orig != this) // protect against self-assignment
    {
        this->h = orig.h;
        this->w = orig.w;
        this->image = orig.image;
    }
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   this->h = orig.h;
   this->w = orig.w;
   this->image = orig.image;

   return *this;   
}

ppm_image::~ppm_image()
{
    /*
    
    for (int i = 0; i < h; i++)
    {
        delete[] image[i];
    }
    delete[] image;
    */
}

void ppm_image::create_pixel_array(int h, int w) 
{
    this->image = new ppm_pixel * [h];
    for (int i = 0; i < h; ++i) {
        this->image[i] = new ppm_pixel[w];
    }
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

    this->create_pixel_array(h, w);
    

    // populate pixels array
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int red;
            int green;
            int blue;
            file >> red;
            file >> green;
            file >> blue;
            this->image[i][j] = ppm_pixel{ red, green, blue };
        }
    }

    return true;
}

bool ppm_image::save(const std::string& filename) const
{
    ofstream file;
    file.open(filename);
    file << "P3\n";
    file << this->w << " " << this->h << "\n";
    file << "255\n";
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            file << this->image[i][j].r << "\n" << this->image[i][j].g << "\n" << this->image[i][j].b << "\n";
        }
    }
    file.close();
    return true;
}

 ppm_image ppm_image::resize(int w, int h) const
{
    ppm_image result(w, h);
    result.create_pixel_array(h, w);

    for (int i = 0; i < h; i++) 
    {
        for (int j = 0; j < w; j++) {
            int height_prop = floor((i / (double) (h - 1)) * (this->h - 1));
            int width_prop = floor((j / (double) (w - 1)) * (this->w - 1));
            result.set(i, j, this->image[height_prop][width_prop]);
        }
    }
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result(w, h);
    result.create_pixel_array(h, w);

    for (int i = 0; i < h; i++) 
    {
        for (int j = 0; j < w; j++)
        {
            result.image[h-i-1][j] = this->image[i][j];
        }
    }
    
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
    ppm_image result(w, h);
    result.create_pixel_array(h, w);
    if (w + starty >= this->w || h + startx >= this->h) {
        cout << "The range selected is out of bounds on the given image, so it was cropped to get the maximum of it.\n";
        w = this->w - starty;
        h = this->h - startx;
    }

    for (int i = startx; i < startx+h; i++)
    {
        for (int j = starty; j < starty+w; j++)
        {
            result.image[i - startx][j - starty] = this->image[i][j];
        }
    }
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{

    for (int i = startx; i < startx + image.h; i++)
    {
        for (int j = starty; j < starty + image.w; j++)
        {
            this->image[i][j] = image.image[i - startx][j - starty];
            
        }
    }
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
    ppm_image result(w, h);
    result.create_pixel_array(h, w);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            result.image[i][j].r = (int) this->image[i][j].r * (1 - alpha) + other.image[i][j].r * alpha;
            result.image[i][j].g = (int) this->image[i][j].g * (1 - alpha) + other.image[i][j].g * alpha;
            result.image[i][j].b = (int) this->image[i][j].b * (1 - alpha) + other.image[i][j].b * alpha;
        }
    }

    return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
    ppm_image result(w, h);
    result.create_pixel_array(h, w);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            result.image[i][j].r = 255 * pow(this->image[i][j].r/255.0f, 1/gamma);
            result.image[i][j].g = 255 * pow(this->image[i][j].g/255.0f, 1 / gamma);
            result.image[i][j].b = 255 * pow(this->image[i][j].b/255.0f, 1 / gamma);
        }
    }
   return result;
}

ppm_image ppm_image::grayscale() const
{
    ppm_image result(w, h);
    result.create_pixel_array(h, w);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int c = (this->image[i][j].r + this->image[i][j].g + this->image[i][j].b) / 3;
            result.image[i][j] = ppm_pixel{ c, c, c };
        }
    }
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
    return this->image[row][col];
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
    this->image[row][col] = c;
}

int ppm_image::height() const
{
   return this->h;
}

int ppm_image::width() const
{
   return this->w;
}
