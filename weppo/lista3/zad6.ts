const fib = () => {
    const seq: [number, number] = [0, 1];

    return {
        next: () => {
            const val = seq[0];
            seq[0] = seq[1];
            seq[1] = val + seq[0];

            return {
                value: val,
                done: false
            }
        }
    }
}

function* fibGenerator() {
    const seq: [number, number] = [0, 1];
    while (true) {
        const val = seq[0];
        seq[0] = seq[1];
        seq[1] = val + seq[0];
        yield val;
    }
}

// for (let fib of fibGenerator()) console.log(fib);

var _it = fib();
for ( var _result; _result = _it.next(), !_result.done; ) {
console.log( _result.value );
}