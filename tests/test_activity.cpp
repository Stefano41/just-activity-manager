#include <iostream>
#include <cassert>
#include <string>
#include "../include/activity.h"

using namespace std;

void testCostruttoreDefault() {
    Activity a("Studiare OOP", "Ripassare polimorfismo");
    assert(a.getNome() == "Studiare OOP");
    assert(a.getDescrizione() == "Ripassare polimorfismo");
    assert(a.getStato() == Activity::Status::ToDo);
    assert(a.getPriorita() == Activity::Priorita::Media);
    std::cout << "testCostruttoreDefault: OK\n";
}

void testCostruttoreCompleto() {
    Activity a("Consegna", "Finire entro venerdi",
               Activity::Priorita::Alta, Activity::Status::In_progress);
    assert(a.getPriorita() == Activity::Priorita::Alta);
    assert(a.getStato() == Activity::Status::In_progress);
    std::cout << "testCostruttoreCompleto: OK\n";
}

void testIdGenerato() {
    Activity a("Test", "desc");
    Activity b("Test2", "desc2");
    assert(!a.getId().empty());
    assert(a.getId() != b.getId());
    std::cout << "testIdGenerato: OK\n";
}

void testSetNome() {
    Activity a("Vecchio nome", "desc");
    a.setNome("Nuovo nome");
    assert(a.getNome() == "Nuovo nome");
    std::cout << "testSetNome: OK\n";
}

void testSetDescrizione() {
    Activity a("Nome", "Vecchia desc");
    a.setDescrizione("Nuova desc");
    assert(a.getDescrizione() == "Nuova desc");
    std::cout << "testSetDescrizione: OK\n";
}

void testSetStato() {
    Activity a("Nome", "desc");
    a.setStato(Activity::Status::Completata);
    assert(a.getStato() == Activity::Status::Completata);
    std::cout << "testSetStato: OK\n";
}

void testSetPriorita() {
    Activity a("Nome", "desc");
    a.setPriorita(Activity::Priorita::Alta);
    assert(a.getPriorita() == Activity::Priorita::Alta);
    std::cout << "testSetPriorita: OK\n";
}

int main() {
    testCostruttoreDefault();
    testCostruttoreCompleto();
    testIdGenerato();
    testSetNome();
    testSetDescrizione();
    testSetStato();
    testSetPriorita();
    std::cout << "\nTutti i test passati.\n";
    return 0;
}