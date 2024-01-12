// ConsoleApplication2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <algorithm>
#include <memory>
#include "generic_wrapper.h"
#include "Header.h"
#include "basic_shared_ptr.h"

void sub() {
    for (int i = 0; i < 10000000; i++) {
        generic_wrapper<int> g(500);
    }
}

void shared_test() {
    auto p1 = basic_shared_ptr<int>::make_shared(10);
    std::cout <<"1: " << p1.count() << std::endl;
    auto p2(p1);
    std::cout << "2: " << p1.count() << std::endl;
    auto p3 = p2;
    std::cout << "3: " << p1.count() << std::endl;
    basic_shared_ptr<int> p4;
    basic_shared_ptr<int> p5;
    std::cout << "4: " << p1.count() << std::endl;
    p4 = p2;
    std::cout << "5: " << p1.count() << std::endl;
    std::swap(p5, p3);
    std::cout << "6: " << p1.count() << std::endl;
    p2=std::move(p4);
    std::cout << "7: " << p1.count() << std::endl;
    std::cout << "7.1: " << p4.count() << std::endl;
    std::cout << "7.1: " << p4.expose() << std::endl;
    {
        auto p6 = p1;
        std::cout << "8: " << p1.count() << std::endl;
    }
    std::cout << "9: " << p1.count() << std::endl;
}

void t3() {
    std::shared_ptr<int> sp1(new int(5));
    auto sp2 = std::make_shared<int>(5);
    std::unique_ptr<int> up1(new int(5));
    auto up2 = std::make_unique<int>(5);
}


int main()
{
    std::cout << "Hello World!\n";
    generic_wrapper<int> g(5);
    std::cout << g.expose() <<" " << *g.expose() << std::endl;
    generic_wrapper<int> gt = generic_wrapper<int>::make_wrapped(10);
    std::cout << gt.expose() << " " << *gt.expose() << std::endl;
    generic_wrapper<someclass> g2(10, 'b');
    sub();
    shared_test();
    t3();
    std::cout << "Shortstop" << std::endl;
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
