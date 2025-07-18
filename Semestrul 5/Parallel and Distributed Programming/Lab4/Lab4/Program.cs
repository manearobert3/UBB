

using Lab4;

class Program
{
    public static void Main(string[] args)
    {
        string[] urls = {
            "wonderfullushbrightspell.neverssl.com",
            "targetedattacks.trendmicro.com",
            "streamhd4k.com",
        };
        while (true)
        {
            Console.WriteLine("Menu:");
            Console.WriteLine("1. Run with Callbacks");
            Console.WriteLine("2. Run with Task");
            Console.WriteLine("3. Run Async/Await Tasks");
            Console.WriteLine("4. Exit");
            Console.Write("Select an option: ");

            var input = Console.ReadLine();

            switch (input)
            {
                case "1":
                    Callbacks.run(urls.ToList());
                    break;
                case "2":
                    Tasks.run(urls.ToList());
                    break;
                case "3":
                    AsyncAwaitTasks.run(urls.ToList());
                    break;
                case "4":
                    return;
                default:
                    Console.WriteLine("Invalid option. Please try again.");
                    break;
            }

            Console.WriteLine();
        }
    }
}
