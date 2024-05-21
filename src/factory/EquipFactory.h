#include <functional>
#include <map>
#include <typeindex>

#include "../entities/item/equipment/Equipment.h"

class EquipFactory {
public:
    using CreateFunction = std::function<Equipment* ()>;

    static EquipFactory& instance() {
        static EquipFactory instance;
        return instance;
    }

    template <typename T>
    void registerClass() {
        classMap[typeid(T)] = []() -> Equipment* { return new T(); };
    }

    Equipment* createInstance(const std::type_index& type) const {
        auto it = classMap.find(type);
        if (it != classMap.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    EquipFactory() = default;
    std::unordered_map<std::type_index, CreateFunction> classMap;
};
