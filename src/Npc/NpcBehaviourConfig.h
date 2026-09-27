#ifndef WILDLIFESIM_NPCBEHAVIOURCONFIG_H
#define WILDLIFESIM_NPCBEHAVIOURCONFIG_H

#include <string>

struct NpcBehaviourProfile
{
    int courageMin = 0;
    int courageMax = 0;
    bool hasWeapon = false;
};

const NpcBehaviourProfile& GetNpcBehaviourProfile(const std::string& archetype);

#endif
