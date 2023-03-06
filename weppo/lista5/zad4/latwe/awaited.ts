type MyAwaited<T> = T extends Promise<infer U> ?
                    (U extends Promise<unknown> ? MyAwaited<U> : U) 
                    : (T extends { then: (onfulfilled: (arg: (infer K)) => any) => any } ? K : never); 

type ExampleType = Promise<string>

type Result = MyAwaited<ExampleType> // string