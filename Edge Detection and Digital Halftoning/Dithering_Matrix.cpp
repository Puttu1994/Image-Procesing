#include <stdio.h>
#include <iostream>
#include <stdlib.h>



using namespace std;



int** ditheringMatrix(int d_size){

    int** ditMtrx;
    ditMtrx = new int* [d_size];

    for(int i=0;i<d_size;i++){
        ditMtrx[i] = new int [d_size];
    }

    int initial_value = 0;
    int affine = 0;
    int d_new;
    int temp[][2] = {{1,2},{3,0}};

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            ditMtrx[i][j] = temp[i][j];
        }
    }


    if(d_size == 2){
        return ditMtrx;
    }

    else{
        d_new = (d_size/2);

    for(int i=0;i<d_size;i++){
        for(int j=0;j<d_size;j++){

            if( (i< (d_size/2)) && (j< (d_size/2))){
                    affine = 1;
            }
            else if((i< (d_size/2)) && (j>= (d_size/2))){
                    affine = 2;
            }
            else if((i>= (d_size/2)) && (j< (d_size/2))){
                    affine = 3;
            }
            else{
                    affine = 0;
            }

            ditMtrx[i][j] = 4*((ditheringMatrix(d_new))[(i%d_new)][(j%d_new)]) + affine;

        }
    }
    return ditMtrx;
}


}

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	int Height = 400;
	int Width = 600;

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
	fread(Imagedata, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	int** dithMat;
    unsigned char ImageOut[Height][Width][1];
    int ditherSize = 32;
    float temp;

    dithMat = ditheringMatrix(ditherSize);
    float thrshScale = ((float)255/(ditherSize*ditherSize));
    cout<<"thrsscale "<<thrshScale<<endl;


    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){

            temp = ((float)dithMat[i%ditherSize][j%ditherSize]+0.5)*thrshScale;
            //cout<<dithMat[i%ditherSize][j%ditherSize]<<" temp "<<temp<<endl;

            if(Imagedata[i][j][0]<= temp && Imagedata[i][j][0] >= 0){
                ImageOut[i][j][0] = 0;
            }

            else if(Imagedata[i][j][0] > temp && Imagedata[i][j][0] < 256){
                ImageOut[i][j][0] = 255;
            }

//            cout<<"IM"<<(int)Imagedata[i][j][0]<<"ij"<<i<<j<<" "<<r<<endl;
        }
    }



//        cout<<"test complete"<<endl;

        for(int i=0;i<ditherSize;i++){
            for(int j=0;j<ditherSize;j++){
                cout<<dithMat[i][j]<<endl;
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
