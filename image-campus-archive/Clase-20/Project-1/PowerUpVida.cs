using System;
class PowerUpVida : PowerUp
{
    private int cantidadVidas;

	public PowerUpVida(float posX, float posY, float duracionMundo, float duracionEfecto, int cantidadVidas) :
	base (posX, posY, duracionMundo, duracionEfecto)
	{
        this.cantidadVidas = cantidadVidas;
	}

    public override void Consumir()
    {
        throw new NotImplementedException();
    }
}

