public class Archer : Character
{
    private float attackRange;
    private int arrowCount;

    public Archer(float attackRange, int arrowCount, string name, int age) : base(name, age)
    {
        this.attackRange = attackRange;
        this.arrowCount = arrowCount;
    }

    public void ShootTarget(float distance)
    {
        if (this.arrowCount >= 1)
        {
            Random random = new Random();
            this.arrowCount --;
            float hitChance = Math.Clamp(100.0f - ((distance - this.attackRange)), 0.0f, 100.0f) / 2;

            if (random.Next(100) < hitChance)
            {
                Console.WriteLine("La flecha dio en el objetivo!");
            }
            else
            {
                Console.WriteLine("La flecha ha fallado el objetivo!");
            }

        }
        else
        {
            Console.WriteLine("No me quedan mas flechas!");
        }
    }

    public int GetArrowCount()
    {
        return this.arrowCount;
    }

    public void ShowStats()
    {
        Console.WriteLine($"Nombre: {this.name}");
        Console.WriteLine($"Edad: {this.age}");
        Console.WriteLine($"Attack Range: {this.attackRange}");
        Console.WriteLine($"Arrows: {this.arrowCount}");
    }
}

