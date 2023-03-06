type MyExclude<T, U> = T extends U ? never : T;

type uno = 1 | 2 | 3;

type result = MyExclude<uno, 1>;