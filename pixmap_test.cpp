#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   ppm_image image;
   image.load("../images/feep.ppm");
   image.save("feep-test-save2.ppm"); // should match original
   
   // should print 4 4
   cout << "loaded feep: " << image.width() << " " << image.height() << endl;

   // test: copy constructor
   ppm_image copy = image; 
   copy.save("feep-test-copy.ppm"); // should match original and load into gimp

   // test: assignment operator works
   copy = image; 
   copy.save("feep-test-assignment.ppm"); // should match original and load into gimp

   // should print r,g,b
   ppm_pixel pixel = image.get(1, 1);
   cout << (int) pixel.r << " " << (int) pixel.g << " " << (int) pixel.b << endl;

   // test: setting a color works
   pixel.r = 255;
   image.set(1, 1, pixel);
   image.save("feep-test-newcolor.ppm");

   // test a non-trivial image
   image.load("../images/earth-ascii.ppm"); // a real image
   image.save("earth-load.ppm");
   // should print 400 400
   cout << "loaded earth: " << image.width() << " " << image.height() << endl;


   // flip horizontal
   ppm_image flip = image.flip_horizontal();
   flip.save("earth-flip.ppm");
   
   // resize
   ppm_image resize = image.resize(200,300);
   resize.save("earth-200-300.ppm");


   // gamma correction
   ppm_image gamma = image.gammaCorrect(0.6f);
   gamma.save("earth-gamma-0.6.ppm");

   gamma = image.gammaCorrect(2.2f);
   gamma.save("earth-gamma-2.2.ppm");


   // grayscale
   ppm_image grayscale = image.grayscale(); 
   grayscale.save("earth-grayscale.ppm");


   // sub image
   ppm_image sub = image.subimage(200, 200, 100, 100);
   sub.save("earth-subimage.ppm");

   // invert colors
   ppm_image inverted = image.invertColors();
   inverted.save("earth-test-invert-colors.ppm");

   // extract main colors
   ppm_image mainColorsExtracted = image.extractMainColors();
   mainColorsExtracted.save("earth-test-extract-main-colors.ppm");

   // extract main colors
   ppm_image whiteExtracted = image.extractWhite(0.8f);
   whiteExtracted.save("earth-test-extract-white.ppm");

   // swirlColors
   ppm_image swirlColors = image.swirlColors();
   swirlColors.save("earth-test-swirl-colors.ppm");

   // add border
   ppm_image bordered = image.addBorder(3, ppm_pixel{ 255, 255, 255 });
   bordered.save("earth-test-border3px.ppm");

   // alpha blend
   ppm_image soup;
   soup.load("../images/soup-ascii.ppm");

   int y = (int) (0.5f * (image.width() - soup.width()));
   int x = (int) (0.5f * (image.height() - soup.height()));
   ppm_image background = image.subimage(x, y, soup.width(), soup.height());
   background.save("background-test.ppm");
   ppm_image blend = background.alpha_blend(soup, 0.5f);
   image.replace(blend, x, y);
   image.save("earth-blend-0.5.ppm");


   // lightest blend

   y = (int)(0.5f * (image.width() - soup.width()));
   x = (int)(0.5f * (image.height() - soup.height()));
   background = image.subimage(x, y, soup.width(), soup.height());
   ppm_image lightest_blend = background.lightest(soup, 0.5f);
   image.replace(lightest_blend, x, y);
   image.save("earth-lightest-blend-0.5.ppm");
   
   ppm_image earth;
   earth.load("../images/earth-ascii.ppm");
   ppm_image filtered_by_Iryna = earth.IrynasFilter(0.8f, 0.5f);
   filtered_by_Iryna.save("earth-filtered_by_Iryna.ppm");
}

