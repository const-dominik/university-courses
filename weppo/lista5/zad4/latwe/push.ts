type Push<T extends any[], K> = [...T, K]

type Resul = Push<[1, 2], '3'> // [1, 2, '3']
