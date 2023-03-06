process.stdin.resume();
process.stdin.setEncoding('utf-8');

const inputs: string[] = [];
let inputString = '';
let currentLine = 0;

process.stdin.on('data', (inputStdin: string) => {
    inputString += inputStdin;
});

process.stdin.on('end', () => {
    inputString.trim().split('\n').forEach(string => {
        return inputs.push(string.trim());
    });
    inputString = '';

    main();
});

const readline = () => inputs[currentLine++];

type NumWithIndex = [val: number, index: number];
type FunResponse = {
    evens: number,
    odds: number,
    index: number
}

const findFirst = (elements: number[]) => {
    let evens = 0;
    let odds = 0;
    let biggestEven: NumWithIndex = [-Infinity, -1];
    let biggestOdd: NumWithIndex = [-Infinity, -1];

    elements.forEach((num, i) => {
        if (num % 2) {
            odds++;
            if (num > biggestOdd[0]) {
                biggestOdd[0] = num;
                biggestOdd[1] = i;
            }
        } else {
            evens++;
            if (num > biggestEven[0]) {
                biggestEven[0] = num;
                biggestEven[1] = i;
            }
        }
    });

    return evens > odds ? biggestEven[1] : biggestOdd[1];
}

const findNext = (elems: number[], lastNum: number) => {
    let biggestNum = -Infinity;
    let biggestIndex = -1;
    
    elems.forEach((el, i) => {
        const sameParity = (el % 2 === 0) === (lastNum % 2 === 0)
        if (el === -1 || sameParity) return;
        if (el > biggestNum) {
            biggestNum = el;
            biggestIndex = i;
        }
    });

    return biggestIndex;
}

const main = () => {
    const _ = Number(readline());
    const elements = readline().split(" ").map(Number);

    let index = findFirst(elements);
    let elem = elements[index];
    elements[index] = -1;
    
    while (true) {
        const next = findNext(elements, elem);
        if (next === -1) break;
        elem = elements[next];
        elements[next] = -1;
        index = next;
    }

    const minSum = elements.reduce((acc, val, i) => {
        if (val === -1) return acc;
        return acc + val;
    }, 0);

    console.log(minSum);
}