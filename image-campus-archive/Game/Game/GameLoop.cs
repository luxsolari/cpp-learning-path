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

        public GameLoop (RenderWindow window)
        {
            this.window = window;
        }

        private void Start()
        {
            Console.WriteLine("Se inicio el loop");
            Vector2u windowSize = window.Size;
            Vector2f playerPosition = new Vector2f(windowSize.X / 2f, windowSize.Y / 2f);


            //background = new Entity("filepath para un background");
            //background.Graphic.TextureRect = new IntRect(0, 0, 3000, (int)1080);
            //ground.Graphic.TextureRect = new IntRect(0, 0, 1080, 1920);
            //background.Graphic.Texture.Repeated = true;
            //ground.Graphic.Texture.Repeated = true;
            
            //ground = new Entity("filepath del ground");
            player = new Player("assets/images/spritesheet.png", new Vector2i(48, 48), 100f);
            // Suscripcion a evento
            window.Closed += OnCloseWindow;
        }


        // 1. Capturar input ProcessInput
        private void ProcessInput()
        {
            window.DispatchEvents();
        }

        // 2. Update() actualizar frame
        private void Update(Time deltaTime)
        {
            player.Update(deltaTime.AsSeconds());
            Thread.Sleep(12); 
        }

        // 3. Draw() dibujar frame en pantalla
        private void Draw()
        {
            window.Clear(Color.Black);
            //window.Draw(background.Graphic);
            //window.Draw(ground.Graphic);
            window.Draw(player.Graphic);
            window.Display();
        }

        private void Finish()
        {
            Console.WriteLine("Se termino el loop");

            // Des-Suscripcion de un evento
            window.Closed -= OnCloseWindow;
        }

        private void OnCloseWindow(Object sender, EventArgs e)
        {
            isRunning = false;
            window.Close();
        }

        public void Play()
        {
            Clock clock = new Clock();
            isRunning = true;
            int framesRendered = 0;
            float elapsedTime = 0;
            
            Start();

            while (isRunning)
            {
                Time deltaTime = clock.Restart();
                ProcessInput();
                Update(deltaTime);
                Draw();
                framesRendered ++;
                elapsedTime += deltaTime.AsSeconds();

                if (elapsedTime >= 1.0f) // un segundo pasó, mostramos el conteo de FPS.
                {
                    Console.SetCursorPosition(0, 1);
                    Console.Write($"FPS: {(int)(framesRendered / elapsedTime)}");
                    Console.WriteLine();
                    elapsedTime = 0;
                    framesRendered = 0;
                }
                
            }

            Finish();
        }
    }
}
