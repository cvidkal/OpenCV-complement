#include "getMatch.h"
#include "anms.h"
#include "TickMeter.h"


int main()
{
	Mat a = imread("1.png");
	Mat b = imread("2.png");
	vector<KeyPoint> kpts,kpts2;
	Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();
	fast->detect(a, kpts);
	fast->detect(b, kpts2);

	vector<int> idx;
	TickMeter tm;
	tm.start();
	anms(kpts, 500, idx,a.size());
	tm.stop();
	cout << tm.getTimeSec() << endl;

	tm.reset();
	tm.start();
	anms(kpts2, 500, idx, a.size());
	tm.stop();
	cout << tm.getTimeSec() << endl;

	Mat out;
	drawKeypoints(a, kpts, out);
	
	imshow("ttt", out);
	cvWaitKey(0);
}