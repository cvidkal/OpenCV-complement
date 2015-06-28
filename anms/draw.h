#ifndef __DRAW_H_
#define __DRAW_H_

#include <opencv2\opencv.hpp>

#include <vector>
using namespace cv;
using namespace std;


/*
	This function is used for drawing feature tracking line between former image and current image.
*/
Mat drawTrackLine(const Mat &img, const vector<KeyPoint> &origin, const vector<KeyPoint> &now, const vector<DMatch> &dmatch, Scalar color = CV_RGB(255, 255, 0), int thickness = 1);
Mat drawTrackLine(const Mat&img, const vector<Point2f> &origin, const vector<Point2f> &now, Scalar color = CV_RGB(255, 255, 0), int thickness = 1);
/*
	This funtion is designed for displaying Debug information
*/
Mat drawInfo(const Mat &img, const string &str, const Point2i &pos, Scalar color = CV_RGB(0, 255, 255), int thickness = 1);

#endif