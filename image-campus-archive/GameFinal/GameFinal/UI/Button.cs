using System;
using OneMoreSnake.Handlers;
using SFML.Graphics;
using SFML.System;
using SFML.Window;

namespace OneMoreSnake.UI
{
    internal class Button
    {
        private readonly RectangleShape buttonShape;
        private readonly Font font;
        private readonly Text text;
        private readonly RenderWindow window;


        public Button(RenderWindow window, string textureFilePath, string fontFilePath, Vector2f position,
            string buttonText)
        {
            this.window = window;

            buttonShape = new RectangleShape(new Vector2f(300, 70));
            font = new Font(fontFilePath);
            text = new Text(buttonText, font);

            FloatRect backgroundRect = buttonShape.GetLocalBounds();

            buttonShape.Origin = new Vector2f(backgroundRect.Width / 2f, backgroundRect.Height / 2f);

            SetText(buttonText);
            SetPosition(position);

            window.MouseButtonReleased += OnReleaseMouseButton!;
        }

        public event Action OnPressed = null!;

        ~Button()
        {
            window.MouseButtonReleased -= OnReleaseMouseButton!;
        }

        private void OnReleaseMouseButton(object sender, MouseButtonEventArgs eventArgs)
        {
            FloatRect bounds = buttonShape.GetGlobalBounds();
            if (bounds.Contains(eventArgs.X, eventArgs.Y))
            {
                SoundHandler.SFXLibrary["sfx-click"].Play();
                OnPressed?.Invoke();
            }
        }

        public void SetText(string newText)
        {
            text.DisplayedString = newText;
            FloatRect textRect = text.GetLocalBounds();
            text.Origin = new Vector2f(textRect.Width / 2f, textRect.Height / 2f);
        }

        public void SetColor(Color color)
        {
            buttonShape.FillColor = color;
        }

        public void FormatText(Color fillColor, Color outlineColor, uint size, bool outline, float outlineThickness)
        {
            text.FillColor = fillColor;
            text.CharacterSize = size;
            text.Style = Text.Styles.Bold;

            if (outline)
            {
                text.OutlineColor = outlineColor;
                text.OutlineThickness = outlineThickness;
            }
            else
            {
                text.OutlineColor = Color.Transparent;
                text.OutlineThickness = 0f;
            }
        }

        public void SetPosition(Vector2f position)
        {
            text.Position = position;
            buttonShape.Position = position;
        }

        public void Draw()
        {
            window.Draw(buttonShape);
            window.Draw(text);
        }
    }
}