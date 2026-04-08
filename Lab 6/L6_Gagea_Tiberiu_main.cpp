#include "L6_Gagea_Tiberiu_arena.h"
#include <iostream>

int main() {
    try {
        arena::Warrior arthas("Arthas");
        arena::Mage jaina("Jaina");
        arena::Enemy vlad("Vlad", arena::EnemyType::VAMPIRE);
        arena::Enemy smaug("Smaug", arena::EnemyType::DRAGON);

        std::cout << "---Incepe Lupta!---";
        std::cout << arthas << "\n";
        std::cout << jaina << " | Mana: " << jaina.getMana() << "\n";
        std::cout << vlad << "\n\n";

        std::cout << "[Atac] Vlad ataca Jaina normal (Damage 20)\n";
        vlad.attack(jaina);
        std::cout << jaina << " | Mana: " << jaina.getMana() << "\n";
        //Asteptat: Mana 30, HP 80

        std::cout << "\n[Atac] Vlad ataca Jaina critic (Damage 40)\n";
        vlad.attack(jaina, true);
        std::cout << jaina << " | Mana: " << jaina.getMana() << "\n";
        //Asteptat: Mana 0, HP 70
        std::cout << vlad << " (Vampirul s-a vindecat)\n";
        //Asteptat: 100 HP max, nu poate depasi

        std::cout << "\n[Atac] Smaug ataca Arthas (Damage 50)\n";
        smaug.attack(arthas);
        std::cout << arthas << " (Armura 20 a blocat o parte din damage)\n";
        //Asteptat: 100 - (50 - 20) = 70 HP

        std::cout << "\n[Atac] Jaina ataca Smaug de mai multe ori...\n";
        while (jaina.getMana() > 0) {
            jaina.attack(smaug);
        }
        std::cout << smaug << "\n";

        //Provocam intentionat o exceptie OutOfMana
        std::cout << "\n[Test Exceptie] Jaina incearca sa atace fara mana...\n";
        jaina.attack(smaug);
    } catch (const arena::errors::OutOfManaException& e) {
        std::cerr << "Eroare de Mana Prinsa: " << e.what() << "\n";
    } catch (const arena::errors::InvalidActionException& e) {
        std::cerr << "Eroare de Actiune Prinsa: " << e.what() << "\n";
    } catch (const arena::errors::GameException& e) {
        std::cerr << "Eroare Generica de Joc Prinsa: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exceptie neasteptata: " << e.what() << "\n";
    }
    std::cout << "\nTestare terminata cu succes!\n";
    return 0;
}