internal class TV : ElectronicDevice
{
    private float screenSize;
    private float brightness;
    private int channel;

    public TV (string brand, float screenSize) : base(brand, false)
    {
        this.screenSize = screenSize;
    }

    public void SetChannel(int channel)
    {
        if (this.isOn)
        {
            if (channel > 0 && channel < 9999)
            {
                this.channel = channel;
                Console.WriteLine($"Se cambio al canal {channel}.");
            }
            else
            {
                Console.WriteLine("Ese canal no lo tengo kpo. Vofi.");
            }
        }
        else
        {
            Console.WriteLine("Prendé el televisor primero, amigo.");
        }
    }

    public void SetBrightness(int brightness)
    {
        if (this.isOn)
        {
            if ((brightness / 100) >= 0 && (brightness / 100) <= 1)
            {
                this.brightness = brightness;
                Console.WriteLine($"Se cambio el brillo a {brightness}%.");
            }
            else
            {
                Console.WriteLine("No tires fruta con el brillo, es de 0 a 100.");
            }
        }
        else
        {
            Console.WriteLine("Prendé el televisor primero, amigo.");
        }
    }

    public void PrintInfo()
    {
        Console.WriteLine($"Marca: {this.brand}");
        Console.WriteLine($"Pulgadas: {this.screenSize}");
        Console.WriteLine($"Estado: {(this.isOn ? "Encendido" : "Apagado")}");
        Console.WriteLine($"Canal actual: {this.channel}");
        Console.WriteLine($"Brillo actual: {this.brightness}");
    }

}
