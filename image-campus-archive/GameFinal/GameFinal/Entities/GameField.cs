using System.Collections.Generic;
using OneMoreSnake.Handlers;
using OneMoreSnake.States;
using OneMoreSnake.UI;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.Entities
{
    public class GameField
    {
        private readonly List<Bound> bounds;

        private readonly Clock clock = new Clock();
        public int BoundsPassableTime;
        private Time deltaTime = Time.Zero;

        public GameField()
        {
            bounds = new List<Bound>(4);
            // Boundaries initialization
            for (var i = 0; i < 4; ++i)
            {
                bounds.Add(new Bound(new RectangleShape()));
                bounds[i].ImpassableColor = new Color(150, 0, 0);
                bounds[i].PassableColor = new Color(0, 0, 150);
                bounds[i].BoundRect.FillColor = bounds[i].ImpassableColor;

                bounds[i].IsPassable = false;
                bounds[i].BoundRect.Size = (i + 1) % 2 != 0
                    ? new Vector2f(Globals.GameFieldWidth, Globals.BlockSize)
                    : new Vector2f(Globals.BlockSize, Globals.GameFieldHeight);

                if (i < 2)
                {
                    bounds[i].BoundRect.Position = new Vector2f(0, 0);
                }
                else
                {
                    bounds[i].BoundRect.Origin = bounds[i].BoundRect.Size;
                    bounds[i].BoundRect.Position = new Vector2f(Globals.GameFieldWidth, Globals.GameFieldHeight);
                }
            }
        }

        public void Update(ref Snake player)
        {
            deltaTime += clock.Restart();

            if (deltaTime.AsMilliseconds() > 1000)
            {
                if (BoundsPassableTime > 0)
                {
                    player.IncreaseScore(1, HUD.ElapsedTime);
                    --BoundsPassableTime;
                    if (BoundsPassableTime < 4)
                    {
                        foreach (Bound bound in bounds) bound.BoundRect.FillColor = new Color(150, 0, 150);
                        SoundHandler.SFXLibrary["sfx-time"].setPitch(2f);
                        SoundHandler.SFXLibrary["sfx-time"].Play();
                    }
                }

                if (BoundsPassableTime == 0)
                    foreach (Bound bound in bounds)
                    {
                        bound.IsPassable = false;
                        bound.BoundRect.FillColor = bound.ImpassableColor;
                    }

                deltaTime = Time.Zero;
            }

            if (player.IsOutsideBounds())
            {
                if (player.GetIsInvulnerable())
                {
                    // Loop over bounds and come out on the opposite side.
                    player.LoopOverBounds();
                }
                else
                {
                    // Check if bounds are currently passable or not.
                    // Loop over if boundary is passable, otherwise crash player into boundary, lose a life, and reset to starting position.
                    Bound collisioningBound = bounds[player.GetCollisioningBoundIndex()];
                    if (collisioningBound.IsPassable)
                    {
                        player.LoopOverBounds();
                    }
                    else
                    {
                        SoundHandler.BGMLibrary["bgm-gameplay1"].Pause();
                        player.Reset();
                        GameState.MovementDelta = Time.Zero;
                        GameState.MovementClock.Restart();
                        Snake.MovementAllowed = false;
                        SoundHandler.SFXLibrary["sfx-game-over"].Play();
                    }
                }
            }
        }

        public void Render(ref WindowHandler window)
        {
            for (var i = 0; i < 4; ++i) window.GetRenderWindow().Draw(bounds[i].BoundRect);
        }

        public List<Bound> GetBounds()
        {
            return bounds;
        }
    }
}