using System.Text.Json.Serialization;

namespace Evaluacion_II.Items;

[Serializable]
public class Armor : Item
{
    public float BonusArmor { get; set; }
    public float BonusMagicResist { get; set; }
    
    public Armor(string? name, float bonusArmor, float bonusMagicResist) : base(name)
    {
        BonusArmor = bonusArmor;
        BonusMagicResist = bonusMagicResist;
    }
}