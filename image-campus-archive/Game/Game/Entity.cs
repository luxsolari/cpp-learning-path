using SFML.Graphics;
using SFML.System;

namespace Game;

public class Entity
{
    // Imagen => Textura => Sprite
    private readonly Texture texture;
    protected readonly Sprite sprite;

    public Vector2f Position
    {
        get => this.sprite.Position; 
        set => this.sprite.Position = value;
    }
    public float Rotation
    {
        get => this.sprite.Rotation;
        set => this.sprite.Rotation = value;
    }
    public Vector2f Scale
    {
        get => this.sprite.Scale;
        set => this.sprite.Scale = value;
    }

    public Sprite Graphic => this.sprite;
    
    public Entity(string imageFilePath)
    {
        this.texture = new Texture(imageFilePath);
        this.sprite = new Sprite(texture);
    }

    public void Translate(Vector2f translation) => Position += translation;
    public void Rotate(float rotation) => Rotation += rotation;
    
    public virtual void Update (float deltaTime) { }
    
}