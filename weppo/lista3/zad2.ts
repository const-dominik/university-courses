function forEach(tab: any[], f: Function) {
    for (let i = 0; i < tab.length; i++) {
        f(tab[i]);
    }
}

function map(tab: any[], f: Function) {
    const newTab: any[] = [];
    for (let i = 0; i < tab.length; i++) {
        newTab[i] = f(tab[i]);
    }
    return newTab;
}

function filter(tab: any[], f: Function) {
    const newTab: any[] = [];
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