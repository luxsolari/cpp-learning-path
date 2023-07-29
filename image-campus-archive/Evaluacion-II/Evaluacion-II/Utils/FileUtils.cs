using System.Text.Json;

namespace Evaluacion_II.Utils;

public static class FileUtils
{
    /// Metodo genérico para "deserializar" un archivo JSON en una lista de objetos
    /// Intenta leer un archivo JSON que contenga una lista de tipo T,
    /// Devuelve una lista de tipo T en caso de que el archivo no esté vacío,
    /// de lo contrario devuelve una nueva lista vacío de T.
    /// https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/generics/generic-classes
    public static List<T>? DeserializeIntoList<T>(string filePath)
    {
        return File.Exists(filePath)
            ? JsonSerializer.Deserialize<List<T>>(File.ReadAllText(filePath))
            : new List<T>();
    }
    

    /// "Serializa" un string de texto a JSON y lo escribe en un archivo del mismo tipo.
    /// Si el archivo no existe, lo crea.
    /// Si el artchivo existía previamente, sobreescribe su contenido.
    public static void SerializeToJSONFile<T>(ref T list, ref string filePath)
    {
        //JsonSerializerOptions settings = new JsonSerializerOptions({ TypeNameHandling = TypeNameHandling.All };
        var options = new JsonSerializerOptions()
        {
            WriteIndented = true,
        };
        string jsonString = JsonSerializer.Serialize(list, list.GetType(), options);
        File.WriteAllText(filePath, jsonString);
    }
}