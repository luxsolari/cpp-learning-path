namespace Evaluacion_II.Champions;

[Serializable]
public struct BaseStats
{
    // Offensive stats
    public float AbilityPower { get; set; }
    public float AttackDamage { get; set; } //

    public float ArmorPenetration { get; set; }
    public float MagicPenetration { get; set; }
    
    public float Agility    { get; set; } //
    public float CriticalChance { get; set; }
    public float CriticalRate { get; set; }

    // Defensive stats
    public float MaxHealth   { get; set; }  //
    public float Armor       { get; set; }  //
    public float MagicResist { get; set; }  //
    
    // Other
    public float HealthRegen { get; set; } //
    public Resource Resource { get; set; } //
    
    public BaseStats(
        float modAttackDamage, 
        float modAgility, 
        float modMaxHealth, 
        float modArmor, 
        float modMagicResist, 
        float modHealthRegen, 
        float modCritChance, 
        float modCritRate,
        Resource resource) : this()
    {
        AttackDamage        = 50 * modAttackDamage;
        Agility             = 50 * modAgility;
        MaxHealth           = 1000 * modMaxHealth;
        Armor               = 25 * modArmor;
        MagicResist         = 25 * modMagicResist;
        HealthRegen         = 10 * modHealthRegen;
        CriticalChance      = 1  * modCritChance;
        CriticalRate        = 1  * modCritRate;
        ArmorPenetration    = 0.0f;
        MagicPenetration    = 0.0f;
        AbilityPower        = 0.0f;
        Resource            = resource;
    }

    public override string ToString()
    {
        string statsString = $"Attack Damage: {this.AttackDamage}\n" +
                             $"Ability Power: {this.AbilityPower}\n" +
                             
                             $"Max Health   : {this.MaxHealth}\n" +
                             $"Health Regen : {this.HealthRegen}\n" +
                             
                             $"Armor        : {this.Armor}\n" +
                             $"Magic Resist : {this.MagicResist}\n" +
                             
                             $"Crit. Chance : {this.CriticalChance * 100:0}%\n" +
                             $"Crit. Rate   : {this.CriticalRate * 100:0}%\n" +
                             
                             $"Max {this.Resource.Type}   : {this.Resource.MaxResourceAmount}\n" +
                             $"{this.Resource.Type} Regen : {this.Resource.ResourceRegenAmount}\n";
        return statsString;
    }
}   