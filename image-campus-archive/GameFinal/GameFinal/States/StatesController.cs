using OneMoreSnake.Entities;
using OneMoreSnake.Enums;
using OneMoreSnake.Handlers;
using OneMoreSnake.UI;
using SFML.System;

namespace OneMoreSnake.States
{
    internal class StatesController
    {
        private readonly ControlsMenuState controlsMenuState;
        private readonly CreditsScreenState creditsScreenState;
        private readonly GameOverState gameOverState;
        private readonly MainMenuState mainMenuState;
        private ProgramState currentState = ProgramState.MainMenuScreen;
        private GameState gameState = null!;
        private WindowHandler window;

        public StatesController(ref WindowHandler window)
        {
            this.window = window;
            mainMenuState = new MainMenuState(this.window);
            controlsMenuState = new ControlsMenuState(this.window);
            creditsScreenState = new CreditsScreenState(this.window);
            gameOverState = new GameOverState(this.window);
        }

        public void Start()
        {
            mainMenuState.OnPlayPressed += FromMainMenuToGame;
            mainMenuState.OnControlsPressed += FromMainMenuToControls;
            mainMenuState.OnCreditsPressed += FromMainMenuToCredits;
            mainMenuState.OnQuitPressed += QuitApplication;

            controlsMenuState.OnReturnToMainMenuPressed += FromControlsToMainMenu;
            controlsMenuState.OnQuitPressed += FromControlsToMainMenu;
            creditsScreenState.OnReturnToMainMenuPressed += FromCreditsToMainMenu;
            creditsScreenState.OnQuitPressed += FromCreditsToMainMenu;

            gameOverState.OnQuitToMainMenuPressed += FromGameOverToMainMenu;
            gameOverState.OnRestartPressed += FromGameOverToGame;
            gameOverState.OnRestartButtonPressed += FromGameOverToGame;
            gameOverState.OnQuitToMainMenuButtonPressed += FromGameOverToMainMenu!;

            while (window.GetRenderWindow().IsOpen)
            {
                switch (currentState)
                {
                    case ProgramState.MainMenuScreen:
                        mainMenuState.Play();
                        break;
                    case ProgramState.ControlsScreen:
                        controlsMenuState.Play();
                        break;
                    case ProgramState.CreditsScreen:
                        creditsScreenState.Play();
                        break;
                    case ProgramState.GameScreen:
                        gameState.Play();
                        break;
                    case ProgramState.GameOverScreen:
                        gameOverState.Play();
                        break;
                    default:
                        window.GetRenderWindow().Close();
                        break;
                }
            }
        }

        private void FromMainMenuToGame()
        {
            mainMenuState.IsRunning = false;
            gameState = new GameState(ref window);
            gameState.OnQuitToMainMenuPressed += FromGameToMainMenu;
            gameState.OnGameOverTriggered += FromGameToGameOver;
            currentState = ProgramState.GameScreen;
            GameState.MovementDelta = Time.Zero;
            GameState.MovementClock.Restart();
            Snake.MovementAllowed = false;
            gameState.IsRunning = true;
            SoundHandler.SFXLibrary["sfx-wall1"].setPitch(3f);
            SoundHandler.SFXLibrary["sfx-wall1"].Play();
        }

        private void FromMainMenuToControls()
        {
            mainMenuState.IsRunning = false;
            currentState = ProgramState.ControlsScreen;
            controlsMenuState.IsRunning = true;
        }

        private void FromControlsToMainMenu()
        {
            controlsMenuState.IsRunning = false;
            currentState = ProgramState.MainMenuScreen;
            mainMenuState.IsRunning = true;
        }

        private void FromMainMenuToCredits()
        {
            mainMenuState.IsRunning = false;
            currentState = ProgramState.CreditsScreen;
            creditsScreenState.IsRunning = true;
        }

        private void FromCreditsToMainMenu()
        {
            creditsScreenState.IsRunning = false;
            currentState = ProgramState.MainMenuScreen;
            mainMenuState.IsRunning = true;
        }

        private void FromGameToMainMenu()
        {
            gameState.IsRunning = false;
            gameState.OnQuitToMainMenuPressed -= FromGameToMainMenu;
            gameState.OnGameOverTriggered -= FromGameToGameOver;
            gameState = null!;
            currentState = ProgramState.MainMenuScreen;
            mainMenuState.IsRunning = true;
        }

        private void FromGameToGameOver()
        {
            gameState.IsRunning = false;
            gameState.OnQuitToMainMenuPressed -= FromGameToMainMenu;
            gameState.OnGameOverTriggered -= FromGameToGameOver;
            gameState = null!;
            currentState = ProgramState.GameOverScreen;
            gameOverState.IsRunning = true;
        }

        private void FromGameOverToMainMenu()
        {
            gameOverState.IsRunning = false;
            currentState = ProgramState.MainMenuScreen;
            mainMenuState.IsRunning = true;
        }

        private void FromGameOverToGame()
        {
            gameOverState.IsRunning = false;
            gameState = new GameState(ref window);
            gameState.OnQuitToMainMenuPressed += FromGameToMainMenu;
            gameState.OnGameOverTriggered += FromGameToGameOver;
            currentState = ProgramState.GameScreen;
            HUD.ElapsedTime = 0;
            GameState.MovementDelta = Time.Zero;
            GameState.MovementClock.Restart();
            Snake.MovementAllowed = false;
            gameState.IsRunning = true;
            SoundHandler.SFXLibrary["sfx-wall1"].setPitch(3f);
            SoundHandler.SFXLibrary["sfx-wall1"].Play();
        }

        private void QuitApplication()
        {
            mainMenuState.IsRunning = false;
            currentState = ProgramState.None;
        }
    }
}