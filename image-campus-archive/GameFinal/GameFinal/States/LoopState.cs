using System;
using OneMoreSnake.Handlers;
using SFML.System;

namespace OneMoreSnake.States
{
    public abstract class LoopState
    {
        public bool IsRunning = true;
        protected WindowHandler windowHandler;

        protected LoopState(ref WindowHandler window)
        {
            windowHandler = window;
        }

        private Time DeltaTime { get; set; } = Time.Zero;
        private Clock Clock { get; } = new Clock();

        protected void OnCloseWindow(object? sender, EventArgs e)
        {
            IsRunning = false;
            windowHandler.GetRenderWindow().Close();
        }

        protected abstract void Start();
        protected abstract void Update(float deltaTime);
        protected abstract void Draw();
        protected abstract void Finish();

        public void Play()
        {
            IsRunning = true;

            Start();

            while (IsRunning)
            {
                DeltaTime = Clock.Restart();
                windowHandler.GetRenderWindow().DispatchEvents();
                Update(DeltaTime.AsSeconds());
                Draw();
                windowHandler.GetRenderWindow().Display();
            }

            Finish();
        }

        public void Stop()
        {
            if (!IsRunning)
            {
                Console.WriteLine("Cannot stop a state that is not running.");
                return;
            }

            IsRunning = false;

            Finish();
        }
    }
}