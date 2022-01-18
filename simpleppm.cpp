#include <fstream>
#include <iostream>
#include <string>

#define WIDTH 1024
#define HEIGHT 1024

// Alternatively
// const uint32_t WIDTH = 1024;
// const uint32_t HEIGHT = 1024;
// const uint32_t SQUREDIMS = 16;

// PPM (Portable PixMap) format http://netpbm.sourceforge.net/doc/ppm.html
// or more palatably, https://en.wikipedia.org/wiki/Netpbm
// Has support for 0-255 colours in each RGB channel; 24 bits per pixel

// Let's make a struct to define each pixel
struct Image
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

int main()
{
	// Define the output file. It will write to a bmp format
	// which can then be opened with many editors, such as Gimp,
	// or the default linux "display" command on most distros
	std::string outputfile = "simpleppm.bmp";

	// 2D array for simplicity, which we'll fill as a checkerboard
	Image checkerboard[WIDTH][HEIGHT];
	for(uint32_t i = 0; i < WIDTH; i++)
	{
		for(uint32_t j = 0; j < HEIGHT; j++)
		{
			// Add up i and j, and then check if it's odd or even
			// Then, since PPM format will want this in the range of 0-255,
			// multiply by 255 to scale it
			// This maybe isn't the best pattern to look at, since it 
			// will probably look gray.
			// You can have fun enhancing it
			checkerboard[i][j].r = ((i + j) % 2 == 0) * 255;
			checkerboard[i][j].g = checkerboard[i][j].r;
			checkerboard[i][j].b = checkerboard[i][j].r;
		}
	}



	// Use an output stream (https://www.cplusplus.com/reference/fstream/ofstream/)
	// Included from <fstream>
	// bitmask flags (out, binary) allow for stream output in binary mode
	std::ofstream output_stream(outputfile, std::ios::out | std::ios::binary);

	// Write out the header to the stream
	// PPM headers can be defined in different ways, available at the wikipedia link above
	// We'll use the P6 header here.
	output_stream << "P3\n"
				  << WIDTH << " "
				  << HEIGHT << "\n"
				  << "255\n";


	// Images are 2D, so loop through all pixels
	// Alternatively, we could use offsets to do 1 loop... try it as a challenge
	for(uint32_t i = 0; i < WIDTH; i++)
	{
		for(uint32_t j = 0; j < HEIGHT; j++)
		{
			output_stream << (unsigned char) checkerboard[i][j].r
						  << (unsigned char) checkerboard[i][j].g
						  << (unsigned char) checkerboard[i][j].b;
		}
	}

	// Close the file for safety
	output_stream.close();

	return 0;
}