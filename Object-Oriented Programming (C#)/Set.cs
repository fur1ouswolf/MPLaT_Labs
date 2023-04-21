using System;
using System.Collections.Generic;

namespace Collections
{
    public abstract class Set
    {
        private int _maxValue;
        public int MaxValue
        {
            get => _maxValue;
        }
        public abstract void Add(int element);
        public abstract void Remove(int element);
        public abstract bool Contains(int element);

        public virtual void Fill(string elements)
        {
            string[] elementsArray = elements.Split(',');
            foreach (string element in elementsArray)
            {
                int num;
                if (int.TryParse(element, out num))
                {
                    Add(num);
                }
            }
        }

        public virtual void Fill(int[] elements)
        {
            foreach (int element in elements)
            {
                Add(element);
            }
        }

        public virtual void Print()
        {
            Console.Write("{ ");
            foreach (int element in ToList())
            {
                Console.Write(element + " ");
            }
            Console.WriteLine("}");
        }

        public virtual List<int> ToList()
        {
            List<int> list = new List<int>();
            for (int i = 0; i < int.MaxValue; i++)
            {
                if (Contains(i))
                {
                    list.Add(i);
                }
            }
            return list;
        }
    }

}