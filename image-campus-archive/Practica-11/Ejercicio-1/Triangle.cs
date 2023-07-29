namespace Ejercicio_1;

public class Triangle : GeometricFigure
{
    private float b;
    private float h;

    public Triangle(string name, float b, float h) : base(name)
    {
        this.b = b;
        this.h = h;
    }

    public override string GetName()
    {
        return this.name;
    }

    public float GetBase()
    {
        return this.b;
    }

    public float GetHeight()
    {
        return this.h;
    }
    
    public override string GetData()
    {
        return $"Este es un {this.name} que tiene {this.b} cm de base y {this.h} cm de altura.";
    }
}