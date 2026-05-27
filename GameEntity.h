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

    // virtualna metoda do klonowania entity
    virtual GameEntity* clone() const = 0;

    private:
    // przechowuje nazwę obiektu
    std::string _name;
};


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