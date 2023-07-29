using SFML.Graphics;
using SFML.Window;

namespace Snake
{
    public static class Program
    {
        public static void Main(string[] args)
        {
            RenderWindow appWindow = new RenderWindow(new VideoMode(500, 500), "SNAKE");
            appWindow.Closed += delegate(object? sender, EventArgs eventArgs) { appWindow.Close(); };

            while (appWindow.IsOpen)
            {
                appWindow.DispatchEvents();
                
                
                appWindow.Clear(new Color(26, 28, 36));
                appWindow.Display();
            }
        }
    }
    
};
