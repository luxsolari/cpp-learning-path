using System;
using OneMoreSnake.Handlers;
using OneMoreSnake.UI;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.States
{
    internal class MainMenuState : LoopState
    {
        private readonly Button controlsButton;
        private readonly Button creditsButton;
        private readonly Button playButton;

        private readonly Text pointsRecordText;
        private readonly Button quitButton;
        private readonly Text recordsText;
        private readonly Text speedRecordText;
        private readonly Text timeRecordText;
        private readonly Text titleText;


        public MainMenuState(WindowHandler window) : base(ref window)
        {
            var fontFilePath = Globals.FontPath;
            Font titleFont = new Font(fontFilePath);
            titleText = new Text("One More Snake", titleFont);
            recordsText = new Text("Your Best Records: ", titleFont);

            pointsRecordText = new Text("Best Score: 999999 points", titleFont);
            speedRecordText = new Text("Best Speed : 999 U/S", titleFont);
            timeRecordText = new Text("Best Time  : 9999 seconds", titleFont);

            var buttonSpacing = 80f;

            titleText.CharacterSize = 120;
            titleText.FillColor = Color.White;
            titleText.Style = Text.Styles.Bold;
            titleText.OutlineColor = Color.Black;
            titleText.OutlineThickness = 1f;

            recordsText.CharacterSize = 32;
            recordsText.FillColor = Color.White;
            recordsText.Style = Text.Styles.Bold;
            recordsText.OutlineColor = Color.Black;
            recordsText.OutlineThickness = 1f;

            pointsRecordText.CharacterSize = 32;
            pointsRecordText.FillColor = Color.White;
            pointsRecordText.Style = Text.Styles.Bold;
            pointsRecordText.OutlineColor = Color.Black;
            pointsRecordText.OutlineThickness = 1f;

            speedRecordText.CharacterSize = 32;
            speedRecordText.FillColor = Color.White;
            speedRecordText.Style = Text.Styles.Bold;
            speedRecordText.OutlineColor = Color.Black;
            speedRecordText.OutlineThickness = 1f;

            timeRecordText.CharacterSize = 32;
            timeRecordText.FillColor = Color.White;
            timeRecordText.Style = Text.Styles.Bold;
            timeRecordText.OutlineColor = Color.Black;
            timeRecordText.OutlineThickness = 1f;

            FloatRect titleRect = titleText.GetLocalBounds();
            FloatRect recordsRect = recordsText.GetLocalBounds();

            FloatRect pointsRecordRect = pointsRecordText.GetLocalBounds();
            FloatRect timeRecordRect = timeRecordText.GetLocalBounds();
            FloatRect speedRecordRect = speedRecordText.GetLocalBounds();

            titleText.Origin = new Vector2f(titleRect.Width / 2f, 0);
            titleText.Position = new Vector2f(Globals.WindowWidthResolution / 2f, titleRect.Height - 70);

            recordsText.Origin = new Vector2f(recordsRect.Width / 2f, 0);
            recordsText.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                titleRect.Height + recordsRect.Height + 50);

            pointsRecordText.Origin = new Vector2f(recordsRect.Width / 1.5f, 0);
            pointsRecordText.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                recordsText.Position.Y + pointsRecordRect.Height + 30);

            timeRecordText.Origin = new Vector2f(recordsRect.Width / 1.5f, 0);
            timeRecordText.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                pointsRecordText.Position.Y + timeRecordRect.Height + 10);

            speedRecordText.Origin = new Vector2f(recordsRect.Width / 1.5f, 0);
            speedRecordText.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                timeRecordText.Position.Y + speedRecordRect.Height + 10);

            Vector2f quitButtonPosition = new Vector2f(Globals.WindowWidthResolution / 2f,
                Globals.WindowHeightResolution - buttonSpacing);
            Vector2f creditsButtonPosition = new Vector2f(Globals.WindowWidthResolution / 2f,
                quitButtonPosition.Y - buttonSpacing);
            Vector2f controlsButtonPosition = new Vector2f(Globals.WindowWidthResolution / 2f,
                creditsButtonPosition.Y - buttonSpacing);
            Vector2f playButtonPosition = new Vector2f(Globals.WindowWidthResolution / 2f,
                controlsButtonPosition.Y - buttonSpacing);

            playButton = new Button(windowHandler.GetRenderWindow(), null!, Globals.FontPath,
                playButtonPosition, "Play");
            controlsButton = new Button(windowHandler.GetRenderWindow(), null!, Globals.FontPath,
                controlsButtonPosition, "How To Play");
            creditsButton = new Button(windowHandler.GetRenderWindow(), null!, Globals.FontPath,
                creditsButtonPosition, "Credits");
            quitButton = new Button(windowHandler.GetRenderWindow(), null!, Globals.FontPath,
                quitButtonPosition, "Quit");

            playButton.SetColor(new Color(0, 220, 0));
            controlsButton.SetColor(new Color(0, 0, 220));
            creditsButton.SetColor(new Color(255, 220, 0));
            quitButton.SetColor(new Color(220, 0, 0));

            playButton.FormatText(Color.White, Color.Black, 32, true,
                1f);
            controlsButton.FormatText(Color.White, Color.Black, 32, true,
                1f);
            creditsButton.FormatText(Color.White, Color.Black, 32, true,
                1f);
            quitButton.FormatText(Color.White, Color.Black, 32, true,
                1f);

            View view = new View(windowHandler.GetRenderWindow().GetView())
            {
                Center = new Vector2f(Globals.WindowWidthResolution / 2f, Globals.WindowHeightResolution / 2f)
            };

            windowHandler.GetRenderWindow().SetView(view);
        }

        public event Action OnPlayPressed = null!;
        public event Action OnControlsPressed = null!;
        public event Action OnCreditsPressed = null!;
        public event Action OnQuitPressed = null!;

        private void OnPressPlay()
        {
            OnPlayPressed.Invoke();
        }

        private void OnPressControls()
        {
            OnControlsPressed.Invoke();
        }

        private void OnPressCredits()
        {
            OnCreditsPressed.Invoke();
        }

        private void OnPressQuit()
        {
            OnQuitPressed.Invoke();
        }

        protected override void Start()
        {
            playButton.OnPressed += OnPressPlay;
            controlsButton.OnPressed += OnPressControls;
            creditsButton.OnPressed += OnPressCredits;
            quitButton.OnPressed += OnPressQuit;
            windowHandler.GetRenderWindow().Closed += OnCloseWindow;
            SoundHandler.BGMLibrary["bgm-main"].Play(true);
        }

        protected override void Update(float deltaTime)
        {
            pointsRecordText.DisplayedString = $"Best Score: {Globals.MaxScore:000000} points";
            timeRecordText.DisplayedString = $"Best Time: {Globals.MaxTime:000} seconds";
            speedRecordText.DisplayedString = $"Best Speed: {Globals.MaxTopSpeed:000} u/s";
        }

        protected override void Draw()
        {
            windowHandler.GetRenderWindow().Clear(new Color(16, 16, 16));
            windowHandler.GetRenderWindow().Draw(titleText);
            windowHandler.GetRenderWindow().Draw(recordsText);

            windowHandler.GetRenderWindow().Draw(pointsRecordText);
            windowHandler.GetRenderWindow().Draw(timeRecordText);
            windowHandler.GetRenderWindow().Draw(speedRecordText);

            playButton.Draw();
            controlsButton.Draw();
            creditsButton.Draw();
            quitButton.Draw();
        }

        protected override void Finish()
        {
            playButton.OnPressed -= OnPressPlay;
            controlsButton.OnPressed -= OnPressControls;
            creditsButton.OnPressed -= OnPressCredits;
            quitButton.OnPressed -= OnPressQuit;
            windowHandler.GetRenderWindow().Closed -= OnCloseWindow;
            SoundHandler.BGMLibrary["bgm-main"].Stop();
        }
    }
}