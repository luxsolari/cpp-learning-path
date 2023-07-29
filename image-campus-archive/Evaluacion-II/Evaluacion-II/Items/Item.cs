using System.Text.Json.Serialization;

namespace Evaluacion_II.Items;

[Serializable]
public abstract class Item
{
    public string? Name { get ; set ; }

    protected Item(string? name)
    {
        this.Name = name;
    }
}