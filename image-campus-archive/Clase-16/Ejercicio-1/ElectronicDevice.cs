internal class ElectronicDevice
{
    protected string brand;
    protected bool isOn;

    public ElectronicDevice (string brand, bool isOn)
    {
        this.brand = brand;
        this.isOn = isOn;
    }

    public void TurnOn ()
    {
        if (this.isOn)
        {
            Console.WriteLine("Ya está encendido, no te hagas el piola amigo");
        }
        else
        {
            this.isOn = true;
            Console.WriteLine("Ahora esta encendido.");
        }
    }

    public void TurnOff()
    {
        if (!this.isOn)
        {
            Console.WriteLine("Ya está apagado, no te hagas el piola amigo");
        }
        else
        {
            this.isOn = true;
            Console.WriteLine("Ahora esta apagado.");
        }
    }
}