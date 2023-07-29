using Evaluacion_II.Champions;

namespace Evaluacion_II;
[Serializable]
public class Player
{
    public string Name { get; set; }
    public List<Champion> PlayerChampions { get; set; }
    public float Score { get; set; }
    public int Gold { get; set; }

    public Player() { }
    
    public Player(string name, List<Champion> playerChampions, float score, int gold)
    {
        Name = name;
        PlayerChampions = playerChampions;
        Score = score;
        Gold = gold;
    }
    
    public void PrintInfo ()
    {
        Console.WriteLine($"Name: {this.Name}");
        Console.WriteLine($"Score: \n{this.Score}");
        Console.WriteLine($"Gold : \n{this.Gold}");
    }
}