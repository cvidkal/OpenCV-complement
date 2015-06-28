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
	int width = imgSize.width / 20;
	int height = imgSize.height / 20;
	int c_robust = 1;
	static vector<vector<int>> table;

	if (table.empty())
	{
		table.resize(width*height);
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				int lx = x - 1 < 0 ? 0 : x - 1;
				int ly = y - 1 < 0 ? 0 : y - 1;
				int rx = x + 1 >= width ? width - 1 : x + 1;
				int ry = y + 1 >= height ? height - 1 : y + 1;
				for (int j = lx; j <= rx; j++)
				{
					for (int k = ly; k <= ry; k++)
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
	for (size_t i = 0; i < bucket.size(); i++)
	{
		bucket[i].clear();
	}
	std::sort(keypoints.begin(), keypoints.end(), [](const KeyPoint &a, const KeyPoint &b){return a.response > b.response; });
	std::vector<std::pair<int, int>> radius;
	radius.reserve(keypoints.size());
	for (size_t i = 0; i < keypoints.size(); i++)
	{
		int r = 0xffffff;
		int x, y;
		x = keypoints[i].pt.x / 20;
		y = keypoints[i].pt.y / 20;
		if (mask[y*width+x])
		{
			for (auto j : bucket[y*width+x])
			{
				int temp;
				if (keypoints[i].response <= c_robust*keypoints[j].response)
				{
					if ((temp = dist(keypoints[i], keypoints[j])) < r)
						r = temp;
				}
			}
		}
		if (!mask2[y*width + x])
		{
			for (auto k : table[y*width + x])
			{
				mask[k] = 1;
			}
		}
		if (!mask2[y*width + x])
		{
			mask2[y*width + x] = 1;
		}
		for (auto k : table[y*width + x])
		{
			bucket[k].push_back(i);
		}
		radius.push_back(std::pair<int, int>(r, i));
	}

	sort(radius.begin(), radius.end(), [](const std::pair<int, int>&a, const std::pair<int, int>&b){return a.first>b.first; });
	idx.clear();
	std::vector<KeyPoint> kptsOut;
	int size = min((size_t)k, keypoints.size());
	for (int i = 0; i < size; i++)
	{
		kptsOut.push_back(keypoints[radius[i].second]);
		idx.push_back(radius[i].second);
	}
	keypoints = kptsOut;

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

