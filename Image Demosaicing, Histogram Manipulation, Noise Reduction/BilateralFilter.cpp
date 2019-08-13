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
        return (-index);
    }

    else if(index>=height){
        return(2*height-index-2);
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


double** bilat_intensity_kernel(unsigned char original_image[][256][1], int row, int col, int kernelsize, float sigma, int height, int width){


    double num = 0;
    double denom = (2*pow(sigma,2));
    double** bilatin;
    bilatin = new double* [kernelsize];
    for(int i=0;i<kernelsize;i++){
        bilatin[i] = new double [kernelsize];
    }


    for(int k=kernelsize-1;k>=0;k--){
                int x = border_extnsn((row+2-k),height);

                for(int l=kernelsize-1;l>=0;l--){
                    int y = border_extnsn((col+2-l),width);
                    num = pow(abs((double)original_image[row][col][0]-(double)original_image[x][y][0]),2);
                    bilatin[kernelsize-k-1][kernelsize-l-1] = exp(-(num/denom));
                    cout<<"Siddartha2"<<"i"<<k<<"j"<<l<<" "<<exp(-(num/denom))<<endl;
        }
        //sum+=kernel_matrix[k][l] * image_matrix[i+1-k][j+1-l];
    }

//    for(int k=0;k<kernelsize;k++){
//                int x = border_extnsn((row+1-k),height);
//
//                for(int l=0;l<kernelsize;l++){
//                    int y = border_extnsn((col+1-l),width);
//                    num = pow(abs((int)original_image[row][col][0]-(int)original_image[x][y][0]),2);
//                    bilatin[kernelsize-k][kernelsize-l] = exp(-(num/denom));
//                    cout<<"Siddartha2"<<"i"<<k<<"j"<<l<<" "<<exp(-(num/denom))<<endl;
//        }
//        //sum+=kernel_matrix[k][l] * image_matrix[i+1-k][j+1-l];
//    }

    return bilatin;

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

double bilatavg(double** biposkernel, double** biintenkernel, int kernelsize){

    double sum = 0;
    for(int i=0;i<kernelsize;i++){
        for(int j=0;j<kernelsize;j++){
            sum+=(biposkernel[i][j]*biintenkernel[i][j]);
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
	const int BytesPerPixel=1;
	int Size = 256;
	const int Height = 256;
	const int Width = 256;

	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
//	if (argc < 4){
//		const int BytesPerPixel = 1; // default is grey image
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
    uint8_t outputImage[Height][Width][1] = {0};
    int kernel_size = 5;
    //int kernel_matrix[3][3][1];

    //arrayinitializer(kernel_matrix,kernel_size,1);

    int count = 0;
    float sigma_C = 5;
    float sigma_S = 8;
    double sum = 0;
    double** bilateralpos_kernel = GaussKernel(kernel_size,sigma_C);
    double** bilateralinten_kernel;
    double k_sum;
    int x;
    int y;
    for(int i=0;i<Height;i++){
            cout<<"i"<<i<<endl;
        for(int j=0;j<Width;j++){

            bilateralinten_kernel = bilat_intensity_kernel(Imagedata,i,j,kernel_size,sigma_S,Height,Width);
            k_sum = bilatavg(bilateralpos_kernel,bilateralinten_kernel,kernel_size);
            sum = 0;
            x = 0;
            for(int k=kernel_size-1;k>=0;k--){
                x = border_extnsn((i+2-k),Height);
                y = 0;
                for(int l=kernel_size-1;l>=0;l--){
                    y = border_extnsn((j+2-l),Height);
                    //gauss = gauss_kernel(k,l,i,j,sigma);
                    sum+=(((double)Imagedata[x][y][0]) * bilateralpos_kernel[k][l] * bilateralinten_kernel[k][l]);
                    //cout<<"Gauss: "<<gauss<<"Sum: "<<sum<<endl;
                    count++;
        }
        //sum+=kernel_matrix[k][l] * image_matrix[i+1-k][j+1-l];
    }

        outputImage[i][j][0] = (uint8_t)(sum/k_sum);
        cout<<"sum: "<<sum/k_sum<<" "<<i<<","<<j<<" "<<outputImage[i][j][0]<<endl;

        }
    }
    cout<<"Count"<<count<<endl;
    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            cout<<"image Pixel"<<outputImage[i][j][0]<<endl;
        }
    }
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
