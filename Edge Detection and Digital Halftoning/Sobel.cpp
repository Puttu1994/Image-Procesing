#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<math.h>

using namespace std;


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

float convolution(int mask[][3], float input_image[321][481], int mask_size, int row, int col, int image_Height, int image_Width){

    int convSum = 0;
    int maskHlf = mask_size/2;
    cout<<"im here"<<endl;

    for(int h=0;h<mask_size;h++){
        for(int w=0;w<mask_size;w++){
            convSum+=(mask[h][w]*(int)input_image[border_extnsn(row+h-maskHlf,image_Height)][border_extnsn(col+w-maskHlf,image_Width)]);
        }
    }
    return convSum;
}

float Min_Max(float** final_image, int Height, int Coloumn, int Max){

    float MaxMin = 0;
    for(int r=0;r<Height;r++){
        for(int w=0;w<Coloumn;w++){
            if(Max == 1){
                if(MaxMin < final_image[r][w]){
                    MaxMin = final_image[r][w];
                }
            }
            else{
                if(MaxMin > final_image[r][w]){
                    MaxMin = final_image[r][w];
                }
            }
        }
    }


return MaxMin;


}


float** sobelEdge(float input_image[321][481], int row, int column){

    int sobelX[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int sobelY[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
//    int sobelGradX[400][600] = {0};
//    int sobelGradY[400][600] = {0};

    float** finalImage;
    finalImage = new float* [321];
    for(int i=0;i<321;i++){
        finalImage[i] = new float [481];
    }
    float gradientX = 0;
    float gradientY = 0;
    for(int h=0;h<row;h++){
        for(int w=0;w<column;w++){

            gradientX = convolution(sobelX,input_image,3,h,w,row,column);
//            sobelGradX[h][w] = gradientX;
            gradientY = convolution(sobelY,input_image,3,h,w,row,column);
//            sobelGradY[h][w] = gradientY;
            finalImage[h][w] = sqrt(pow(gradientX,2)+pow(gradientY,2));
//            finalImage[h][w] = gradientX;
        }
    }


    float Pixel_min = finalImage[0][0];
    float Pixel_max = finalImage[0][0];

    Pixel_max = Min_Max(finalImage, row, column, 1);
    Pixel_min = Min_Max(finalImage, row, column, 0);

    float grad_hist[int(Pixel_max)] = {0};

    for(int r=0;r<row;r++){
        for(int w=0;w<column;w++){
            grad_hist[int(finalImage[r][w])] += 1;
        }
    }
    cout<<"Hist "<<grad_hist[0]<<endl;
    float grad_hist_cdf[int(Pixel_max)] = {0};
    grad_hist_cdf[0] = grad_hist[0];
    for(int x=1;x<Pixel_max;x++){
        grad_hist_cdf[x] += grad_hist_cdf[x-1] + grad_hist[x];
        cout<<"gradHist "<<x<<" "<<grad_hist_cdf[x]<<endl;
    }


    float threshPerc = 0.99 * grad_hist_cdf[(int)(Pixel_max-1)];
    float threshInt;
    for(int i=1;i<Pixel_max;i++){
        if(grad_hist_cdf[i] >= threshPerc){
            threshInt = i;
            break;
        }
    }
    cout<<"thrshint "<<threshInt<<endl;

//    for(int i = 0; i < row; i++){
//        for(int j = 0; j < column; j++){
//            finalImage[i][j] = (unsigned char)(((finalImage[i][j]- Pixel_min)/(Pixel_max - Pixel_min))*255.0);
//        }
//    }
//
    for(int r=0;r<row;r++){
        for(int w=0;w<column;w++){
            if(finalImage[r][w]>=threshInt){
                finalImage[r][w] = 0;
            }
            else{
                finalImage[r][w] = 255;
            }
        }
    }

    return finalImage;
}


int main(int argc, char *argv[]){
	FILE *file;
    const int BytesPerPixel = 3;
	//int Size = 256;
	int Height = 321;
    const int Width = 481;
		// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	// Check if image is grayscale or color//
    cout<<"sid1"<<endl;
	unsigned char Imagedata[Height][Width][BytesPerPixel];
    cout<<"sid2"<<endl;
	// Read image (filename specified by first argument) into image data matrix

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);
    cout<<"sid3"<<endl;
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    float ImageBW[Height][Width];
    float sum = 0;
    unsigned char finalImage[321][481];
   for(int h=0;h<Height;h++){
    for(int w=0;w<Width;w++){
            sum = 0;
        for(int c=0;c<3;c++){
            sum+=(float)Imagedata[h][w][c]/3.0;
        }
        ImageBW[h][w] = (sum);
        //finalImage[h][w] = (unsigned char)sum;
    }
   }


    float** ImageOut;
//    unsigned char SX[Height][Width] = {0};
    cout<<"sid4"<<endl;
//    unsigned char SY[Height][Width] = {0};
//    int** SY;
//    SY = new int* [Height];
//    for(int i=0;i<Height;i++){
//        SY[i] = new int [Width];
//    }
    cout<<"sid5"<<endl;
//    int** SX;
//    SX = new int* [Height];
//    for(int i=0;i<Height;i++){
//        SX[i] = new int [Width];
//    }
    cout<<"sid6"<<endl;
    ImageOut = sobelEdge(ImageBW,Height,Width);
    cout<<"sid7"<<endl;


    for(int h=0;h<Height;h++){
        for(int w=0;w<Width;w++){
            //cout<<h<<" "<<w<<" "<<(int)ImageOut[h][w]<<endl;
            finalImage[h][w] = (unsigned char)ImageOut[h][w];
        }
	}
    cout<<"sid8"<<endl;
//    int sobelThrsh = 0;
//    for(int i=0;i<Height;i++){
//        for(int j=0;j<Width;j++){
//            cout<<"R "<<i<<" W "<<j<<" PV "<<(uint8_t)ImageOut[i][j]<<endl;
//            if(ImageOut[i][j]>sobelThrsh){
//                sobelThrsh = SY[i][j];
//            }
//        }
//    }
//
//    cout<<"max"<<sobelThrsh*0.9<<endl;
//
//    for(int i=0;i<Height;i++){
//        for(int j=0;j<Width;j++){
//            cout<<"R "<<i<<" W "<<j<<" PV "<<(uint8_t)ImageOut[i][j]<<endl;
//            if(ImageOut[i][j]>sobelThrsh*0.7){
//                ImageOut[i][j] = 0;
//            }
//            else{
//                ImageOut[i][j] = 255;
//            }
//        }
//    }

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(finalImage, sizeof(unsigned char), Height*Width*1, file);
	fclose(file);

	return 0;
}
