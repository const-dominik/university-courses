var zad2 = function () {
    var ret = [];
    var _loop_1 = function (i) {
        var nums = i.toString().split("").map(Number);
        var sum = nums.reduce(function (acc, curr) { return acc + curr; }, 0);
        if (nums.every(function (num) { return i % num === 0; }) && i % sum === 0) {
            ret.push(i);
        }
    };
    for (var i = 1; i <= 100000; i++) {
        _loop_1(i);
    }
    return ret;
};
var isPrime = function (num) {
    if (num < 2)
        return false;
    if (num <= 3)
        return true;
    for (var i = 2; i <= num / 2; i++) {
        if (num % i === 0)
            return false;
    }
    return true;
};
var zad3 = function () { return Array.from({ length: 100000 - 1 }, function (_, i) { return i + 2; }).filter(isPrime); };
var fibRec = function (n) {
    if (n === 0 || n === 1) {
        return n;
    }
    return fibRec(n - 1) + fibRec(n - 2);
};
var fibIter = function (n) {
    var seq = [0, 1];
    for (var i = 2; i <= n; i++) {
        seq.push(seq[i - 2] + seq[i - 1]);
    }
    return seq[n];
};
var compare = function () {
    for (var i = 10; i <= 40; i++) {
        console.log("n: ".concat(i));
        console.time("rec");
        fibRec(i);
        console.timeEnd("rec");
        console.time("iter");
        fibIter(i);
        console.timeEnd("iter");
    }
};
compare();
console.log(zad3());
