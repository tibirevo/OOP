#pragma once
#include <iostream>
#include <string>
#include <exception>

namespace arena {
    namespace errors {
        class GameException : public std::exception {
        protected:
            std::string message;
        public:
            explicit GameException(const std::string& msg);
            const char* what() const noexcept override;
        };

        class InvalidActionException : public GameException {
        public:
            explicit InvalidActionException(const std::string& msg);
        };

        class OutOfManaException : public GameException {
        public:
            explicit OutOfManaException(const std::string& msg);
        };
    }

    class GameEntity {
    protected:
        std::string name;
        int hp;
        int maxHp;
    public:
        GameEntity(const std::string& name, int hp);
        virtual ~GameEntity() = default;
        std::string getName() const;
        int getHP() const;
        int getMaxHP() const;
        bool isAlive() const;
        virtual void takeDamage(int damage) = 0;
        virtual void attack(GameEntity& target) = 0;
        friend std::ostream& operator<<(std::ostream& os, const GameEntity& entity);
    };

    class Character : public GameEntity {
    public:
        Character(const std::string& name, int hp);
    };

    class Warrior : public Character {
    private:
        int armor;
    public:
        explicit Warrior(const std::string& name);
        int getArmor() const;
        void takeDamage(int damage) override;
        void attack(GameEntity &target) override;
    };

    class Mage : public Character {
    private:
        int mana;
    public:
        explicit Mage(const std::string& name);
        int getMana() const;
        void takeDamage(int damage) override;
        void attack(GameEntity &target) override;
    };

    enum class EnemyType {
        GOBLIN,
        VAMPIRE,
        DRAGON
    };

    class Enemy : public GameEntity {
    private:
        EnemyType type;
        int baseDamage;
        void applyLifesteal(int damageDealt);
    public:
        Enemy(const std::string& name, EnemyType type);
        EnemyType getType() const;
        void takeDamage(int damage) override;
        void attack(GameEntity &target) override;
        void attack(GameEntity& target, bool isCritical);
    };
}