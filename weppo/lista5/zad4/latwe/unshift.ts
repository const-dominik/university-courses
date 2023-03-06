type Unshift<T extends any[], K> = [K, ...T]

type Ress = Unshift<[1, 2], 0> // [0, 1, 2,]