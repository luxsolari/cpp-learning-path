using System;
namespace Project_1
{
	public class Personaje
	{
		private int vidas;
		private int score;
		private bool esInvulnerable;
		private bool estaFortalecido;

		public Personaje(int vidas)
		{
			this.vidas = vidas;
			score = 0;
			esInvulnerable = false;
			estaFortalecido = false;
		}

		public bool EsInvulnerable() => this.esInvulnerable;
		public bool EstaFortalecido() => this.estaFortalecido;
		public int GetVidas() => this.vidas;
		public int GetScore() => this.score;

	}
}

