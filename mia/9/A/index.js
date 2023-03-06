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
        var n = Number(readline());
        var ns = readline().split(" ").map(Number);
        var wyst = Array.from({ length: n }, function (_) { return 0; });
        for (var index = 0; index < n; index++) {
            var i = Number(index);
            while (1) {
                wyst[i]++;
                if (wyst[i] === 2)
                    break;
                i = ns[i] - 1;
            }
            console.log(i + 1);
            for (var i_1 = 0; i_1 < n; i_1++)
                wyst[i_1] = 0;
        }
    };
})();
