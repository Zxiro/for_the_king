#ifndef EQUIPFACTORY_H
#define EQUIPFACTORY_H

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <functional>
#include "../entities/item/Item.h"

class EquipFactory {
public:
    using CreateFunction = std::function<std::shared_ptr<Item>()>;

    static EquipFactory& instance() {
        static EquipFactory instance;
        return instance;
    }

    template <typename T>
    void registerClass() {
        classMap[typeid(T)] = []() -> std::shared_ptr<Item> { return std::make_shared<T>(); };
    }

    std::shared_ptr<Item> createInstance(const std::type_index& type) const {
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

#endif // EQUIPFACTORY_H
