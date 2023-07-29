namespace Ejercicio_1;

public class Rectangle : GeometricFigure
{
    private float length;
    private float width;

    public Rectangle(string name, float length, float width) : base(name)
    {
        this.length = length;
        this.width = width;
    }

    public override string GetName()
    {
        return this.name;
    }

    public float GetLength()
    {
        return this.length;
    }

    public float GetWidth()
    {
        return this.width;
    }
    
    public override string GetData()
    {
        return $"Este es un {this.name} que tiene {this.length} cm de largo y {this.width} cm de ancho.";
    }
}