const { VTexec } = require('open-term')
const fs = require("fs");
const files = fs.readdirSync(".");
let compileCommand = "g++ -Wall -Wextra -pedantic -std=c++17 ";
compileCommand += files.filter(fileName => fileName.includes(".cpp")).join(" ");
VTexec(compileCommand);