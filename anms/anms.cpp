#include "anms.h"


inline int dist(const KeyPoint &a, const KeyPoint &b)
{
	return (a.pt.x - b.pt.x)*(a.pt.x - b.pt.x) + (a.pt.y - b.pt.y)*(a.pt.y - b.pt.y);
}

void anms(std::vector<KeyPoint> & keypoints, const int k, std::vector<int> &idx)
{
	idx.clear();
	std::vector<KeyPoint> kptsOut;
	std::sort(keypoints.begin(), keypoints.end(), [](const KeyPoint &a, const KeyPoint &b){return a.response > b.response; });
	std::vector<std::pair<int, int>> radius;
	const double c_robust = 1;
	for (size_t i = 0; i < keypoints.size(); i++)
	{
		int r = 0xffffff;
		for (size_t j = 0; j < i; j++)
		{
			int temp;
			if (keypoints[i].response <= c_robust*keypoints[j].response && (temp = dist(keypoints[i], keypoints[j])) < r)
			{
				r = temp;
			}
		}
		radius.push_back(std::pair<int, int>(r, i));
	}
	sort(radius.begin(), radius.end(), [](const std::pair<int, int>&a, const std::pair<int, int>&b){return a.first>b.first; });
	int size = min((size_t)k, keypoints.size());
	for (int i = 0; i < size; i++)
	{
		kptsOut.push_back(keypoints[radius[i].second]);
		idx.push_back(radius[i].second);
	}
	keypoints = kptsOut;
}

