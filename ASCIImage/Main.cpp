#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

char numToChar(int index) {
	char ascii[11] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@', '@'};
	float out = floor(((float)index / 255.0) * 10.0);

	//cout << out;

	return ascii[(int) out];
}

int main() {
	// Crop values
	int minCropX = 24;		// Min width crop
	int maxCropX = 30;		// Max Width crop
	int minCropY = 99;		// Min height crop
	int maxCropY = 110;		// Max height crop

	// Resize values
	int resizeY = 8;		// height resize value
	int resizeX = 8;		// Width resize value

	// Read image
	Mat srcImage = imread("C:/Users/Rey/Documents/My Coding/C++/ASCIImage/ASCIImage/Cat no bg.jpg");

	// If no image was found, stop the program
	if (srcImage.empty()) {
		cout << "Can't open image file\n";
		cin.get();
		return -1;
	}

	string winName = "ASCIImage";

	namedWindow(winName);
	imshow(winName, srcImage);

	// Crop image
	Mat cropImage = srcImage(
		Range(minCropY, srcImage.size().height - maxCropY), 
		Range(minCropX, srcImage.size().width - maxCropX)
	);

	// Resize
	Mat resizeImage; 
	resize(
		cropImage, 
		resizeImage, 
		Size(cropImage.size().height / resizeY, cropImage.size().width / resizeX), 
		INTER_LINEAR
	);

	cout << "Width: " << resizeImage.size().width << endl;
	cout << "Height: " << resizeImage.size().height << endl;
	
	// Convert it to vector;
	vector<uchar> output;
	output.assign(resizeImage.data, resizeImage.data + resizeImage.total() * resizeImage.channels());

	cout << system("cls");
	cout << endl << endl;

	// Print to console
	int widthSize = output.size() / resizeImage.size().width;
	for (int i = 0; i < output.size(); i++) {
		if (i % widthSize == 0) cout << endl;

		cout << numToChar(int(output[i]));
	}

	cout << endl;

	waitKey(0);

	return 0;
}