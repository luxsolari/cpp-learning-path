using SFML.System;
using SFML.Graphics;

namespace Game
{
    public class Entity
    {
        private readonly Texture texture;
        protected readonly Sprite sprite;

        public Vector2f Position { get => sprite.Position; set => sprite.Position = value; }
        public float Rotation { get => sprite.Rotation; set => sprite.Rotation = value; }
        public Vector2f Scale { get => sprite.Scale; set => sprite.Scale = value; }
        
        public Sprite Graphic => sprite;
        
        public bool IsStatic { get; set; }
        public float Mass { get; set; }


        public Entity (string imageFilePath)
        {
            texture = new Texture(imageFilePath);
            sprite = new Sprite(texture);
        }

        public void Translate (Vector2f translation) => Position += translation;
        public void Rotate (float rotation) => Rotation += rotation;

        public bool IsColliding (Entity other)
        {
            FloatRect thisRect = Graphic.GetGlobalBounds();
            FloatRect otherRect = other.Graphic.GetGlobalBounds();

            return thisRect.Intersects(otherRect);
        }

        public virtual void Update (float deltaTime) { }
    }
}