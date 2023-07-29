using System.Text.Json.Serialization;

namespace Evaluacion_II.Items;

[Serializable]
public class Consumable : Item
{
    public Consumable(string? name) : base(name)
    {
        
    }
}