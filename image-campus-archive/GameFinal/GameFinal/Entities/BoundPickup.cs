using OneMoreSnake.Handlers;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.Entities
{
    public class BoundPickup : Pickup
    {
        public BoundPickup(Shape shape, Color color) : base(shape, color)
        {
        }

        public BoundPickup(Color color, Vector2i spawnPosition) : base(new CircleShape(Globals.BlockSize / 2f, 4),
            color)
        {
            SetSpawnPosition(spawnPosition);
        }

        public int SpeedIncreaseAmount { get; } = 0;
        public int SegmentsIncreaseAmount { get; } = 5;
        public int ScoreIncreaseAmount { get; } = 5;

        public override void Spawn(ref WindowHandler window)
        {
            window.GetRenderWindow().Draw(PickupShape);
        }
    }
}