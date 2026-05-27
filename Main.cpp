// Najważniejsze informacje:
// - to jest pierwszy etap większego zadania projektowego,
// - w kolejnym tygodniu projekt będzie rozbudowywany,
// - błędy projektowe popełnione teraz mogą bardzo utrudnić dalszą rozbudowę,
// - przypominam o istnieniu valgrinda,
// - w tym zadaniu celowo używamy zwykłych wskaźników i operatora `new`.
//
// Proszę dopisać brakujący kod oraz dodać potrzebne pliki tak,
// aby program kompilował się, wykonywał poprawnie, a wynik działania był
// identyczny jak przedstawiony na końcu pliku.
//
// Nie wolno modyfikować pliku `Main.cpp` ani `CMakeLists.txt`.
//
// Temat:
// Prosty system przygody RPG.
//
// Program opisuje przygodę w grze RPG.
// W przygodzie mogą brać udział różne obiekty gry: postacie oraz stworzenia.
// Wszystkie obiekty mają wspólną abstrakcyjną klasę bazową `GameEntity`.
//
// Hierarchia w tym etapie:
//
// GameEntity
// ├── Character
// │   ├── Fighter
// │   │   └── Warrior
// │   └── Spellcaster
// │       └── Mage
// └── Creature
//     ├── Beast
//     │   └── Wolf
//     └── Undead
//         └── Skeleton
//
// Uwaga projektowa:
// W kolejnym etapie projektu pojawią się klasy łączące kilka ról naraz.
// Dlatego nie należy pisać rozwiązania „na sztywno” tylko pod klasy widoczne
// w tym pliku. Hierarchia powinna być przygotowana tak, aby dało się ją dalej
// rozbudowywać bez przepisywania całego projektu.
//
// Zadanie ćwiczy:
// - większą hierarchię dziedziczenia,
// - klasy abstrakcyjne,
// - funkcje czysto wirtualne,
// - funkcje wirtualne,
// - `override`,
// - konstruktory klas pochodnych,
// - `protected`,
// - polimorfizm,
// - operator `()`,
// - operator `[]`,
// - operator `+=`,
// - operator `<<`,
// - proste RTTI,
// - wirtualny destruktor,
// - ręczne zarządzanie pamięcią.
//
// Należy zaimplementować:
//
// 1. `GameEntity`
//    - abstrakcyjna klasa bazowa,
//    - przechowuje nazwę obiektu,
//    - pozwala pobrać nazwę,
//    - posiada operator `()`, który zwraca wartość punktową obiektu,
//    - pozwala wypisać obiekt operatorem `<<`,
//    - posiada metodę `summary()` zwracającą tekst:
//         "<category> <type> <name> score=<score> -> <details>"
//
// 2. `Character : public GameEntity`
//    - abstrakcyjna klasa dla postaci,
//    - przechowuje poziom postaci,
//    - kategoria to `"Character"`.
//
// 3. `Fighter : public Character`
//    - abstrakcyjna klasa dla postaci walczących fizycznie,
//    - przechowuje siłę i broń,
//    - score:
//         `level * 10 + strength * 2`
//
// 4. `Spellcaster : public Character`
//    - abstrakcyjna klasa dla postaci magicznych,
//    - przechowuje manę i szkołę magii,
//    - score:
//         `level * 8 + mana * 3`
//
// 5. `Warrior : public Fighter`
//    - konkretna klasa wojownika,
//    - typ: `"Warrior"`,
//    - szczegóły:
//         `"weapon=<weapon> level=<level> strength=<strength>"`,
//    - akcja:
//         `"<name> attacks with <weapon>"`
//
// 6. `Mage : public Spellcaster`
//    - konkretna klasa maga,
//    - typ: `"Mage"`,
//    - szczegóły:
//         `"school=<school> level=<level> mana=<mana>"`,
//    - akcja:
//         `"<name> casts a <school> spell"`
//
// 7. `Creature : public GameEntity`
//    - abstrakcyjna klasa dla stworzeń,
//    - przechowuje poziom zagrożenia,
//    - kategoria to `"Creature"`.
//
// 8. `Beast : public Creature`
//    - abstrakcyjna klasa dla bestii,
//    - przechowuje furię i środowisko,
//    - score:
//         `danger * 7 + fury * 2`
//
// 9. `Undead : public Creature`
//    - abstrakcyjna klasa dla nieumarłych,
//    - przechowuje klątwę i relikt,
//    - score:
//         `danger * 8 + curse * 3`
//
// 10. `Wolf : public Beast`
//    - konkretna klasa wilka,
//    - typ: `"Wolf"`,
//    - szczegóły:
//         `"habitat=<habitat> danger=<danger> fury=<fury>"`,
//    - akcja:
//         `"<name> charges from the <habitat>"`
//
// 11. `Skeleton : public Undead`
//    - konkretna klasa szkieletu,
//    - typ: `"Skeleton"`,
//    - szczegóły:
//         `"relic=<relic> danger=<danger> curse=<curse>"`,
//    - akcja:
//         `"<name> rattles the <relic>"`
//
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
//
// Struktura projektu:
// - include/GameEntity.h
// - include/Adventure.h
// - src/GameEntity.cpp
// - src/Adventure.cpp

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

#include "GameEntity.h"
#include "Adventure.h"

int main() {
    Adventure adventure("Ruins of the Old Moon");

    adventure += new Warrior("Rhea", 5, 12, "blade");
    adventure += new Mage("Ivo", 4, 10, "arcane");
    adventure += new Wolf("Greyfang", 5, 9, "forest");
    adventure += new Skeleton("Old King", 6, 4, "crown");

    std::cout << "Adventure: " << adventure.getName() << "\n";

    for (std::size_t i = 0; i < adventure.size(); ++i) {
        std::cout << *adventure[i] << "\n";
    }

    std::cout << "Total adventure score: " << adventure() << "\n";
    std::cout << "Characters: " << adventure.countCharacters() << "\n";
    std::cout << "Creatures: " << adventure.countCreatures() << "\n";
    std::cout << "Exact warriors: " << adventure.countExactWarriors() << "\n";

    std::cout << "Actions:\n";
    for (std::size_t i = 0; i < adventure.size(); ++i) {
        std::cout << adventure[i]->action() << "\n";
    }

    const Adventure& constAdventure = adventure;
    const GameEntity* selected = constAdventure[1];

    std::cout << "Selected score with operator(): "
              << (*selected)()
              << "\n";

    const GameEntity* firstMage = constAdventure.firstExact(typeid(Mage));

    if (firstMage != nullptr) {
        std::cout << "First exact mage: "
                  << firstMage->getName()
                  << " score="
                  << (*firstMage)()
                  << "\n";
    }

    const GameEntity* strongest = adventure.strongest();

    if (strongest != nullptr) {
        std::cout << "Strongest entity: "
                  << strongest->getName()
                  << " score="
                  << (*strongest)()
                  << "\n";
    }

    return 0;
}

/* Oczekiwany wynik działania programu:
Adventure: Ruins of the Old Moon
Character Warrior Rhea score=74 -> weapon=blade level=5 strength=12
Character Mage Ivo score=62 -> school=arcane level=4 mana=10
Creature Wolf Greyfang score=53 -> habitat=forest danger=5 fury=9
Creature Skeleton Old King score=60 -> relic=crown danger=6 curse=4
Total adventure score: 249
Characters: 2
Creatures: 2
Exact warriors: 1
Actions:
Rhea attacks with blade
Ivo casts a arcane spell
Greyfang charges from the forest
Old King rattles the crown
Selected score with operator(): 62
First exact mage: Ivo score=62
Strongest entity: Rhea score=74
*/