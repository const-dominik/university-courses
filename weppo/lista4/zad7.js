const fs = require("fs");
const util = require("util");
const fsp = require("fs").promises;

fs.readFile("./aaaaa.txt", (err, data) => {
    if (!err) {
        console.log(data.toString());
    }
});

const myReadFile = (path) => {
    return new Promise((res, rej) => {
        fs.readFile(path, (err, data) => {
            if (err) rej(err);
            res(data.toString());
        });
    });
}

const awaitAndLogPromise = async (promise) => {
    promise.then(data => {
        console.log(data);
    })
    // console.log(await promise.data);
}

// awaitAndLogPromise(myReadFile("./aaaaa.txt"));

const utilPromisifiedReadFile = util.promisify(fs.readFile);
// awaitAndLogPromise(utilPromisifiedReadFile("./aaaaa.txt"));

const fsPromise = fsp.readFile("./aaaaa.txt", "utf-8");
awaitAndLogPromise(fsPromise);