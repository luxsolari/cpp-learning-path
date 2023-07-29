using System;
abstract class PowerUp
{
	private float posX;
	private float posY;
	private float duracionMundo;
	private float duracionEfecto;
	protected bool fueConsumido;


	public PowerUp(float posX, float posY, float duracionMundo, float duracionEfecto)
	{
		this.posX = posX;
		this.posY = posY;
		this.duracionMundo = duracionMundo;
		this.duracionEfecto = duracionEfecto;
	}

	public abstract void Consumir();

	public bool FueConsumido() => this.fueConsumido;
}

