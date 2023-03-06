(() => {    
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

    const main = () => {
        const [brokenAmount, _, maxTapes] = readline().split(" ").map(Number);
        const brokenPieces = readline().split(" ").map(Number);

        const distances = Array.from({ length: brokenAmount - 1}, (_, i) => brokenPieces[i+1] - brokenPieces[i]).sort((a, b) => b - a);
        let availableTapes = maxTapes-1;
        let min = brokenPieces[brokenAmount-1] - brokenPieces[0] + 1;
        for (let i = 0; i < availableTapes; i++) {
            min -= (distances[i] - 1);
        }
        console.log(min);
    }
})()