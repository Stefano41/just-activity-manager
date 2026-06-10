#ifndef ACTIVITY_H
#define ACTICITY_H

#include <string>



class Activity
{
public:
    enum class Priorita { Bassa, Media, Alta };
    enum class Status { Todo, In_progress, Completata };
    

private:
    std::string id;
    std::string nome;
    std::string descrizione;
    Priorita priorita;
    Status stato;
    time_t createdAt;
    time_t updatedAt;

};

#endif