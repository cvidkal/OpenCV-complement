#include "getMatch.h"
#include "anms.h"



int main()
{
	Mat a = imread("1.png");
	vector<KeyPoint> kpts;
	Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();
	fast->detect(a, kpts);
	vector<int> idx;
	anms(kpts, 500, idx,a.size());
	Mat out;
	drawKeypoints(a, kpts, out);
	
	imshow("ttt", out);
	cvWaitKey(0);
}