using System;
using OneMoreSnake.Handlers;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.Entities
{
    public abstract class Pickup
    {
        protected readonly Shape PickupShape;
        private bool pickedUp;

        protected Pickup(Shape shape, Color color)
        {
            PickupShape = shape;
            PickupShape.FillColor = color;
        }

        public event Action OnPickedUp = null!;

        public void OnPickUp()
        {
            OnPickedUp.Invoke();
            pickedUp = true;
        }

        protected void SetSpawnPosition(Vector2i spawnPosition)
        {
            PickupShape.Position = (Vector2f)spawnPosition;
        }

        public Vector2i GetSpawnPosition()
        {
            return new Vector2i((int)(PickupShape.Position.X / Globals.BlockSize),
                (int)(PickupShape.Position.Y / Globals.BlockSize));
        }

        public bool HasBeenPickedUp()
        {
            return pickedUp;
        }

        public abstract void Spawn(ref WindowHandler window);
    }
}