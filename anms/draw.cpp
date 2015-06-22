#include "draw.h"





Mat drawTrackLine(const Mat &img,const vector<KeyPoint> &origin,const vector<KeyPoint> &now,const vector<DMatch> &dmatch,Scalar color = CV_RGB(255,255,0),int thickness = 5)
{
	Mat ret = img.clone();
	for (auto &i : dmatch)
	{
		line(ret, origin[i.trainIdx].pt, now[i.queryIdx].pt, color, thickness);
	}
	return ret;
}