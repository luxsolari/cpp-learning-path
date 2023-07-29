namespace Ejercicio_1;

public abstract class GeometricFigure
{
    protected string name;
    
    public GeometricFigure(string name)
    {
        this.name = name;
    }

    public virtual string GetName()
    {
        return this.name;
    }

    public abstract string GetData();
}