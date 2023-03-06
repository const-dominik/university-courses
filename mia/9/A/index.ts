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
        //czytanie danych wejsciowych
        const n = Number(readline());
        const ns = readline().split(" ").map(Number);
        //tworzenie tablicy - dlugosc n, tab[x] = 0;
        const wyst = Array.from({ length: n }, _ => 0);
        for (let index = 0; index < n; index++) {
            let i = index;
            while(1) {
                wyst[i]++;
                if (wyst[i] === 2) break;
                i = ns[i]-1;
            }
            //wypisywanie
            console.log(i+1);
            //reset tablicy
            for (let i=0; i<n; i++) wyst[i] = 0;
        }
    }
})()