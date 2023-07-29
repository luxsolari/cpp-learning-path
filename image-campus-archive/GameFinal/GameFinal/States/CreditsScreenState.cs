using System;
using OneMoreSnake.Handlers;
using OneMoreSnake.UI;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace OneMoreSnake.States
{
    public class CreditsScreenState : LoopState
    {
        private readonly Text credits1;
        private readonly Text credits2;
        private readonly Text credits3;
        private readonly Text credits4;

        private readonly Text credits5;
        private readonly Text credits6;
        private readonly Text credits7;

        private readonly Button quitButton;
        private readonly Text titleText;

        public CreditsScreenState(WindowHandler window) : base(ref window)
        {
            var fontFilePath = Globals.FontPath;
            Font titleFont = new Font(fontFilePath);
            titleText = new Text("Credits", titleFont);
            credits1 = new Text("Game by Luciano Laje", titleFont);
            credits2 = new Text("Graphics created using SFML 2.5.1 - sfml-dev.org", titleFont);
            credits3 = new Text("Hyperspace Font by Neale Davidson - pixelsagas.com", titleFont);
            credits4 = new Text(" Sound FX by John Ginnane, Plaster Brain, Euphrosyn\n" +
                                "  Music by JoshuaEmpyre, FoolBoyMedia, EmcCiscoKid\n" +
                                "                   freesound.org\n" +
                                "    Sound Normalization with Audacity software\n" +
                                "                www.audacityteam.org", titleFont);

            credits5 = new Text("Made with love and passion for Image Campus", titleFont);
            credits6 = new Text("Advisory: No Atari Consoles, Nokia phones nor snakes were harmed", titleFont);
            credits7 = new Text("during the making of this game.", titleFont);

            var buttonSpacing = 80f;

            titleText.CharacterSize = 100;
            titleText.FillColor = Color.White;
            titleText.Style = Text.Styles.Bold;
            titleText.OutlineColor = Color.Black;
            titleText.OutlineThickness = 1f;

            credits1.CharacterSize = 36;
            credits1.FillColor = Color.White;
            credits1.Style = Text.Styles.Bold;
            credits1.OutlineColor = Color.Black;
            credits1.OutlineThickness = 1f;

            credits2.CharacterSize = 24;
            credits2.FillColor = Color.White;
            credits2.Style = Text.Styles.Bold;
            credits2.OutlineColor = Color.Black;
            credits2.OutlineThickness = 1f;

            credits3.CharacterSize = 24;
            credits3.FillColor = Color.White;
            credits3.Style = Text.Styles.Bold;
            credits3.OutlineColor = Color.Black;
            credits3.OutlineThickness = 1f;

            credits4.CharacterSize = 24;
            credits4.FillColor = Color.White;
            credits4.Style = Text.Styles.Bold;
            credits4.OutlineColor = Color.Black;
            credits4.OutlineThickness = 1f;

            credits5.CharacterSize = 30;
            credits5.FillColor = Color.White;
            credits5.Style = Text.Styles.Bold;
            credits5.OutlineColor = Color.Black;
            credits5.OutlineThickness = 1f;

            credits6.CharacterSize = 22;
            credits6.FillColor = Color.White;
            credits6.Style = Text.Styles.Bold;
            credits6.OutlineColor = Color.Black;
            credits6.OutlineThickness = 1f;

            credits7.CharacterSize = 22;
            credits7.FillColor = Color.White;
            credits7.Style = Text.Styles.Bold;
            credits7.OutlineColor = Color.Black;
            credits7.OutlineThickness = 1f;

            FloatRect titleRect = titleText.GetLocalBounds();
            FloatRect credits1Rect = credits1.GetLocalBounds();
            FloatRect credits2Rect = credits2.GetLocalBounds();
            FloatRect credits3Rect = credits3.GetLocalBounds();
            FloatRect credits4Rect = credits4.GetLocalBounds();
            FloatRect credits5Rect = credits5.GetLocalBounds();
            FloatRect credits6Rect = credits6.GetLocalBounds();
            FloatRect credits7Rect = credits7.GetLocalBounds();

            titleText.Origin = new Vector2f(titleRect.Width / 2f, 0);
            titleText.Position = new Vector2f(Globals.WindowWidthResolution / 2f, titleRect.Height - 70);

            credits1.Origin = new Vector2f(credits1Rect.Width / 2f, 0);
            credits1.Position = new Vector2f(Globals.WindowWidthResolution / 2f, titleRect.Height + 70);

            credits2.Origin = new Vector2f(credits2Rect.Width / 2f, 0);
            credits2.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                credits1.Position.Y + credits1Rect.Height + 20);

            credits3.Origin = new Vector2f(credits3Rect.Width / 2f, 0);
            credits3.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                credits2.Position.Y + credits2Rect.Height + 20);

            credits4.Origin = new Vector2f(credits4Rect.Width / 2f, 0);
            credits4.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                credits3.Position.Y + credits3Rect.Height + 40);

            credits5.Origin = new Vector2f(credits5Rect.Width / 2f, 0);
            credits5.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                credits4.Position.Y + credits4Rect.Height + 40);

            credits6.Origin = new Vector2f(credits6Rect.Width / 2f, 0);
            credits6.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                credits5.Position.Y + credits5Rect.Height + 40);

            credits7.Origin = new Vector2f(credits7Rect.Width / 2f, 0);
            credits7.Position = new Vector2f(Globals.WindowWidthResolution / 2f,
                credits6.Position.Y + credits6Rect.Height + 10);

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
            windowHandler.GetRenderWindow().Draw(credits1);
            windowHandler.GetRenderWindow().Draw(credits2);
            windowHandler.GetRenderWindow().Draw(credits3);
            windowHandler.GetRenderWindow().Draw(credits4);
            windowHandler.GetRenderWindow().Draw(credits5);
            windowHandler.GetRenderWindow().Draw(credits6);
            windowHandler.GetRenderWindow().Draw(credits7);
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