function Foo(arg) {
    let privateVar = arg;

    const privateFunction = () => {
        return privateVar;
    }

    Foo.prototype.Bar = function() {
        return privateFunction();
    };
}

const foo = new Foo("aaa");
console.log(foo.Bar());
console.log(foo.privateVar);
// console.log(foo.privateFunction()); - error