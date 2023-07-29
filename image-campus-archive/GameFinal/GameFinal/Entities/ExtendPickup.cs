using OneMoreSnake.Handlers;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.Entities
{
    public class ExtendPickup : Pickup
    {
        public ExtendPickup(float radius, Color color, Vector2i spawnPosition) : base(new CircleShape(radius), color)
        {
            SetSpawnPosition(spawnPosition);
        }

        public int SpeedIncreaseAmount { get; } = 1;
        public int SegmentsIncreaseAmount { get; } = 3;
        public int ScoreIncreaseAmount { get; } = 10;

        public override void Spawn(ref WindowHandler window)
        {
            window.GetRenderWindow().Draw(PickupShape);
        }
    }
}