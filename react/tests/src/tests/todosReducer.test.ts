import { describe, it, expect } from "vitest";
import { v4 as uuidv4 } from "uuid";
import {
    todosReducer,
    type ITodoAction,
} from "../providers/TodosProvider/todosReducer";
import { ITodo } from "../types/ITodo.type";

const createInitialState = (): ITodo[] => {
    const todoId = uuidv4();
    return [
        {
            id: todoId,
            name: "test todo",
            status: "to-do",
            priority: "low",
            createdAt: new Date(),
            updatedAt: new Date(),
            tags: ["work"],
        },
    ];
};

describe("todosReducer", () => {
    it("should add a new todo", () => {
        const initialState: ITodo[] = [];
        const action: ITodoAction = {
            type: "ADD_TODO",
            payload: {
                name: "pay your bills",
                priority: "high",
                tags: ["payment"],
            },
        };
        const state = todosReducer(initialState, action);
        expect(state).toHaveLength(1);
        expect(state[0]).toMatchObject({
            name: "pay your bills",
            status: "to-do",
            priority: "high",
            tags: ["payment"],
        });
    });

    it("should remove a todo", () => {
        const initialState = createInitialState();
        const action: ITodoAction = {
            type: "REMOVE_TODO",
            payload: initialState[0].id,
        };
        const state = todosReducer(initialState, action);
        expect(state).toHaveLength(0);
    });

    it("should set the name of a todo", () => {
        const initialState = createInitialState();
        const action: ITodoAction = {
            type: "SET_NAME",
            payload: { id: initialState[0].id, name: "dominik :)" },
        };
        const state = todosReducer(initialState, action);
        expect(state[0].name).toBe("dominik :)");
    });

    it("should set the status of a todo", () => {
        const initialState = createInitialState();
        const action: ITodoAction = {
            type: "SET_STATUS",
            payload: { id: initialState[0].id, status: "done" },
        };
        const state = todosReducer(initialState, action);
        expect(state[0].status).toBe("done");
    });

    it("should set the priority of a todo", () => {
        const initialState = createInitialState();
        const action: ITodoAction = {
            type: "SET_PRIORITY",
            payload: { id: initialState[0].id, priority: "high" },
        };
        const state = todosReducer(initialState, action);
        expect(state[0].priority).toBe("high");
    });

    it("should set the tags of a todo", () => {
        const initialState = createInitialState();
        const action: ITodoAction = {
            type: "SET_TAGS",
            payload: {
                id: initialState[0].id,
                tags: ["payment", "work", "university"],
            },
        };
        const state = todosReducer(initialState, action);
        expect(state[0].tags).toEqual(["payment", "work", "university"]);
    });

    it("should add todo to existing todos", () => {
        const initialState = createInitialState();
        const action: ITodoAction = {
            type: "ADD_TODO",
            payload: {
                name: "buy groceries",
                priority: "medium",
                tags: ["shopping"],
            },
        };
        const state = todosReducer(initialState, action);
        expect(state).toHaveLength(2);
        expect(state[1]).toMatchObject({
            name: "buy groceries",
            status: "to-do",
            priority: "medium",
            tags: ["shopping"],
        });
    });

    it("should not remove a non-existent todo", () => {
        const initialState = createInitialState();
        const action: ITodoAction = {
            type: "REMOVE_TODO",
            payload: "non-existent-id",
        };
        const state = todosReducer(initialState, action);
        expect(state).toHaveLength(1);
    });
});
