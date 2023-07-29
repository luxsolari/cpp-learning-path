using System;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace OneMoreSnake.Handlers
{
    public class WindowHandler
    {
        private readonly RenderWindow window = null!;
        private readonly Vector2u windowSize;
        private readonly string windowTitle;

        public WindowHandler(string title, Vector2u size)
        {
            windowTitle = title;
            windowSize = size;
            VideoMode videoMode = new VideoMode(windowSize.X, windowSize.Y);
            window = new RenderWindow(videoMode, windowTitle, Styles.Default);
            window.SetFramerateLimit(Globals.FpsLimit);

            window.Closed += OnWindowClose;
        }

        public void DispatchEvents()
        {
            window.DispatchEvents();
        }

        public RenderWindow GetRenderWindow()
        {
            return window;
        }

        private void OnWindowClose(object? sender, EventArgs e)
        {
            window.Close();
        }
    }
}