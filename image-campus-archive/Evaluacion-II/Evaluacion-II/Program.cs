using System.Text.Json;
using Evaluacion_II.Utils;

namespace Evaluacion_II;
public static class Program
{
    public static void Main(string[] args)
    {
        DibujarBanner();
        Console.Write("Presiona una tecla para comenzar...\n\n");
        Console.ReadKey(true);
        ShowMainMenu();
    }

    public static void ShowMainMenu()
    {
        bool quitSelected = false;

        // Load player "databse"
        Globals.players = FileUtils.DeserializeIntoList<Player>(Globals.playersFile);
        
        while (!quitSelected)
        {
            Console.WriteLine();
            Console.WriteLine("  MENU PRINCIPAL  ");
            Console.WriteLine("------------------");
            Console.WriteLine("1 - Iniciar con Jugadores nuevos ");
            Console.WriteLine("2 - Iniciar con Jugadores guardados");
            Console.WriteLine("3 - Rankings      ");
            Console.WriteLine("4 - Salir         ");
            Console.WriteLine("------------------");
            Console.Write("-> ");
            ConsoleKey pressedKey = Console.ReadKey().Key;

            Player player1 = null;
            Player player2 = null;
            Game game;
            switch (pressedKey)
            {
                case ConsoleKey.D1:
                case ConsoleKey.NumPad1:
                    Console.WriteLine();
                    Console.WriteLine($"Inicializando nuevo jugador 1...");
                    player1 = GeneratorUtils.CreateNewPlayer();
                    Console.WriteLine($"Inicializando nuevo jugador 2...");
                    player2 = GeneratorUtils.CreateNewPlayer();
                    
                    Console.WriteLine($"Iniciando partida con los jugadores {player1.Name} y {player2.Name}...");
                    Thread.Sleep(3000);

                    game = new Game(ref player1, ref player2);
                    game.Play();

                    Globals.players?.Add(player1);
                    Globals.players?.Add(player2);
                    FileUtils.SerializeToJSONFile(ref Globals.players, ref Globals.playersFile);
                    Console.Clear();
                    DibujarBanner();
                    break;
                case ConsoleKey.D2:
                case ConsoleKey.NumPad2:
                    bool jugador1Encontrado = false;
                    bool jugador2Encontrado = false;

                    do
                    {
                        Console.WriteLine();
                        Console.WriteLine("Ingresa el nombre del jugador 1: ");
                        Console.Write("-> ");
                        string player1NameString = Console.ReadLine() ?? "";
                    
                        foreach (Player loadedPlayer in Globals.players!)
                            if (loadedPlayer.Name == player1NameString) player1 = loadedPlayer;

                        if (player1 == null)
                            Console.WriteLine("Jugador no encontrado!");
                        else
                            jugador1Encontrado = true;
                    } while (!jugador1Encontrado);

                    do
                    {
                        Console.WriteLine();
                        Console.WriteLine("Ingresa el nombre del jugador 2: ");
                        Console.Write("-> ");
                        string player2NameString = Console.ReadLine() ?? "";
                    
                        foreach (Player loadedPlayer in Globals.players!)
                            if (loadedPlayer.Name == player2NameString) player2 = loadedPlayer;

                        if (player2 == null)
                            Console.WriteLine("Jugador no encontrado!");
                        else
                            jugador2Encontrado = true;
                    } while (!jugador2Encontrado);
                    
                    Console.WriteLine($"Iniciando partida con los jugadores {player1.Name} y {player2.Name}...");
                    game = new Game(ref player1, ref player1);
                    game.Play();
                    
                    FileUtils.SerializeToJSONFile(ref Globals.players, ref Globals.playersFile);
                    Thread.Sleep(3000);
                    Console.Clear();
                    DibujarBanner();
                    break;
                case ConsoleKey.D3:
                case ConsoleKey.NumPad3:
                    Console.Clear();
                    Console.WriteLine();
                    Console.WriteLine("RANKING DE PUNTAJES");
                    Console.WriteLine("-------------------");
                    // Sorting de una lista usando lambda expression
                    // https://stackoverflow.com/questions/1250281/c-sharp-how-to-sort-a-sorted-list-by-its-value-column
                    if (Globals.players is { Count: > 0 })
                    {
                        var sortedPlayers = Globals.players.OrderByDescending(p => p.Score).ThenByDescending(p => p.Gold);
                        foreach (Player sortedPlayer in sortedPlayers)
                        {
                            Console.WriteLine($"{sortedPlayer.Score} puntos, {sortedPlayer.Gold} Gold - {sortedPlayer.Name} ");
                        }
                    }
                    else
                    {
                        Console.WriteLine("No hay jugadores guardados.");
                    }

                    Console.WriteLine("-------------------");
                    Console.WriteLine("Presiona cualquier tecla para volver al menu principal.");
                    Console.ReadKey(true);
                    Console.Clear();
                    DibujarBanner();
                    break;
                case ConsoleKey.D4:
                case ConsoleKey.NumPad4:
                    Console.WriteLine();
                    quitSelected = true;
                    Console.WriteLine("Saliendo de League of Consoles...");
                    Thread.Sleep(2000);
                    break;
            }
        }
    }
    
    private static void DibujarBanner()
    {
        Console.SetWindowSize(120, 35);
        Thread.Sleep(50);
        Console.WriteLine(
            "--------------------------------------------------------------------------------------------------------");
        Thread.Sleep(50);
        Console.WriteLine(
            "De los creadores de  'Totally Predictable Battle Simulator and Totally Predictable 'Rock-Paper-Scissors'");
        Thread.Sleep(50);
        Console.WriteLine(
            "--------------------------------------------------------------------------------------------------------");
        Thread.Sleep(150);
        Console.WriteLine(
            "       ╔╗   ╔═══╗╔═══╗╔═══╗╔╗ ╔╗╔═══╗    ╔═══╗ ╔═══╗    ╔═══╗╔═══╗╔═╗ ╔╗╔═══╗╔═══╗╔╗   ╔═══╗╔═══╗       ");
        Thread.Sleep(50);
        Console.WriteLine(
            "       ║║   ║╔══╝║╔═╗║║╔═╗║║║ ║║║╔══╝    ║╔═╗║ ║╔══╝    ║╔═╗║║╔═╗║║║╚╗║║║╔═╗║║╔═╗║║║   ║╔══╝║╔═╗║       ");
        Thread.Sleep(50);
        Console.WriteLine(
            "       ║║   ║╚══╗║║ ║║║║ ╚╝║║ ║║║╚══╗    ║║ ║║ ║╚══╗    ║║ ╚╝║║ ║║║╔╗╚╝║║╚══╗║║ ║║║║   ║╚══╗║╚══╗       ");
        Thread.Sleep(50);
        Console.WriteLine(
            "       ║║ ╔╗║╔══╝║╚═╝║║║╔═╗║║ ║║║╔══╝    ║║ ║║ ║╔══╝    ║║ ╔╗║║ ║║║║╚╗║║╚══╗║║║ ║║║║ ╔╗║╔══╝╚══╗║       ");
        Thread.Sleep(50);
        Console.WriteLine(
            "       ║╚═╝║║╚══╗║╔═╗║║╚╩═║║╚═╝║║╚══╗    ║╚═╝║╔╝╚╗      ║╚═╝║║╚═╝║║║ ║║║║╚═╝║║╚═╝║║╚═╝║║╚══╗║╚═╝║       ");
        Thread.Sleep(50);
        Console.WriteLine(
            "       ╚═══╝╚═══╝╚╝ ╚╝╚═══╝╚═══╝╚═══╝    ╚═══╝╚══╝      ╚═══╝╚═══╝╚╝ ╚═╝╚═══╝╚═══╝╚═══╝╚═══╝╚═══╝       ");
        Thread.Sleep(50);
    }
}