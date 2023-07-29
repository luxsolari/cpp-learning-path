using OneMoreSnake.Handlers;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.Entities
{
    public class InvulPickup : Pickup
    {
        public InvulPickup(Color color, Vector2i spawnPosition) : base(new CircleShape(Globals.BlockSize / 2f, 3),
            color)
        {
            SetSpawnPosition(spawnPosition);
        }

        public int SpeedIncreaseAmount { get; } = 0;
        public int SegmentsIncreaseAmount { get; } = 0;
        public int ScoreIncreaseAmount { get; } = 5;

        public override void Spawn(ref WindowHandler window)
        {
            window.GetRenderWindow().Draw(PickupShape);
        }
    }
}