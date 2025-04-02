using System.Collections.Generic;
using System;
using System.Linq;

namespace aggregator
{
    public interface IEventAggregator
    {
        void AddSubscriber<T>(Action<T> Subscriber);
        void RemoveSubscriber<T>(Action<T> Subscriber);
        void Publish<T>(T Event);
    }

    public class EventAggregator : IEventAggregator
    {
        private static readonly EventAggregator _instance = new EventAggregator();

        Dictionary<Type, List<object>> _subscribers = new Dictionary<Type, List<object>>();

        public static EventAggregator GetInstance() { return _instance; }

        #region IEventAggregator Members
        public void AddSubscriber<T>(Action<T> Subscriber)
        {
            if (!_subscribers.ContainsKey(typeof(T)))
                _subscribers.Add(typeof(T), new List<object>());
            _subscribers[typeof(T)].Add(Subscriber);
        }

        public void RemoveSubscriber<T>(Action<T> Subscriber)
        {
            if (_subscribers.ContainsKey(typeof(T)))
                _subscribers[typeof(T)].Remove(Subscriber);
        }

        public void Publish<T>(T Event)
        {
            if (_subscribers.ContainsKey(typeof(T)))
                foreach (Action<T> subscriber in _subscribers[typeof(T)].OfType<Action<T>>())
                    subscriber(Event);
        }
        #endregion
    }
}
