function createGenerator(n: number) {
    var _state = 0;
    return {
        next: function() {
            return {
                value: _state,
                done: _state++ >= n
            }
        }
    }
}

var foo = {
    [Symbol.iterator]: () => createGenerator(100)
};
var foo2 = {
    [Symbol.iterator]: () => createGenerator(10)
};

for (var f of foo) console.log(f);
for (var f of foo2) console.log(f);