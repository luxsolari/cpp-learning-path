using System;

public class Star
{
    private string name;
	private int posX;
	private int posY;
    
    // Constructor
	public Star(string name,int posX, int posY)
    {
        this.name = name;
        this.posX = posX;
        this.posY = posY;
    }

    public void Show()
    {
        Console.SetCursorPosition(this.posX, this.posY);
        Console.Write("*");
    }

    public void Hide()
    {
        Console.SetCursorPosition(this.posX, this.posY);
        Console.Write(" ");
    }

    public void Move(int posX, int posY)
    {
        this.posX = posX;
        this.posY = posY;
    }

    public void PrintCoordinates()
    {
        Console.Write(this.name + " Posicion: X=" + this.posX + " Y=" + this.posY);
    }

    public int GetPosX()
    {
        return this.posX;
    }
    public int GetPosY()
    {
        return this.posY;
    }

}
