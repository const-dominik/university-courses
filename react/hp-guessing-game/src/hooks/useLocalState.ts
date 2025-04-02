import { useState } from "react";

const useLocalState = (
    key: string,
    defaultValue: number
): [number, (val: number) => void] => {
    const [state, setState] = useState(() => {
        const localState = localStorage.getItem(key);
        return localState ? parseInt(localState, 10) : defaultValue;
    });

    const setLocalState = (value: number) => {
        setState(value);
        localStorage.setItem(key, JSON.stringify(value));
    };

    return [state, setLocalState];
};

export default useLocalState;
