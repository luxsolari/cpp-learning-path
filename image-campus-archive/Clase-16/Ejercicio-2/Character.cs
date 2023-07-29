public class Character
{
    protected string name;
    protected int age;

    public Character(string name, int age)
    {
        this.name = name;
        this.age = age;
    }

    string GetName ()
    {
        return this.name;
    }

    int GetAge ()
    {
        return this.age;
    }
}

