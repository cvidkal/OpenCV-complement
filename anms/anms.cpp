#include "anms.h"
#include "TickMeter.h"


inline int dist(const KeyPoint &a, const KeyPoint &b)
{
	return (a.pt.x - b.pt.x)*(a.pt.x - b.pt.x) + (a.pt.y - b.pt.y)*(a.pt.y - b.pt.y);
}

//inline bool isBucketEmpty(vector<vector<int>>&bucket,const int &x,const int &y,vector<int> mask,vector<vector<int>> &table,vector<int>& idx)
//{
//	idx.clear();
//	int lx = x - 1 < 0 ? 0 : x - 1;
//	int ly = y - 1 < 0 ? 0 : y - 1;
//	int rx = x + 1 >= bucketSize.width ? bucketSize.width - 1 : x + 1;
//	int ry = y + 1 >= bucketSize.height ? bucketSize.height - 1 : y + 1;
//	static vector<int> aaa;
//	aaa.reserve(9);
//	aaa.clear();
//	for (int j = lx; j <= rx; j++)
//	{
//		for (int k = ly; k <= ry; k++)
//		{
//			aaa.push_back(k*bucketSize.width + j);
//		}
//	}
//	for (auto c : aaa)
//	{
//		for (size_t i = 0; i < bucket[c].size(); i++)
//		{
//			idx.push_back(bucket[c][i]);
//		}
//	}
//	if (idx.empty())
//		return true;
//	else
//		return false;
//}
//


void anms(std::vector<KeyPoint> & keypoints, const int k, std::vector<int> &idx,cv::Size imgSize)
{
	TickMeter tm1, tm2, tm3, tm4;
	TickMeter tm5;
	int width = imgSize.width / 20;
	int height = imgSize.height / 20;
	int c_robust = 1;
	static vector<vector<int>> table;

//	tm1.start();
	if (table.empty())
	{
		table.resize(width*height);
		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				int lx = x - 1 < 0 ? 0 : x - 1;
				int ly = y - 1 < 0 ? 0 : y - 1;
				int rx = x + 1 >= width ? width - 1 : x + 1;
				int ry = y + 1 >= height ? height - 1 : y + 1;
				for (int j = lx; j <= rx; ++j)
				{
					for (int k = ly; k <= ry; ++k)
					{
						table[y*width+x].push_back(k*width + j);
					}
				}
			}
		}
	}
	vector<int> mask,mask2;//mask: whether there has point in the 3*3 neiborhood.   mask2:whether the bucket[i] is empty.
	mask.resize(width*height);
	mask2.resize(width*height);
	static vector<vector<int>> bucket;
	bucket.resize(width*height);
	for (size_t i = 0; i < bucket.size(); ++i)
	{
		bucket[i].clear();
	}
	std::sort(keypoints.begin(), keypoints.end(), [](const KeyPoint &a, const KeyPoint &b){return a.response > b.response; });

	std::vector<std::pair<int, int>> radius;
	radius.reserve(keypoints.size());
//	tm3.start();
	for (size_t i = 0; i < keypoints.size(); ++i)
	{
		int r = 0xffffff;
		int x, y;
		x = keypoints[i].pt.x / 20;
		y = keypoints[i].pt.y / 20;
		int idx = y*width + x;
		if (mask[idx])
		{
//			tm2.start();
			for (int k = 0; k < bucket[idx].size();++k)
			{
				int &j = bucket[idx][k];
				int temp;
//				tm4.start();
				if (keypoints[i].response < c_robust*keypoints[j].response)
				{
					if ((temp = dist(keypoints[i], keypoints[j])) < r)
						r = temp;
				}
//				tm4.stop();
			}
//			tm2.stop();
		}
		if (!mask2[idx])
		{
			for (int j = 0; j < table[idx].size();++j)
			{
				mask[table[idx][j]] = 1;
			}
		}
		if (!mask2[idx])
		{
			mask2[idx] = 1;
		}
		for (int j = 0; j < table[idx].size(); ++j)
		{
			bucket[table[idx][j]].push_back(i);
		}
		radius.push_back(std::pair<int, int>(r, i));
	}
//	tm3.stop();
	sort(radius.begin(), radius.end(), [](const std::pair<int, int>&a, const std::pair<int, int>&b){return a.first>b.first; });
	idx.clear();
	idx.reserve(500);
	std::vector<KeyPoint> kptsOut;
	kptsOut.reserve(500);
	int size = min((size_t)k, keypoints.size());
	for (int i = 0; i < size; ++i)
	{
		kptsOut.push_back(keypoints[radius[i].second]);
		idx.push_back(radius[i].second);
	}
	keypoints = kptsOut;
	//tm1.stop();
	//cout << "a--:" << tm1.getTimeSec() << endl;
	//cout << "b--:" << tm2.getTimeSec() << endl;
	//cout << "c--:" << tm3.getTimeSec() << endl;
	//cout << "d--:" << tm4.getTimeSec() << endl;



	//TickMeter tm;
	//idx.clear();
	//std::vector<KeyPoint> kptsOut;
	//tm.start();
	//std::sort(keypoints.begin(), keypoints.end(), [](const KeyPoint &a, const KeyPoint &b){return a.response > b.response; });
	//tm.stop();
	//cout << "sort1" << tm.getTimeMilli() << endl;
	//std::vector<std::pair<int, int>> radius;
	//radius.reserve(keypoints.size());
	//const double c_robust = 1;
	//tm.reset();
	//tm.start();
	//int r = 0xffffff;
	//for (size_t i = 0; i < keypoints.size(); i++)
	//{
	//	for (size_t j = 0; j < i; j++)
	//	{
	//		int temp;
	//		if (keypoints[i].response <= c_robust*keypoints[j].response)
	//		{
	//			if ((temp = dist(keypoints[i], keypoints[j])) < r)
	//				r = temp;
	//		}
	//	}
	//	radius.push_back(std::pair<int, int>(r, i));
	//}
	//tm.stop();
	//cout << "loop1" << tm.getTimeMilli() << endl;
	//tm.reset();
	//tm.start();
	//sort(radius.begin(), radius.end(), [](const std::pair<int, int>&a, const std::pair<int, int>&b){return a.first>b.first; });
	//tm.stop();
	//cout << "sort2" << tm.getTimeMilli() << endl;
	//int size = min((size_t)k, keypoints.size());
	//tm.reset();
	//tm.start();
	//for (int i = 0; i < size; i++)
	//{
	//	kptsOut.push_back(keypoints[radius[i].second]);
	//	idx.push_back(radius[i].second);
	//}
	//tm.stop();
	//cout << "loop2" << tm.getTimeMilli() << endl;
	//keypoints = kptsOut;
}

