using System;
using System.Collections.Generic;

namespace Collections
{ 
    public class SimpleSet : Set
    {
        private bool[] _m;
        private int _maxValue;

        public int MaxValue
        {
            get => _maxValue;
        }

        public SimpleSet(int maxValue)
        {
            _m = new bool[maxValue + 1];
            _maxValue = maxValue;
        }

        public override void Add(int element)
        {
            if (element > _maxValue)
                throw new SetElementOutOfRangeException($"Element {element} is out of range");

            _m[element] = true;
        }

        public override void Remove(int element)
        {
            if (element >= 0 && element < _m.Length)
            {
                _m[element] = false;
            }
        }

        public override bool Contains(int element)
        {
            if (element >= 0 && element < _m.Length)
            {
                return _m[element];
            }
            return false;
        }

        public static SimpleSet operator +(SimpleSet set1, SimpleSet set2)
        {
            int maxNumber = Math.Max(set1._m.Length, set2._m.Length) - 1;
            SimpleSet unionSet = new SimpleSet(maxNumber);
            for (int i = 0; i < maxNumber; i++)
            {
                if (set1.Contains(i) || set2.Contains(i))
                {
                    unionSet.Add(i);
                }
            }
            return unionSet;
        }

        public static SimpleSet operator *(SimpleSet set1, SimpleSet set2)
        {
            int maxNumber = Math.Min(set1._m.Length, set2._m.Length) - 1;
            SimpleSet intersectionSet = new SimpleSet(maxNumber);
            for (int i = 0; i < maxNumber; i++)
            {
                if (set1.Contains(i) && set2.Contains(i))
                {
                    intersectionSet.Add(i);
                }
            }
            return intersectionSet;
        }
        
        public override List<int> ToList()
        {
            List<int> list = new List<int>();
            for (int i = 0; i <= _maxValue; i++)
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