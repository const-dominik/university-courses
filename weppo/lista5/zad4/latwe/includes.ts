import { Equal } from "@type-challenges/utils"

type Includes<T extends any[], K> = T extends [infer R, ...infer rest] ?
                                    Equal<R, K> extends true ? true : Includes<rest, K> : false;

type isPillarMen = Includes<['Kars', 'Esidisi', 'Wamuu', 'Santana'], 'Dio'> // expected to be `false`
