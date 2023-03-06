const readline = require("node:readline");
const fs = require("node:fs");

const rl = readline.createInterface({
    input: fs.createReadStream('logs.txt'),
    output: process.stdout,
    terminal: false
});

const occurences = {};

rl.on("line", line => {
    const [, ip] = line.split(" ");
    occurences[ip] = occurences[ip] ? occurences[ip] + 1 : 1; 
});

rl.on("close", () => {
    console.log(Object.entries(occurences).sort(([, a], [, b]) => b-a).slice(0, 3).map(el => `${el[0]} ${el[1]}`).join("\n"));
});