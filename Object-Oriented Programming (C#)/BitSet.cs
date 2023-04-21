using System;
using System.Collections.Generic;

namespace Collections
{
    public class BitSet : Set
    {
        private int[] _m;
        private int _maxValue;

        public BitSet(int maxValue)
        {
            _m = new int[(maxValue / 32) + 1];
            _maxValue = maxValue;
        }

        public override void Add(int element)
        {
            if (element > _maxValue)
                throw new SetElementOutOfRangeException($"Element {element} is out of range");

            int arrayIndex = element / 32;
            int bitIndex = element % 32;

            _m[arrayIndex] |= (1 << bitIndex);
        }


        public override void Remove(int element)
        {
            if (element >= 0 && element < _m.Length * 32)
            {
                int arrayIndex = element / 32;
                int bitIndex = element % 32;
                _m[arrayIndex] &= ~(1 << bitIndex);
            }
        }

        public override bool Contains(int element)
        {
            if (element >= 0 && element < _m.Length * 32)
            {
                int arrayIndex = element / 32;
                int bitIndex = element % 32;
                return (_m[arrayIndex] & (1 << bitIndex)) != 0;
            }
            return false;
        }

        public static BitSet operator +(BitSet set1, BitSet set2)
        {
            int maxNumber = Math.Max(set1._m.Length * 32, set2._m.Length * 32) - 1;
            BitSet unionSet = new BitSet(maxNumber);
            for (int i = 0; i < set1._m.Length; i++)
            {
                unionSet._m[i] = set1._m[i] | set2._m[i];
            }
            return unionSet;
        }

        public static BitSet operator *(BitSet set1, BitSet set2)
        {
            int maxNumber = Math.Min(set1._m.Length * 32, set2._m.Length * 32) - 1;
            BitSet intersectionSet = new BitSet(maxNumber);
            for (int i = 0; i < intersectionSet._m.Length; i++)
            {
                intersectionSet._m[i] = set1._m[i] & set2._m[i];
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