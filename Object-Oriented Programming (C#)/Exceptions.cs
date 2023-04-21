using System;

namespace Collections
{ 
    public class SetException : Exception
    {
        public SetException() : base() { }
        public SetException(string message) : base(message) { }
        public SetException(string message, Exception innerException) : base(message, innerException) { }
    }
    
    public class SetElementOutOfRangeException : Exception
    {
        public SetElementOutOfRangeException(string message) : base(message)
        {
        }
    }
}