using SFML.Graphics;

namespace OneMoreSnake.Entities
{
    public class Bound
    {
        public Bound(RectangleShape boundRect)
        {
            BoundRect = boundRect;
        }

        public RectangleShape BoundRect { get; set; }

        public bool IsPassable { get; set; } = false;

        public Color ImpassableColor { get; set; }

        public Color PassableColor { get; set; }
    }
}