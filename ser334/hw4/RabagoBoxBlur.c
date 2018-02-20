////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
//MACRO DEFINITIONS

#pragma warning(disable: 4996)

//problem assumptions
#define BMP_HEADER_SIZE_BYTES 14
#define BMP_DIB_HEADER_SIZE_BYTES 40
#define MAXIMUM_IMAGE_SIZE 256

//bmp compression methods
//none:
#define BI_RGB 0

////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

struct BMP_Header {
	char signature[2];		//ID field
	int size;			//Size of the BMP file
	short reserved1;		//Application specific
	short reserved2;		//Application specific
	int offset_pixel_array;  	//Offset where the pixel array (bitmap data) can be found
};

struct DIB_Header {
	int header_size;		
	int width, height;
	short planes, bpp;
	int compression, image_size,
	xPPM, yPPM, CCT, ICC;
};

typedef struct{
	uint8_t blue;
	uint8_t green;
	uint8_t red;
}pixel;

////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE

void main(int argc, char* argv[]) {

	//sample code to read first 14 bytes of BMP file format
	FILE* file = fopen( argv[1], "rb");
	struct BMP_Header header;
	struct DIB_Header bheader;
	pixel **image, **output;
	char zero = 0;

	//read bitmap file header (14 bytes)
	fread(&header.signature, sizeof(char)*2, 1, file);
	fread(&header.size, sizeof(int), 1, file);
	fread(&header.reserved1, sizeof(short), 1, file);
	fread(&header.reserved2, sizeof(short), 1, file);
	fread(&header.offset_pixel_array, sizeof(int), 1, file);
	
	//printf("signature: %c%c\n",header.signature[0], header.signature[1]);
	//printf("size: %d\n", header.size);
	//printf("offset_pixel_array: %d\n", header.offset_pixel_array);

	fread(&bheader.header_size, sizeof(int), 1, file); 
	fread(&bheader.width, sizeof(int), 1, file);
	fread(&bheader.height, sizeof(int), 1, file);
	fread(&bheader.planes, sizeof(short), 1, file);
	fread(&bheader.bpp, sizeof(short), 1, file);
	fread(&bheader.compression, sizeof(int), 1, file);
	fread(&bheader.image_size, sizeof(int), 1, file);
	fread(&bheader.xPPM, sizeof(int), 1, file);
	fread(&bheader.yPPM, sizeof(int), 1, file);
	fread(&bheader.CCT, sizeof(int), 1, file);
	fread(&bheader.ICC, sizeof(int), 1, file);
	
	image = malloc(sizeof(pixel) * bheader.height * bheader.width);
	for(int i=0;i<bheader.width;i++) 
		image[i] = (pixel *)malloc(sizeof(pixel) * bheader.width);

	
	//printf("width: %d\n",bheader.width);
	//printf("height: %d\n",bheader.height);
	
	int padding = 3*bheader.width%4;
	if(padding != 0){
		padding = 4 - padding;	
	}

	fseek(file,54,SEEK_SET);
	for(int i=0;i<bheader.height;i++){
		for(int j=0;j<bheader.width;j++){
			fread(&image[i][j].blue, sizeof(uint8_t),1,file);
			fread(&image[i][j].green, sizeof(uint8_t),1,file);
			fread(&image[i][j].red, sizeof(uint8_t),1,file);

			//printf("%d,%d(bgr) : %d,%d,%d\n",i,j,
			//image[i][j].blue,image[i][j].green,image[i][j].red);
		}

		fseek(file,padding,SEEK_CUR);
	}

	output = malloc(sizeof(pixel) * bheader.height * bheader.width);
	for(int i=0;i<bheader.width;i++) 
		output[i] = (pixel *)malloc(sizeof(pixel) * bheader.width);

	for(int i=0;i<bheader.height;i++){
		for(int j=0;j<bheader.width;j++){
			if( i == 0 && j == 0 ){

				output[i][j].blue = 
				(image[i][j].blue + image[i+1][j].blue + image[i][j+1].blue + image[i+1][j+1].blue)/4;

				output[i][j].green = 
				(image[i][j].green + image[i+1][j].green + image[i][j+1].green + image[i+1][j+1].green)/4;

				output[i][j].red = 
				(image[i][j].red + image[i+1][j].red + image[i][j+1].red + image[i+1][j+1].red)/4;

			}else if( i == 0 && j == bheader.width-1){

				output[i][j].blue = 
				(image[i][j].blue + image[i+1][j].blue + image[i][j-1].blue + image[i+1][j-1].blue)/4;

				output[i][j].green = 
				(image[i][j].green + image[i+1][j].green + image[i][j-1].green + image[i+1][j-1].green)/4;

				output[i][j].red = 
				(image[i][j].red + image[i+1][j].red + image[i][j-1].red + image[i+1][j-1].red)/4;

			}else if( i == bheader.height-1 && j == 0){

				output[i][j].blue = 
				(image[i][j].blue + image[i-1][j].blue + image[i][j+1].blue + image[i-1][j+1].blue)/4;

				output[i][j].green = 
				(image[i][j].green + image[i-1][j].green + image[i][j+1].green + image[i-1][j+1].green)/4;

				output[i][j].red = 
				(image[i][j].red + image[i-1][j].red + image[i][j+1].red + image[i-1][j+1].red)/4;

			}else if( i == bheader.height-1 && j == bheader.width-1){

				output[i][j].blue = 
				(image[i][j].blue + image[i-1][j].blue + image[i][j-1].blue + image[i-1][j-1].blue)/4;

				output[i][j].green = 
				(image[i][j].green + image[i-1][j].green + image[i][j-1].green + image[i-1][j-1].green)/4;

				output[i][j].red = 
				(image[i][j].red + image[i-1][j].red + image[i][j-1].red + image[i-1][j-1].red)/4;

			}else if( i == 0 ){

				output[i][j].blue = 
				(image[i][j].blue + image[i][j+1].blue + image[i][j-1].blue 
				+ image[i+1][j].blue + image[i+1][j+1].blue + image[i+1][j-1].blue)/6;

				output[i][j].green = 
				(image[i][j].green + image[i][j+1].green + image[i][j-1].green 
				+ image[i+1][j].green + image[i+1][j+1].green + image[i+1][j-1].green)/6;

				output[i][j].red = 
				(image[i][j].red + image[i][j+1].red + image[i][j-1].red 
				+ image[i+1][j].red + image[i+1][j+1].red + image[i+1][j-1].red)/6;
				
			}else if( i == bheader.height-1 ){

				output[i][j].blue = 
				(image[i][j].blue + image[i][j+1].blue + image[i][j-1].blue 
				+ image[i-1][j].blue + image[i-1][j+1].blue + image[i-1][j-1].blue)/6;

				output[i][j].green = 
				(image[i][j].green + image[i][j+1].green + image[i][j-1].green 
				+ image[i-1][j].green + image[i-1][j+1].green + image[i-1][j-1].green)/6;

				output[i][j].red = 
				(image[i][j].red + image[i][j+1].red + image[i][j-1].red 
				+ image[i-1][j].red + image[i-1][j+1].red + image[i-1][j-1].red)/6;

			}else if( j == 0 ){

				output[i][j].blue = 
				(image[i][j].blue + image[i][j+1].blue + image[i-1][j].blue 
				+ image[i+1][j].blue + image[i+1][j+1].blue + image[i+1][j+1].blue)/6;

				output[i][j].green = 
				(image[i][j].green + image[i][j+1].green + image[i-1][j].green 
				+ image[i+1][j].green + image[i+1][j+1].green + image[i+1][j+1].green)/6;

				output[i][j].red = 
				(image[i][j].red + image[i][j+1].red + image[i-1][j].red 
				+ image[i+1][j].red + image[i+1][j+1].red + image[i+1][j+1].red)/6;

			}else if( j == bheader.width-1 ){
				
				output[i][j].blue = 
				(image[i][j].blue + image[i][j-1].blue + image[i-1][j].blue 
				+ image[i+1][j].blue + image[i+1][j-1].blue + image[i+1][j-1].blue)/6;

				output[i][j].green = 
				(image[i][j].green + image[i][j-1].green + image[i-1][j].green 
				+ image[i+1][j].green + image[i+1][j-1].green + image[i+1][j-1].green)/6;

				output[i][j].red = 
				(image[i][j].red + image[i][j-1].red + image[i-1][j].red 
				+ image[i+1][j].red + image[i+1][j-1].red + image[i+1][j-1].red)/6;

			}else {

				output[i][j].blue = 
				( image[i-1][j-1].blue + image[i-1][j].blue + image[i-1][j+1].blue 
				+ image[i][j-1].blue + image[i][j].blue + image[i][j+1].blue
				+ image[i+1][j-1].blue + image[i+1][j].blue + image[i+1][j+1].blue)/9;

				output[i][j].green = 
				( image[i-1][j-1].green + image[i-1][j].green + image[i-1][j+1].green 
				+ image[i][j-1].green + image[i][j].green + image[i][j+1].green
				+ image[i+1][j-1].green + image[i+1][j].green + image[i+1][j+1].green)/9;

				output[i][j].red = 
				( image[i-1][j-1].red + image[i-1][j].red + image[i-1][j+1].red 
				+ image[i][j-1].red + image[i][j].red + image[i][j+1].red
				+ image[i+1][j-1].red + image[i+1][j].red + image[i+1][j+1].red)/9;
				
			}
			
		}
	}

	fclose(file);
	free(image);

	if( argv[2] != NULL ){
		file = fopen( argv[2], "wb");
		fwrite(header.signature,2,1,file);
		fwrite(&header.size,sizeof(int),1,file);
		fwrite(&header.reserved1,sizeof(short),1,file);
		fwrite(&header.reserved2,sizeof(short),1,file);
		fwrite(&header.offset_pixel_array,sizeof(int),1,file);
		fwrite(&bheader, sizeof(struct DIB_Header),1,file);
		
		for(int i=0;i<bheader.height;i++){
			for(int j=0;j<bheader.width;j++){
				fwrite(&output[i][j],sizeof(pixel),1,file);
			}
			fwrite(&zero, 1, padding, file);
		}
		fclose(file);
	}
}
