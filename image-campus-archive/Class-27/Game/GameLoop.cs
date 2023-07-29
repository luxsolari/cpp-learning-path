using System;
using SFML.System;
using SFML.Graphics;

namespace Game
{
    class GameLoop
    {
        private RenderWindow window;
        private bool isRunning;

        private Player player;
        private Entity background;
        private Entity ground;
        private Entity wall;

        public const int MinX = 0;
        public const int MaxX = 3840;
        public const int MinY = 0;
        public const int MaxY = 1080;
        public const int GroundHeight = 72;
        private CameraHandler cameraHandler;

        public GameLoop (RenderWindow window)
        {
            this.window = window;
        }

        private void Start ()
        {
            Vector2f playerPosition = new Vector2f(window.Size.X / 2f, window.Size.Y / 2f);
            Vector2i playerSize = new Vector2i(192, 288);
            Vector2i wallSize = new Vector2i(128, 128);
            float playerSpeed = 300f;
            float playerJumpSpeed = 600f;

            background = new Entity("Assets/Images/Background.png");
            ground = new Entity("Assets/Images/Ground.png");

            player = new Player("Assets/Images/Player.png", playerSize, playerSpeed, playerJumpSpeed);
            wall = new Entity("Assets/Images/Wall.png");

            background.Graphic.TextureRect = new IntRect(0, 0, MaxX, (int)window.Size.Y);
            ground.Graphic.TextureRect = new IntRect(0, 0, MaxX, GroundHeight);

            background.Graphic.Texture.Repeated = true;
            ground.Graphic.Texture.Repeated = true;

            ground.Position = new Vector2f(0f, window.Size.Y - GroundHeight);
            player.Position = new Vector2f(0f, window.Size.Y - GroundHeight - playerSize.Y);
            wall.Position = new Vector2f(window.Size.X / 2f, window.Size.Y - GroundHeight - wallSize.Y);

            ground.Scale = new Vector2f(2f, 2f);

            player.Mass = 100f;
            wall.Mass = 10f;
            wall.IsStatic = true;

            CollisionsHandler.AddEntity(player);
            CollisionsHandler.AddEntity(wall);

            this.cameraHandler = new CameraHandler(window, player);
            
            window.Closed += OnCloseWindow;
            this.window.SetFramerateLimit(60);
        }

        private void ProcessInput ()
        {
            window.DispatchEvents();
        }

        private void Update (float deltaTime)
        {
            player.Update(deltaTime);
            CollisionsHandler.Update();
            this.cameraHandler.Update();
        }

        private void Draw ()
        {
            window.Clear();

            window.Draw(background.Graphic);
            window.Draw(ground.Graphic);
            window.Draw(player.Graphic);
            window.Draw(wall.Graphic);

            window.Display();
        }

        private void Finish ()
        {
            window.Closed -= OnCloseWindow;

            CollisionsHandler.RemoveEntity(player);
            CollisionsHandler.RemoveEntity(wall);
        }

        private void OnCloseWindow (object sender, EventArgs e)
        {
            isRunning = false;
            window.Close();
        }

        public void Play ()
        {
            Clock clock = new Clock();

            isRunning = true;

            Start();

            while (isRunning)
            {
                Time deltaTime = clock.Restart();

                ProcessInput();
                Update(deltaTime.AsSeconds());
                Draw();
            }

            Finish();
        }
    }
}
