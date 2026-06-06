QT       += testlib core
QT       -= gui

# Aggiunge i flag gcov per la copertura
QMAKE_CXXFLAGS += --coverage
QMAKE_LFLAGS   += --coverage

TARGET    = tests
TEMPLATE  = app
CONFIG   += console
CONFIG   -= app_bundle

# Includi le sorgenti del modello logico (escludi il main dell'app)
INCLUDEPATH += ../src

SOURCES += \
    test_activity.cpp \
    ../src/model/deadline.cpp \
    ../src/model/event.cpp \
    ../src/model/reminder.cpp \
    ../src/model/appointment.cpp \
    ../src/model/task.cpp \
    ../src/model/activityrepository.cpp

HEADERS += \
    ../src/model/activity.h \
    ../src/model/deadline.h \
    ../src/model/event.h \
    ../src/model/reminder.h \
    ../src/model/appointment.h \
    ../src/model/task.h \
    ../src/model/activityrepository.h