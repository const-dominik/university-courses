const zad2 = (): number[] => {
    const ret: number[] = [];
    for (let i = 1; i <= 100000; i++) {
        const nums = i.toString().split("").map(Number);
        const sum = nums.reduce((acc, curr) => acc + curr, 0);
        if (nums.every(num => i % num === 0) && i % sum === 0) {
            ret.push(i);
        }
    }
    return ret;
}

const isPrime = (num: number): boolean => {
    if (num < 2) return false;
    if (num <= 3) return true;
    for (let i = 2; i <= num/2; i++) {
        if (num % i === 0) return false;
    }
    return true;
}

const zad3 = () => Array.from({ length: 100000 - 1 }, (_, i) => i + 2).filter(isPrime);

const fibRec = (n: number): number => {
    if (n === 0 || n === 1) {
        return n;
    }
    return fibRec(n-1) + fibRec(n-2);
}

const fibIter = (n: number): number => {
    const seq = [0, 1];
    for (let i = 2; i <= n; i++) {
        seq.push(seq[i-2] + seq[i-1]);
    }
    return seq[n];
}

const compare = (): void => {
    for (let i = 10; i <= 40; i++) {
        console.log(`n: ${i}`);
        console.time("rec");
        fibRec(i);
        console.timeEnd("rec");
        console.time("iter");
        fibIter(i);
        console.timeEnd("iter");
    }
}

console.log(zad2());
console.log(zad3());
compare();