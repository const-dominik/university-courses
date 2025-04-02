import { render, fireEvent, screen, waitFor } from "@testing-library/react";
import TodoGrid from "../../src/components/TodoGrid/TodoGrid";
import { TodosContext } from "../../src/providers/TodosProvider/TodosProvider";
import { vi, beforeEach, test, expect, afterEach, describe } from "vitest";
import { ITags, ITodoPriority, ITodoStatus } from "../types/ITodo.type";

const mockAddTodo = vi.fn();
const mockRemoveTodo = vi.fn();
const mockEditTodo = vi.fn();

const mockedContextValue = {
    todos: [
        {
            id: "1",
            name: "Test Todo 1",
            priority: "high" as ITodoPriority,
            tags: ["work"] as ITags[],
            status: "done" as ITodoStatus,
            createdAt: new Date(),
            updatedAt: new Date(),
        },
        {
            id: "2",
            name: "Test Todo 2",
            priority: "low" as ITodoPriority,
            tags: ["personal"] as ITags[],
            status: "in-progress" as ITodoStatus,
            createdAt: new Date(),
            updatedAt: new Date(),
        },
    ],
    addTodo: mockAddTodo,
    removeTodo: mockRemoveTodo,
    editTodo: mockEditTodo,
};

beforeEach(() => {
    render(
        <TodosContext.Provider value={mockedContextValue}>
            <TodoGrid />
        </TodosContext.Provider>
    );
});

afterEach(() => {
    vi.resetAllMocks();
});

test("should render all todos", () => {
    const todo1 = screen.getByText(/test todo 1/i);
    const todo2 = screen.getByText(/test todo 2/i);

    expect(todo1).toBeInTheDocument();
    expect(todo2).toBeInTheDocument();
});

test("should call removeTodo when delete button is clicked", async () => {
    const deleteButtons = screen.getAllByLabelText(/delete/i);
    fireEvent.click(deleteButtons[0]);

    // await waitFor(() => {
    expect(mockRemoveTodo).toHaveBeenCalledWith("1");
    // });
});

test("should switch to edit mode when edit button is clicked", () => {
    const editButtons = screen.getAllByLabelText(/edit/i);
    fireEvent.click(editButtons[0]);

    expect(screen.getByLabelText(/save/i)).toBeInTheDocument();
    expect(screen.getByLabelText(/cancel/i)).toBeInTheDocument();
});

test("should call editTodo with updated values when save button is clicked", async () => {
    const editButtons = screen.getAllByLabelText(/edit/i);
    fireEvent.click(editButtons[0]);

    const combobox = screen.getAllByRole("combobox");
    const priorityInput = combobox.find((el) => el.textContent === "High");
    const statusInput = combobox.find((el) => el.textContent === "Done");
    if (!priorityInput || !statusInput) {
        throw new Error("Priority input not found");
    }

    fireEvent.mouseDown(priorityInput);
    const priorityOption = await screen.findByRole("option", {
        name: /medium/i,
    });
    fireEvent.click(priorityOption);

    fireEvent.mouseDown(statusInput);
    const statusOption = await screen.findByRole("option", {
        name: /in progress/i,
    });
    fireEvent.click(statusOption);

    const saveButton = screen.getByLabelText(/save/i);
    fireEvent.click(saveButton);

    await waitFor(() => {
        expect(mockEditTodo).toHaveBeenCalledWith("1", {
            priority: "medium",
            status: "in-progress",
        });
    });
});

test("shouldn't update todo if edit has been canceled", async () => {
    const editButtons = screen.getAllByLabelText(/edit/i);
    fireEvent.click(editButtons[0]);

    const cancelButton = screen.getByLabelText(/cancel/i);
    fireEvent.click(cancelButton);

    expect(screen.queryByLabelText(/save/i)).not.toBeInTheDocument();
    expect(screen.queryByLabelText(/cancel/i)).not.toBeInTheDocument();

    await waitFor(() => {
        expect(mockEditTodo).not.toHaveBeenCalled();
    });
});
