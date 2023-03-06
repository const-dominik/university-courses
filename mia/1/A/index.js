process.stdin.resume();
process.stdin.setEncoding('utf-8');
var inputs = [];
var inputString = '';
var currentLine = 0;
process.stdin.on('data', function (inputStdin) {
    inputString += inputStdin;
});
process.stdin.on('end', function () {
    inputString.trim().split('\n').forEach(function (string) {
        return inputs.push(string.trim());
    });
    inputString = '';
    main();
});
var readline = function () { return inputs[currentLine++]; };
var findFirst = function (elements) {
    var evens = 0;
    var odds = 0;
    var biggestEven = [-Infinity, -1];
    var biggestOdd = [-Infinity, -1];
    elements.forEach(function (num, i) {
        if (num % 2) {
            odds++;
            if (num > biggestOdd[0]) {
                biggestOdd[0] = num;
                biggestOdd[1] = i;
            }
        }
        else {
            evens++;
            if (num > biggestEven[0]) {
                biggestEven[0] = num;
                biggestEven[1] = i;
            }
        }
    });
    return evens > odds ? biggestEven[1] : biggestOdd[1];
};
var findNext = function (elems, lastNum) {
    var biggestNum = -Infinity;
    var biggestIndex = -1;
    elems.forEach(function (el, i) {
        var sameParity = (el % 2 === 0) === (lastNum % 2 === 0);
        if (el === -1 || sameParity)
            return;
        if (el > biggestNum) {
            biggestNum = el;
            biggestIndex = i;
        }
    });
    return biggestIndex;
};
var main = function () {
    var _ = Number(readline());
    var elements = readline().split(" ").map(Number);
    var index = findFirst(elements);
    var elem = elements[index];
    elements[index] = -1;
    while (true) {
        var next = findNext(elements, elem);
        if (next === -1)
            break;
        elem = elements[next];
        elements[next] = -1;
        index = next;
    }
    var minSum = elements.reduce(function (acc, val, i) {
        if (val === -1)
            return acc;
        return acc + val;
    }, 0);
    console.log(minSum);
};
