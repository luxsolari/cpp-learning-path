using System;
using System.Collections.Generic;
using SFML.System;
using SFML.Graphics;

namespace Game
{
    class AnimatedEntity : Entity
    {
        private Dictionary<string, AnimationData> animations = new Dictionary<string, AnimationData>();
        protected Vector2i frameSize;
        private string currentAnimationName;
        private Vector2i currentImagePosition;
        private float currentFrameTime;
        private float frameTimer;

        protected int CurrentFrameIndex => currentImagePosition.X;
        
        public AnimatedEntity (string imageFilePath, Vector2i frameSize) : base(imageFilePath)
        {
            this.frameSize = frameSize;

            sprite.TextureRect = new IntRect()
            {
                Left = 0,
                Top = 0,
                Width = frameSize.X,
                Height = frameSize.Y
            };
        }

        protected void AddAnimation (string animationName, AnimationData animationData)
        {
            if (animations.ContainsKey(animationName))
            {
                Console.WriteLine($"There already is an animation named: {animationName}.");
                return;
            }

            animations.Add(animationName, animationData);
        }        
        
        protected void RemoveAnimation (string animationName)
        {
            if (!animations.ContainsKey(animationName))
            {
                Console.WriteLine($"There is no animation named: {animationName}.");
                return;
            }

            animations.Remove(animationName);
        }

        protected void SetCurrentAnimation (string animationName)
        {
            if (!animations.ContainsKey(animationName))
            {
                Console.WriteLine($"There is no animation named: {animationName}.");
                return;
            }

            if (currentAnimationName != animationName)
            {
                currentAnimationName = animationName;
                currentFrameTime = 1f / animations[currentAnimationName].frameRate;
                currentImagePosition = new Vector2i(0, animations[currentAnimationName].rowIndex);
                frameTimer = 0f;
            }
        }

        public void SetCurrentFrame(int index)
        {
            currentImagePosition.X = index;
        }

        public override void Update (float deltaTime)
        {
            frameTimer += deltaTime;

            // ¡Cambiamos de cuadro!
            if (frameTimer >= currentFrameTime)
            {
                AnimationData animation = animations[currentAnimationName];

                // Le restamos el current frame time para que no se desfase la animación.
                frameTimer -= currentFrameTime;

                // Frames Count = Columns Count = Cantidad de cuadros en la animación.
                if (currentImagePosition.X < animation.framesCount - 1)
                    currentImagePosition.X++;
                else if (animation.loop)
                    currentImagePosition.X = 0;

                // Cambiamos el Texture Rect del sprite para hacer "zoom" sobre un cuadro particular.
                sprite.TextureRect = new IntRect()
                {
                    Left = currentImagePosition.X * frameSize.X,
                    Top = currentImagePosition.Y * frameSize.Y,
                    Width = frameSize.X,
                    Height = frameSize.Y
                };
            }
        }
    }
}
