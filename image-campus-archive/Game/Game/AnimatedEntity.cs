using SFML.System;
using SFML.Graphics;

namespace Game; 

class AnimatedEntity : Entity
{
    private Dictionary<string, AnimationData> animations =new Dictionary<string, AnimationData>();
    private Vector2i frameSize;
    private Vector2i currentImagePosition;
    private string currentAnimationName;
    private float currentFrameTime;
    private float frameTimer;
    
    public AnimatedEntity(string imageFilePath, Vector2i frameSize) : base(imageFilePath)
    {
        this.frameSize = frameSize;
    }

    protected void AddAnimation (string animationName, AnimationData animationData)
    {
        if (animations.ContainsKey(animationName))
        {
            Console.WriteLine($"There already is an animation named: {animationName}");
            return;
        }
        animations.Add(animationName, animationData);
    }

    protected void RemoveAnimation(string animationName)
    {
        if (!animations.ContainsKey(animationName))
        {
            Console.WriteLine($"There is no animation named: {animationName}");
            return;
        }
        animations.Remove(animationName);
    }

    public void SetCurrentAnimation (string animationName)
    {
        if (!animations.ContainsKey(animationName))
        {
            Console.WriteLine($"There is no animation named: {animationName}");
            return;
        }
        this.currentAnimationName = animationName;
        this.currentFrameTime = 1f / this.animations[currentAnimationName].frameRate;
        this.frameTimer = 0f;
        this.currentImagePosition = new Vector2i(0, animations[currentAnimationName].rowIndex);
    }
    public override void Update(float deltaTime)
    {
        this.frameTimer += deltaTime;

        // cambiamos de cuadro de animacion
        if (this.frameTimer >= this.currentFrameTime)
        {
            AnimationData animation = animations[currentAnimationName];

            frameTimer -= currentFrameTime;
            if (currentImagePosition.X < animation.framesCount - 1)
                currentImagePosition.X++;
            else if (animation.loop) 
                currentImagePosition.X = 0;

            this.sprite.TextureRect = new IntRect() { 
                Left   = currentImagePosition.X * frameSize.X,
                Top    = currentImagePosition.Y * frameSize.Y, 
                Width  = frameSize.X, 
                Height = frameSize.Y
            };
        }
    }
}
