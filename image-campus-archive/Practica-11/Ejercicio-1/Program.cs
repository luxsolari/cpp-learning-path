namespace Ejercicio_1;

internal static class Program {
    public static void Main(string[] args)
    {
        GeometricFigure[] figures = new GeometricFigure[3];
        Random random = new Random();
        
        for (int i = 0; i < 3; i++)
        {
            // Usamos el operador "?" para indicar que este tipo es "nulleable" es decir, puede contener valor nulo.
            GeometricFigure? figure = null;
            switch (random.Next(0, 2))
            {
                case 0:
                    figure = new Circle("Circulito", 5f);
                    break;
                case 1:
                    figure = new Triangle("Triangulito", 2f, 3f);
                    break;
                case 2:
                    figure = new Rectangle("Rectangulito", 4f, 2f);
                    break;
            }

            figures[i] = figure;
        }

        foreach (GeometricFigure? figure in figures)
        {
            Console.WriteLine(figure.GetData());
            if (figure is Circle) 
                // Suprimimos el warning de posible valor nulo con el operador "!". Sabemos que figure siempre va a tener un valor en este programa.
                Console.WriteLine($"El radio de este {figure.GetName()} es {((figure as Circle)!).GetRadius()}");

        }
    }
}