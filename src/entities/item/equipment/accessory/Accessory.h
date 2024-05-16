#ifndef ACCESSORY_H
#define ACCESSORY_H
#include "../Equipment.h"

class Accessory: public Equipment
{
public:
    Accessory(): Equipment(EquipmentType::accessory)
    {
        
    }
};
#endif