const fs = require("node:fs");

const content = fs.readFileSync("./aaaaa.txt", "utf-8");
console.log(content);