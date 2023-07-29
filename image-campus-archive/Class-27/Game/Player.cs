using System;
using SFML.System;
using SFML.Window;

namespace Game
{    
    class Player : AnimatedEntity
    {
        private enum State
        {
            Idle,
            Moving,
            Jumping
        }

        private enum FaceDirection
        {
            Left,
            Right
        }
        private float moveSpeed;
        private float jumpSpeed;
        private float jumpDuration;
        private float jumpTime;
        private float initialVerticalPosition;
        private FaceDirection currentFaceDirection = FaceDirection.Right;
        private State currentState = State.Idle;
        
        public Player (string imageFilePath, Vector2i frameSize, float moveSpeed, float jumpSpeed) : base(imageFilePath, frameSize)
        {
            this.moveSpeed = moveSpeed;
            this.jumpSpeed = jumpSpeed;

            AnimationData idleRight = new AnimationData()
            {
                frameRate = 6,
                framesCount = 6,
                rowIndex = 0,
                loop = true
            };

            AnimationData idleLeft = new AnimationData()
            {
                frameRate = 6,
                framesCount = 6,
                rowIndex = 1,
                loop = true
            };

            AnimationData walkRight = new AnimationData()
            {
                frameRate = 6,
                framesCount = 6,
                rowIndex = 2,
                loop = true
            };

            AnimationData walkLeft = new AnimationData()
            {
                frameRate = 6,
                framesCount = 6,
                rowIndex = 3,
                loop = true
            };
            
            AnimationData jumpRight = new AnimationData()
            {
                frameRate = 6,
                framesCount = 3,
                rowIndex = 4,
                loop = false
            };

            AnimationData jumpLeft = new AnimationData()
            {
                frameRate = 6,
                framesCount = 3,
                rowIndex = 5,
                loop = false
            };

            AddAnimation("Idle Left", idleLeft);
            AddAnimation("Idle Right", idleRight);
            AddAnimation("Walk Left", walkLeft);
            AddAnimation("Walk Right", walkRight);
            AddAnimation("Jumping Right", jumpRight);
            AddAnimation("Jumping Left", jumpLeft);
            SetCurrentAnimation("Idle Right");
        }

        private void OnIdle(float deltaTime)
        {
            bool moveLeft = Keyboard.IsKeyPressed(Keyboard.Key.Left);
            bool moveRight = Keyboard.IsKeyPressed(Keyboard.Key.Right);
            bool jump = Keyboard.IsKeyPressed(Keyboard.Key.Up);

            if (jump)
            {
                currentState = State.Jumping;
                Jump();
                UpdateCurrentAnimation();
            }
            else if (moveLeft ^ moveRight)
            {
                currentState = State.Moving;
                currentFaceDirection = moveLeft ? FaceDirection.Left : FaceDirection.Right;
                
                this.Move(deltaTime);
                UpdateCurrentAnimation();
            }

        }
        
        private void OnMoving(float deltaTime)
        {
            bool moveLeft = Keyboard.IsKeyPressed(Keyboard.Key.Left);
            bool moveRight = Keyboard.IsKeyPressed(Keyboard.Key.Right);
            bool jump = Keyboard.IsKeyPressed(Keyboard.Key.Up);
           
            
            if (jump)
            {
                currentState = State.Jumping;
                Jump();
                UpdateCurrentAnimation();
            }
            else if (moveLeft ^ moveRight)
            {
                currentState = State.Moving;
                currentFaceDirection = moveLeft ? FaceDirection.Left : FaceDirection.Right;
                
                this.Move(deltaTime);
                UpdateCurrentAnimation();
            }
            else
            {
                currentState = State.Idle;
                UpdateCurrentAnimation();
            }
        }

        private void UpdateCurrentAnimation()
        {
            string stateAnimName = currentState switch
            {
                State.Idle => "Idle",
                State.Moving => "Walk",
                State.Jumping => "Jumping",
                _ => "Idle"
            };
            string directionAnimName = currentFaceDirection switch
            {
                FaceDirection.Left => "Left",
                FaceDirection.Right => "Right",
                _ => "Right"
            };;

            SetCurrentAnimation($"{stateAnimName} {directionAnimName}");
            
        }

        private void Move(float deltaTime)
        {
            float directionMultiplier = this.currentFaceDirection == FaceDirection.Right ? 1f : -1f;
            float movementX = moveSpeed * deltaTime * directionMultiplier;

            float targetPositionX = Math.Clamp(Position.X + movementX, GameLoop.MinX, GameLoop.MaxX - frameSize.X);
            Position = new Vector2f(targetPositionX, Position.Y);
        }
        
        private void Jump()
        {
            float a = PhysicsHandler.gravity * 0.5f;
            float b = jumpSpeed;
            
            this.jumpTime = 0;
            this.jumpDuration = (-b - MathF.Sqrt(b * b)) / (2f * a);
            this.initialVerticalPosition = Position.Y;
        }
        
        private void OnJumping(float deltaTime)
        {
            bool moveLeft = Keyboard.IsKeyPressed(Keyboard.Key.Left);
            bool moveRight = Keyboard.IsKeyPressed(Keyboard.Key.Right);
            
            jumpTime += deltaTime;
            if (jumpTime <= jumpDuration)
            {

                Vector2f position = new Vector2f(0f, 0f);
                
                float a = -PhysicsHandler.gravity;
                float t = jumpTime;
                float vi = -jumpSpeed;
                float di = initialVerticalPosition;
                
                if (moveLeft ^ moveRight)
                {
                    FaceDirection faceDirection = moveLeft ? FaceDirection.Left : FaceDirection.Right;

                    if (currentFaceDirection != faceDirection)
                    {
                        int currentFrameIndex = CurrentFrameIndex;
                        currentFaceDirection = faceDirection;
                        
                        UpdateCurrentAnimation();
                        SetCurrentFrame(currentFrameIndex);
                    }
                    
                    this.Move(deltaTime);
                }
                position.Y =  a * t * t * 0.5f + vi * t + di;

                Position = new Vector2f(Position.X, position.Y);
            }
            else
            {
                currentState = State.Idle;
                UpdateCurrentAnimation();
            }
        }

        public override void Update (float deltaTime)
        {
            base.Update(deltaTime);

            switch (currentState)
            {
                case State.Idle:
                    this.OnIdle(deltaTime);
                    break;
                case State.Moving:
                    this.OnMoving(deltaTime);
                    break;
                case State.Jumping:
                    this.OnJumping(deltaTime);
                    break;
            }
            
        }
    }
}
