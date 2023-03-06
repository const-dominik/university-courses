type First<T extends any[]> = T[0];

type arr1 = ['a', 'b'];
type rest = First<arr1>