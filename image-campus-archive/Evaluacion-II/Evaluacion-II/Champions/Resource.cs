using Evaluacion_II.Enums;

namespace Evaluacion_II.Champions;

public class Resource
{
    public ResourceType Type { get;}
    public float MaxResourceAmount { get; }
    public float ResourceRegenAmount { get; }

    public Resource(ResourceType type, float maxResourceAmount, float resourceRegenAmount)
    {
        Type = type;
        MaxResourceAmount = maxResourceAmount;
        ResourceRegenAmount = resourceRegenAmount;
    }
}