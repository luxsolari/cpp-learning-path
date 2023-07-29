namespace OneMoreSnake
{
    public static class Globals
    {
        public const uint FpsLimit = 144;
        public const int BlockSize = 20;

        public const uint WindowWidthResolution = 1280;
        public const uint WindowHeightResolution = 720;

        public const uint GameFieldWidth = WindowWidthResolution;
        public const uint GameFieldHeight = WindowHeightResolution - 80;

        public const int GridSizeX = (int)(GameFieldWidth / BlockSize);
        public const int GridSizeY = (int)(GameFieldHeight / BlockSize);

        public const string FontPath = "Assets/Fonts/Hyperspace.ttf";
        public const string SFXPath = "Assets/SFX";
        public const string BGMPath = "Assets/BGM";

        public static string recordsFile = @"records.json";
        public static int CurrentSessionScore { get; set; }
        public static int CurrentSessionTopSpeed { get; set; }
        public static int CurrentSessionTime { get; set; }

        public static int MaxScore { get; set; }
        public static int MaxTopSpeed { get; set; }
        public static int MaxTime { get; set; }
    }
}