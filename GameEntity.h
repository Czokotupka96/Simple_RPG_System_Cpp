#pragma once
#include <string>
#include <iostream>


// GameEntity --------------------------------------------------

// abstrakcyjna klasa bazowa
class GameEntity {
    public:
    // konstruktor przyjmujacy nazwe
    GameEntity(const std::string& name);
    // wirtualny destruktor
    virtual ~GameEntity() = default;

    // pozwala pobrac nazwe
    std::string getName() const;
    // posiada operator `()`, który zwraca wartość punktową obiektu
    int operator()() const;
    // obliczeine wartosci punktowej obiektu
    virtual int score() const = 0;
    // pozwala wypisać obiekt operatorem `<<`
    friend std::ostream& operator<<(std::ostream& os, const GameEntity& entity);
    //posiada metodę `summary()` zwracającą tekst: "<category> <type> <name> score=<score> -> <details>
    std::string summary() const;
    // metoda wirtualna details pozwala pobrac detale
    virtual std::string details() const = 0;
    // metoda wirtulna type pozwalajaca pobrac typ
    virtual std::string type() const = 0;
    // metoda akcja pozwalajaca wykonac akcje
    virtual std::string action() const = 0;
    // metoda wirtualna category pozwalajca pobrac kategorie
    virtual std::string category() const = 0;

    // virtualna metoda do klonowania lisci
    virtual GameEntity* clone() const = 0;

    private:
    // przechowuje nazwę obiektu
    std::string _name;
};

// 1. `GameEntity`
//    - abstrakcyjna klasa bazowa,
//    - przechowuje nazwę obiektu,
//    - pozwala pobrać nazwę,
//    - posiada operator `()`, który zwraca wartość punktową obiektu,
//    - pozwala wypisać obiekt operatorem `<<`,
//    - posiada metodę `summary()` zwracającą tekst:
//         "<category> <type> <name> score=<score> -> <details>"


// Character --------------------------------------------------

// abstrakcyjna klasa dla postaci
class Character : virtual public GameEntity {
    public:
    // konstruktor przyjmujacy nazwe i poziom postaci
    Character(const std::string& name, int level);
    // kategoria to "Character"
    std::string category() const override;

    protected:
    // przechowuje poziom postaci
    int _level;
};

// 2. `Character : public GameEntity`
//    - abstrakcyjna klasa dla postaci,
//    - przechowuje poziom postaci,
//    - kategoria to `"Character"`.


// Fighter --------------------------------------------------

// abstrakcyjna klasa dla postaci walczących fizycznie
class Fighter : virtual public Character {
    public:
    // konstruktor przyjmujacy nazwe, poziom, sile i bron
    Fighter(const std::string& name, int level, int strength, const std::string& weapon);
    // score: level * 10 + strength * 2
    int score() const override;

    protected:
    // przechowuje siłę i broń
    int _strength;
    std::string _weapon;
};

// 3. `Fighter : public Character`
//    - abstrakcyjna klasa dla postaci walczących fizycznie,
//    - przechowuje siłę i broń,
//    - score:
//         `level * 10 + strength * 2`


// Spellcaster --------------------------------------------------

// abstrakcyjna klasa dla postaci magicznych
class Spellcaster : virtual public Character {
    public:
    // konstruktor przyjmujacy nazwe, poziom, mane i szkole magii
    Spellcaster(const std::string& name, int level, int mana, const std::string& school);
    // score: level * 8 + mana * 3
    int score() const override;

    protected:
    // przechowuje manę i szkołę magii
    int _mana;
    std::string _school;
};

// 4. `Spellcaster : public Character`
//    - abstrakcyjna klasa dla postaci magicznych,
//    - przechowuje manę i szkołę magii,
//    - score:
//         `level * 8 + mana * 3`


// Warrior --------------------------------------------------

// konkretna klasa wojownika
class Warrior : public Fighter {
    public:
    // konstruktor przyjmujacy nazwe, poziom, sile i bron
    Warrior(const std::string& name, int level, int strength, const std::string& weapon);
    // typ: `"Warrior"`
    std::string type() const override;
    // szczegóły: "weapon=<weapon> level=<level> strength=<strength>"
    std::string details() const override;
    // akcja: "<name> attacks with <weapon>"
    std::string action() const override;

    // klonowanie
    GameEntity* clone() const override;
};

// 5. `Warrior : public Fighter`
//    - konkretna klasa wojownika,
//    - typ: `"Warrior"`,
//    - szczegóły:
//         `"weapon=<weapon> level=<level> strength=<strength>"`,
//    - akcja:
//         `"<name> attacks with <weapon>"`


// Mage --------------------------------------------------

// konkretna klasa maga
class Mage : public Spellcaster {
    public:
    // konstruktor przyjmujacy nazwe, poziom, mane i szkole magii
    Mage(const std::string& name, int level, int mana, const std::string& school);
    // typ: `"Mage"`
    std::string type() const override;
    // szczegóły: "school=<school> level=<level> mana=<mana>"
    std::string details() const override;
    // akcja: "<name> casts a <school> spell"
    std::string action() const override;

    // klonowanie
    GameEntity* clone() const override;
};

// 6. `Mage : public Spellcaster`
//    - konkretna klasa maga,
//    - typ: `"Mage"`,
//    - szczegóły:
//         `"school=<school> level=<level> mana=<mana>"`,
//    - akcja:
//         `"<name> casts a <school> spell"`


// Creature --------------------------------------------------

// abstrakcyjna klasa dla stworzeń
class Creature : virtual public GameEntity {
    public:
    // konstruktor przyjmujacy nazwe i poziom zagrozenia
    Creature(const std::string& name, int danger);
    // kategoria to `"Creature"`
    std::string category() const override;

    protected:
    // przechowuje poziom zagrożenia
    int _danger;
};

// 7. `Creature : public GameEntity`
//    - abstrakcyjna klasa dla stworzeń,
//    - przechowuje poziom zagrożenia,
//    - kategoria to `"Creature"`.


// Beast --------------------------------------------------

// abstrakcyjna klasa dla bestii
class Beast : virtual public Creature {
    public:
    // konstruktor przyjmujacy nazwe, poziom zagrozenia, furie i srodowisko
    Beast(const std::string& name, int danger, int fury, const std::string& habitat);
    // score: danger * 7 + fury * 2
    int score() const override;

    protected:
    // przechowuje furię i środowisko
    int _fury;
    std::string _habitat;
};

// 8. `Beast : public Creature`
//    - abstrakcyjna klasa dla bestii,
//    - przechowuje furię i środowisko,
//    - score:
//         `danger * 7 + fury * 2`


// Undead --------------------------------------------------

// abstrakcyjna klasa dla nieumarłych
class Undead : virtual public Creature {
    public:
    // konstruktor przyjmujacy nazwe, poziom zagrozenia, klatwe i relikt
    Undead(const std::string& name, int danger, int curse, const std::string& relic);
    // score: danger * 8 + curse * 3
    int score() const override;

    protected:
    // przechowuje klątwę i relikt
    int _curse;
    std::string _relic;
};

// 9. `Undead : public Creature`
//    - abstrakcyjna klasa dla nieumarłych,
//    - przechowuje klątwę i relikt,
//    - score:
//         `danger * 8 + curse * 3`


// Wolf --------------------------------------------------

// konkretna klasa wilka
class Wolf : public Beast {
    public:
    // konstruktor przyjmujacy nazwe, poziom zagrozenia, furie i srodowisko
    Wolf(const std::string& name, int danger, int fury, const std::string& habitat);
    // typ: `"Wolf"`
    std::string type() const override;
    // szczegóły: "habitat=<habitat> danger=<danger> fury=<fury>"
    std::string details() const override;
    // akcja: "<name> charges from the <habitat>"
    std::string action() const override;

    // klonowanie
    GameEntity* clone() const override;
};

// 10. `Wolf : public Beast`
//    - konkretna klasa wilka,
//    - typ: `"Wolf"`,
//    - szczegóły:
//         `"habitat=<habitat> danger=<danger> fury=<fury>"`,
//    - akcja:
//         `"<name> charges from the <habitat>"`


// Skeleton --------------------------------------------------

// konkretna klasa szkieletu
class Skeleton : public Undead {
    public:
    // konstruktor przyjmujacy nazwe, poziom zagrozenia, klatwe i relikt
    Skeleton(const std::string& name, int danger, int curse, const std::string& relic);
    // typ: `"Skeleton"`
    std::string type() const override;
    // szczegóły: "relic=<relic> danger=<danger> curse=<curse>"
    std::string details() const override;
    // akcja: "<name> rattles the <relic>"
    std::string action() const override;

    // klonowanie
    GameEntity* clone() const override;
};
// 11. `Skeleton : public Undead`
//    - konkretna klasa szkieletu,
//    - typ: `"Skeleton"`,
//    - szczegóły:
//         `"relic=<relic> danger=<danger> curse=<curse>"`,
//    - akcja:
//         `"<name> rattles the <relic>"`