namespace Game;
using SFML.System;
using SFML.Window;
using SFML.Graphics;

class Player : AnimatedEntity
{
    // Fields
    private float speed;
    

    public Player(string imageFilePath, Vector2i frameSize, float speed) : base(imageFilePath, frameSize)
    {
        this.speed = speed;
        AnimationData idleLeft = new AnimationData()
        {
            frameRate = 6,
            framesCount = 3,
            rowIndex = 0,
            loop = true,
        };
        AnimationData idleRight = new AnimationData()
        {
            frameRate = 6,
            framesCount = 2,
            rowIndex = 1,
            loop = true,
        };
        AnimationData walkLeft = new AnimationData()
        {
            frameRate = 6,
            framesCount = 2,
            rowIndex = 2,
            loop = true,
        };
        AnimationData walkRight = new AnimationData()
        {
            frameRate = 6,
            framesCount = 2,
            rowIndex = 3,
            loop = true,
        };

        AddAnimation("idleLeft", idleLeft);
        AddAnimation("idleRight", idleRight);
        AddAnimation("walkLeft", walkLeft);
        AddAnimation("walkRight", walkRight);

        SetCurrentAnimation("idleLeft");
    }

    public override void Update(float deltaTime)
    {
        base.Update(deltaTime);
        Vector2f input = new Vector2f(0, 0);

        if (Keyboard.IsKeyPressed(Keyboard.Key.Left))
            input.X -= 100f;
        if (Keyboard.IsKeyPressed(Keyboard.Key.Right))
            input.X += 100f;
        if (Keyboard.IsKeyPressed(Keyboard.Key.Up))
            input.Y -= 100f;
        if (Keyboard.IsKeyPressed(Keyboard.Key.Down))
            input.Y += 100f;
        
        Vector2f translation = VectorUtils.Normalize(input) * speed * deltaTime ;
        Translate(translation);
    }
}