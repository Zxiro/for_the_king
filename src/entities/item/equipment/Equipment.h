#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "../enum/EquipmentType.h"
#include "../item/Item.h"

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
    
private:
    EquipmentType type;
    std::vector<std::string> skills;
};
#endif