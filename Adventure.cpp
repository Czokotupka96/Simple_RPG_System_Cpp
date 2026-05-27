#include "Adventure.h"


// konstruktor przyjmujacy nazwe
Adventure::Adventure(const std::string& name)
    : _name(name) {}

// usuwa obiekty w destruktorze
Adventure::~Adventure() {
    for(auto& el : _entities) {
        if(el != nullptr) {
            delete el;
        }
    }
    _entities.clear();
}

// pozwala pobrac nazwe
std::string Adventure::getName() const {
    return _name;
}
// pozwala dodawać obiekty operatorem `+=`
void Adventure::operator+=(GameEntity* entity) {
    if(entity != nullptr) {
        _entities.push_back(entity);
    }
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
        if(el != nullptr && el->category() == "Character") {
            count++;
        }
    }
    return count;
}
// pozwala policzyć stworzenia
int Adventure::countCreatures() const {
    int count = 0;
    for(auto& el : _entities) {
        if(el != nullptr && el->category() == "Creature") {
            count++;
        }
    }
    return count;
}
// pozwala policzyć dokładnie obiekty klasy `Warrior`
int Adventure::countExactWarriors() const {
    int count = 0;
    for(auto& el : _entities) {
        if(el != nullptr && el->type() == "Warrior") {
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