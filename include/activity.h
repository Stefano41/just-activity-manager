#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <ctime>

class Activity
{
public:
    enum class Priorita
    {
        Bassa,
        Media,
        Alta 
    };
    enum class Status
    {
        ToDo,
        In_progress,
        Completata
    };
    Activity(const std::string& nome, const std::string& descrizione, const Activity::Priorita& priorita = Priorita::Media, const Activity::Status& stato = Status::ToDo);
    ~Activity() = default;
    std::string const getId();
    std::string const getNome();
    std::string const getDescrizione();
    Status const getStato();
    Priorita const getPriorita();
    time_t const getCreatedAt();
    time_t const getUpdatedAt();
    void setNome(const std::string &);
    void setDescrizione(const std::string &);
    void setStato(const Activity::Status &);
    void setPriorita(const Activity::Priorita &);

private:
    std::string id;
    std::string nome;
    std::string descrizione;
    Priorita priorita;
    Status stato;
    time_t createdAt;
    time_t updatedAt;

    void generaId();
    void updateTime();
};

#endif