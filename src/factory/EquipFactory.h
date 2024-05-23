#include <functional>
#include <map>
#include <typeindex>

#include "../entities/item/equipment/Equipment.h"

class EquipFactory {
public:
    using CreateFunction = std::function<std::shared_ptr<Equipment> ()>;

    static EquipFactory& instance() {
        static EquipFactory instance;
        return instance;
    }

    template <typename T>
    void registerClass() {
        classMap[typeid(T)] = []() -> std::shared_ptr<Equipment> { return std::make_shared<T>(); };
    }

    std::shared_ptr<Equipment> createInstance(const std::type_index& type) const {
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
