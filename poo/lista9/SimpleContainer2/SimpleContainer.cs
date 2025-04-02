using System;
using System.Collections.Generic;
using System.Reflection;

namespace SC
{
    public class SimpleContainer
    {
        private class TypeRegistration
        {
            public Type Implementation { get; set; }
            public bool IsSingleton { get; set; }
            public object? Instance { get; set; }

            public TypeRegistration(Type typeImplementation, bool singleton)
            {
                Implementation = typeImplementation;
                IsSingleton = singleton;
                Instance = null;
            }
        }

        private readonly Dictionary<Type, TypeRegistration> _registrations = new();

        public void RegisterType<T>(bool singleton)
            where T : class
        {
            RegisterType(typeof(T), typeof(T), singleton);
        }

        public void RegisterType<From, To>(bool singleton)
            where To : From
        {
            RegisterType(typeof(From), typeof(To), singleton);
        }

        public void RegisterInstance<T>(T instance)
        {
            Type type = typeof(T);
            if (!_registrations.TryGetValue(type, out TypeRegistration? value))
            {
                _registrations[type] = new TypeRegistration(type, true) { Instance = instance };
            }
            else
            {
                value.Instance = instance;
            }
        }

        private void RegisterType(Type from, Type to, bool singleton)
        {
            if (!_registrations.ContainsKey(from))
            {
                _registrations[from] = new TypeRegistration(to, singleton);
            }
            else
            {
                _registrations[from].Implementation = to;
                _registrations[from].IsSingleton = singleton;
            }
        }

        public T Resolve<T>()
        {
            Type type = typeof(T);
            ArgumentNullException.ThrowIfNull(type);
            return (T)Resolve(type);
        }

        private object Resolve(Type type, HashSet<Type>? resolvedTypes = null)
        {
            ArgumentNullException.ThrowIfNull(type);

            resolvedTypes ??= [];

            if (resolvedTypes.Contains(type))
            {
                throw new InvalidOperationException($"Cyclic dependency detected: {type.FullName}");
            }

            resolvedTypes.Add(type);

            if (!_registrations.TryGetValue(type, out TypeRegistration? value))
            {
                if (type.IsInterface || type.IsAbstract)
                {
                    throw new InvalidOperationException($"Type not registered :( {type.FullName}");
                }
                return CreateInstance(type, resolvedTypes);
            }

            var registration = value;

            if (registration.IsSingleton)
            {
                registration.Instance ??= CreateInstance(
                    registration.Implementation,
                    resolvedTypes
                );
                return registration.Instance!;
            }

            return CreateInstance(registration.Implementation, resolvedTypes);
        }

        private object CreateInstance(Type type, HashSet<Type> resolvedTypes)
        {
            ConstructorInfo[] constructors = type.GetConstructors()
                .OrderByDescending(c => c.GetParameters().Length)
                .ToArray();

            if (constructors.Length == 0)
            {
                throw new InvalidOperationException($"No constructors available");
            }

            if (
                constructors.Length > 1
                && constructors[0].GetParameters().Length == constructors[1].GetParameters().Length
            )
            {
                throw new InvalidOperationException($"Ambiguous constructors");
            }

            ConstructorInfo constructor = constructors[0];

            ParameterInfo[] parameters = constructor.GetParameters();
            object[] resolvedParameters = new object[parameters.Length];

            for (int i = 0; i < parameters.Length; i++)
            {
                Type parameterType = parameters[i].ParameterType;
                resolvedParameters[i] = Resolve(parameterType, resolvedTypes);
            }

            return constructor.Invoke(resolvedParameters);
        }
    }
}
