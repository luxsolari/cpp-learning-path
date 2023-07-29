using System.Text.Json.Serialization;

namespace Evaluacion_II.Items;

[Serializable]
public class Weapon : Item
{
    public float BonusDamage { get; set; }
    public float BonusAbilityPower { get; set; }
    public float BonusAgility { get; set;}
    public float BonusCriticalChance { get; set; }
    public float BonusCriticalRate { get; set; }
    
    public Weapon(string? name, float bonusDamage, float bonusAbilityPower, float bonusAgility, float bonusCriticalChance, float bonusCriticalRate) : base(name)
    {
        this.BonusDamage = bonusDamage;
        this.BonusAbilityPower = bonusAbilityPower;
        this.BonusAgility = bonusAgility;
        this.BonusCriticalChance = bonusCriticalChance;
        this.BonusCriticalRate = bonusCriticalRate;
    }
}
