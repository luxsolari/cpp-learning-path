using System.Text.Json.Serialization;
using Evaluacion_II.Enums;
using Evaluacion_II.Items;

namespace Evaluacion_II.Champions;
[Serializable]
public class Champion
{
    public string Name { get; set; }
    public bool IsChargingAttack { get; set; }
    public bool IsDefending { get; set; }
    public float CurrentHealth { get; set; }
    public Role Role { get; set; }
    public BaseStats Stats { get; set; }
    
    public List<object> Skills { get; set; }
    
    // Consideracion especial para permitir "serializacion polimorfica"
    // https://stackoverflow.com/questions/8513042/json-net-serialize-deserialize-derived-types
    // https://docs.microsoft.com/en-us/dotnet/standard/serialization/system-text-json-polymorphism
    public List<object> Inventory { get; set; } = new List<object>();
    public List<Role> Strengths { get; } = new List<Role>();
    public List<Role> Resistances { get; } = new List<Role>();

    public Champion()
    {
    }

    [JsonConstructor]
    public Champion(string name, BaseStats stats, Role role, List<Role> strengths, List<Role> resistances)
    {
        Name = name;
        Stats = stats;
        CurrentHealth = Stats.MaxHealth;
        Role = role;
        Strengths = strengths;
        Resistances = resistances;
    }
    public void AutoAttack(Champion target, AttackType attackType, ref bool isCritical)
    {
        Console.WriteLine($"{this.Name} ataca!");
        // Calculos de daño y resistencias "efectivos" inspirados en sistemas de daño y resistencias de LoL
        // No es una imitacion 100% precisa, pero es una aproximación
        // https://leagueoflegends.fandom.com/wiki/Damage
        float attackerEffectiveAD = Stats.AttackDamage;
        float attackerEffectiveAP = Stats.AbilityPower;
        float attackerEffectiveCritRate = this.Stats.CriticalRate;
        float targetEffectiveArmor = target.Stats.Armor;
        float targetEffectiveMR = target.Stats.MagicResist;

        foreach (Item item in this.Inventory)
        {
            if (item is Weapon weapon)
            {
                attackerEffectiveAD += weapon.BonusDamage;
                attackerEffectiveAP += weapon.BonusAbilityPower;
                attackerEffectiveCritRate += weapon.BonusCriticalRate;
            }
        }
        
        foreach (Item item in target.Inventory)
        {
            if (item is Armor armor)
            {
                targetEffectiveArmor += armor.BonusArmor;
                targetEffectiveMR    += armor.BonusMagicResist;
            }
        }

        bool magicDamage = attackerEffectiveAD <= attackerEffectiveAP;

        // Daño reducido si es un ataque rapido
        if (attackType == AttackType.Fast)
            attackerEffectiveCritRate *= 0.70f;
        
        // Aplicamos crit rate si el golpe es critico y si el champion es capaz de asestar criticos
        if (this.Stats.CriticalChance > 0f && isCritical)
        {
            if (magicDamage) attackerEffectiveAP *= attackerEffectiveCritRate;
            attackerEffectiveAD *= attackerEffectiveCritRate;
            Console.WriteLine("Es un golpe crítico!");
        }

        // Formulas de mitigacion de daño tomadas de LoL
        // https://leagueoflegends.fandom.com/wiki/Armor#Formula
        // https://leagueoflegends.fandom.com/wiki/Magic_resistance
        float battleDamage = 0.0f;
        if (magicDamage) 
            battleDamage = Math.Clamp(attackerEffectiveAP * (100 / (100 + targetEffectiveMR)), min: 0.0f, max: float.PositiveInfinity);
        else 
            battleDamage = Math.Clamp(attackerEffectiveAD * (100 / (100 + targetEffectiveArmor)), min: 0.0f, max: float.PositiveInfinity);

        if (attackType == AttackType.Charged)
            battleDamage *= 1.75f;
        
        // Aplicamos Debilidades/Resistencias
        if (this.Strengths.Count > 0)
        {
            foreach (Role strength in this.Strengths)
            {
                if (target.Role == strength)
                {
                    battleDamage *= 2f;
                    Console.WriteLine("Es muy efectivo!");
                    break;
                }
            }
        }

        if (target.Resistances.Count > 0)
        {
            foreach (Role resistance in target.Resistances)
            {
                if (this.Role == resistance)
                {
                    battleDamage *= 0.5f;
                    Console.WriteLine("No es muy efectivo...");
                    break;
                }
            }
        }
        
        // Mitigación si el objetivo seleccionó la opcion 4- Defender
        if (target.IsDefending) battleDamage *= 0.25f;
        
        // Aplicamos daño al objetivo
        target.ReceiveDamage(battleDamage);
    }

    public bool IsAlive()
    {
        return this.CurrentHealth > 0.0f;
    }

    public void ReceiveDamage(float battleDamage)
    {
        if (CurrentHealth <= battleDamage) 
            CurrentHealth = 0f;
        else
            this.CurrentHealth -= battleDamage;
        
        Console.WriteLine($"{this.Name} recibio {battleDamage:0} daño. HP: {this.CurrentHealth:0}/{this.Stats.MaxHealth:0}");
        Console.WriteLine();
    }

    public void PrintInfo()
    {
        Console.WriteLine($"Name: {this.Name}");
        Console.WriteLine($"Basic Stats: \n{this.Stats}");
    }
}

// AD 100 DEF 100 => AD 100 DEF 80 = 20 DAMAGE
// AD 100 DEF 120 => AD 100 DEF 80 = 20 DAMAGE
// AD 100 DEF 150 => AD 100 DEF 80 = 20 DAMAGE
