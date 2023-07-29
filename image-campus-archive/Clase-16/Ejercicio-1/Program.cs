internal class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Prueba de televisores");
        Console.WriteLine("---------------------");

        TV televisor1 = new TV("Samsung", 24.5f);
        TV televisor2 = new TV("LG", 22.2f);

        televisor1.TurnOn();
        televisor1.SetChannel(300);
        televisor1.SetBrightness(50);

        Console.WriteLine();
        
        televisor2.TurnOn();
        televisor2.SetChannel(700);
        televisor2.SetBrightness(75);

        Console.WriteLine();

        televisor1.PrintInfo();
        Console.WriteLine();
        televisor2.PrintInfo();

        televisor1.TurnOff();
        televisor2.TurnOff();
    }
}