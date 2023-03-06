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
        const [n, v] = readline().split(" ").map(Number);
        let money = 0;
        let fuel = 0;
        let currentCity = 1;
        while (currentCity != n) {
            const neededFuel = n - currentCity > v ? v-fuel : (n-currentCity)-fuel;
            money += neededFuel*currentCity;
            fuel += neededFuel;
            if (fuel >= n - currentCity) return console.log(money);
            currentCity++;
            fuel--;
        }
    }
})()