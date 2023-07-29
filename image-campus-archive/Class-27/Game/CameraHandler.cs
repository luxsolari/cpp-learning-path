using System;
using SFML.Graphics;
using SFML.System;

namespace Game
{
    public class CameraHandler
    {
        private readonly RenderWindow window;
        private View view;
        private Entity followTarget;

        public CameraHandler(RenderWindow window, Entity followTarget)
        {
            this.window = window;
            this.view = new View(window.GetView());
            this.followTarget = followTarget;
        }

        public void Update()
        {
            float viewHalfWidth = view.Size.X / 2f;
            float minViewPosX = GameLoop.MinX + viewHalfWidth;
            float maxViewPosX = GameLoop.MaxX - viewHalfWidth;

            float targetHalfWidth = followTarget.Graphic.TextureRect.Width / 2f;
            float viewPosX = Math.Clamp(followTarget.Position.X + targetHalfWidth, minViewPosX, maxViewPosX);
            
            view.Center = new Vector2f(viewPosX, view.Center.Y);
            window.SetView(this.view);
        }
    }
}