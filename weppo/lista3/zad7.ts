function* fibGenerator() {
    const seq: [number, number] = [0, 1];
    while (true) {
        const val = seq[0];
        seq[0] = seq[1];
        seq[1] = val + seq[0];
        yield val;
    }
}

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

function* take(it: any, top: number) {
    while (top > 0) {
        yield it.next().value;
        top--;
    }
}

for (let num of take( fib(), 10 ) ) {
    console.log(num);
    }
for (let num of take( fibGenerator(), 10 ) ) {
    console.log(num);
    }