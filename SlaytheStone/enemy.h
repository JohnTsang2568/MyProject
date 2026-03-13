#ifndef ENEMY_H
#define ENEMY_H
#include <QString>
#include <entity.h>

class Enemy : public Entity
{
public:
    Enemy();
    enum class Intention{attack,buff,debuff,block,flee,sleep};

    enum class AttackType{a,b,c,d,e,f};

private:
    Intention intention=Intention::sleep;


    AttackType attack_type= AttackType::a;

};

#endif // ENEMY_H
