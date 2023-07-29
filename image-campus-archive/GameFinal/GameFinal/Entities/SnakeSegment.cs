using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.Entities
{
    public class SnakeSegment
    {
        public RectangleShape bodyRect;
        public int index;
        public Vector2i Position;

        public SnakeSegment(int index, int x, int y, RectangleShape bodyRect)
        {
            this.bodyRect = bodyRect;
            this.index = index;
            Position.X = x;
            Position.Y = y;
        }
    }
}