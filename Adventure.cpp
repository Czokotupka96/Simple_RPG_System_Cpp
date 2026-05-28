#include "Adventure.h"
#include <utility>


// konstruktor przyjmujacy nazwe
Adventure::Adventure(const std::string& name)
    : _name(name) {}

// konstruktor kopiujacy
Adventure::Adventure(const Adventure& other) : _name(other._name) {
    for(auto& el : other._entities) {
        if(el != nullptr) {
            _entities.push_back(el->clone());
        }
    }
}
// konstruktor przenoszacy
Adventure::Adventure(Adventure&& other) noexcept
    : _name(std::move(other._name)), _entities(std::move(other._entities)) {}

// usuwa obiekty w destruktorze
Adventure::~Adventure() {
    for(auto& el : _entities) {
        if(el != nullptr) {
            delete el;
        }
    }
    _entities.clear();
}

// przeladowany operator=
Adventure& Adventure::operator=(const Adventure& other) {
    if(this == &other) {
        return *this;
    }

    for(auto& el : _entities) {
        if(el != nullptr) {
            delete el;
        }
    }
    _entities.clear();
    _name = other._name;

    for(auto& el : other._entities) {
        if(el != nullptr) {
            _entities.push_back(el->clone());
        }
    }
    return *this;
}
// przeladowany operator= przenoszacy
Adventure& Adventure::operator=(Adventure&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    for (auto& el : _entities) {
        if (el != nullptr) {
            delete el;
        }
    }
    _entities.clear();

    _name = std::move(other._name);
    _entities = std::move(other._entities);

    return *this;
}

// pozwala pobrac nazwe
std::string Adventure::getName() const {
    return _name;
}
// pozwala dodawać obiekty operatorem `+=`
Adventure& Adventure::operator+=(GameEntity* entity) {
    if(entity != nullptr) {
        _entities.push_back(entity);
    }
    return *this;
}
// pozwala pobrac rozmiar
std::size_t Adventure::size() const {
    return _entities.size();
}

// udostępnia obiekty przez operator `[]`
// wersja const
const GameEntity* Adventure::operator[](std::size_t index) const {
    if(index >= size()) {
        throw "Out of bounds error";
    } else {
        return _entities[index];
    }
}
// wersja nie const
GameEntity* Adventure::operator[](std::size_t index) {
    if(index >= size()) {
        throw "Out of bounds error";
    } else {
        return _entities[index];
    }
}

// posiada operator `()`, który zwraca sumę punktów
int Adventure::operator()() const {
    int sum = 0;
    for(auto& el : _entities) {
        if(el != nullptr) {
            sum += el->score();
        }
    }
    return sum;
}
// pozwala policzyć postacie
int Adventure::countCharacters() const {
    int count = 0;
    for(auto& el : _entities) {
        if(dynamic_cast<Character*>(el) != nullptr) {
            count++;
        }
    }
    return count;
}
// pozwala policzyć stworzenia
int Adventure::countCreatures() const {
    int count = 0;
    for(auto& el : _entities) {
        if(dynamic_cast<Creature*>(el) != nullptr) {
            count++;
        }
    }
    return count;
}
// pozwala policzyć dokładnie obiekty klasy `Warrior`
int Adventure::countExactWarriors() const {
    int count = 0;
    for(auto& el : _entities) {
        if(el != nullptr && typeid(*el) == typeid(Warrior)) {
            count++;
        }
    }
    return count;
}

// pozwala znaleźć pierwszy obiekt o dokładnym typie podanym przez `typeid`
// wersja const 
const GameEntity* Adventure::firstExact(const std::type_info& type) const {
    for(auto& el : _entities) {
        if(el != nullptr && typeid(*el) == type) {
            return el;
        }
    }
    return nullptr;
}
// wersja nie const
GameEntity* Adventure::firstExact(const std::type_info& type) {
    for(auto& el : _entities) {
        if(el != nullptr && typeid(*el) == type) {
            return el;
        }
    }
    return nullptr;
}

// pozwala znaleźć obiekt o największym score
// wersja const
const GameEntity* Adventure::strongest() const {
    if(size() == 0 ) {
        return nullptr;
    }

    GameEntity* best = _entities[0];
    for(auto& el : _entities) {
        if(el != nullptr && el->score() > best->score()) {
            best = el;
        }
    }
    return best;
}
// wersja nie const
GameEntity* Adventure::strongest() {
    if(size() == 0 ) {
        return nullptr;
    }

    GameEntity* best = _entities[0];
    for(auto& el : _entities) {
        if(el != nullptr && el->score() > best->score()) {
            best = el;
        }
    }
    return best;
}