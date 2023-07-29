namespace Ejercicio_1;

public class Circle : GeometricFigure
{
    private float radius;
    
    public Circle(string name, float radius) : base(name)
    {
        this.radius = radius;
    }

    public override string GetName()
    {
        return this.name;
    }

    public float GetRadius()
    {
        return this.radius;
    }

    public override string GetData()
    {
        return $"Este es un {this.name} que tiene {this.radius} cm de radio.";
    }
    
}