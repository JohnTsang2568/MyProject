#include "class.h"

character::character() : name("Soyorin"), lp("Anon"), pp("Saki"), cp(0) {}

character::character(const std::string& name, const std::string& lp, const std::string& pp)
    : name(name), lp(lp), pp(pp), cp(0) {}

void character::setName(const std::string& name) {
    this->name = name;
}

void character::setLp(const std::string& lp) {
    this->lp = lp;
}

void character::setPp(const std::string& pp) {
    this->pp = pp;
}

void character::setCp(int cp) {
    this->cp = cp;
}

std::string character::getName() const {
    return name;
}

std::string character::getLp() const {
    return lp;
}

std::string character::getPp() const {
    return pp;
}

int character::getCp() const {
    return cp;
}