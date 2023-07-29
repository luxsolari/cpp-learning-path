using OneMoreSnake.Entities;
using OneMoreSnake.Enums;
using OneMoreSnake.Handlers;
using OneMoreSnake.States;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.UI
{
    internal class HUD
    {
        private const string LivesLabel = "Lives: ";
        private const string ScoreLabel = "Score: ";
        private const string SpeedLabel = "Speed: ";
        private const string TimeLabel = "Time: ";
        private const string ControlsLabel = "Use Arrow/WASD keys to move";
        private const string ReadyLabel = "Ready";
        private const string SetLabel = " Set ";
        private const string GoLabel = " GO! ";
        private const float MarginSize = 20f;

        private readonly Clock clock = new Clock();

        private readonly Text controlsText;
        private readonly Font font;
        private readonly Text goText;
        private readonly Snake player;
        private readonly Text readyText;
        private readonly Text scoreText;
        private readonly Text setText;
        private readonly Text speedText;
        private readonly Text timeText;
        private readonly RenderWindow window;
        private Time deltaTime = Time.Zero;
        private Text livesText;


        public HUD(ref WindowHandler window, ref Snake player, string fontFilePath)
        {
            this.window = window.GetRenderWindow();
            this.player = player;

            font = new Font(fontFilePath);

            livesText = new Text(LivesLabel + $"{player.GetLives():00}", font);
            scoreText = new Text(ScoreLabel + $"{player.GetScore():000000}", font);
            speedText = new Text(SpeedLabel + $"{player.GetSpeed():00}", font);
            timeText = new Text(TimeLabel + $"{ElapsedTime:00}", font);
            controlsText = new Text(ControlsLabel, font);
            readyText = new Text(ReadyLabel, font);
            setText = new Text(SetLabel, font);
            goText = new Text(GoLabel, font);

            livesText.FillColor = Color.Red;
            livesText.OutlineColor = Color.Black;
            livesText.OutlineThickness = 1f;
            livesText.Style = Text.Styles.Bold;
            livesText.CharacterSize = 32;

            scoreText.FillColor = Color.White;
            scoreText.OutlineColor = Color.Black;
            scoreText.OutlineThickness = 1f;
            scoreText.Style = Text.Styles.Bold;
            scoreText.CharacterSize = 32;

            speedText.FillColor = Color.Green;
            speedText.OutlineColor = Color.Black;
            speedText.OutlineThickness = 1f;
            speedText.Style = Text.Styles.Bold;
            speedText.CharacterSize = 32;

            timeText.FillColor = Color.White;
            timeText.OutlineColor = Color.Black;
            timeText.Style = Text.Styles.Bold;
            timeText.OutlineThickness = 1f;
            timeText.CharacterSize = 32;

            controlsText.FillColor = Color.White;
            controlsText.OutlineColor = Color.Black;
            controlsText.Style = Text.Styles.Bold;
            controlsText.OutlineThickness = 1f;
            controlsText.CharacterSize = 48;

            readyText.FillColor = Color.Red;
            readyText.OutlineColor = Color.Black;
            readyText.Style = Text.Styles.Bold;
            readyText.OutlineThickness = 1f;
            readyText.CharacterSize = 36;

            setText.FillColor = Color.Yellow;
            setText.OutlineColor = Color.Black;
            setText.Style = Text.Styles.Bold;
            setText.OutlineThickness = 1f;
            setText.CharacterSize = 50;

            goText.FillColor = Color.Green;
            goText.OutlineColor = Color.Black;
            goText.Style = Text.Styles.Bold;
            goText.OutlineThickness = 1f;
            goText.CharacterSize = 80;

            var controlsWidth = controlsText.GetGlobalBounds().Width;
            var controlsHeight = controlsText.GetGlobalBounds().Height;

            View? view = window.GetRenderWindow().GetView();
            Vector2f center = view.Center;

            Vector2f controlsOffset = new Vector2f(-MarginSize - controlsWidth / 2f, -MarginSize - controlsHeight);

            livesText.Position = new Vector2f(0 + MarginSize,
                Globals.WindowHeightResolution - livesText.GetGlobalBounds().Height - MarginSize);

            speedText.Position = new Vector2f(livesText.GetGlobalBounds().Width + MarginSize * 2,
                Globals.WindowHeightResolution - speedText.GetGlobalBounds().Height - MarginSize);

            scoreText.Position = new Vector2f(
                Globals.WindowWidthResolution - scoreText.GetGlobalBounds().Width - MarginSize,
                Globals.WindowHeightResolution - scoreText.GetGlobalBounds().Height - MarginSize);

            timeText.Position = new Vector2f(scoreText.Position.X - timeText.GetGlobalBounds().Width - MarginSize - 10,
                Globals.WindowHeightResolution - timeText.GetGlobalBounds().Height - MarginSize);

            controlsText.Position = center + controlsOffset;


            readyText.Position = new Vector2f(Globals.GameFieldWidth / 2f - readyText.GetGlobalBounds().Width / 2f,
                Globals.GameFieldHeight / 3f);
            setText.Position = new Vector2f(Globals.GameFieldWidth / 2f - setText.GetGlobalBounds().Width / 2f,
                Globals.GameFieldHeight / 3f);
            goText.Position = new Vector2f(Globals.GameFieldWidth / 2f - goText.GetGlobalBounds().Width / 2f,
                Globals.GameFieldHeight / 3f);
        }

        public static int ElapsedTime { get; set; }

        public void Update()
        {
            livesText.DisplayedString = LivesLabel + $"{player.GetLives():00}";
            scoreText.DisplayedString = ScoreLabel + $"{player.GetScore():000000}";
            speedText.DisplayedString = SpeedLabel + $"{player.GetSpeed():00}";

            if (player.GetDirection() != Direction.None || Snake.MovementAllowed)
            {
                deltaTime += clock.Restart();

                controlsText.DisplayedString = ControlsLabel;

                if (!player.HasLost && deltaTime.AsMilliseconds() > 1000)
                {
                    timeText.DisplayedString = TimeLabel + $"{ElapsedTime:00}";
                    ElapsedTime++;
                    deltaTime = Time.Zero;
                }
                else if (player.HasLost)
                {
                    livesText.DisplayedString = LivesLabel + $"{0:00}";
                    scoreText.DisplayedString = ScoreLabel + $"{0:000000}";
                    speedText.DisplayedString = SpeedLabel + $"{0:00}";
                    deltaTime = Time.Zero;
                }
            }
        }

        public void Draw()
        {
            window.Draw(livesText);
            window.Draw(scoreText);
            window.Draw(speedText);
            window.Draw(timeText);

            if (GameState.MovementDelta.AsMilliseconds() <= 3200)
            {
                if (!player.HasLost &&
                    player.GetDirection() == Direction.None &&
                    GameState.MovementDelta.AsMilliseconds() >= 0 &&
                    GameState.MovementDelta.AsMilliseconds() < 1000)
                    window.Draw(readyText);
                else if (!player.HasLost &&
                         player.GetDirection() == Direction.None &&
                         GameState.MovementDelta.AsMilliseconds() >= 1001 &&
                         GameState.MovementDelta.AsMilliseconds() < 2000)
                    window.Draw(setText);
                else if (!player.HasLost &&
                         player.GetDirection() == Direction.None &&
                         GameState.MovementDelta.AsMilliseconds() >= 1001 &&
                         GameState.MovementDelta.AsMilliseconds() < 3000)
                    window.Draw(goText);
                if (!player.HasLost && player.GetDirection() == Direction.None) window.Draw(controlsText);
            }
        }

        public void SetLivesText(int text)
        {
            livesText = new Text(LivesLabel + $"{text:00}", font);
        }
    }
}