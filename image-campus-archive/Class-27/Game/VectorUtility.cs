using System;
using SFML.System;

namespace Game
{
    static class VectorUtility
    {
        public static Vector2f Normalize (Vector2f vector)
        {
            Vector2f normalized;

            float length = MathF.Sqrt(vector.X * vector.X + vector.Y * vector.Y);

            normalized = (length > 0f) ? vector / length : new Vector2f(0f, 0f);

            return normalized;
        }
    }
}
