#include <iostream>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
	ppm_image earth;
	earth.load("../images/earth-ascii.ppm");

	float threshold = 0.8;
	float alpha = 0.5;
	ppm_image mainColors = earth.extractMainColors();
	ppm_image whites = earth.extractWhite(threshold);

	ppm_image filtered_by_Iryna = mainColors.lightest(whites, alpha);

	// Filter as a function
	// ppm_image filtered_by_Iryna = earth.IrynasFilter(0.8f, 0.5f); 
	filtered_by_Iryna.save("earth-filtered_by_Iryna.ppm");
}

