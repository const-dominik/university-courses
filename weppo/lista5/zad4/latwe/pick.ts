interface Todo {
    title: string
    description: string
    completed: boolean  
}

type MyPick<T, K extends keyof T> = {
    [k in K]: T[k]
}

