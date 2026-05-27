#pragma once
#include "GameEntity.h"
#include <vector>
#include <typeinfo>

// jest właścicielem dodanych obiektów
class Adventure {
    public:
    // konstruktor przyjmujacy nazwe
    Adventure(const std::string& name);
    // usuwa obiekty w destruktorze
    ~Adventure();
    // kosntruktor kopiujacy
    Adventure(const Adventure& other);
    // operator przypisania
    Adventure& operator=(const Adventure& other);

    // pozwala pobrac nazwe
    std::string getName() const;
    // pozwala dodawać obiekty operatorem `+=`
    void operator+=(GameEntity* entity);
    // pozwala pobrac rozmiar
    std::size_t size() const;

    // udostępnia obiekty przez operator `[]`
    // wersja const
    const GameEntity* operator[](std::size_t index) const;
    // wersja nie const
    GameEntity* operator[](std::size_t index);

    // posiada operator `()`, który zwraca sumę punktów
    int operator()() const;
    // pozwala policzyć postacie
    int countCharacters() const;
    // pozwala policzyć stworzenia
    int countCreatures() const;
    // pozwala policzyć dokładnie obiekty klasy `Warrior`
    int countExactWarriors() const;

    // pozwala znaleźć pierwszy obiekt o dokładnym typie podanym przez `typeid`
    // wersja const 
    const GameEntity* firstExact(const std::type_info& type) const;
    // wersja nie const
    GameEntity* firstExact(const std::type_info& type);

    // pozwala znaleźć obiekt o największym score
    // wersja const
    const GameEntity* strongest() const;
    // wersja nie const
    GameEntity* strongest();

    private:
    // przechowuje wskaźniki do `GameEntity`
    std::vector<GameEntity*> _entities;
    // przechowuje nazwe
    std::string _name;
};


// 12. `Adventure`
//    - przechowuje wskaźniki do `GameEntity`,
//    - jest właścicielem dodanych obiektów,
//    - usuwa obiekty w destruktorze,
//    - pozwala dodawać obiekty operatorem `+=`,
//    - udostępnia obiekty przez operator `[]`,
//    - posiada operator `()`, który zwraca sumę punktów,
//    - pozwala policzyć postacie,
//    - pozwala policzyć stworzenia,
//    - pozwala policzyć dokładnie obiekty klasy `Warrior`,
//    - pozwala znaleźć pierwszy obiekt o dokładnym typie podanym przez `typeid`,
//    - pozwala znaleźć obiekt o największym score.