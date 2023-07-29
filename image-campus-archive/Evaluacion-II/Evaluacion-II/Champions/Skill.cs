namespace Evaluacion_II.Champions;

public class Skill
{
    public string Name { get; }
    public float BaseDamage { get; }
    
    public float Cost { get; }

    public Skill(){}
    public Skill(string name, float baseDamage, float cost)
    {
        Name = name;
        BaseDamage = baseDamage;
        Cost = cost;
    }
}