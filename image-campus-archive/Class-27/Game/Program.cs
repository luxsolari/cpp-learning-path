using SFML.Window;
using SFML.Graphics;

namespace Game
{
    class Program
    {
        static void Main ()
        {
            VideoMode videoMode = new VideoMode(1280, 720);
            string title = "Mi Jueguito";

            RenderWindow renderWindow = new RenderWindow(videoMode, title);

            GameLoop gameLoop = new GameLoop(renderWindow);

            gameLoop.Play();
        }
    }
}
