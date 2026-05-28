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
    // konstruktor kopiujacy
    Adventure(const Adventure& other);
    // operator przypisania
    Adventure& operator=(const Adventure& other);
    // konstruktor przenoszacy
    Adventure(Adventure&& other) noexcept;
    // przenoszacy operator przypisania
    Adventure& operator=(Adventure&& other) noexcept;

    // pozwala pobrac nazwe
    std::string getName() const;
    // pozwala dodawać obiekty operatorem `+=`
    Adventure& operator+=(GameEntity* entity);
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
    // przechowuje nazwe
    std::string _name;
    // przechowuje wskaźniki do `GameEntity`
    std::vector<GameEntity*> _entities;
};
