#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "../enum/EquipmentType.h"
#include "../item/Item.h"
#include "../exception/UnImplementException.h"

class Equipment: public Item
{
public:
    Equipment(EquipmentType type): type(type)
    {
        
    }

    virtual std::vector<std::string> getSkills()
    {
        return skills;
    }

    virtual static std::string getName()
    {
        throw UnImplementException();
    }
private:
    EquipmentType type;
    std::vector<std::string> skills;
};
#endif