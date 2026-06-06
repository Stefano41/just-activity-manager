/*
 * tests/test_activity.cpp
 * ─────────────────────────────────────────────────────────────────────────────
 * Test unitari con Qt Test per la gerarchia Activity.
 *
 * Struttura cartella tests/:
 *   tests/
 *     tests.pro
 *     test_activity.cpp   ← questo file
 *
 * Ogni metodo che inizia con "test" viene eseguito automaticamente da Qt Test.
 * ─────────────────────────────────────────────────────────────────────────────
 */

#include <QtTest/QtTest>
#include "../src/model/deadline.h"
#include "../src/model/event.h"
#include "../src/model/reminder.h"
#include "../src/model/appointment.h"
#include "../src/model/task.h"
#include "../src/model/activityrepository.h"

class TestActivity : public QObject {
    Q_OBJECT

private slots:

    // ── Deadline ──────────────────────────────────────────────────────────────

    void testDeadlineIsOverdue_scaduta() {
        // Una deadline nel passato deve essere scaduta
        Deadline d("Test", "desc", QDateTime::currentDateTime().addDays(-1), 2, "Studio");
        QVERIFY(d.isOverdue());
    }

    void testDeadlineIsOverdue_nonScaduta() {
        // Una deadline nel futuro non deve essere scaduta
        Deadline d("Test", "desc", QDateTime::currentDateTime().addDays(5), 2, "Studio");
        QVERIFY(!d.isOverdue());
    }

    void testDeadlineIsOverdue_completata() {
        // Una deadline scaduta ma completata non deve risultare scaduta
        Deadline d("Test", "desc", QDateTime::currentDateTime().addDays(-1), 2, "Studio");
        d.setCompleted(true);
        QVERIFY(!d.isOverdue());
    }

    void testDeadlineSummary_contienePriorita() {
        Deadline d("Consegna", "desc", QDateTime::currentDateTime().addDays(3), 3, "Lavoro");
        QVERIFY(d.getSummary().contains("Consegna"));
    }

    // ── Event ─────────────────────────────────────────────────────────────────

    void testEventDurationMinutes() {
        QDateTime start = QDateTime::currentDateTime();
        QDateTime end   = start.addSecs(90 * 60);  // 90 minuti
        Event e("Meeting", "desc", start, end, "Aula 1");
        QCOMPARE(e.getDurationMinutes(), 90);
    }

    void testEventIsOverdue_terminato() {
        QDateTime start = QDateTime::currentDateTime().addDays(-2);
        QDateTime end   = QDateTime::currentDateTime().addDays(-1);
        Event e("Passato", "desc", start, end, "Sala");
        QVERIFY(e.isOverdue());
    }

    void testEventIsOverdue_inCorso() {
        QDateTime start = QDateTime::currentDateTime().addDays(-1);
        QDateTime end   = QDateTime::currentDateTime().addDays(1);
        Event e("InCorso", "desc", start, end, "Sala");
        QVERIFY(!e.isOverdue());
    }

    void testEventPartecipanti() {
        QDateTime start = QDateTime::currentDateTime().addDays(1);
        Event e("Meet", "desc", start, start.addSecs(3600), "Online");
        e.addParticipant("Alice");
        e.addParticipant("Bob");
        QCOMPARE(e.getParticipants().size(), 2);
        e.removeParticipant("Alice");
        QCOMPARE(e.getParticipants().size(), 1);
    }

    // ── Reminder ─────────────────────────────────────────────────────────────

    void testReminderIsOverdue() {
        Reminder r("Memo", "desc", QDateTime::currentDateTime().addDays(-1), false, 0);
        QVERIFY(r.isOverdue());
    }

    void testReminderRicorrente_nextOccurrence() {
        QDateTime base = QDateTime::currentDateTime().addDays(-3);
        Reminder r("Memo", "desc", base, true, 7);
        // La prossima occorrenza deve essere nel futuro
        QVERIFY(r.getNextOccurrence() > QDateTime::currentDateTime());
    }

    // ── Task ─────────────────────────────────────────────────────────────────

    void testTaskCompletionPercentage_vuoto() {
        Task t("Task", "desc", QDate::currentDate().addDays(5), 60);
        QCOMPARE(t.getCompletionPercentage(), 0.0f);
    }

    void testTaskCompletionPercentage_parziale() {
        Task t("Task", "desc", QDate::currentDate().addDays(5), 60);
        t.addSubtask("Sotto1");
        t.addSubtask("Sotto2");
        t.setSubtaskCompleted(0, true);
        QCOMPARE(t.getCompletionPercentage(), 50.0f);
    }

    void testTaskTag() {
        Task t("Task", "desc", QDate::currentDate().addDays(5), 60);
        t.addTag("urgente");
        t.addTag("lavoro");
        QVERIFY(t.getTags().contains("urgente"));
        t.removeTag("urgente");
        QVERIFY(!t.getTags().contains("urgente"));
    }

    // ── Serializzazione JSON ──────────────────────────────────────────────────

    void testDeadlineToFromJson() {
        Deadline d("Test JSON", "desc", QDateTime::currentDateTime().addDays(2), 1, "Personale");
        QJsonObject json = d.toJson();
        // Il JSON deve contenere i campi fondamentali
        QVERIFY(json.contains("title"));
        QVERIFY(json.contains("dueDate"));
        QVERIFY(json.contains("priority"));
        QCOMPARE(json["title"].toString(), QString("Test JSON"));
    }

    // ── ActivityRepository ────────────────────────────────────────────────────

    void testRepositoryAdd() {
        ActivityRepository repo;
        repo.add(new Deadline("D1", "desc", QDateTime::currentDateTime().addDays(1), 1, "Studio"));
        QCOMPARE(repo.getAll().size(), 1);
    }

    void testRepositoryRemove() {
        ActivityRepository repo;
        auto* d = new Deadline("D1", "desc", QDateTime::currentDateTime().addDays(1), 1, "Studio");
        QString id = d->getId();
        repo.add(d);
        QVERIFY(repo.remove(id));
        QCOMPARE(repo.getAll().size(), 0);
    }

    void testRepositorySearch_trovato() {
        ActivityRepository repo;
        repo.add(new Deadline("Consegna progetto", "desc",
                              QDateTime::currentDateTime().addDays(1), 1, "Studio"));
        repo.add(new Event("Meeting", "desc",
                           QDateTime::currentDateTime().addDays(1),
                           QDateTime::currentDateTime().addDays(1).addSecs(3600), "Sala"));
        auto results = repo.search("progetto");
        QCOMPARE(results.size(), 1);
    }

    void testRepositorySearch_nonTrovato() {
        ActivityRepository repo;
        repo.add(new Deadline("Consegna", "desc",
                              QDateTime::currentDateTime().addDays(1), 1, "Studio"));
        auto results = repo.search("xyz_inesistente");
        QCOMPARE(results.size(), 0);
    }

    void testRepositoryFilterOverdue() {
        ActivityRepository repo;
        repo.add(new Deadline("Scaduta",    "desc", QDateTime::currentDateTime().addDays(-1), 1, "Studio"));
        repo.add(new Deadline("NonScaduta", "desc", QDateTime::currentDateTime().addDays(5),  1, "Studio"));
        auto overdue = repo.filterOverdue();
        QCOMPARE(overdue.size(), 1);
    }

    void testRepositoryPersistenzaJson(QTemporaryDir& dir) {
        ActivityRepository repo;
        repo.add(new Deadline("PersistTest", "desc",
                              QDateTime::currentDateTime().addDays(3), 2, "Lavoro"));
        QString path = dir.filePath("test.json");
        QVERIFY(repo.saveToJson(path));

        ActivityRepository repo2;
        QVERIFY(repo2.loadFromJson(path));
        QCOMPARE(repo2.getAll().size(), 1);
        QCOMPARE(repo2.getAll().first()->getTitle(), QString("PersistTest"));
    }
};

QTEST_MAIN(TestActivity)
#include "test_activity.moc"
