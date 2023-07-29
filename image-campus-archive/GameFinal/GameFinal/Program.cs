using System.Collections.Generic;
using OneMoreSnake.Handlers;
using OneMoreSnake.States;
using OneMoreSnake.Utils;
using SFML.System;

namespace OneMoreSnake
{
    public class Program
    {
        private static void Main(string[] args)
        {
            // Load records "databse"
            var records = FileUtils.DeserializeIntoList<int>(Globals.recordsFile)!;
            if (records.Count > 0)
            {
                Globals.MaxScore = records[0];
                Globals.MaxTime = records[1];
                Globals.MaxTopSpeed = records[2];
            }

            WindowHandler windowHandler = new WindowHandler("One More Snake",
                new Vector2u(Globals.WindowWidthResolution, Globals.WindowHeightResolution));
            StatesController statesController = new StatesController(ref windowHandler);
            SoundHandler.Initialize();

            statesController.Start();

            if (records.Count == 0)
            {
                records = new List<int>(3);
                records.Add(Globals.MaxScore);
                records.Add(Globals.MaxTime);
                records.Add(Globals.MaxTopSpeed);
            }
            else
            {
                records[0] = Globals.MaxScore;
                records[1] = Globals.MaxTime;
                records[2] = Globals.MaxTopSpeed;
            }

            FileUtils.SerializeToJSONFile(ref records, ref Globals.recordsFile);
        }
    }
}