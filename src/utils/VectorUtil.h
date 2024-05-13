#ifndef VECTORUTIL_HEADER
#define VECTORUTIL_HEADER
#include <vector>

using namespace std;

class VectorUtil {
public:
	template <class T>
	static bool c_find(vector<T> list, T target) {
		return find(list.begin(), list.end(), target) != list.end();
	}

	template <class T>
	static void earse(vector<T> *list, T target) {
		int index = 0;
		for (auto item : list) {
			if (item == target) {
				break;
			}
			index += 1;
		}

		list->erase(list->begin() + index);
	}
};
#endif