using SFML.Graphics;
using SFML.Window;

namespace Game
{
    internal class Program
    {
        static void Main(string[] args)
        {
            VideoMode videoMode = new VideoMode(1280, 720);
            RenderWindow renderWindow = new RenderWindow(videoMode, "TEST");

            GameLoop gameLoop = new GameLoop(renderWindow);
            gameLoop.Play();

        }
    }
}