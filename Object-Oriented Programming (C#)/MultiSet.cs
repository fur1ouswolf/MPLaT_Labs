using System;

namespace Collections
{
    public class MultiSet : Set
    {
        private int[] _m;
        private int _maxValue;

        public MultiSet(int maxValue)
        {
            _m = new int[maxValue + 1];
            _maxValue = maxValue;
        }

        public override void Add(int element)
        {
            if (element > _maxValue)
                throw new SetElementOutOfRangeException($"Element {element} is out of range");

            _m[element]++;
        }

        public override void Remove(int element)
        {
            if (_m[element] > 0)
                _m[element]--;
        }

        public override bool Contains(int element)
        {
            return _m[element] > 0;
        }

        public override void Fill(string str)
        {
            string[] elements = str.Split(' ');
            foreach (string element in elements)
            {
                int value = int.Parse(element);
                Add(value);
            }
        }

        public override void Fill(int[] arr)
        {
            foreach (int element in arr)
            {
                Add(element);
            }
        }

        public override void Print()
        {
            for (int i = 0; i < _m.Length; i++)
            {
                if (_m[i] > 0)
                    Console.Write(i + " ");
            }
            Console.WriteLine();
        }
    }


}