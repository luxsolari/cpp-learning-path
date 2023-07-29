using System;
using System.Collections.Generic;
using OneMoreSnake.Entities;
using OneMoreSnake.Enums;
using OneMoreSnake.UI;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.Handlers
{
    public class PickupHandler
    {
        private readonly static int maxX = (int)(Globals.GameFieldWidth / Globals.BlockSize - 2);
        private readonly static int maxY = (int)(Globals.GameFieldHeight / Globals.BlockSize - 2);
        private readonly static Random random = new Random();

        private static double invulPickupChance  = 0.05;
        private static double wallPickupChance   = 0.35;
        private static double extendPickupChance = 0.70;

        private readonly Clock clockBase = new Clock();
        private readonly Clock clockExtend = new Clock();
        private readonly Clock clockSpecial = new Clock();
        private readonly List<Pickup> pickupPool = new List<Pickup>();
        private Time deltaTimeBase = Time.Zero;
        private Time deltaTimeExtend = Time.Zero;
        private Time deltaTimeSpecial = Time.Zero;

        public PickupHandler(ref Snake player, ref GameField gameField)
        {
            InitializePool(player, gameField);
        }

        private void InitializePool(Snake player, GameField gameField)
        {
            Vector2i spawnPosition = new Vector2i((random.Next() % maxX + 1) * Globals.BlockSize,
                (random.Next() % maxY + 1) * Globals.BlockSize);
            Pickup newPickUp = new ExtendPickup(Globals.BlockSize / 2f, Color.Red, spawnPosition);
            newPickUp.OnPickedUp += delegate { OnPickedUp(newPickUp, ref player, ref gameField); };
            pickupPool.Add(newPickUp);
        }

        public void Update(Snake player, GameField gameField)
        {
            deltaTimeBase += clockBase.Restart();
            deltaTimeExtend += clockExtend.Restart();
            deltaTimeSpecial += clockSpecial.Restart();

            if (player.GetDirection() != Direction.None)
            {
                foreach (Pickup pickup in pickupPool)
                    if (player.GetPosition() == pickup.GetSpawnPosition())
                        pickup.OnPickUp();

                _ = pickupPool.RemoveAll(pickup => pickup.HasBeenPickedUp());

                if (!player.HasLost && deltaTimeExtend.AsMilliseconds() > 3000)
                {
                    var chance = (float)random.NextDouble();

                    if (chance >= 1 - extendPickupChance)
                    {
                        Vector2i extendPickupPosition = new Vector2i((random.Next() % maxX + 1) * Globals.BlockSize,
                            (random.Next() % maxY + 1) * Globals.BlockSize);
                        Pickup extendPickup = new ExtendPickup(Globals.BlockSize / 2f, Color.Red, extendPickupPosition);
                        extendPickup.OnPickedUp += delegate { OnPickedUp(extendPickup, ref player, ref gameField); };
                        pickupPool.Add(extendPickup);
                        deltaTimeExtend = Time.Zero;
                    }
                }

                if (!player.HasLost && deltaTimeSpecial.AsMilliseconds() > 20000)
                {
                    double wallChance = random.NextDouble();
                    double invulChance = random.NextDouble();

                    if (wallChance >= 1 - wallPickupChance)
                    {
                        Vector2i wallPickupPosition = new Vector2i((random.Next() % maxX + 1) * Globals.BlockSize,
                            (random.Next() % maxY + 1) * Globals.BlockSize);
                        Pickup wallPickup = new BoundPickup(Color.Blue, wallPickupPosition);
                        wallPickup.OnPickedUp += delegate { OnPickedUp(wallPickup, ref player, ref gameField); };
                        pickupPool.Add(wallPickup);
                        deltaTimeSpecial = Time.Zero;
                    }

                    if (invulChance >= 1 - invulPickupChance && deltaTimeSpecial > Time.Zero)
                    {
                        Vector2i invulSpawnPosition = new Vector2i((random.Next() % maxX + 1) * Globals.BlockSize,
                            (random.Next() % maxY + 1) * Globals.BlockSize);
                        Pickup invulPickup = new InvulPickup(Color.Yellow, invulSpawnPosition);
                        invulPickup.OnPickedUp += delegate { OnPickedUp(invulPickup, ref player, ref gameField); };
                        pickupPool.Add(invulPickup);
                        deltaTimeSpecial = Time.Zero;
                    }
                }

                if (!player.HasLost && deltaTimeBase.AsMilliseconds() > 30000)
                {
                    extendPickupChance = Math.Clamp(extendPickupChance + 0.05, 0, 1);
                    wallPickupChance   = Math.Clamp(wallPickupChance   + 0.02, 0, 1);
                    invulPickupChance  = Math.Clamp(extendPickupChance + 0.01, 0, 1);
                    deltaTimeBase = Time.Zero;
                }
            }

            if (player.HasLost) deltaTimeBase = Time.Zero;
        }

        public void Render(ref WindowHandler window)
        {
            foreach (Pickup pickup in pickupPool) pickup.Spawn(ref window);
        }

        private void OnPickedUp(Pickup pickup, ref Snake player, ref GameField gameField)
        {
            if (pickup is ExtendPickup applePickup)
            {
                player.IncreaseScore(applePickup.ScoreIncreaseAmount, HUD.ElapsedTime);
                player.Extend(applePickup.SegmentsIncreaseAmount);
                player.ChangeSpeed(applePickup.SpeedIncreaseAmount);
            }

            if (pickup is BoundPickup wallPickup)
            {
                foreach (Bound bound in gameField.GetBounds())
                {
                    bound.IsPassable = true;
                    bound.BoundRect.FillColor = bound.PassableColor;
                }

                player.IncreaseScore(wallPickup.ScoreIncreaseAmount, HUD.ElapsedTime);
                player.Extend(wallPickup.SegmentsIncreaseAmount);
                player.ChangeSpeed(wallPickup.SpeedIncreaseAmount);
                gameField.BoundsPassableTime = 15;
            }

            if (pickup is InvulPickup invulPickup)
            {
                player.IncreaseScore(invulPickup.ScoreIncreaseAmount, HUD.ElapsedTime);
                player.Extend(invulPickup.SegmentsIncreaseAmount);
                player.ChangeSpeed(invulPickup.SpeedIncreaseAmount);

                player.SetIsInvulnerable(true);
                player.InvulnerableTime = 10;
            }

            SoundHandler.SFXLibrary["sfx-pickup1"].Play();
        }
    }
}