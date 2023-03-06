type Length<T extends readonly any[]> = T["length"];

const test = [1, 2, 3] as const;

type testLen = Length<typeof test>;