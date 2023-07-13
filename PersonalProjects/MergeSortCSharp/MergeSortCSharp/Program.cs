namespace MergeSortCSharp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            List<int> intList = new List<int>();
            Random rGen = new Random();

            for (int i = 0; i < 10; i++)
            {
                intList.Add(rGen.Next(0, 10));
            }
            Console.WriteLine("Before Sort:");
            foreach (int i in intList)
            {
                Console.Write(i + " ");
            }

            intList = MergeSort.Sort(intList);
            Console.WriteLine("After Sort:");
            foreach(int i in intList)
            {
                Console.Write(i + " "); 
            }
        }
    }
}