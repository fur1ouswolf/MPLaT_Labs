using System;

namespace Collections
{
    internal class Program
    {
        static void Main()
        {
            Console.WriteLine("Select representation option:");
            Console.WriteLine("1 - Logical array");
            Console.WriteLine("2 - Bit array");
            Console.WriteLine("3 - Multiset");
            Console.WriteLine("4 - Array test");
            int option = int.Parse(Console.ReadLine());

            Console.WriteLine("Enter the maximum number that can be represented in the set:");
            int maxNumber = int.Parse(Console.ReadLine());

            Set set;
            switch (option)
            {
                case 1:
                    set = new SimpleSet(maxNumber);
                    break;
                case 2:
                    set = new BitSet(maxNumber);
                    break;
                case 3:
                    set = new MultiSet(maxNumber);
                    break;
                case 4:
                    Console.WriteLine("Enter a first set as a string of elements:");
                    string firstSet = Console.ReadLine();
                    Console.WriteLine("Enter a first set as a string of elements:");
                    string secondSet = Console.ReadLine();
                    
                    SimpleSet sset1 = new SimpleSet(maxNumber);
                    SimpleSet sset2 = new SimpleSet(maxNumber);
                    sset1.Fill(firstSet);
                    sset2.Fill(secondSet);
                    SimpleSet ssetC = sset1 + sset2;
                    SimpleSet ssetD = sset1 * sset2;
                    Console.WriteLine("Simple set C (A ∪ B):");
                    ssetC.Print();
                    Console.WriteLine("Simple set D (A ∩ B):");
                    ssetD.Print();
                    BitSet bset1 = new BitSet(maxNumber);
                    BitSet bset2 = new BitSet(maxNumber);
                    bset1.Fill(firstSet);
                    bset2.Fill(secondSet);
                    BitSet bsetC = bset1 + bset2;
                    BitSet bsetD = bset1 * bset2;
                    Console.WriteLine("Bit set C (A ∪ B):");
                    bsetC.Print();
                    Console.WriteLine("Bit set D (A ∩ B):");
                    bsetD.Print();
                    return;
                default:
                    Console.WriteLine("Invalid option!");
                    return;
            }

            Console.WriteLine("Enter the initial set:");
            string input = Console.ReadLine();
            try
            {
                set.Fill(input);
            }
            catch (SetException e)
            {
                Console.WriteLine($"Error: {e.Message}");
            }

            while (true)
            {
                Console.WriteLine();
                Console.WriteLine("Select an option:");
                Console.WriteLine("1 - Add an element");
                Console.WriteLine("2 - Remove an element");
                Console.WriteLine("3 - Check the presence of an element");
                Console.WriteLine("4 - Print all elements");
                Console.WriteLine("0 - Exit");

                int choice = int.Parse(Console.ReadLine());
                switch (choice)
                {
                    case 1:
                        Console.WriteLine("Enter the element to add:");
                        int elementToAdd = int.Parse(Console.ReadLine());
                        try
                        {
                            set.Add(elementToAdd);
                            Console.WriteLine($"Element {elementToAdd} added successfully.");
                        }
                        catch (SetException e)
                        {
                            Console.WriteLine($"Error: {e.Message}");
                        }

                        break;
                    case 2:
                        Console.WriteLine("Enter the element to remove:");
                        int elementToRemove = int.Parse(Console.ReadLine());
                        try
                        {
                            set.Remove(elementToRemove);
                            Console.WriteLine($"Element {elementToRemove} removed successfully.");
                        }
                        catch (SetException e)
                        {
                            Console.WriteLine($"Error: {e.Message}");
                        }

                        break;
                    case 3:
                        Console.WriteLine("Enter the element to check:");
                        int elementToCheck = int.Parse(Console.ReadLine());
                        if (set.Contains(elementToCheck))
                        {
                            Console.WriteLine($"Element {elementToCheck} is in the set.");
                        }
                        else
                        {
                            Console.WriteLine($"Element {elementToCheck} is not in the set.");
                        }

                        break;
                    case 4:
                        set.Print();
                        break;
                    case 0:
                        return;
                    default:
                        Console.WriteLine("Invalid option.");
                        break;
                }
            }
        }
    }
}