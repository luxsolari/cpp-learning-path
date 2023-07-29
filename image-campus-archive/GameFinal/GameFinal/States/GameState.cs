using System;
using OneMoreSnake.Entities;
using OneMoreSnake.Enums;
using OneMoreSnake.Handlers;
using OneMoreSnake.UI;
using SFML.Audio;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace OneMoreSnake.States
{
    internal class GameState : LoopState
    {
        public static Clock MovementClock = new Clock();
        public static Time MovementDelta = Time.Zero;
        private GameField gameField = null!;
        private HUD hud = null!;
        private PickupHandler pickupHandler = null!;
        private Snake player = null!;

        public GameState(ref WindowHandler window) : base(ref window)
        {
        }

        private Time UpdateTime { get; set; } = Time.Zero;

        public event Action OnQuitToMainMenuPressed = null!;
        public event Action OnGameOverTriggered = null!;

        private void OnPressKey(object? sender, KeyEventArgs keyEventArgs)
        {
            if (keyEventArgs.Code == Keyboard.Key.Escape && IsRunning) OnQuitToMainMenuPressed.Invoke();
        }

        private void TriggerGameOver()
        {
            Globals.CurrentSessionScore = player.GetScore();
            Globals.CurrentSessionTopSpeed = player.GetTopSpeed();
            Globals.CurrentSessionTime = HUD.ElapsedTime;
            OnGameOverTriggered.Invoke();
        }

        private void ProcessInput()
        {
            windowHandler.DispatchEvents();

            if (Snake.MovementAllowed)
            {
                if ((Keyboard.IsKeyPressed(Keyboard.Key.Up) || Keyboard.IsKeyPressed(Keyboard.Key.W)) &&
                    player.GetPhysicalDirection() != Direction.Down)
                    player.SetDirection(Direction.Up);
                else if ((Keyboard.IsKeyPressed(Keyboard.Key.Down) || Keyboard.IsKeyPressed(Keyboard.Key.S)) &&
                         player.GetPhysicalDirection() != Direction.Up)
                    player.SetDirection(Direction.Down);
                else if ((Keyboard.IsKeyPressed(Keyboard.Key.Left) || Keyboard.IsKeyPressed(Keyboard.Key.A)) &&
                         player.GetPhysicalDirection() != Direction.Right)
                    player.SetDirection(Direction.Left);
                else if ((Keyboard.IsKeyPressed(Keyboard.Key.Right) || Keyboard.IsKeyPressed(Keyboard.Key.D)) &&
                         player.GetPhysicalDirection() != Direction.Left)
                    player.SetDirection(Direction.Right);
            }
        }

        protected override void Start()
        {
            UpdateTime = Time.Zero;
            gameField = new GameField();
            player = new Snake();
            pickupHandler = new PickupHandler(ref player, ref gameField);
            hud = new HUD(ref windowHandler, ref player, Globals.FontPath);

            windowHandler.GetRenderWindow().Closed += OnCloseWindow;
            windowHandler.GetRenderWindow().KeyPressed += OnPressKey;
        }

        protected override void Update(float deltaTime)
        {
            if (windowHandler.GetRenderWindow().HasFocus())
            {
                ProcessInput();
                var timestep = 1.0f / player.GetSpeed();

                if (Snake.MovementAllowed)
                {
                    if (player.GetDirection() != Direction.None &&
                        SoundHandler.BGMLibrary["bgm-gameplay1"].Status() != SoundStatus.Playing)
                        SoundHandler.BGMLibrary["bgm-gameplay1"].Play(true);

                    if (!player.HasLost && UpdateTime.AsSeconds() >= timestep)
                    {
                        player.Update();
                        gameField.Update(ref player);
                        UpdateTime = Time.FromSeconds(UpdateTime.AsSeconds() - timestep);
                    }

                    pickupHandler.Update(player, gameField);
                    hud.Update();

                    if (player.HasLost) TriggerGameOver();

                    UpdateTime += Time.FromSeconds(deltaTime);
                }
                else
                {
                    MovementDelta += MovementClock.Restart();
                    if (MovementDelta.AsSeconds() >= 0.0f && MovementDelta.AsSeconds() < 0.025f)
                    {
                        SoundHandler.SFXLibrary["sfx-wall1"].setPitch(3f);
                        SoundHandler.SFXLibrary["sfx-wall1"].Play();
                    }

                    if (MovementDelta.AsSeconds() > 1.0f && MovementDelta.AsSeconds() < 1.025f)
                    {
                        SoundHandler.SFXLibrary["sfx-wall1"].setPitch(3f);
                        SoundHandler.SFXLibrary["sfx-wall1"].Play();
                    }

                    if (MovementDelta.AsSeconds() >= 2.2f)
                    {
                        SoundHandler.SFXLibrary["sfx-wall1"].Stop();
                        SoundHandler.SFXLibrary["sfx-wall1"].setPitch(1f);
                        SoundHandler.SFXLibrary["sfx-wall1"].Play();
                        Snake.MovementAllowed = true;
                    }
                }
            }
            else
            {
                UpdateTime = Time.Zero;
            }
        }

        protected override void Draw()
        {
            windowHandler.GetRenderWindow().Clear(new Color(16, 16, 16));
            pickupHandler.Render(ref windowHandler);
            gameField.Render(ref windowHandler);
            player.Render(ref windowHandler);
            hud.Draw();
        }

        protected override void Finish()
        {
            windowHandler.GetRenderWindow().Closed -= OnCloseWindow;
            windowHandler.GetRenderWindow().KeyPressed -= OnPressKey;
            UpdateTime = Time.Zero;
            SoundHandler.BGMLibrary["bgm-gameplay1"].Stop();
        }
    }
}