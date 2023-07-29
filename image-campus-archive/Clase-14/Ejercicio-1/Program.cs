using System;

internal static class Program
{
    private static void Main()
    {
        int offsetX = 1;
        int offsetY = 5;
        int width = Console.BufferWidth - offsetX;
        int height = Console.BufferHeight - offsetY;
        Random random = new Random();
        bool salir = false;

        DibujarMarco(width, height, offsetX, offsetY);
        Star[] stars = new Star[3]
        {
            new Star("Polaris", random.Next(offsetX+1, width-1), random.Next(offsetY+1, height-1)), 
            new Star("Altair",  random.Next(offsetX+1, width-1), random.Next(offsetY+1, height-1)), 
            new Star("Canopus", random.Next(offsetX+1, width-1), random.Next(offsetY+1, height-1))
        };

        for (int i = 0; i < stars.Length; i++)
        {
            stars[i].Show();
        }

        Console.SetCursorPosition(0,0);
        for (int i = 0; i < stars.Length; i++)
        {
            stars[i].PrintCoordinates();
            Console.Write("  ");
        }

        while (!salir)
        {
            ConsoleKey key = Console.ReadKey(true).Key;
            switch (key)
            {
                case ConsoleKey.Escape:
                    Console.Clear();
                    salir = true;
                    break;
                default:
                    if (Console.BufferWidth != width + offsetX || Console.BufferHeight != height + offsetY)
                    {
                        width = Console.BufferWidth - offsetX;
                        height = Console.BufferHeight - offsetY;
                        Console.Clear();
                        DibujarMarco(width, height, offsetX, offsetY);

                        Console.SetCursorPosition(0,0);
                        for (int i = 0; i < stars.Length; i++)
                        {
                            stars[i].PrintCoordinates();
                            Console.Write("  ");
                        }
                        for (int i = 0; i < stars.Length; i++)
                        {
                            stars[i].Move(random.Next(offsetX+1, width-1), random.Next(offsetY+1, height));
                            stars[i].Show();
                        }

                    }
                    else
                    {
                        Console.SetCursorPosition(0,0);
                        Console.WriteLine();
                        Console.SetCursorPosition(0, 0);
                        for (int i = 0; i < stars.Length; i++)
                        {
                            stars[i].PrintCoordinates();
                            Console.Write("  ");
                        }
                        for (int i = 0; i < stars.Length; i++)
                        {
                            stars[i].Hide();
                            stars[i].Move(random.Next(offsetX+1, width-1), random.Next(offsetY+1, height));
                            stars[i].Show();
                        }
                    }
                    break;
            }
        }
    }

    static void DibujarMarco(int width, int height, int offsetX, int offsetY)
    {
        Console.SetCursorPosition(offsetX - 1, offsetY - 1);

        // Dibujamos un marco en la consola
        for (int i = 0; i <= height; i++)
        {
            if (i == 0 || i == height)
            {
                for (int j = 0; j <= width; j++)
                {
                    if (j == 0 || j == width) Console.Write("+");
                    else Console.Write("-");
                }
            }
            else
            {
                for (int j = 0; j <= width; j++)
                {
                    if (j == 0 || j == width) Console.Write("|");
                    else Console.Write(" ");
                }
            }
        }
    }
}


