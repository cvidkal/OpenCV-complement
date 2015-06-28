#include "getMatch.h"


void GetMatch::GetInliers(const vector<vector<DMatch>> &dmatches, vector<int> &idx,double _ratio,double _distance)
{
	if (_distance == -1)
	{
		for (size_t i = 0; i < dmatches.size(); i++)
		{
			if (dmatches[i][0].distance < _ratio*dmatches[i][1].distance)
			{
				idx.push_back(i);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < dmatches.size(); i++)
		{
			if (dmatches[i][0].distance < _distance&&dmatches[i][0].distance < _ratio*dmatches[i][1].distance)
			{
				idx.push_back(i);
			}
		}
	}

}

void GetMatch::GetInliers(const vector<DMatch> &dmatch, vector<int> &idx,double _distance)
{
	for (size_t i = 0; i < dmatch.size(); i++)
	{
		if (dmatch[i].distance < _distance)
		{
			idx.push_back(i);
		}
	}
}

void GetMatch::GetDMatch(const vector<vector<DMatch>> &dmatches, const vector<int>&idx, vector<DMatch> &dmatch)
{
	for (auto i : idx)
	{
		dmatch.push_back(dmatches[i][0]);
	}
}

GetMatch::~GetMatch()
{
}



void GetMatch::preparePoint2D(const vector<KeyPoint> &query, const vector<KeyPoint> train, const vector<DMatch> &dmatch, vector<Point2f> &query2D, vector<Point2f> &train2D)
{
	for (auto &i : dmatch)
	{
		if (i.queryIdx < 0)
			continue;
		query2D.push_back(query[i.queryIdx].pt);
		train2D.push_back(train[i.trainIdx].pt);
	}
}



