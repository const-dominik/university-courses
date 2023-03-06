function forEach<T>(tab: T[], f: (t: T) => unknown): void {
    for (let i = 0; i < tab.length; i++) {
        f(tab[i]);
    }
}

function map<T, K>(tab: T[], f: (t: T) => K): K[] {
    const newTab: K[] = [];
    for (let i = 0; i < tab.length; i++) {
        newTab[i] = f(tab[i]);
    }
    return newTab;
}

function filter<T>(tab: T[], f: (t: T) => boolean): T[] {
    const newTab: T[] = [];
    for (let i = 0; i < tab.length; i++) {
        if (f(tab[i])) {
            newTab.push(tab[i]);
        }
    }
    return newTab;
}

const a = [1, 2, 3, 4];
forEach(a, (el: number) => console.log(el += 1));
console.log(map(a, (el: number) => el.toString()));
console.log(filter(a, function(el: number) {
    return el > 2;
}));