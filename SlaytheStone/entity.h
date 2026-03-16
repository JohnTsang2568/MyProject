#ifndef ENTITY_H
#define ENTITY_H
#include<string>
#include<resource.h>
#include <card.h>

class Entity
{
    using hand=std::vector<std::unique_ptr<Card>>;
public:
    Entity();
    virtual ~Entity()=default;
    enum class Status{normal,bleed,trapped};
    enum class LifeStatus{alive,dead};
    enum class EntityType{player,enemy};
    EntityType getType(){return this->type;};
    Resource::ExtraResource getResource(){return this->resource;};
    void setLifeStatus(LifeStatus _lstatus) {this->life_status=_lstatus;};
    void setStatus(Status _status) {this->status=_status;};
    std::string getName(){return this->name;};
    Status getStatus(){return this->status;};
    LifeStatus getLifeStatus(){return this->life_status;};
    void changeLife(int amount){this->life=amount+this->life;};
    void changeResource(Resource::ExtraResource now,int amount){
        switch(now)
        {
        case Resource::ExtraResource::block:
        {
            this->block+=amount;
            break;
        }
        case Resource::ExtraResource::soul:
        {
            this->soul+=amount;
            break;
        }
        default:
        {
            return;
        }
        }
    };
    void setDead(){
        if(this->life<=0)
        {
            this->life_status= LifeStatus::dead;
        }
    }




protected:
    int life=60;
    int block=0;
    int soul=0;
    std::string name="";
    Resource::ExtraResource resource = Resource::ExtraResource::block;
    Status status=Status::normal;
    LifeStatus life_status=LifeStatus::alive;
    EntityType type= EntityType::player;

};

#endif // ENTITY_H
