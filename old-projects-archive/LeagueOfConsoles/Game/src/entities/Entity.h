#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
class Entity
{
public:
	Entity();
	~Entity();

private:
	std::string name;

	// Offensive stats
	float baseAttackDamage;
	float baseAbilityPower;
	float baseCriticalStrikeChance;
	float baseCriticalStrikeDamage;

	float baseArmorPenetration; // Flat armor penetration
	float baseMagicPenetration; // Flat magic penetration

	float baseArmorPenetrationPercent; // Percent armor penetration
	float baseMagicPenetrationPercent; // Percent magic penetration

	// Defensive stats
	float baseHealth;
	float baseArmor;		// Flat armor value
	float baseMagicResist;  // Flat magic resist value

	// Utility stats
	float baseAttackSpeed;
	float baseMovementSpeed;
	float baseHealthRegen;
	float baseLifeSteal;
	float baseSpellVamp;
	float baseTenacity;

	float baseCooldownReduction;

	float baseExperienceGain;
	float baseGoldGain;

	
};

#endif
