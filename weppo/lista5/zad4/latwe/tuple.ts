type TupleToObject<T extends readonly any[]> = {
    [k in T[number]]: k;
}

const tuple = ['tesla', 'model 3', 'model X', 'model Y'] as const;
type res = TupleToObject<typeof tuple>;