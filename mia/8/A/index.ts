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
    
    const palindrome = (s: string) => s === [...s].reverse().join("");

    const main = () => {
        const str = readline();

    }
})()