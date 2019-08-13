#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<math.h>



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


void floydSteinberg(float*** outputMatrix, int error, int row, int col,int direction, int height, int width, int ch){

  //  cout<<"Nandeeeee"<<endl;
//    int FSF[3][3] = {{0,0,0},{0,0,7},{3,5,1}};
//    int FSR[3][3] = {{0,0,0},{7,0,0},{1,5,3}};

//    int FSF[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,7,5},{3,5,7,5,3},{1,3,5,3,1}};
//    int FSR[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{5,7,0,0,0},{3,5,7,5,3},{1,3,5,3,1}};

    int FSF[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,8,4},{2,4,8,4,2},{1,2,4,2,1}};
    int FSR[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{8,4,0,0,0},{2,4,8,4,2},{1,2,4,2,1}};
    for(int h=0;h<5;h++){

        if(direction==0){


            for(int w=0;w<5;w++){
                    if((row+h-2)<0 || (row+h-2)> (height-1) || (col+w-2)<0 || (col+w-2) > (width-1)){
                    //cout<<"direction 0"<<row<<" "<<col<<endl;
                    continue;
                }

                    else{
                        //cout<<"BenqBF"<<" "<<outputMatrix[row+h-1][col+w-1]<<"row "<<row<<" col "<<col<<endl;
                        //cout<<"Error1"<<error<<" "<<FSF[h][w]/16<<" "<<error*(FSF[h][w]/16)<<" "<<outputMatrix[row+h-1][col+w-1]+ error*(FSF[h][w]/16)<<endl;
                        outputMatrix[row+h-2][col+w-2][ch] += (float)(error * ((FSF[h][w]/42.0)));
                        //cout<<"BenqAF"<<" "<<outputMatrix[row+h-1][col+w-1]<<"row "<<row<<" col "<<col<<endl;
                    }


            }
        }

        else{

                for(int w=4;w>=0;w--){
                        if((row+h-2)<0 || (row+h-2)> (height-1) || (col+w-2)<0 || (col+w-2) > (width-1)){
                    //cout<<"direction 1"<<row<<" "<<col<<endl;
                        continue;
                    }

                    else{
                        //cout<<"MSIBF"<<outputMatrix[row+h-1][col+w-1]<<"row "<<row<<" col "<<col<<endl;
                        //cout<<"Error2"<<error<<" "<<FSR[h][w]/16<<" "<<error*(FSR[h][w]/16)<<" "<<outputMatrix[row+h-1][col+w-1]+ error*(FSF[h][w]/16)<<endl;
                        outputMatrix[row+h-2][col+w-2][ch] += (float)(error * (FSR[h][w]/42.0));
                        //cout<<"MSIAF"<<outputMatrix[row+h-1][col+w-1]<<"row "<<row<<" col "<<col<<endl;
                    }

            }

        }
    }


}

unsigned char*** serpentineParser(float*** outputMatrix, int Height, int Width){

//    double** outputMatrix;
//    outputMatrix = new double*[Height];
//    for(int h=0;h<Height;h++){
//        outputMatrix[h] = new double [Width];
//    }
//
//
//    for(int h=0;h<Height;h++){
//        for(int w=0;w<Width;w++){
//            outputMatrix[h][w] = original_Image[h][w][0];
//        }
//    }

    unsigned char*** finalImage;
    finalImage = new unsigned char** [400];
    for(int i=0;i<Height;i++){
        finalImage[i] = new unsigned char* [600];
        for(int j=0;j<Width;j++){
            finalImage[i][j] = new unsigned char[3];
        }
    }
    int error = 0;
    int thrshValue = 0;
//    cout<<Height<<" "<<Width<<endl;


    for(int h=0;h<Height;h++){
       // cout<<"Siddartha "<<Height<<" "<<Width<<endl;
        if(h%2==0)
        {
            for(int ch=0;ch<3;ch++){

                for(int w=0;w<Width;w++){
                error = 0;
                thrshValue = 0;
//            if(outputMatrix[h][w]>255){
//                outputMatrix[h][w] = 255;
//            }
//            if(outputMatrix[h][w]<0){
//                outputMatrix[h][w] = 0;
//            }
                if(outputMatrix[h][w][ch] >= 127){
                thrshValue = 255;
                }
                else{
                    thrshValue = 0;
                }

                error =  (outputMatrix[h][w][ch] - thrshValue);
                finalImage[h][w][ch] = thrshValue;
                floydSteinberg(outputMatrix, error, h, w, 0, Height, Width,ch);
                }



            }

        }

        else{

            for(int ch=0;ch<3;ch++){

                for(int w=Width-1;w>=0;w--){
                error = 0;
                thrshValue = 0;
//            if(outputMatrix[h][w]>255){
//                outputMatrix[h][w] = 255;
//            }
//            if(outputMatrix[h][w]<0){
//                outputMatrix[h][w] = 0;
//            }
                if(outputMatrix[h][w][ch] >= 127){
                    thrshValue = 255;
                }
                else{
                    thrshValue = 0;
                }
                error = (outputMatrix[h][w][ch] - thrshValue);
                finalImage[h][w][ch] = thrshValue;
                floydSteinberg(outputMatrix, error, h, w, 1, Height, Width,ch);
            }

            }

        }
    }
    return finalImage;
}



int main(int argc, char *argv[]){
    cout<<"0"<<endl;
	FILE *file;
    const int BytesPerPixel = 3;
	//int Size = 256;
	int Height = 375;
	const int Width = 500;
		// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	// Check if image is grayscale or color//
	unsigned char Imagedata[Height][Width][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix

	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	//cout<<"im here 2"<<endl;


    cout<<"1"<<endl;
    //cout<<"height "<<Height<<" Width "<<Width<<endl;
//    unsigned char** ImageOut;
    float*** errorDiff;
    errorDiff = new float** [Height];
    for(int i=0;i<Height;i++){
        errorDiff[i] = new float* [Width];
        for(int j=0;j<Width;j++){
            errorDiff[i][j] = new float [3];
        }
    }
//    cout<<"im here 3"<<endl;
    cout<<"2"<<endl;
	for(int h=0;h<Height;h++){
        for(int w=0;w<Width;w++){
                for(int ch=0;ch<3;ch++){
                    errorDiff[h][w][ch] = (float)Imagedata[h][w][ch];
                }
        }
	}





  //  cout<<"im here 4"<<endl;

//    cout<<"height "<<Height<<" Width "<<Width<<endl;

    cout<<"3"<<endl;
	unsigned char*** ImageOut = serpentineParser(errorDiff,Height, Width);

//    cout<<"height "<<Height<<" Width "<<Width<<endl;
//	for(int h=0;h<Height;h++){
//        for(int w=0;w<Width;w++){
//            cout<<h<<" "<<w<<" "<<(int)ImageOut[h][w]<<endl;
////            ImageOut[h][w] = errorDiff[h][w];
//        }
//	}
    cout<<"4"<<endl;
    unsigned char finalImage[375][500][3];

    cout<<"5"<<endl;
    for(int h=0;h<Height;h++){
        for(int w=0;w<Width;w++){
              for(int ch=0;ch<1;ch++){
    //            cout<<h<<" "<<w<<" "<<(int)ImageOut[h][w]<<endl;
                finalImage[h][w][ch] = ImageOut[h][w][ch];
              }
        }
	}
    cout<<"6"<<endl;
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite((unsigned char*)finalImage, sizeof(unsigned char), Height*Width*1, file);
	fclose(file);

	return 0;
}

