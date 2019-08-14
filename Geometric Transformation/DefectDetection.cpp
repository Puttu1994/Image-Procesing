#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <iterator>

using namespace std;


int defect_mask[9]  = {1,1,1,1,0,1,1,1,1};

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



int convolutionMorph(int input_image[691][550], int row, int col, int image_Height, int image_Width){

    int morphsum = 0;
    int maskcount = 0;


    for(int h=0;h<3;h++){
        for(int w=0;w<3;w++){
            if((defect_mask[w+maskcount]*255) == input_image[border_extnsn(row+h-1,image_Height)][border_extnsn(col+w-1,image_Height)]){
                morphsum++;
            }
        }
        maskcount += 3;
    }
    return morphsum;
}



void morphParser(int Image[][550], int Height, int Width, bool &defect, int &defectCount){

    int finalImage[691][550] = {0};
    int update = 0;

    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){

            update = convolutionMorph(Image,i,j,Height,Width);

            if(update == 9){
                defect = true;
                defectCount++;
                Image[i][j] = 255;
            }
        }

    }
    cout<<defectCount<<" "<<defect<<endl;


}

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int BytesPerPixel = 1;
	int Height = 691;
	int Width = 550;

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

    int originalImage[691][550];
    bool defect = false;
    int defectCount = 0;

    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            originalImage[i][j] = (int)Imagedata[i][j][0];
        }
    }


    morphParser(originalImage, Height, Width,defect,defectCount);

    if(defect){
        cout<<"Total Defect: "<<defectCount<<endl;
    }

    else{
        cout<<"There are no Defects!!"<<endl;
    }


    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            Imagedata[i][j][0] = (unsigned char)originalImage[i][j];
        }
    }






    // Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite((unsigned char*)Imagedata, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
