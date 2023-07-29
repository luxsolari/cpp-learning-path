using System;
using OneMoreSnake.Handlers;
using OneMoreSnake.UI;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace OneMoreSnake.States
{
    public class ControlsMenuState : LoopState
    {
        //|
        private const string instructions = "Use the arrow keys or the WASD keys to move around.\n\n" +
                                            "Your goal is to score the most points as you can,\n" +
                                            "as fast as possible. \n" +
                                            "You score bonus points the longer the game goes on,\n" +
                                            "so keep an eye on that timer.";

        private readonly string bluePickupsString = "Blue pickups allow to temporarily loop over walls. \n";
        private readonly Text bluePickupText;
        private readonly Text instructionsText;
        private readonly Button quitButton;

        private readonly string redPickupsString = "Red pickups extend your body and make you go faster.\n";

        private readonly Text redPickupText;

        private readonly Text titleText;
        private readonly string YellowPickupsString = "Yellow pickups give you invulnerability for some time. \n";
        private readonly Text yellowPickupText;

        public ControlsMenuState(WindowHandler window) : base(ref window)
        {
            var fontFilePath = Globals.FontPath;
            Font titleFont = new Font(fontFilePath);
            titleText = new Text("How to Play", titleFont);

            redPickupText = new Text(redPickupsString, titleFont);
            bluePickupText = new Text(bluePickupsString, titleFont);
            yellowPickupText = new Text(YellowPickupsString, titleFont);
            instructionsText = new Text(instructions, titleFont);

            var buttonSpacing = 80f;

            titleText.CharacterSize = 100;
            titleText.FillColor = Color.White;
            titleText.Style = Text.Styles.Bold;
            titleText.OutlineColor = Color.Black;
            titleText.OutlineThickness = 1f;

            instructionsText.CharacterSize = 30;
            instructionsText.FillColor = Color.White;
            instructionsText.Style = Text.Styles.Bold;
            instructionsText.OutlineColor = Color.Black;
            instructionsText.OutlineThickness = 1f;

            redPickupText.CharacterSize = 30;
            redPickupText.FillColor = Color.Red;
            redPickupText.Style = Text.Styles.Bold;
            redPickupText.OutlineColor = Color.Black;
            redPickupText.OutlineThickness = 1f;

            bluePickupText.CharacterSize = 30;
            bluePickupText.FillColor = Color.Blue;
            bluePickupText.Style = Text.Styles.Bold;
            bluePickupText.OutlineColor = Color.Black;
            bluePickupText.OutlineThickness = 1f;

            yellowPickupText.CharacterSize = 30;
            yellowPickupText.FillColor = Color.Yellow;
            yellowPickupText.Style = Text.Styles.Bold;
            yellowPickupText.OutlineColor = Color.Black;
            yellowPickupText.OutlineThickness = 1f;

            FloatRect titleRect = titleText.GetLocalBounds();
            FloatRect instructionsRect = instructionsText.GetLocalBounds();

            titleText.Origin = new Vector2f(titleRect.Width / 2f, 0);
            titleText.Position = new Vector2f(Globals.WindowWidthResolution / 2f, titleRect.Height - 70);

            instructionsText.Origin = new Vector2f(instructionsRect.Width / 2f, 0);
            instructionsText.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                titleRect.Height + 70);

            redPickupText.Origin = new Vector2f(instructionsRect.Width / 2f, 0);
            redPickupText.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                instructionsRect.Height + 210);

            bluePickupText.Origin = new Vector2f(instructionsRect.Width / 2f, 0);
            bluePickupText.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                instructionsRect.Height + 255);

            yellowPickupText.Origin = new Vector2f(instructionsRect.Width / 2f, 0);
            yellowPickupText.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                instructionsRect.Height + 300);

            Vector2f quitButtonPosition = new Vector2f(Globals.WindowWidthResolution / 2f,
                Globals.WindowHeightResolution - buttonSpacing);
            quitButton = new Button(windowHandler.GetRenderWindow(), null!, Globals.FontPath,
                quitButtonPosition, "Go Back");
            quitButton.SetColor(new Color(200, 0, 0));
            quitButton.FormatText(Color.White, Color.Black, 32, true,
                1f);

            View view = new View(windowHandler.GetRenderWindow().GetView())
            {
                Center = new Vector2f(Globals.WindowWidthResolution / 2f, Globals.WindowHeightResolution / 2f)
            };
            windowHandler.GetRenderWindow().SetView(view);
        }

        public event Action OnQuitPressed = null!;
        public event Action OnReturnToMainMenuPressed = null!;

        private void OnPressKey(object? sender, KeyEventArgs keyEventArgs)
        {
            if (keyEventArgs.Code == Keyboard.Key.Escape && IsRunning) OnReturnToMainMenuPressed.Invoke();
        }

        private void OnPressQuit()
        {
            OnQuitPressed.Invoke();
        }

        protected override void Start()
        {
            windowHandler.GetRenderWindow().Clear(new Color(16, 16, 16));
            windowHandler.GetRenderWindow().Closed += OnCloseWindow;
            windowHandler.GetRenderWindow().KeyPressed += OnPressKey;
            quitButton.OnPressed += OnPressQuit;
            SoundHandler.BGMLibrary["bgm-credits"].Play(true);
        }

        protected override void Update(float deltaTime)
        {
        }

        protected override void Draw()
        {
            windowHandler.GetRenderWindow().Clear(new Color(16, 16, 16));
            windowHandler.GetRenderWindow().Draw(titleText);
            windowHandler.GetRenderWindow().Draw(instructionsText);
            windowHandler.GetRenderWindow().Draw(redPickupText);
            windowHandler.GetRenderWindow().Draw(bluePickupText);
            windowHandler.GetRenderWindow().Draw(yellowPickupText);
            quitButton.Draw();
        }

        protected override void Finish()
        {
            windowHandler.GetRenderWindow().Closed -= OnCloseWindow;
            windowHandler.GetRenderWindow().KeyPressed -= OnPressKey;
            quitButton.OnPressed -= OnPressQuit;
            SoundHandler.BGMLibrary["bgm-credits"].Stop();
        }
    }
}