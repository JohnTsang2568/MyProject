#ifndef ENTITY_H
#define ENTITY_H
#include<string>
class Entity
{
public:
    Entity();
    enum class Status{normal,bleed,trapped};
    enum class LifeStatus{alive,dead};
    void setLifeStatus(LifeStatus _lstatus) {this->life_status=_lstatus;};
    void setStatus(Status _status) {this->status=_status;};
    std::string getName(){return this->name;};
    Status getStatus(){return this->status;};
    LifeStatus getLifeStatus(){return this->life_status;};
    void changeLife(int amount){this->life=amount+this->life;};
    void changeBlock(int amount){this->block=amount+this->block;};
    void setDead(){
        if(this->life<=0)
        {
            this->life_status= LifeStatus::dead;
        }
    }

protected:
    int life=60;
    int block=0;
    std::string name="";
    Status status=Status::normal;
    LifeStatus life_status=LifeStatus::alive;

};

#endif // ENTITY_H
