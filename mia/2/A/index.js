(function () {
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
    var main = function () {
        var _a = readline().split(" ").map(Number), n = _a[0], v = _a[1];
        var money = 0;
        var fuel = 0;
        var currentCity = 1;
        while (currentCity != n) {
            var neededFuel = n - currentCity > v ? v - fuel : (n - currentCity) - fuel;
            money += neededFuel * currentCity;
            fuel += neededFuel;
            if (fuel >= n - currentCity)
                return console.log(money);
            currentCity++;
            fuel--;
        }
    };
})();
