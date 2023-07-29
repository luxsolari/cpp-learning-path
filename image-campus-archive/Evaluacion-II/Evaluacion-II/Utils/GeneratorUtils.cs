using Evaluacion_II.Champions;
using Evaluacion_II.Enums;

namespace Evaluacion_II.Utils;

public static class GeneratorUtils
{
    public static Player CreateNewPlayer()
    {
        string newPlayerName;
        do
        {
            Console.WriteLine("Ingresa tu nombre:");
            newPlayerName = Console.ReadLine() ?? string.Empty;
        } while (newPlayerName.Trim().Length <= 0);

        Player createdPlayer = new Player(newPlayerName, new List<Champion>(), 0.0f, 500);
        return createdPlayer;
    }
    public static Champion CreateNewChampion()
    {
        Console.WriteLine("CREANDO NUEVO CAMPEON");
        string championName;
        do
        {
            Console.Write("Ingresa el nombre del campeon: ");
            championName = Console.ReadLine() ?? string.Empty;
        } while (championName.Trim().Length <= 0);

        Console.WriteLine("Selecciona la clase de tu Campeon:");
        Console.WriteLine("1 - Luchador     ");
        Console.WriteLine("2 - Mago         ");
        Console.WriteLine("3 - Tirador      ");
        Console.WriteLine("4 - Asesino      ");
        Console.WriteLine("5 - Tanque       ");
        Console.WriteLine("6 - Soporte      ");
        Console.WriteLine("7 - Especialista ");
        Console.WriteLine("------------------------------------------------------");
        Console.Write    ("-> ");
        int opcionRol = Convert.ToInt16(Console.ReadLine());
        Role championRole = (Role)opcionRol;
        BaseStats baseStats = default;
        List<Role> strengths = new List<Role>();
        List<Role> resistances = new List<Role>();
        switch (championRole)
        {
            case Role.Fighter:
                baseStats = new BaseStats(modAttackDamage: 1.6f, modAgility: 1.1f, modMaxHealth: 1.2f, modArmor: 0.9f,
                    modMagicResist: 0.8f, modHealthRegen: 3f, modCritChance: 0.2f, modCritRate: 1.75f, 
                    new Resource(ResourceType.Energy, 100, 20));
                strengths.Add(Role.Marksman);
                strengths.Add(Role.Assassin);
                resistances.Add(Role.Assassin);
                resistances.Add(Role.Tank);
                resistances.Add(Role.Support);
                break;
            case Role.Mage:
                baseStats = new BaseStats(modAttackDamage: 0.65f, modAgility: 0.6f, modMaxHealth: 0.7f, modArmor: 0.6f,
                    modMagicResist: 0.9f, modHealthRegen: 1.25f, modCritChance: 0.0f, modCritRate: 1.0f,
                    new Resource(ResourceType.Energy, 100, 20));
                strengths.Add(Role.Fighter);
                strengths.Add(Role.Marksman);
                resistances.Add(Role.Tank);
                resistances.Add(Role.Support);
                break;
            case Role.Marksman:
                baseStats = new BaseStats(modAttackDamage: 1.85f, modAgility: 1.25f, modMaxHealth: 0.5f, modArmor: 0.5f,
                    modMagicResist: 0.5f, modHealthRegen: 1.25f, modCritChance: 0.2f, modCritRate: 1.75f,
                    new Resource(ResourceType.Energy, 100, 20));
                strengths.Add(Role.Mage);
                strengths.Add(Role.Marksman);
                strengths.Add(Role.Assassin);
                strengths.Add(Role.Support);
                resistances.Add(Role.Tank);
                resistances.Add(Role.Support);
                break;
            case Role.Assassin:
                baseStats = new BaseStats(modAttackDamage: 1.8f, modAgility: 1.5f, modMaxHealth: 1f, modArmor: 1f,
                    modMagicResist: 1f, modHealthRegen: 1.2f, modCritChance: 0.2f, modCritRate: 1.85f,
                    new Resource(ResourceType.Energy, 100, 20));
                strengths.Add(Role.Mage);
                strengths.Add(Role.Marksman);
                strengths.Add(Role.Specialist);
                resistances.Add(Role.Tank);
                resistances.Add(Role.Support);
                break;
            case Role.Tank:
                baseStats = new BaseStats(modAttackDamage: 0.6f, modAgility: 1f, modMaxHealth: 2f, modArmor: 2f,
                    modMagicResist: 1.5f, modHealthRegen: 5f, modCritChance: 0.0f, modCritRate: 1.0f,
                    new Resource(ResourceType.Energy, 100, 20));
                resistances.Add(Role.Fighter);
                resistances.Add(Role.Mage);
                resistances.Add(Role.Marksman);
                resistances.Add(Role.Assassin);
                resistances.Add(Role.Tank);
                resistances.Add(Role.Support);
                break;
            case Role.Support:
                baseStats = new BaseStats(modAttackDamage: 0.4f, modAgility: 0.8f, modMaxHealth: 1.2f, modArmor: 1.25f,
                    modMagicResist: 1.15f, modHealthRegen: 3f, modCritChance: 0.0f, modCritRate: 1.0f,
                    new Resource(ResourceType.Energy, 100, 20));
                break;
            case Role.Specialist:
                baseStats = new BaseStats(modAttackDamage: 1.65f, modAgility: 1.5f, modMaxHealth: 1.1f, modArmor: 1f,
                    modMagicResist: 1f, modHealthRegen: 1.1f, modCritChance: 0.25f, modCritRate: 1.75f,
                    new Resource(ResourceType.Energy, 100, 20));
                strengths.Add(Role.Tank);
                strengths.Add(Role.Specialist);
                strengths.Add(Role.Support);
                break;
        }

        Champion createdChampion = new Champion(championName, baseStats, (Role) opcionRol, strengths, resistances);
        Console.WriteLine("Creacion del Campeon completa!");
        Console.WriteLine("------------------------------------------------------");
        createdChampion.PrintInfo();
        Console.WriteLine("------------------------------------------------------");
        Console.Write    ("-> ");
        Console.ReadKey(true);
        return createdChampion;
    }
}