#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include "../include/activity.h"

struct TestResult {
    std::string name;
    bool passed;
    std::string error;
};

std::vector<TestResult> results;

#define RUN_TEST(func) \
    try { \
        func(); \
        results.push_back({#func, true, ""}); \
    } catch (const std::exception& e) { \
        results.push_back({#func, false, e.what()}); \
    } catch (...) { \
        results.push_back({#func, false, "Errore sconosciuto"}); \
    }

#define ASSERT(cond) \
    if (!(cond)) throw std::runtime_error("Assertion fallita: " #cond);

void testCostruttoreDefault() {
    Activity a("Studiare OOP", "Ripassare polimorfismo");
    ASSERT(a.getNome() == "Studiare OOP");
    ASSERT(a.getDescrizione() == "Ripassare polimorfismo");
    ASSERT(a.getStato() == Activity::Status::ToDo);
    ASSERT(a.getPriorita() == Activity::Priorita::Media);
}

void testCostruttoreCompleto() {
    Activity a("Consegna", "Finire entro venerdi",
               Activity::Priorita::Alta, Activity::Status::In_progress);
    ASSERT(a.getPriorita() == Activity::Priorita::Alta);
    ASSERT(a.getStato() == Activity::Status::In_progress);
}

void testIdGenerato() {
    Activity a("Test", "desc");
    Activity b("Test2", "desc2");
    ASSERT(!a.getId().empty());
    ASSERT(a.getId() != b.getId());
}

void testSetNome() {
    Activity a("Vecchio nome", "desc");
    a.setNome("Nuovo nome");
    ASSERT(a.getNome() == "Nuovo nome");
}

void testSetDescrizione() {
    Activity a("Nome", "Vecchia desc");
    a.setDescrizione("Nuova desc");
    ASSERT(a.getDescrizione() == "Nuova desc");
}

void testSetStato() {
    Activity a("Nome", "desc");
    a.setStato(Activity::Status::Completata);
    ASSERT(a.getStato() == Activity::Status::Completata);
}

void testSetPriorita() {
    Activity a("Nome", "desc");
    a.setPriorita(Activity::Priorita::Alta);
    ASSERT(a.getPriorita() == Activity::Priorita::Alta);
}

void writeXml(const std::string& path) {
    int failures = 0;
    for (auto& r : results) if (!r.passed) failures++;

    std::ofstream f(path);
    f << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    f << "<testsuite name=\"ActivityTests\" tests=\"" << results.size()
      << "\" failures=\"" << failures << "\">\n";
    for (auto& r : results) {
        f << "  <testcase name=\"" << r.name << "\"";
        if (r.passed) {
            f << "/>\n";
        } else {
            f << ">\n";
            f << "    <failure message=\"" << r.error << "\"/>\n";
            f << "  </testcase>\n";
        }
    }
    f << "</testsuite>\n";
}

int main() {
    RUN_TEST(testCostruttoreDefault);
    RUN_TEST(testCostruttoreCompleto);
    RUN_TEST(testIdGenerato);
    RUN_TEST(testSetNome);
    RUN_TEST(testSetDescrizione);
    RUN_TEST(testSetStato);
    RUN_TEST(testSetPriorita);

    int failures = 0;
    for (auto& r : results) {
        std::cout << (r.passed ? "OK" : "FAIL") << " - " << r.name;
        if (!r.passed) std::cout << " (" << r.error << ")";
        std::cout << "\n";
        if (!r.passed) failures++;
    }

    writeXml("test_results.xml");
    std::cout << "\n" << (results.size() - failures) << "/" << results.size() << " test passati.\n";

    return failures > 0 ? 1 : 0;
}