using System;
using System.Collections.Generic;
using OneMoreSnake.Enums;
using OneMoreSnake.Handlers;
using OneMoreSnake.UI;
using SFML.Graphics;
using SFML.System;

namespace OneMoreSnake.Entities
{
    public class Snake
    {
        public static bool MovementAllowed = false;
        private readonly Clock clock = new Clock();
        private readonly List<SnakeSegment> snakeBody;
        private readonly Vector2i snakeStartPos;
        private Time deltaTime = Time.Zero;
        private Direction direction;
        public int InvulnerableTime;


        private bool isInvulnerable;
        private bool isRecovering;
        private int lives;
        private int score;
        private int speed;
        private int topSpeed;

        public Snake()
        {
            snakeBody = new List<SnakeSegment>();
            snakeBody.Clear();

            Random random = new Random();
            var maxX = (int)(Globals.GameFieldWidth / Globals.BlockSize - 3);
            var maxY = (int)(Globals.GameFieldHeight / Globals.BlockSize - 3);
            snakeStartPos = new Vector2i(1 + random.Next() % maxX, random.Next() % maxY + 1);

            snakeBody.Add(new SnakeSegment(0, snakeStartPos.X, 3,
                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
            snakeBody.Add(new SnakeSegment(1, snakeStartPos.X, 2,
                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
            snakeBody.Add(new SnakeSegment(2, snakeStartPos.X, 1,
                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));

            SetDirection(Direction.None);
            speed = 10;
            lives = 3;
            score = 0;
            HasLost = false;
        }

        public bool HasLost { get; set; }

        public void SetDirection(Direction dir)
        {
            direction = dir;
        }

        public int GetSpeed()
        {
            return speed;
        }

        public int GetTopSpeed()
        {
            return topSpeed;
        }

        public Vector2i GetPosition()
        {
            return snakeBody.Count > 0 ? snakeBody[0].Position : new Vector2i(1, 1);
        }

        public void SetPosition(Vector2i newPos)
        {
            snakeBody[0].Position = newPos;
        }

        public int GetLives()
        {
            return lives;
        }

        public int GetScore()
        {
            return score;
        }

        public void SetIsInvulnerable(bool invulnerable)
        {
            isInvulnerable = invulnerable;
        }

        public bool GetIsInvulnerable()
        {
            return isInvulnerable;
        }

        public List<SnakeSegment> GetSnakeBody()
        {
            return snakeBody;
        }

        public void IncreaseScore(int baseScoreAmount, float timeElapsed)
        {
            score += baseScoreAmount +
                     baseScoreAmount * (snakeBody.Count / 50) +
                     (int)(baseScoreAmount * (timeElapsed / 50f));
        }

        public void ChangeSpeed(int speedIncreaseAmount)
        {
            speed = Math.Clamp(speed + speedIncreaseAmount, 5, int.MaxValue);
        }

        public void Lose()
        {
            HasLost = true;
            lives = 0;
            speed = 0;
        }

        public void Extend(int extendAmount)
        {
            if (snakeBody.Count == 0) return;

            for (var i = 0; i < extendAmount; i++)
            {
                SnakeSegment tailHead = snakeBody[^1];
                if (snakeBody.Count > 1)
                {
                    SnakeSegment tailBone = snakeBody[^2];

                    if (tailHead.Position.X == tailBone.Position.X)
                    {
                        if (tailHead.Position.Y > tailBone.Position.Y)
                            snakeBody.Add(new SnakeSegment(snakeBody.Count, tailHead.Position.X,
                                tailHead.Position.Y + 1,
                                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
                        else
                            snakeBody.Add(new SnakeSegment(snakeBody.Count, tailHead.Position.X,
                                tailHead.Position.Y - 1,
                                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
                    }
                    else if (tailHead.Position.Y == tailBone.Position.Y)
                    {
                        if (tailHead.Position.X > tailBone.Position.X)
                            snakeBody.Add(new SnakeSegment(snakeBody.Count, tailHead.Position.X + 1,
                                tailHead.Position.Y,
                                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
                        else
                            snakeBody.Add(new SnakeSegment(snakeBody.Count, tailHead.Position.X - 1,
                                tailHead.Position.Y,
                                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
                    }
                }
                else
                {
                    if (direction == Direction.Up)
                        snakeBody.Add(new SnakeSegment(snakeBody.Count, tailHead.Position.X,
                            tailHead.Position.Y + 1,
                            new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
                    else if (direction == Direction.Down)
                        snakeBody.Add(new SnakeSegment(snakeBody.Count, tailHead.Position.X,
                            tailHead.Position.Y - 1,
                            new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
                    else if (direction == Direction.Left)
                        snakeBody.Add(new SnakeSegment(snakeBody.Count, tailHead.Position.X + 1,
                            tailHead.Position.Y,
                            new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
                    else if (direction == Direction.Right)
                        snakeBody.Add(new SnakeSegment(snakeBody.Count, tailHead.Position.X - 1,
                            tailHead.Position.Y,
                            new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
                }
            }
        }

        public Direction GetPhysicalDirection()
        {
            if (snakeBody.Count <= 1) return Direction.None;

            SnakeSegment head = snakeBody[0];
            SnakeSegment neck = snakeBody[1];

            return head.Position.X == neck.Position.X
                ? head.Position.Y > neck.Position.Y ? Direction.Down : Direction.Up
                : head.Position.Y == neck.Position.Y
                    ? head.Position.X > neck.Position.X ? Direction.Right : Direction.Left
                    : Direction.None;
        }

        public Direction GetDirection()
        {
            return direction;
        }

        public void Reset()
        {
            snakeBody.Clear();
            SetDirection(Direction.None);
            snakeBody.Add(new SnakeSegment(0, snakeStartPos.X, 3,
                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
            snakeBody.Add(new SnakeSegment(1, snakeStartPos.X, 2,
                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));
            snakeBody.Add(new SnakeSegment(2, snakeStartPos.X, 1,
                new RectangleShape(new Vector2f(Globals.BlockSize - 1f, Globals.BlockSize - 1f))));

            --lives;
            speed = 10;
            if (lives == 0) Lose();
        }

        private void Move()
        {
            for (var i = snakeBody.Count - 1; i > 0; --i) snakeBody[i].Position = snakeBody[i - 1].Position;

            if (direction == Direction.Left)
                --snakeBody[0].Position.X;
            else if (direction == Direction.Right)
                ++snakeBody[0].Position.X;
            else if (direction == Direction.Up)
                --snakeBody[0].Position.Y;
            else if (direction == Direction.Down) ++snakeBody[0].Position.Y;
        }

        public void Update()
        {
            if (snakeBody.Count == 0) return;

            if (direction == Direction.None) return;

            if (speed >= topSpeed) topSpeed = speed;

            deltaTime += clock.Restart();

            if (deltaTime.AsMilliseconds() > 1000)
            {
                if (InvulnerableTime > 0)
                {
                    --InvulnerableTime;
                    if (InvulnerableTime < 6)
                    {
                        SoundHandler.SFXLibrary["sfx-time"].setPitch(1.5f);
                        SoundHandler.SFXLibrary["sfx-time"].Play();
                    }

                    if (!isRecovering) IncreaseScore(2, HUD.ElapsedTime);
                }

                if (InvulnerableTime == 0)
                {
                    isInvulnerable = false;
                    isRecovering = false;
                }

                deltaTime = Time.Zero;
            }

            Move();
            CheckCollision();
        }

        private void Cut(int cutIndex)
        {
            SoundHandler.SFXLibrary["sfx-wall2"].Play();
            _ = snakeBody.RemoveAll(segment => segment.index >= cutIndex);
            --lives;
            speed = Math.Clamp(speed / 2, 5, int.MaxValue);
            if (lives == 0) Lose();
        }

        public void Render(ref WindowHandler window)
        {
            if (snakeBody.Count == 0) return;

            if (isInvulnerable && InvulnerableTime > 4)
            {
                SnakeSegment headRect = snakeBody[0];
                headRect.bodyRect.FillColor = Color.White;
                for (var i = 1; i < snakeBody.Count; ++i)
                {
                    SnakeSegment segment = snakeBody[i];
                    segment.bodyRect.FillColor = Color.Yellow;
                }
            }
            else if (isInvulnerable && InvulnerableTime <= 4)
            {
                SnakeSegment headRect = snakeBody[0];
                headRect.bodyRect.FillColor = Color.White;
                for (var i = 1; i < snakeBody.Count; ++i)
                {
                    SnakeSegment segment = snakeBody[i];
                    segment.bodyRect.FillColor = new Color(180, 0, 180);
                }
            }
            else
            {
                SnakeSegment headRect = snakeBody[0];
                headRect.bodyRect.FillColor = Color.Yellow;
                for (var i = 1; i < snakeBody.Count; ++i)
                {
                    SnakeSegment segment = snakeBody[i];
                    segment.bodyRect.FillColor = Color.Green;
                }
            }

            SnakeSegment head = snakeBody[0];
            snakeBody[0].bodyRect.Position =
                new Vector2f(head.Position.X * Globals.BlockSize, head.Position.Y * Globals.BlockSize);
            window.GetRenderWindow().Draw(snakeBody[0].bodyRect);

            for (var i = 1; i < snakeBody.Count; ++i)
            {
                SnakeSegment segment = snakeBody[i];
                segment.bodyRect.Position = new Vector2f(segment.Position.X * Globals.BlockSize,
                    segment.Position.Y * Globals.BlockSize);
                window.GetRenderWindow().Draw(snakeBody[i].bodyRect);
            }
        }

        private void CheckCollision()
        {
            if (snakeBody.Count < 5) return;

            SnakeSegment head = snakeBody[0];
            for (var i = 1; i < snakeBody.Count; ++i)
            {
                SnakeSegment segment = snakeBody[i];
                if (!isInvulnerable && segment.bodyRect.Position == head.bodyRect.Position)
                {
                    Cut(segment.index - 1);
                    SetIsInvulnerable(true);
                    InvulnerableTime = 3;
                    isRecovering = true;
                    break;
                }
            }
        }

        public bool IsOutsideBounds()
        {
            return GetPosition().X <= 0 ||
                   GetPosition().X >= Globals.GridSizeX - 1 ||
                   GetPosition().Y <= 0 ||
                   GetPosition().Y >= Globals.GridSizeY - 1;
        }

        public void LoopOverBounds()
        {
            if (GetPosition().X <= 0)
                SetPosition(new Vector2i(Globals.GridSizeX - 2, GetPosition().Y));
            else if (GetPosition().X >= Globals.GridSizeX - 1)
                SetPosition(new Vector2i(1, GetPosition().Y));
            else if (GetPosition().Y <= 0)
                SetPosition(new Vector2i(GetPosition().X, Globals.GridSizeY - 2));
            else if (GetPosition().Y >= Globals.GridSizeY - 1) SetPosition(new Vector2i(GetPosition().X, 1));
        }

        public int GetCollisioningBoundIndex()
        {
            return GetPosition().X <= 0 ? 0
                : GetPosition().X >= Globals.GridSizeX - 1 ? 1
                : GetPosition().Y <= 0 ? 2
                : GetPosition().Y >= Globals.GridSizeY - 1 ? 3
                : -1;
        }
    }
}