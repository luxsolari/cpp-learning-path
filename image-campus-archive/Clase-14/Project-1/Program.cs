static void Main()
{

    Console.WriteLine(Console.BufferWidth + "x" + Console.BufferHeight);
    Console.WriteLine(Console.WindowWidth + "x" + Console.WindowHeight);

    Console.Title = "Mi programa genial";

    Console.BackgroundColor = ConsoleColor.DarkBlue;
    Console.ForegroundColor = ConsoleColor.Yellow;

    Console.Clear();

    int variableSize = 15;

    int[] nums = new int[variableSize];

    Random random = new Random();

    for (int i = 0; i < nums.Length; i++)
    {
        nums[i] = random.Next(100, 200);
        Console.Write(nums[i] + ", ");
    }

    Console.WriteLine();

    int[,] numsBidimensional = new int[3, 5];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            numsBidimensional[i, j] = random.Next(20, 40);
            Console.Write(numsBidimensional[i, j] + ", ");
        }

        Console.WriteLine();
    }

    Console.ReadKey();

    int width = Console.WindowWidth;
    int height = Console.WindowHeight;

    Console.WindowWidth = 80;
    Console.WindowWidth = 20;

    Console.ReadKey();

}