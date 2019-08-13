#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;



int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	int Height = 400;
	int Width = 400;

	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}

	// Allocate image data array
	unsigned char Imagedata[Height][Width][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	//fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	//fclose(file);
	fread(Imagedata, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    int Pixel_count[256] = {0};
    double CDF1[256] = {0};
    double mapping[256] = {0};
    unsigned char ImageOut[Height][Width][1] = {0};

    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            Pixel_count[Imagedata[i][j][0]]++;
        }
    }


    double pixcount = 0;
    for(int i=0;i<256;i++){
        pixcount+= ((double)Pixel_count[i]/((double)Height*(double)Width));
        cout<<pixcount<<endl;
        CDF1[i] = pixcount;
        mapping[i] = CDF1[i]*255;
    }

//    for(int i=0;i<256;i++){
//        cout<<i<<mapping[i]<<endl;
//    }


    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            ImageOut[i][j][0] = mapping[Imagedata[i][j][0]];
        }
    }


	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite((unsigned char*)ImageOut, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
