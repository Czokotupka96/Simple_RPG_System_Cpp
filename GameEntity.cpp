#include "GameEntity.h"


// GameEntity --------------------------------------------------

// konstruktor przyjmujacy nazwe
GameEntity::GameEntity(const std::string& name)
    : _name(name) {}

// pozwala pobrac nazwe
std::string GameEntity::getName() const {
    return _name;
}
// posiada operator `()`, który zwraca wartość punktową obiektu
int GameEntity::operator()() const {
    return score();
}
//posiada metodę `summary()` zwracającą tekst: "<category> <type> <name> score=<score> -> <details>
std::string GameEntity::summary() const {
    return category() + " " + type() + " " + getName() + " score=" + std::to_string(score()) + " -> " + details();
}
// pozwala wypisać obiekt operatorem `<<`
std::ostream& operator<<(std::ostream& os, const GameEntity& entity) {
    return os << entity.summary();
}

// 1. `GameEntity`
//    - abstrakcyjna klasa bazowa,
//    - przechowuje nazwę obiektu,
//    - pozwala pobrać nazwę,
//    - posiada operator `()`, który zwraca wartość punktową obiektu,
//    - pozwala wypisać obiekt operatorem `<<`,
//    - posiada metodę `summary()` zwracającą tekst:
//         "<category> <type> <name> score=<score> -> <details>"



// Character --------------------------------------------------

// konstruktor przyjmujacy nazwe i poziom postaci
Character::Character(const std::string& name, int level)
    : GameEntity(name), _level(level) {}

// kategoria to "Character"
std::string Character::category() const {
    return "Character";
}

// 2. `Character : public GameEntity`
//    - abstrakcyjna klasa dla postaci,
//    - przechowuje poziom postaci,
//    - kategoria to `"Character"`.


// Fighter --------------------------------------------------

// konstruktor przyjmujacy nazwe, poziom, sile i bron
Fighter::Fighter(const std::string& name, int level, int strength, const std::string& weapon)
    : GameEntity(name), Character(name, level), _strength(strength), _weapon(weapon) {}

// score: level * 10 + strength * 2
int Fighter::score() const {
    return _level * 10 + _strength * 2;
}

// 3. `Fighter : public Character`
//    - abstrakcyjna klasa dla postaci walczących fizycznie,
//    - przechowuje siłę i broń,
//    - score:
//         `level * 10 + strength * 2`


// Spellcaster --------------------------------------------------

// konstruktor przyjmujacy nazwe, poziom, mane i szkole magii
Spellcaster::Spellcaster(const std::string& name, int level, int mana, const std::string& school)
    : GameEntity(name), Character(name, level), _mana(mana), _school(school) {}

// score: level * 8 + mana * 3
int Spellcaster::score() const {
    return _level * 8 + _mana * 3;
}

// 4. `Spellcaster : public Character`
//    - abstrakcyjna klasa dla postaci magicznych,
//    - przechowuje manę i szkołę magii,
//    - score:
//         `level * 8 + mana * 3`


// Warrior --------------------------------------------------

// konstruktor przyjmujacy nazwe, poziom, sile i bron
Warrior::Warrior(const std::string& name, int level, int strength, const std::string& weapon)
    : GameEntity(name), Character(name, level), Fighter(name, level, strength, weapon) {}
    
// typ: `"Warrior"`
std::string Warrior::type() const {
    return "Warrior";
}
// szczegóły: "weapon=<weapon> level=<level> strength=<strength>"
std::string Warrior::details() const {
    return "weapon=" + _weapon + " level=" + std::to_string(_level) + " strength=" + std::to_string(_strength);
}
// akcja: "<name> attacks with <weapon>"
std::string Warrior::action() const {
    return getName() + " attacks with " + _weapon;
}
// klonowanie
GameEntity* Warrior::clone() const {
    return new Warrior(*this);
}


// 5. `Warrior : public Fighter`
//    - konkretna klasa wojownika,
//    - typ: `"Warrior"`,
//    - szczegóły:
//         `"weapon=<weapon> level=<level> strength=<strength>"`,
//    - akcja:
//         `"<name> attacks with <weapon>"`


// Mage --------------------------------------------------

// konkretna klasa maga
// konstruktor przyjmujacy nazwe, poziom, mane i szkole magii
Mage::Mage(const std::string& name, int level, int mana, const std::string& school) 
    : GameEntity(name), Character(name, level), Spellcaster(name, level, mana, school) {}

// typ: `"Mage"`
std::string Mage::type() const {
    return "Mage";
}
// szczegóły: "school=<school> level=<level> mana=<mana>"
std::string Mage::details() const {
    return "school=" + _school + " level=" + std::to_string(_level) + " mana=" + std::to_string(_mana);
}
// akcja: "<name> casts a <school> spell"
std::string Mage::action() const {
    return getName() + " casts a " + _school + " spell";
}
// klonowanie
GameEntity* Mage::clone() const {
    return new Mage(*this);
}

// 6. `Mage : public Spellcaster`
//    - konkretna klasa maga,
//    - typ: `"Mage"`,
//    - szczegóły:
//         `"school=<school> level=<level> mana=<mana>"`,
//    - akcja:
//         `"<name> casts a <school> spell"`


// Creature --------------------------------------------------

// konstruktor przyjmujacy nazwe i poziom zagrozenia
Creature::Creature(const std::string& name, int danger)
    : GameEntity(name), _danger(danger) {}

// kategoria to `"Creature"`
std::string Creature::category() const {
    return "Creature";
}

// 7. `Creature : public GameEntity`
//    - abstrakcyjna klasa dla stworzeń,
//    - przechowuje poziom zagrożenia,
//    - kategoria to `"Creature"`.


// Beast --------------------------------------------------

// konstruktor przyjmujacy nazwe, poziom zagrozenia, furie i srodowisko
Beast::Beast(const std::string& name, int danger, int fury, const std::string& habitat) 
    : GameEntity(name), Creature(name, danger), _fury(fury), _habitat(habitat) {}

// score: danger * 7 + fury * 2
int Beast::score() const {
    return _danger * 7 + _fury * 2;
}

// 8. `Beast : public Creature`
//    - abstrakcyjna klasa dla bestii,
//    - przechowuje furię i środowisko,
//    - score:
//         `danger * 7 + fury * 2`


// Undead --------------------------------------------------

// konstruktor przyjmujacy nazwe, poziom zagrozenia, klatwe i relikt
Undead::Undead(const std::string& name, int danger, int curse, const std::string& relic)
    : GameEntity(name), Creature(name, danger), _curse(curse), _relic(relic) {}
    
// score: danger * 8 + curse * 3
int Undead::score() const {
    return _danger * 8 + _curse * 3;
}

// 9. `Undead : public Creature`
//    - abstrakcyjna klasa dla nieumarłych,
//    - przechowuje klątwę i relikt,
//    - score:
//         `danger * 8 + curse * 3`


// Wolf --------------------------------------------------

// konstruktor przyjmujacy nazwe, poziom zagrozenia, furie i srodowisko
Wolf::Wolf(const std::string& name, int danger, int fury, const std::string& habitat)
    : GameEntity(name), Creature(name, danger), Beast(name, danger, fury, habitat) {}
    
// typ: `"Wolf"`
std::string Wolf::type() const {
    return "Wolf";
}
// szczegóły: "habitat=<habitat> danger=<danger> fury=<fury>"
std::string Wolf::details() const {
    return "habitat=" + _habitat + " danger=" + std::to_string(_danger) + " fury=" + std::to_string(_fury);
}
// akcja: "<name> charges from the <habitat>"
std::string Wolf::action() const {
    return getName() + " charges from the " + _habitat;
}
// klonowanie
GameEntity* Wolf::clone() const {
    return new Wolf(*this);
}


// 10. `Wolf : public Beast`
//    - konkretna klasa wilka,
//    - typ: `"Wolf"`,
//    - szczegóły:
//         `"habitat=<habitat> danger=<danger> fury=<fury>"`,
//    - akcja:
//         `"<name> charges from the <habitat>"`


// Skeleton --------------------------------------------------

// konstruktor przyjmujacy nazwe, poziom zagrozenia, klatwe i relikt
Skeleton::Skeleton(const std::string& name, int danger, int curse, const std::string& relic)
    : GameEntity(name), Creature(name, danger), Undead(name, danger, curse, relic) {}
    
// typ: `"Skeleton"`
std::string Skeleton::type() const {
    return "Skeleton";
}
// szczegóły: "relic=<relic> danger=<danger> curse=<curse>"
std::string Skeleton::details() const {
    return "relic=" + _relic + " danger=" + std::to_string(_danger) + " curse=" + std::to_string(_curse);
}
// akcja: "<name> rattles the <relic>"
std::string Skeleton::action() const {
    return getName() + " rattles the " + _relic;
}
// klonowanie
GameEntity* Skeleton::clone() const {
    return new Skeleton(*this);
}

// 11. `Skeleton : public Undead`
//    - konkretna klasa szkieletu,
//    - typ: `"Skeleton"`,
//    - szczegóły:
//         `"relic=<relic> danger=<danger> curse=<curse>"`,
//    - akcja:
//         `"<name> rattles the <relic>"`