namespace QuickSortCSharp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            List<int> list = new List<int>();
            Random rand = new Random();

            Console.Write("Enter how many random numbers to generate: ");
            int userIn = Int32.Parse(Console.ReadLine()!);

            for (int i = 0; i < userIn; i++)
            {
                list.Add(rand.Next(0, 10));
            }

            Console.WriteLine("Unsorted List: ");
            foreach(int i in list)
            {
                Console.Write(i + " ");
            }

            QuickSort.Sort(list);
            Console.WriteLine("Sorted List: ");
            foreach (int i in list)
            {
                Console.Write(i + " "); 
            }
        }
    }
}