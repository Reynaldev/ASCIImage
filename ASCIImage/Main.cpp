#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

enum Convert {
	Image,
	Video
};

char numToChar(int index) {
	char ascii[11] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@', '@'};
	int out = floor(((float)index / 255.0) * 10.0);

	//cout << out;

	return ascii[out];
}

int main() {
	// Use power of 2 (2, 4, 8, 16, 32...) when cropping and resizing for better result
	// Crop values
	int minCropX = 232;		// Min width crop
	int maxCropX = 232;		// Max Width crop
	int minCropY = 112;		// Min height crop
	int maxCropY = 112;		// Max height crop

	// Resize values
	int resizeY = 8;		// height resize value
	int resizeX = 8;		// Width resize value

	// Config
	Convert convert = Video;
	string winName = "ASCIImage";

	if (convert == Image) {
		// Read image
		Mat srcImage = imread( "C:/Users/Rey/Documents/My Coding/C++/ASCIImage/ASCIImage/Milos.jpg");

		// If no image was found, stop the program
		if (srcImage.empty()) {
			cout << "Can't open image file\n";
			cin.get();
			return -1;
		}

		// Window
		namedWindow(winName);
		imshow(winName, srcImage);

		// Crop the image (Only crop when needed)
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

		system("cls");

		// Print to console
		int widthSize = output.size() / resizeImage.size().width;
		for (int i = 0; i < output.size(); i++) {
			if (i % widthSize == 0) cout << endl;

			cout << numToChar(int(output[i]));
		}

		cout << endl;

		waitKey(0);
	}
	else if (convert == Video) {
		// Get video
		VideoCapture cap("C:/Users/Rey/Documents/My Coding/C++/ASCIImage/ASCIImage/Cat-Jump.mp4");

		// Check
		if (!cap.isOpened()) {
			cout << "Cannot open the video file\n";
			cin.get();
			return -1;
		}

		// Window
		namedWindow(winName);

		system("cls");

		while (cap.isOpened()) {
			// Read new frame
			Mat frame;
			bool success = cap.read(frame);

			// Video loop
			// If we reach the end frame, set position back from the start
			if (success == false) {
				//cout << "Reached the end frame\n";
				break;
			}

			// Show
			imshow(winName, frame);

			// Crop the image (Only crop when needed)
			Mat cropFrame = frame(
				Range(minCropY, frame.size().height - maxCropY),
				Range(minCropX, frame.size().width - maxCropX)
			);

			// Resize
			Mat resizeFrame;
			resize(
				cropFrame,
				resizeFrame,
				Size(cropFrame.size().height / resizeY, cropFrame.size().width / resizeX),
				INTER_LINEAR
			);

			//cout << "Width: " << resizeFrame.size().width << endl;
			//cout << "Height: " << resizeFrame.size().height << endl;

			// Convert it to vector;
			vector<uchar> output;
			output.assign(resizeFrame.data, resizeFrame.data + resizeFrame.total() * resizeFrame.channels());

			system("cls");

			// Print to console
			int widthSize = output.size() / resizeFrame.size().width;
			for (int i = 0; i < output.size(); i++) {
				if (i % widthSize == 0) cout << endl;

				cout << numToChar(int(output[i]));
			}

			// If the Esc key is pressed
			if (waitKey(10) == 27) {
				cout << "Esc key is pressed. Stopping the video.\n";
				break;
			}
		}
	}

	return 0;
}