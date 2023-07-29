namespace Proyecto_1
{
    internal class Program
    {
        static void Main()
        {
            Console.WriteLine("Clase 13 " + "21/mayo/2022");

            Console.WriteLine("Texto de nro entero de 16 bits: ");
            int nShort = Convert.ToInt16(Console.ReadLine());

            Console.WriteLine("Texto de nro entero de 32 bits: ");
            int nInt = Convert.ToInt32(Console.ReadLine());

            Console.WriteLine("Texto de nro entero de 64 bits: ");
            long nLong = Convert.ToInt64(Console.ReadLine());

            int width = Console.WindowWidth;
            int height = Console.WindowHeight;
        }
    }
}