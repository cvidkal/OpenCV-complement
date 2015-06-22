#include "getMatch.h"


void GetMatch::operator() (const vector<vector<DMatch>> &dmatches, vector<int> &idx)
{
	switch (_type)
	{
	case distCheck:
		for (size_t i = 0; i < dmatches.size(); i++)
		{
			if (dmatches[i][0].distance < _distance)
			{
				idx.push_back(i);
			}
		}
		break;
	case ratioCheck:
		for (size_t i = 0; i < dmatches.size(); i++)
		{
			if (dmatches[i][0].distance < _ratio*dmatches[i][1].distance)
			{
				idx.push_back(i);
			}
		}
		break;
	case dist_ratioCheck:
		for (size_t i = 0; i < dmatches.size(); i++)
		{
			if (dmatches[i][0].distance < _distance&&dmatches[i][0].distance < _ratio*dmatches[i][1].distance)
			{
				idx.push_back(i);
			}
		}
		break;
	default:
		break;
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



void GetMatch::GetDMatch(vector<DMatch> &dmatch, const vector<int>&idx)
{
	vector<DMatch> temp;
	for (auto i : idx)
	{
		temp.push_back(dmatch[i]);
	}
	dmatch = temp;
}
void GetMatch::GetDMatch(vector<DMatch> &dmatch, const Mat& mask)
{
	CV_Assert(dmatch.size() == mask.rows);
	vector<DMatch> temp;
	for (size_t i = 0; i < mask.rows; i++)
	{
		if (mask.at<char>(i))
		{
			temp.push_back(dmatch[i]);
		}
	}
	dmatch = temp;
}






