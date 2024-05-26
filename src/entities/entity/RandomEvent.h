#ifndef RANDOM_EVENT_H
#define RANDOM_EVENT_H

#include "Entity.h"
#include "../../structs/Position.h"
#include "creature/Player.h"
#include <cstdlib>
#include "../enum/EventType.h";


class RandomEvent : public Entity {
public:
    RandomEvent(const Position& pos) : Entity(pos, "?") {}

    bool isPassable() const override {
        return true;
    }

    bool canTeleport() const override {
        return false;
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
    EventType type= static_cast<EventType>(rand() % 5);

    void foundMoney(Player& player) {
        int amount = rand() % 100 + 1;
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
