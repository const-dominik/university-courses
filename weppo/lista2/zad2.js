const someObj = {
    a: 1,
    b: "aaa",
    "1": 3,
    "{}": 111
}

console.log(someObj.a, someObj["b"]); //1
console.log(someObj[1], someObj[2], someObj[{}])
someObj[3] = 5;
someObj[{}] = 1;
console.log(someObj);// 2

const tab = [1, 2, 3];
console.log(tab["aaa"], tab["length"], tab[someObj]);
tab.test = 1;
console.log(tab.test);
tab.length = 5;
console.log(tab.length);
console.log(tab[3])
