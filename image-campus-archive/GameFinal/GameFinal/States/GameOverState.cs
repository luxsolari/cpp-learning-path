using System;
using OneMoreSnake.Entities;
using OneMoreSnake.Enums;
using OneMoreSnake.Handlers;
using OneMoreSnake.UI;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace OneMoreSnake.States
{
    public class GameOverState : LoopState
    {
        private readonly float buttonSpacing = 80f;
        private readonly Text currentSessionScoreText;
        private readonly Text currentSessionSpeedText;
        private readonly Text currentSessionTimeText;
        private readonly GameField gameField;
        private readonly Text gameOverText;
        private readonly HUD hud;
        private readonly Text newScoreRecordText;
        private readonly Text newSpeedRecordText;
        private readonly Text newTimeRecordText;
        private readonly Button restartButton;
        private readonly Button returnToMainMenuButton;

        private readonly float textSpacing = 80f;
        private Snake player;

        public GameOverState(WindowHandler window) : base(ref window)
        {
            var fontFilePath = Globals.FontPath;
            Font gameOverTextFont = new Font(fontFilePath);
            gameField = new GameField();
            player = new Snake();
            player.GetSnakeBody().Clear();
            player.HasLost = true;
            player.SetDirection(Direction.Down);
            hud = new HUD(ref windowHandler, ref player, Globals.FontPath);
            gameOverText = new Text("GAME OVER", gameOverTextFont);

            currentSessionScoreText = new Text($"Score: {Globals.CurrentSessionScore}", gameOverTextFont);
            currentSessionSpeedText = new Text($"Top speed: {Globals.CurrentSessionTopSpeed}", gameOverTextFont);
            currentSessionTimeText = new Text($"Total time: {Globals.CurrentSessionTime} sec.", gameOverTextFont);
            newScoreRecordText = new Text("NEW HIGH SCORE!", gameOverTextFont);
            newSpeedRecordText = new Text("NEW SPEED RECORD!", gameOverTextFont);
            newTimeRecordText = new Text("NEW TIME RECORD!", gameOverTextFont);


            gameOverText.CharacterSize = 120;
            gameOverText.FillColor = new Color(255, 0, 0);
            gameOverText.OutlineColor = Color.Black;
            gameOverText.Style = Text.Styles.Bold;
            gameOverText.OutlineThickness = 2f;

            currentSessionScoreText.CharacterSize = 36;
            currentSessionScoreText.FillColor = new Color(255, 255, 255);
            currentSessionScoreText.OutlineColor = Color.Black;
            currentSessionScoreText.Style = Text.Styles.Bold;
            currentSessionScoreText.OutlineThickness = 2f;

            currentSessionSpeedText.CharacterSize = 36;
            currentSessionSpeedText.FillColor = new Color(255, 255, 255);
            currentSessionSpeedText.OutlineColor = Color.Black;
            currentSessionSpeedText.Style = Text.Styles.Bold;
            currentSessionSpeedText.OutlineThickness = 2f;

            currentSessionTimeText.CharacterSize = 36;
            currentSessionTimeText.FillColor = new Color(255, 255, 255);
            currentSessionTimeText.OutlineColor = Color.Black;
            currentSessionTimeText.Style = Text.Styles.Bold;
            currentSessionTimeText.OutlineThickness = 2f;

            gameOverText.Origin = new Vector2f(gameOverText.GetGlobalBounds().Width / 2f,
                gameOverText.GetGlobalBounds().Height / 2f);
            gameOverText.Position = new Vector2f(Globals.WindowWidthResolution / 2f, textSpacing);

            currentSessionTimeText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - currentSessionTimeText.GetGlobalBounds().Width / 2f,
                textSpacing * 2);
            currentSessionSpeedText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - currentSessionSpeedText.GetGlobalBounds().Width / 2f,
                textSpacing * 2.5f);
            currentSessionScoreText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - currentSessionScoreText.GetGlobalBounds().Width / 2f,
                textSpacing * 3);

            newScoreRecordText.CharacterSize = 36;
            newScoreRecordText.FillColor = new Color(255, 0, 0);
            newScoreRecordText.OutlineColor = Color.Black;
            newScoreRecordText.Style = Text.Styles.Bold;
            newScoreRecordText.OutlineThickness = 2f;

            newScoreRecordText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - newScoreRecordText.GetGlobalBounds().Width / 2f,
                textSpacing * 4f);

            newSpeedRecordText.CharacterSize = 36;
            newSpeedRecordText.FillColor = new Color(255, 0, 0);
            newSpeedRecordText.OutlineColor = Color.Black;
            newSpeedRecordText.Style = Text.Styles.Bold;
            newSpeedRecordText.OutlineThickness = 2f;

            newSpeedRecordText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - newSpeedRecordText.GetGlobalBounds().Width / 2f,
                textSpacing * 4.5f);

            newTimeRecordText.CharacterSize = 36;
            newTimeRecordText.FillColor = new Color(255, 0, 0);
            newTimeRecordText.OutlineColor = Color.Black;
            newTimeRecordText.Style = Text.Styles.Bold;
            newTimeRecordText.OutlineThickness = 2f;

            newTimeRecordText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - newTimeRecordText.GetGlobalBounds().Width / 2f,
                textSpacing * 5f);

            View view = new View(windowHandler.GetRenderWindow().GetView())
            {
                Center = new Vector2f(Globals.WindowWidthResolution / 2f, Globals.WindowHeightResolution / 2f)
            };

            Vector2f restartButtonPosition = new Vector2f(Globals.WindowWidthResolution / 2f - 200f,
                Globals.GameFieldHeight - buttonSpacing);
            restartButton = new Button(windowHandler.GetRenderWindow(), null!, Globals.FontPath,
                restartButtonPosition, "Restart");
            restartButton.SetColor(new Color(0, 220, 0));
            restartButton.FormatText(Color.White, Color.Black, 32, true,
                1f);

            Vector2f returnToMainMenuButtonPos = new Vector2f(Globals.WindowWidthResolution / 2f + 200f,
                Globals.GameFieldHeight - buttonSpacing);
            returnToMainMenuButton = new Button(windowHandler.GetRenderWindow(), null!, Globals.FontPath,
                returnToMainMenuButtonPos, "To Main Menu");
            returnToMainMenuButton.SetColor(new Color(220, 0, 0));
            returnToMainMenuButton.FormatText(Color.White, Color.Black, 32, true,
                1f);

            windowHandler.GetRenderWindow().SetView(view);
        }

        public event Action OnQuitToMainMenuPressed = null!;
        public event Action OnRestartPressed = null!;

        public event Action OnRestartButtonPressed = null!;
        public event Action OnQuitToMainMenuButtonPressed = null!;

        private void OnPressKey(object? sender, KeyEventArgs keyEventArgs)
        {
            if (keyEventArgs.Code == Keyboard.Key.Escape && IsRunning)
                OnQuitToMainMenuPressed.Invoke();
            else if (keyEventArgs.Code == Keyboard.Key.R && IsRunning) OnRestartPressed.Invoke();
        }

        private void OnMainMenuButtonPress()
        {
            OnQuitToMainMenuButtonPressed.Invoke();
        }

        private void OnRestartButtonPress()
        {
            OnRestartButtonPressed.Invoke();
        }

        protected override void Start()
        {
            windowHandler.GetRenderWindow().KeyPressed += OnPressKey;
            windowHandler.GetRenderWindow().Closed += OnCloseWindow;
            returnToMainMenuButton.OnPressed += OnMainMenuButtonPress;
            restartButton.OnPressed += OnRestartButtonPress;

            currentSessionScoreText.DisplayedString = $"Score: {Globals.CurrentSessionScore} points";
            currentSessionSpeedText.DisplayedString = $"Top speed: {Globals.CurrentSessionTopSpeed} u/s";
            currentSessionTimeText.DisplayedString = $"Total Time: {Globals.CurrentSessionTime} sec.";

            currentSessionTimeText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - currentSessionTimeText.GetGlobalBounds().Width / 2f,
                textSpacing * 2);
            currentSessionSpeedText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - currentSessionSpeedText.GetGlobalBounds().Width / 2f,
                textSpacing * 2.5f);
            currentSessionScoreText.Position = new Vector2f(
                Globals.WindowWidthResolution / 2f - currentSessionScoreText.GetGlobalBounds().Width / 2f,
                textSpacing * 3);

            HUD.ElapsedTime = 0;
            SoundHandler.SFXLibrary["sfx-game-over"].Play();
            SoundHandler.BGMLibrary["bgm-credits"].Play(true);
        }

        protected override void Update(float deltaTime)
        {
            gameField.Update(ref player);
            hud.Update();
        }

        protected override void Draw()
        {
            windowHandler.GetRenderWindow().Clear(new Color(16, 16, 16));
            windowHandler.GetRenderWindow().Draw(gameOverText);
            windowHandler.GetRenderWindow().Draw(currentSessionTimeText);
            windowHandler.GetRenderWindow().Draw(currentSessionSpeedText);
            windowHandler.GetRenderWindow().Draw(currentSessionScoreText);
            restartButton.Draw();
            returnToMainMenuButton.Draw();

            if (Globals.CurrentSessionScore > Globals.MaxScore)
                windowHandler.GetRenderWindow().Draw(newScoreRecordText);

            if (Globals.CurrentSessionTopSpeed > Globals.MaxTopSpeed)
                windowHandler.GetRenderWindow().Draw(newSpeedRecordText);

            if (Globals.CurrentSessionTime > Globals.MaxTime) windowHandler.GetRenderWindow().Draw(newTimeRecordText);

            gameField.Render(ref windowHandler);
            hud.Draw();
        }

        protected override void Finish()
        {
            windowHandler.GetRenderWindow().KeyPressed -= OnPressKey;
            windowHandler.GetRenderWindow().Closed -= OnCloseWindow;

            if (Globals.CurrentSessionScore > Globals.MaxScore) Globals.MaxScore = Globals.CurrentSessionScore;

            if (Globals.CurrentSessionTime > Globals.MaxTime) Globals.MaxTime = Globals.CurrentSessionTime;

            if (Globals.CurrentSessionTopSpeed > Globals.MaxTopSpeed)
                Globals.MaxTopSpeed = Globals.CurrentSessionTopSpeed;

            SoundHandler.BGMLibrary["bgm-credits"].Stop();
        }
    }
}