#ifndef __DRAW_H_
#define __DRAW_H_

#include <opencv2\opencv.hpp>

#include <vector>
using namespace cv;
using namespace std;


/*
	This function is used for drawing feature tracking line between former image and current image.
*/
Mat drawTrackLine(const Mat &img, const vector<KeyPoint> &origin, const vector<KeyPoint> &now, const vector<DMatch> &dmatch, Scalar color = CV_RGB(255, 255, 0), int thickness = 5);


#endif