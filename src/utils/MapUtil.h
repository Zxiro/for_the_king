#include <functional>
#include <map>
#include <vector>
#include "../exception/ElementNotFoundException.h"

template <typename KeyType, typename ValueType>
class MapUtil
{
public:
	static std::vector<KeyType> filterKeys(const std::map<KeyType, ValueType>& myMap, std::function<bool(const KeyType&)> predicate) {
        std::vector<KeyType> keys;
        for (const auto& pair : myMap) {
            if (predicate(pair.first)) {
                keys.push_back(pair.first);
            }
        }
        return keys;
    }

    static std::pair<KeyType, ValueType> findFirst(const std::map<KeyType, ValueType>& myMap, std::function<bool(const KeyType&)> predicate)
	{
        std::vector<KeyType> keys;
        for (const auto& pair : myMap) {
            if (predicate(pair.first)) {
                return pair;
            }
        }

        throw ElementNotFoundException();
	}
};
