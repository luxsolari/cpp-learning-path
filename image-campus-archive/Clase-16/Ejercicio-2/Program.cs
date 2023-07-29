internal class Program
{
    static void Main(string[] args)
    {
        Archer archer = new Archer(50, 3, "Archer", 25);
        Mage mage = new Mage(50, 50, "Mage", 22);


        for (int i = 0; i < 5; i++)
        {
            Console.WriteLine($"Intento {i + 1}");
            Target objetivo = new Target(50, 50);
            archer.ShootTarget(objetivo.GetDistance());
            mage.EnchantTarget(objetivo.GetMagicResist());
            Console.WriteLine();
        }

        archer.ShowStats();
        Console.WriteLine();
        mage.ShowStats();

    }
}
