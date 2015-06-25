#include "draw.h"





Mat drawTrackLine(const Mat &img,const vector<KeyPoint> &origin,const vector<KeyPoint> &now,const vector<DMatch> &dmatch,Scalar color,int thickness)
{
	Mat ret = img.clone();
	for (auto &i : dmatch)
	{
		line(ret, origin[i.trainIdx].pt, now[i.queryIdx].pt, color, thickness);
	}
	return ret;
}


Mat drawInfo(const Mat &img, const string &str, const Point2i &pos, Scalar color, int thickness)
{
	Mat ret = img.clone();
	putText(ret, str, pos, cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, color, thickness);
	return ret;
}