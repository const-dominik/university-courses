const fibRec = (n: number): number => {
    if (n === 0 || n === 1) {
        return n;
    }
    return fibRec(n-1) + fibRec(n-2);
}

const memoize = (fn: Function) => {
    var fibCache: number[] = [];
    return (n: number) => {
        if (fibCache.length < n) {
            return fibCache[n];
        } else {
            const result = fn(n);
            fibCache[n] = result;
            return result;
        }
    }
}

const memoFib = memoize(fibRec);
console.time("test");
console.log(memoFib(40));
console.timeEnd("test");
console.time("test")
console.log(memoFib(40));
console.timeEnd("test");
