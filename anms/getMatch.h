#ifndef __GETMATCH_H_
#define __GETMATCH_H_

#include <opencv2\opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

enum matchType
{
	distCheck = 0x01,
	ratioCheck = 0x02,
	dist_ratioCheck = 0x04,
};

class GetMatch
{
	
public:
	GetMatch(matchType type, double ratio = 0.6, double distance = 90)
	{
		_type = type;
		_ratio = ratio;
		_distance = distance;
	}
	~GetMatch();
	static void GetDMatch(const vector<vector<DMatch>> &dmatches, const vector<int>&idx, vector<DMatch> &dmatch);
	static void GetDMatch(vector<DMatch> &dmatch, const vector<int>&idx);
	template<typename T>
	static void GetMaskObj(vector<T> &dmatch, const Mat& mask);
	template<typename T> static 
	void GetMaskObj(vector<T> &dmatch, const vector<int>&mask);
	static void GetInliers(const vector<vector<DMatch>> &dmatches, vector<int> &idx, double _ratio, double _distance = -1);
	static void GetInliers (const vector<DMatch> &dmatch, vector<int> &idx,double _distance=90);
	static void preparePoint2D(const vector<KeyPoint> &query, const vector<KeyPoint> train, const vector<DMatch> &dmatch, vector<Point2f> &query2D, vector<Point2f> &train2D);
private:
	matchType _type;
	double _ratio;
	double _distance;
};


template<typename T>
void GetMatch::GetMaskObj(vector<T> &dmatch, const vector<int>&mask)
{
	vector<T> temp;
	for (auto i : mask)
	{
		temp.push_back(dmatch[i]);
	}
	dmatch = temp;
}
template<typename T>
void GetMatch::GetMaskObj(vector<T> &dmatch, const Mat& mask)
{
	CV_Assert(dmatch.size() == mask.rows);
	vector<T> temp;
	for (size_t i = 0; i < mask.rows; i++)
	{
		if (mask.at<char>(i))
		{
			temp.push_back(dmatch[i]);
		}
	}
	dmatch = temp;
}



#endif