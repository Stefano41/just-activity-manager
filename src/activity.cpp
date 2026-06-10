#include "../include/activity.h"

#include <sstream>
#include <iomanip>
#include <random>

Activity::Activity(const std::string& nome, const std::string& descrizione, const Activity::Priorita& priorita, const Activity::Status& stato): nome(nome), descrizione(descrizione), priorita(priorita), stato(stato){
    createdAt = std::time(nullptr);
    updatedAt = createdAt;
    generaId();
}

std::string Activity::getId() const{
    return id;
}

std::string Activity::getNome() const{
    return nome;
}

std::string Activity::getDescrizione() const{
    return descrizione;
}

Activity::Status Activity::getStato() const{
    return stato;
}

Activity::Priorita Activity::getPriorita() const{
    return priorita;
}

time_t Activity::getCreatedAt() const{
    return createdAt;
}

time_t Activity::getUpdatedAt() const{
    return updatedAt;
}

void Activity::setNome(const std::string& NewName){
    nome = NewName;
    updateTime();
}

void Activity::setDescrizione(const std::string& NewDescription){
    descrizione = NewDescription;
    updateTime();
}

void Activity::setStato(const Activity::Status& NewStatus){
    stato = NewStatus;
    updateTime();
}

void Activity::setPriorita(const Activity::Priorita& NewPriority){
    priorita = NewPriority;
    updateTime();
}

void Activity::generaId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1000, 9999);
    
    std::ostringstream oss;
    oss << "ACT-" << std::time(nullptr) << "-" << dis(gen);
    id = oss.str();
}

void Activity::updateTime(){
    updatedAt = time(nullptr);
}

