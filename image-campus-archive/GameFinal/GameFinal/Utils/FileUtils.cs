using System.Collections.Generic;
using System.IO;
using System.Text.Json;

namespace OneMoreSnake.Utils
{
    public static class FileUtils
    {
        public static List<T>? DeserializeIntoList<T>(string filePath)
        {
            return File.Exists(filePath)
                ? JsonSerializer.Deserialize<List<T>>(File.ReadAllText(filePath))
                : new List<T>();
        }

        public static void SerializeToJSONFile<T>(ref T list, ref string filePath)
        {
            JsonSerializerOptions options = new JsonSerializerOptions
            {
                WriteIndented = true
            };
            var jsonString = JsonSerializer.Serialize(list, list!.GetType(), options);
            File.WriteAllText(filePath, jsonString);
        }
    }
}