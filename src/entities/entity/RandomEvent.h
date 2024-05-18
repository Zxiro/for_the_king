#ifndef RANDOM_EVENT_H
#define RANDOM_EVENT_H

#include "Entity.h"
#include "../../structs/Position.h"
#include "creature/Player.h"
#include <cstdlib>
#include <ctime>

enum class EventType {
    FoundMoney,
    SteppedOnMine,
    Teleport,
    Blessed,
    Cursed
};

class RandomEvent : public Entity {
public:
    RandomEvent() : Entity(Position{ 0, 0 }, "RandomEvent"), type(EventType::FoundMoney) {}
    RandomEvent(const Position& pos, EventType eventType)
        : Entity(pos, "RandomEvent"), type(eventType) {}

    bool isPassable() const override {
        return true;
    }

    void triggerEvent(Player& player) {
        switch (type) {
        case EventType::FoundMoney:
            foundMoney(player);
            break;
        case EventType::SteppedOnMine:
            steppedOnMine(player);
            break;
        case EventType::Teleport:
            teleport(player);
            break;
        case EventType::Blessed:
            blessed(player);
            break;
        case EventType::Cursed:
            cursed(player);
            break;
        }
    }

private:
    EventType type;

    void foundMoney(Player& player) {
        int amount = rand() % 100 + 1;
        player.modifyMoney(amount);
        std::cout << "You found " << amount << " money!\n";
    }

    void steppedOnMine(Player& player) {
        int maxHP = player.getVitality();
        player.setVitality(maxHP * 0.9);
        std::cout << "You stepped on a mine! Max HP -10%\n";
    }

    void teleport(Player& player) {
        int newX = rand() % 140;
        int newY = rand() % 50;
        player.setPosition(Position{ newX, newY });
        std::cout << "You were teleported to (" << newX << ", " << newY << ")!\n";
    }

    void blessed(Player& player) {
        int attack = player.getPAttack();
        player.setAttack(attack * 1.1);
        std::cout << "You were blessed! Attack +10%\n";
    }

    void cursed(Player& player) {
        int pDefense = player.getPDefense();
        int mDefense = player.getMDefense();
        player.setPDefense(pDefense * 0.9);
        player.setMDefense(mDefense * 0.9);
        std::cout << "You were cursed! Physical and Magical Defense -10%\n";
    }
};

#endif // RANDOM_EVENT_H
