public class Mage : Character
{
    private int castingLevel;
    private float maxMana;
    private float mana;

    public Mage(int castingLevel, float mana, string name, int age) : base(name, age)
    {
        this.castingLevel = castingLevel;
        this.mana = mana;
        this.maxMana = mana;
    }

    public void EnchantTarget(int targetMagicResist)
    {
        float manaCost = 10f + targetMagicResist * 0.05f;

        if (mana >= manaCost )
        {
            Random random = new Random();
            this.mana -= manaCost;
            float hitChance = Math.Clamp(100.0f - (targetMagicResist - this.castingLevel), 0.0f, 100.0f) / 2;

            if (random.Next(100) < hitChance)
            {
                Console.WriteLine("El objetivo ha quedado encantado!");
            }
            else
            {
                Console.WriteLine("El objetivo resistio la magia!");
            }
        }
        else
        {
            Console.WriteLine("No tengo mas mana!");
        }
    }

    public float GetMana()
    {
        return this.mana;
    }

    public void ShowStats()
    {
        Console.WriteLine($"Nombre: {this.name}");
        Console.WriteLine($"Edad: {this.age}");
        Console.WriteLine($"Casting Level: {this.castingLevel}");
        Console.WriteLine($"Mana: {this.mana} / {this.maxMana}");
    }

}
