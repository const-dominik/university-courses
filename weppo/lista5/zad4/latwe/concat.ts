type Concat<T extends any[], U extends any[]> = [T[number], U[number]];

type Res = Concat<[1], [2]> // expected to be [1, 2]