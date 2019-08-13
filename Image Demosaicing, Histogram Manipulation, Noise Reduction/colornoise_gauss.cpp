// Siddartha Yeliyur Shivakumara Swamy
// 3149024723
// yeliyurs@usc.edu
// January 22nd 2019











// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
# define pi           3.14159265358979323846  /* pi */

using namespace std;



void arrayinitializer(int matrix[][3][1],int ksize,int initialvalue){

    for(int i=0;i<ksize;i++){
        for(int j=0;j<ksize;j++){
            matrix[i][j][0] = initialvalue;
        }
    }
}


int border_extnsn(int index, int height){

    if(index<0){
        return (-index-1);
    }

    else if(index>=height){
        return(2*height-index-1);
    }
    else{
        return index;
    }

}


//float gauss_kernel(int g_row, int g_col, int i_row, int i_col, float sigma){
//
//
//    float denom = 1/(sqrt(2*pi)*sigma);
//    //cout<<"Denom"<<denom<<endl;
//    float expdenom = 2*(pow(sigma,2));
//    //cout<<"expDenom"<<expdenom<<endl;
//    float num = pow((g_row-i_row),2) + pow((g_col-i_col),2);
//    //cout<<"num"<<num<<endl;
//    //cout<<"num/denom"<<(exp(-(num)/expdenom)/denom)<<endl;
//    return exp(-(num)/expdenom)/denom;
//}

double** GaussKernel(int kernelsize, float sigma){

    double sum = 0;
    double denom = 1/(sqrt(2*pi)*sigma);
    double expdenom = 2*(pow(sigma,2));
    double** gausskernel;
    gausskernel = new double* [kernelsize];
    for(int i=0;i<kernelsize;i++){
        gausskernel[i] = new double [kernelsize];
    }
    for(int i=0;i<kernelsize;i++){
        for(int j=0;j<kernelsize;j++){

            double num = pow((i-2),2) + pow((j-2),2);
            gausskernel[i][j] = exp(-(num)/expdenom)*denom;
            sum+=exp(-(num)/expdenom)*denom;
            cout<<"Siddartha"<<"i"<<i<<"j"<<j<<" "<<exp(-(num)/expdenom)*denom<<endl;

        }

    }
    cout<<"sum"<<sum;
    return gausskernel;
}

double kernelsum(double** kernel_matrix, int kernelsize){

    double sum = 0;
    for(int i=0;i<kernelsize;i++){
            for(int j=0;j<kernelsize;j++){
                sum+=kernel_matrix[i][j];
            }
}
    return sum;
}

//int** convolution(int kernel_matrix[][3],int kernel_size,unsigned char image_matrix[][400][1],int height,int width){
//
//    int** output_matrix = new int*[height];
//    for(int i=0;i<height;i++)
//    {
//        output_matrix[i]=new int[width];
//    }
//
//    int sum;
//
//    for(int i=0;i<height;i++){
//        for(int j=0;j<width;j++){
//
//            sum = 0;
//            for(int k=kernel_size;k>=0;k++){
//                    int x = border_extnsn((i+1-k),kernel_size);
//
//                for(int l=kernel_size;l>=0;l++){
//                        int y = border_extnsn((j+1-l),kernel_size);
//                        sum+=(long)((kernel_matrix[k][l] * (int)image_matrix[x][y][0])/9);
//                    }
//                    //sum+=kernel_matrix[k][l] * image_matrix[i+1-k][j+1-l];
//                }
//                output_matrix[i][j] = sum;
//            }
//        }
//        return output_matrix;
//}


//template <size_t size_x, size_t size_y>
//float convolution(unsigned char ImagePixel[][256][1], int i, int j){
//
//int kernel_matrix[3][3] = {1};
//int kernel_size = 3;
//
//float sum = 0;
//for(int k=kernel_size;k>=0;k--){
//        int x = border_extnsn((i+1-k),kernel_size);
//
//    for(int l=kernel_size;l>=0;l--){
//            int y = border_extnsn((j+1-l),kernel_size);
//            cout<<k<<":"<<l<<endl;
//            sum+=(float)((kernel_matrix[k][l] * (int)ImagePixel[x][y][0])/9);
//        }
//        //sum+=kernel_matrix[k][l] * image_matrix[i+1-k][j+1-l];
//    }
//    return sum;
//}
//int sum=0;
//for (int i=0;i<size_x;i++)
//{
//    for(int j=0;j<size_y;j++)
//    {
//        sum += ImagePixel[i,j] * kernel_matrix[i,j]
//    }
//}
//
//return sum/9;
//
//
////return sum;
//
//}



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
	const int BytesPerPixel = 3;
	int Size = 256;
	int Height = 256;
	int Width = 256;

	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
//	if (argc < 4){
//		BytesPerPixel = 1; // default is grey image
//	}
//	else {
//		BytesPerPixel = atoi(argv[3]);
//		// Check if size is specified
//		if (argc >= 5){
//			Size = atoi(argv[4]);
//		}
//	}

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
    uint8_t outputImage[Height][Width][3] = {0};
    int kernel_size = 9;
    //int kernel_matrix[3][3][1];

    //arrayinitializer(kernel_matrix,kernel_size,1);

    int count = 0;
    float sigma = 3;
    double sum = 0;
    double** gauss_kernel = GaussKernel(kernel_size,sigma);
    double k_sum = kernelsum(gauss_kernel,kernel_size);

    for(int chnl=0;chnl<3;chnl++){


        for(int i=0;i<Height-1;i++){
            cout<<"i"<<i<<endl;
        for(int j=0;j<Width-1;j++){

            sum = 0;
            for(int k=kernel_size-1;k>=0;k--){
                int x = border_extnsn((i+1-k),Height);

                for(int l=kernel_size-1;l>=0;l--){
                    int y = border_extnsn((j+1-l),Height);
                    //gauss = gauss_kernel(k,l,i,j,sigma);
                    sum+=(gauss_kernel[k][l] * ( (double)Imagedata[x][y][chnl]));
                    //cout<<"Gauss: "<<gauss<<"Sum: "<<sum<<endl;
                    count++;
        }
        //sum+=kernel_matrix[k][l] * image_matrix[i+1-k][j+1-l];
    }

        outputImage[i][j][chnl] = (uint8_t)(sum/k_sum);
        //cout<<"sum: "<<sum/k_sum<<" "<<i<<","<<j<<" "<<outputImage[i][j][0]<<endl;

        }
    }



    }



//    cout<<"Count"<<count<<endl;
//    for(int i=0;i<Height;i++){
//        for(int j=0;j<Width;j++){
//            cout<<"image Pixel"<<outputImage[i][j][0]<<endl;
//        }
//    }
    //outputImage = convolution(kernel_matrix,3,Imagedata,Height,Width)

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite((unsigned char*)outputImage, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
