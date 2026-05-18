#include "L8_Gagea_Tiberiu_cats.hpp"
#include <iostream>
#include <stdexcept>

namespace meaw {
    int HouseCat::next_id = 1;
    HouseCat::HouseCat(const std::string &name, const std::string &owner) : name(name), owner_name(owner), collar_id(get_next_id()){}

    HouseCat::HouseCat() {
        name = "Unknown";
        owner_name = "Nobody";
        collar_id = 0;
    }

    std::string HouseCat::ask_name() const {
        return name;
    }

    int HouseCat::get_collar_id() const {
        return collar_id;
    }

    int HouseCat::get_next_id() {
        int current_id = next_id;
        next_id++;
        return current_id;
    }


    StrayCat::StrayCat(const std::string &name, int battles) : name(name), battles_won(battles){}

    StrayCat::StrayCat() {
        name = "Unknown";
        battles_won = 0;
    }

    std::string StrayCat::ask_name() const {
        return name;
    }


    Tiger::Tiger(const std::string &name, uint16_t stripes) : name(name), stripes(stripes){}

    Tiger::Tiger() {
        name = "Unknown";
        stripes = 0;
    }

    std::string Tiger::ask_name() const {
        throw std::logic_error("You lost a hand!");
    }

    uint16_t Tiger::get_stripes() const {
        return stripes;
    }
}
