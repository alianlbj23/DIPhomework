#include "library.h"
using namespace std;
using namespace cv;

void DrawPicture(cv::Mat image, std::string name) {
	namedWindow(name);
	imshow(name, image);
}

Mat padding(Mat img) {
	Mat src(img.rows + 2, img.cols + 2, CV_8UC1);
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (i == 0 || i == src.rows - 1) {
				src.at<uchar>(i, j) = 0;
			}
			else if (j == 0 || j == src.cols - 1) {
				src.at<uchar>(i, j) = 0;
			}
			else {
				src.at<uchar>(i, j) = img.at<uchar>(i-1, j-1);
			}
		}
	}
	return src;
}

Mat BoxFilter(Mat img) {
	int sum = 0, rowIndex = 0, colIndex = 0;
	Mat src(img.rows, img.cols, CV_8UC1);

	for (int i = 1; i < img.rows-1; i++) {
		for (int j = 1; j < img.cols-1; j++) {
			rowIndex = i - 1;
			colIndex = j - 1;//準備從九宮格的左上角開始跑
			sum = 0;
			for (int count = 1; count <= 9; count++) { //9個連加
				sum += (int)img.at<uchar>(rowIndex, colIndex);
				colIndex += 1;
				if (count%3==0) {
					rowIndex += 1;
					colIndex = j-1;
				}
			}
			sum = sum / 9;
			src.at<uchar>(i, j) = sum;
		}
	}
	return src;
}

Mat MediaFilter(Mat img) {
	int sum = 0, rowIndex = 0, colIndex = 0, index = 0;
	Mat src(img.rows, img.cols, CV_8UC1);
	int dataArray[9] = { 0 };
	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			rowIndex = i - 1;
			colIndex = j - 1;//準備從九宮格的左上角開始跑
			index = 0;
			for (int count = 1; count <= 9; count++) { //9個連加
				dataArray[index++] = (int)img.at<uchar>(rowIndex, colIndex);
				colIndex += 1;
				if (count % 3 == 0) {
					rowIndex += 1;
					colIndex = j - 1;
				}
			}
			/*for (int z = 0;z < 9;z++) {
				cout << dataArray[z] <<" ";
			}
			puts("");*/
			sort(dataArray, dataArray + 9);
			src.at<uchar>(i, j) = dataArray[4];
		}
	}
	return src;
}

Mat Laplacian(Mat img) {
	int sum = 0, rowIndex = 0, colIndex = 0, index = 0;
	Mat src(img.rows, img.cols, CV_8UC1);
	int dataArray[9] = { 0 , -1, 0, -1, 5, -1, 0, -1, 0};
	for (int i = 1; i < img.rows - 1; i++) {
		for (int j = 1; j < img.cols - 1; j++) {
			rowIndex = i - 1;
			colIndex = j - 1;//準備從九宮格的左上角開始跑
			sum = 0;
			index = 0;
			for (int count = 1; count <= 9; count++) { //9個連加
				sum += (int)img.at<uchar>(rowIndex, colIndex)* dataArray[index++];
				colIndex += 1;
				if (count % 3 == 0) {
					rowIndex += 1;
					colIndex = j - 1;
				}
			}
			/*for (int z = 0;z < 9;z++) {
				cout << dataArray[z] <<" ";
			}
			puts("");*/
			if (sum > 255) {
				sum = 255;
			}
			else if (sum < 0) {
				sum = 0;
			}
			src.at<uchar>(i, j) = sum;
		}
	}
	return src;
}