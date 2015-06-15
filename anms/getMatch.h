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

	void GetDMatch(const vector<vector<DMatch>> &dmatches, const vector<int>&idx, vector<DMatch> &dmatch);

	void operator() (const vector<vector<DMatch>> &dmatches, vector<int> &idx);
private:
	matchType _type;
	double _ratio;
	double _distance;
};




#endif