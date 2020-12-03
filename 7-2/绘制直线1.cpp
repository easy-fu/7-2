#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main()
{
	
	cv::Mat srcMat= cv::imread("C:/Users/DELL/Desktop/18.jpg", 1);
	if (srcMat.empty())
	{
		std::cout << "failed to read image!" << std::endl;
		return - 1;
	}
	Mat cannyMat;
	cv::Mat dx;
	cv::Mat dy;
	Mat lineMat;

	Sobel(srcMat, dy, CV_16SC1, 0, 2, 3);
	Sobel(srcMat, dx, CV_16SC1, 1, 0, 3);
	Canny(dx, dy, cannyMat, 60, 180);

	cv::HoughLines(cannyMat, lineMat, 1, CV_PI / 180, 100);
	int height = lineMat.rows;
	int width = lineMat.cols;
	
	for (int i=0; i<height; i++)
	{
		for(int j=0;j<width;j++)
		{
			float rho = lineMat.at<Vec3f>(i, j)[0], theta = lineMat.at<Vec3f>(i, j)[1];
			cv::Point pt1, pt2;
			double a = cos(theta);
			double b = sin(theta);
			double x0 = a * rho;
			double y0 = b * rho;

			pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
			pt1.y = saturate_cast<int>(y0 + 1000 * (a));
			pt2.x = saturate_cast<int>(x0 -1000 * (-b));
			pt2.y= saturate_cast<int>(y0 -1000 * (a));
			cv::line(srcMat, pt1, pt2,cv::Scalar(0, 0, 255), 1, CV_AA);
		}
	}
	
	imshow("srcMat", srcMat);
	imshow("cannyMat", cannyMat);
	cv::waitKey(0);

}