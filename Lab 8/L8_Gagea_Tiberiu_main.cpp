#include <iostream>
#include "L8_Gagea_Tiberiu_cats.hpp"

using namespace meaw;

int main() {
    std::cout << "=== 1. TESTARE CLASE PISICI SI FUNCTIE PREZENTARE ===\n";

    HouseCat garfield("Garfield", "Jon");
    StrayCat tom("Tom", 15);
    Tiger sherkhan("Sherkhan", 120);

    // Testam ID-urile statice la HouseCat
    HouseCat alt_housecat; // Folosim default constructorul
    std::cout << "Garfield ID: " << garfield.get_collar_id() << "\n";
    std::cout << "Unknown ID: " << alt_housecat.get_collar_id() << "\n";

    // Testam functia globala de prezentare (Duck Typing)
    std::cout << "Prezentare Garfield: " << get_cat_presentation(garfield) << "\n";
    std::cout << "Prezentare Tom: " << get_cat_presentation(tom) << "\n";
    std::cout << "Prezentare Tigru: " << get_cat_presentation(sherkhan) << "\n"; // Aici NU trebuie sa dea eroare!


    std::cout << "\n=== 2. TESTARE CatBasket NORMAL (N = 2) ===\n";

    CatBasket<HouseCat, 2> houseBasket; // Garsoniera are loc de 2 pisici
    std::cout << "Cosul este dinamic initial? " << (houseBasket.is_dynamic() ? "Da" : "Nu") << "\n";

    houseBasket.push_back(garfield);
    houseBasket.push_back(alt_housecat);
    std::cout << "Am adaugat 2 pisici. Cosul este dinamic acum? " << (houseBasket.is_dynamic() ? "Da" : "Nu") << "\n";

    // Adaugam a 3-a pisica (declanseaza mutarea in hala dinamica)
    HouseCat felix("Felix", "Ana");
    houseBasket.push_back(felix);
    std::cout << "Am adaugat a 3-a pisica. Cosul este dinamic acum? " << (houseBasket.is_dynamic() ? "Da" : "Nu") << "\n";
    std::cout << "Capacitate noua: " << houseBasket.capacity() << ", Dimensiune curenta: " << houseBasket.size() << "\n";

    std::cout << "Pisicile din cos:\n";
    houseBasket.print_names();


    std::cout << "\n=== 3. TESTARE EXCEPTII (Erori) ===\n";

    try {
        std::cout << "Incercam sa accesam pisica de pe pozitia 10...\n";
        HouseCat pisica_inexistenta = houseBasket[10]; // Asta trebuie sa dea crash
    } catch (const std::out_of_range& e) {
        std::cout << "Eroare prinsa cu succes: " << e.what() << "\n";
    }

    try {
        CatBasket<StrayCat, 1> cos_gol;
        std::cout << "Incercam sa scoatem o pisica dintr-un cos gol...\n";
        cos_gol.pop_back(); // Asta trebuie sa dea crash
    } catch (const std::out_of_range& e) {
        std::cout << "Eroare prinsa cu succes: " << e.what() << "\n";
    }


    std::cout << "\n=== 4. TESTARE SPECIALIZARE CatBasket (N = 0) SI TIGRI ===\n";

    CatBasket<Tiger, 0> tigerBasket;
    std::cout << "Cosul Tiger (N=0) este dinamic initial? " << (tigerBasket.is_dynamic() ? "Da" : "Nu") << "\n";

    tigerBasket.push_back(sherkhan);
    tigerBasket.push_back(Tiger("Rajah", 80));
    tigerBasket.push_back(Tiger("Tigress", 95));

    std::cout << "Capacitate TigerBasket: " << tigerBasket.capacity() << ", Dimensiune curenta: " << tigerBasket.size() << "\n";

    std::cout << "Testam print_names() pentru Tigri (ar trebui sa vedem doar mesaje de eroare):\n";
    // Aici functia print_names din interiorul cosului trebuie sa prinda cu try-catch exeptia de la tigru
    tigerBasket.print_names();

    std::cout << "\n=== TOATE TESTELE AU FOST TRECUTE CU SUCCES! ===\n";

    return 0;
}