public class Target
{
    private int magicResist;
    private float distance;

    public Target(int magicResist, float distance)
    {
        this.magicResist = magicResist;
        this.distance = distance;
    }

    public int GetMagicResist()
    {
        return this.magicResist;
    }

    public float GetDistance()
    {
        return this.distance;
    }
}
