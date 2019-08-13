#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;


//void *borderextnsn(int dimension, unsigned char originalImage[][256][1],int ImageMod[][258]){
//	int newdimension = dimension+2;
//	//int ImageMod[newdimension][newdimension];
//
//	ImageMod[0][0] = (int)originalImage[1][1];
//	ImageMod[0][newdimension-1] = (int)originalImage[dimension-2][dimension-2];
//	ImageMod[newdimension-1][0] = (int)originalImage[dimension-2][1];
//	ImageMod[newdimension-1][newdimension-1] = (int)originalImage[dimension-2][dimension-2];
//
//
//	for(int j=0;j < dimension;j++){
//		ImageMod[0][j+1] = (int)originalImage[0][j];
//		ImageMod[j+1][0] = (int)originalImage[j][0];
//		ImageMod[newdimension-1][j+1] = (int)originalImage[dimension-1][j];
//		ImageMod[j+1][newdimension-1] = (int)originalImage[j][dimension-1];
//	}
//
//	for(int i=0;i<dimension;i++){
//		for(int j=0;j<dimension;j++){
//			ImageMod[i+1][j+1] = (int)originalImage[i][j];
//		}
//	}
//
//	return ImageMod;
//}

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	int Height = 300;
	int Width = 390;

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

	uint8_t ImageOut[Height][Width][3] = {0};
    //int tempImage[Size+2][Size+2];
    uint8_t ImageMod[Height+2][Width+2][1] = {'\0'};
    int newHeight = Height+2;
    int newWidth = Width+2;
	//borderextnsn(Size,Imagedata,ImageMod);


	ImageMod[0][0][0] = Imagedata[1][1][0];
	ImageMod[0][newWidth-1][0] = Imagedata[1][Width-2][0];
	ImageMod[newHeight-1][0][0] = Imagedata[Height-2][1][0];
	ImageMod[newHeight-1][newWidth-1][0] = Imagedata[Height-2][Width-2][0];


	for(int j=0;j < Width;j++){
		ImageMod[0][j+1][0] = Imagedata[0][j][0];
		ImageMod[newHeight-1][j+1][0] = Imagedata[Height-1][j][0];
	}

	for(int j=0;j < Height;j++){
		ImageMod[j+1][0][0] = Imagedata[j][0][0];
		ImageMod[j+1][newWidth-1][0] = Imagedata[j][Width-1][0];
	}

	for(int i=0;i<Height;i++){
//            cout<<"i="<<i<<endl;
		for(int j=0;j<Width;j++){
			ImageMod[i+1][j+1][0] = Imagedata[i][j][0];
//			cout<<(int)ImageMod[i+1][j+1][0]<<endl;
		}
	}


	for(int i=1;i<Height;i++){
		for(int j=0;j<Width;j++){
			int red = 0;
			int blue = 0;
			int green = 0;

			// If I is even and J is even its Green Pixel
			/*
			i,j,color
			even,even,g
			even,odd,r
			odd,even,b
			odd,odd,g
			*/
			if(i%2 == 0){
				if(j%2 == 0){
				blue = (0.5*ImageMod[i+1][j][0] + 0.5*ImageMod[i-1][j][0]);
				red = (0.5*ImageMod[i][j+1][0] + 0.5*ImageMod[i][j-1][0]);
				green = ImageMod[i][j][0];
				//green = (0.2*ImageMod[i+1][j-1][0] + 0.2*ImageMod[i+1][j+1][0] + 0.2*ImageMod[i-1][j-1][0]+ 0.2*ImageMod[i-1][j+1][0] + 0.2*ImageMod[i][j][0]);
				}
				else{
					blue = (0.25*ImageMod[i+1][j-1][0] + 0.25*ImageMod[i+1][j+1][0] + 0.25*ImageMod[i-1][j-1][0]+ 0.25*ImageMod[i-1][j+1][0]);
					green = (0.25*ImageMod[i+1][j][0] + 0.25*ImageMod[i][j+1][0] + 0.25*ImageMod[i-1][j][0] + 0.25*ImageMod[i][j-1][0]);
					red = ImageMod[i][j][0];
				}

			}
			else{
				if(j%2 == 0){
				green = (0.25*ImageMod[i+1][j][0] + 0.25*ImageMod[i][j+1][0] + 0.25*ImageMod[i-1][j][0] + 0.25*ImageMod[i][j-1][0]);
				red = (0.25*ImageMod[i+1][j-1][0] + 0.25*ImageMod[i+1][j+1][0] + 0.25*ImageMod[i-1][j-1][0] + 0.25*ImageMod[i-1][j+1][0]);
				blue = ImageMod[i][j][0];
				}
				else{
					red = (0.5*ImageMod[i+1][j][0] + 0.5*ImageMod[i-1][j][0]);
					blue = (0.5*ImageMod[i][j+1][0] + 0.5*ImageMod[i][j-1][0]);
					green = ImageMod[i][j][0];
					//green = (0.2*ImageMod[i+1][j-1][0] + 0.2*ImageMod[i+1][j+1][0] + 0.2*ImageMod[i-1][j-1][0]+ 0.2*ImageMod[i-1][j+1][0] + 0.2*ImageMod[i][j][0]);
				}
			}

			ImageOut[i][j][0] = blue;
			ImageOut[i][j][1] = green;
			ImageOut[i][j][2] = red;


		}
	}


//	 Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite((unsigned char*)ImageOut, sizeof(unsigned char), Height*Width*3, file);
	fclose(file);

	return 0;
}
