#ifndef __ANMS_H__
#define __ANMS_H__


#include <opencv2\opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

void anms(std::vector<KeyPoint> & keypoints, const int k, std::vector<int> &idx, cv::Size imgSize);


#endif