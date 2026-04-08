#include "L6_Gagea_Tiberiu_arena.h"
#include <algorithm>

namespace arena {
    namespace errors {
        GameException::GameException(const std::string &msg) : message(msg){}

        const char *GameException::what() const noexcept {
            return message.c_str();
        }

        InvalidActionException::InvalidActionException(const std::string &msg) : GameException(msg){}

        OutOfManaException::OutOfManaException(const std::string &msg) : GameException(msg){}
    }

    GameEntity::GameEntity(const std::string &name, int hp) : name(name), hp(hp), maxHp(hp){}

    int GameEntity::getHP() const {
        return hp;
    }

    std::string GameEntity::getName() const {
        return name;
    }

    int GameEntity::getMaxHP() const {
        return maxHp;
    }

    bool GameEntity::isAlive() const {
        return hp > 0;
    }

    std::ostream &operator<<(std::ostream &os, const GameEntity &entity) {
        os << entity.name << " HP: " << entity.hp;
        return os;
    }

    Character::Character(const std::string &name, int hp) : GameEntity(name, hp){}

    Warrior::Warrior(const std::string &name) : Character(name, 100), armor(20){}

    int Warrior::getArmor() const {
        return armor;
    }

    void Warrior::takeDamage(int damage) {
        int effectiveDamage = std::max(0, damage - armor);
        hp = std::max(0, hp - effectiveDamage);
    }

    void Warrior::attack(GameEntity &target) {
        if (!target.isAlive()) {
            throw errors::InvalidActionException("Cannot attack a dead target!");
        }
        target.takeDamage(20);
    }

    Mage::Mage(const std::string &name) : Character(name, 80), mana(50){}

    int Mage::getMana() const {
        return mana;
    }

    void Mage::takeDamage(int damage) {
        if (mana >= damage) {
            mana -= damage;
        }else {
            int remainingDamage = damage - mana;
            mana = 0;
            hp = std::max(0, hp - remainingDamage);
        }
    }

    void Mage::attack(GameEntity &target) {
        if (mana == 0) {
            throw errors::OutOfManaException("Mage is out of mana!");
        }
        if (!target.isAlive()) {
            throw errors::InvalidActionException("Cannot attack a dead target!");
        }
        mana = std::max(0, mana - 10);
        target.takeDamage(25);
    }

    Enemy::Enemy(const std::string &name, EnemyType type) : GameEntity(name, 0), type(type), baseDamage(0) {
        switch (type) {
            case EnemyType::GOBLIN:
                hp = 30; baseDamage = 10; break;
            case EnemyType::VAMPIRE:
                hp = 100; baseDamage = 20; break;
            case EnemyType::DRAGON:
                hp = 200; baseDamage = 50; break;
        }
        maxHp = hp;
    }

    EnemyType Enemy::getType() const {
        return type;
    }

    void Enemy::takeDamage(int damage) {
        hp = std::max(0, hp - damage);
    }

    void Enemy::applyLifesteal(int damageDealt) {
        if (type == EnemyType::VAMPIRE) {
            int heal = damageDealt / 2;
            hp = std::min(maxHp, hp + heal);
        }
    }

    void Enemy::attack(GameEntity &target) {
        if (!target.isAlive()) {
            throw errors::InvalidActionException("Cannot attack a dead target!");
        }
        target.takeDamage(baseDamage);
        applyLifesteal(baseDamage);
    }

    void Enemy::attack(GameEntity &target, bool isCritical) {
        if (!target.isAlive()) {
            throw errors::InvalidActionException("Cannot attack a dead target!");
        }
        int damage = isCritical ? baseDamage * 2 : baseDamage;
        target.takeDamage(damage);
        applyLifesteal(damage);
    }
}
