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
        var _a = readline().split(" ").map(Number), brokenAmount = _a[0], _ = _a[1], maxTapes = _a[2];
        var brokenPieces = readline().split(" ").map(Number);
        var distances = Array.from({ length: brokenAmount - 1 }, function (_, i) { return brokenPieces[i + 1] - brokenPieces[i]; }).sort(function (a, b) { return b - a; });
        var availableTapes = maxTapes - 1;
        var min = brokenPieces[brokenAmount - 1] - brokenPieces[0] + 1;
        for (var i = 0; i < availableTapes; i++) {
            min -= (distances[i] - 1);
        }
        console.log(min);
    };
})();
