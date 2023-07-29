internal class Chair
{
    // Fields - atributos
    private int cantidadPatas;
    private Material material;
    private float masa;
    private float pesoMaximo;
    private float precio;
    private bool reclinable;

    // Methods - metodos
    public Chair ()
    {
        cantidadPatas = 4;
        material = Material.Wood;
        masa = 5000;
        pesoMaximo = 180000;
        precio = 70000;
        reclinable = false;
    }

    public Chair (int cantidadPatas, Material material, float masa, float pesoMaximo, float precio, bool reclinable)
    {
        this.cantidadPatas = cantidadPatas;
        this.material = material;
        this.masa = masa;
        this.pesoMaximo = pesoMaximo;
        this.precio = precio;
        this.reclinable = reclinable;
    }

    public override String ToString()
    {
        return  this.cantidadPatas + " " +
                this.material.ToString() + " " +
                this.masa + " " +
                this.pesoMaximo + " " +
                this.precio + " " +
                this.reclinable;
    }
}
