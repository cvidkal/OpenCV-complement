#include "getMatch.h"
#include "anms.h"


int main()
{
	Ptr<FastFeatureDetector> fast = FastFeatureDetector::create();
	Ptr<ORB> orb = ORB::create();

	Mat img = imread("1.png");
	Mat img2 = imread("2.png");
	vector<KeyPoint> kpts1, kpts2;
	vector<KeyPoint> apts1, apts2;
	fast->detect(img, kpts1);
	fast->detect(img2, kpts2);
	orb->detect(img, kpts1);
	Mat o;
	drawKeypoints(img, kpts1, o);
	imshow("orb", o);
	cvWaitKey(0);
	Mat desp1, desp2;
	Mat adesp1, adesp2;
	orb->detectAndCompute(img, Mat(), kpts1, desp1);
	orb->detectAndCompute(img2, Mat(), kpts2, desp2);
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
	vector<vector<DMatch>> dmatches;
	matcher->knnMatch(desp1, desp2, dmatches, 2);
	GetMatch getMatch = GetMatch(dist_ratioCheck, 0.6, 90);
	vector<int> idx;
	getMatch(dmatches, idx);
	vector<DMatch> dmatch;
	getMatch.GetDMatch(dmatches, idx, dmatch);
	Mat out;
	drawMatches(img, kpts1, img2, kpts2, dmatch, out);
	imshow("orb match", out);
	cout << "match ratio:"<<dmatch.size() / (double)dmatches.size() << endl;

	cvWaitKey(0);
}