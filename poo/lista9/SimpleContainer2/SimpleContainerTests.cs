using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace SC
{
    public interface IFoo { }

    public class Foo : IFoo { }

    public class Bar : IFoo { }

    public class A(B b)
    {
        public B b = b;
    }

    public class A2
    {
        public B b;
        public IC c;

        public A2(B b, IC c)
        {
            this.b = b;
            this.c = c;
        }
    }

    public class B { }

    public interface IC { }

    public class C : IC { }

    public class X
    {
        public X(Y d, string s) { }
    }

    public class Y { }

    public class Cycle(Cycle c)
    {
        public Cycle cycle = c;
    }

    [TestClass]
    public class SimpleContainerTests
    {
        [TestMethod]
        public void TestResolveBaseType()
        {
            var c = new SimpleContainer();
            Foo test = c.Resolve<Foo>();
            Assert.IsNotNull(test);
            Assert.IsInstanceOfType(test, typeof(Foo));

            Assert.ThrowsException<InvalidOperationException>(() => c.Resolve<IFoo>());
        }

        [TestMethod]
        public void TestRegisterSingleton()
        {
            var c = new SimpleContainer();
            c.RegisterType<Foo>(true);
            Foo test1 = c.Resolve<Foo>();
            Foo test2 = c.Resolve<Foo>();
            Assert.AreSame(test1, test2);
        }

        [TestMethod]
        public void TestRegisterNotSingleton()
        {
            var c = new SimpleContainer();
            c.RegisterType<Foo>(false);
            Foo test1 = c.Resolve<Foo>();
            Foo test2 = c.Resolve<Foo>();
            Assert.AreNotSame(test1, test2);
        }

        [TestMethod]
        public void TestRegisterInstance()
        {
            var c = new SimpleContainer();
            IFoo foo = new Foo();
            c.RegisterInstance(foo);
            IFoo foo2 = c.Resolve<IFoo>();
            Assert.AreSame(foo, foo2);
        }

        [TestMethod]
        public void TestRegisterInterface()
        {
            var c = new SimpleContainer();
            c.RegisterType<IFoo, Foo>(false);
            IFoo test = c.Resolve<IFoo>();
            Assert.IsNotNull(test);
            Assert.IsInstanceOfType(test, typeof(Foo));

            c.RegisterType<IFoo, Bar>(false);
            IFoo test2 = c.Resolve<IFoo>();

            Assert.IsNotNull(test2);
            Assert.IsInstanceOfType(test2, typeof(Bar));
        }

        [TestMethod]
        public void TestConstructorInjection1()
        {
            var c = new SimpleContainer();
            A a = c.Resolve<A>();

            Assert.IsNotNull(a);
            Assert.IsNotNull(a.b);
        }

        [TestMethod]
        public void TestConstructorInjection2()
        {
            var c = new SimpleContainer();
            Assert.ThrowsException<InvalidOperationException>(() => c.Resolve<X>());

            c.RegisterInstance("test");
            X x = c.Resolve<X>();
            Assert.IsNotNull(x);
        }

        [TestMethod]
        public void TestConstructorInjection3()
        {
            var c = new SimpleContainer();
            c.RegisterType<IC, C>(false);
            A2 a = c.Resolve<A2>();

            Assert.IsNotNull(a);
            Assert.IsNotNull(a.b);
            Assert.IsNotNull(a.c);
        }

        [TestMethod]
        public void TestCycle()
        {
            var c = new SimpleContainer();
            Assert.ThrowsException<InvalidOperationException>(() => c.Resolve<Cycle>());
        }
    }
}
