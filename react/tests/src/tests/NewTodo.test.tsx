import { render, fireEvent, screen, waitFor } from "@testing-library/react";
import NewTodo from "../../src/components/NewTodo/NewTodo";
import { TodosContext } from "../../src/providers/TodosProvider/TodosProvider";
import { vi, beforeEach, test, expect, afterEach } from "vitest";

const mockAddTodo = vi.fn();
const mockRemoveTodo = vi.fn();
const mockEditTodo = vi.fn();

const mockedContextValue = {
    todos: [],
    addTodo: mockAddTodo,
    removeTodo: mockRemoveTodo,
    editTodo: mockEditTodo,
};

beforeEach(() => {
    render(
        <TodosContext.Provider value={mockedContextValue}>
            <NewTodo />
        </TodosContext.Provider>
    );
});

afterEach(() => {
    vi.resetAllMocks();
});

test("should render necessary fields", () => {
    const input = screen.getByLabelText(/todo name/i);
    const priority = screen.getByLabelText(/priority/i);
    const tags = screen.getByLabelText(/tags/i);
    expect(input).toBeInTheDocument();
    expect(priority).toBeInTheDocument();
    expect(tags).toBeInTheDocument();
});

test("should add a new todo when proper data is passed", async () => {
    const name = screen.getByLabelText(/todo name/i);
    const priority = screen.getByLabelText(/priority/i);
    const tags = screen.getByLabelText(/tags/i);
    const add = screen.getByRole("button", { name: /add/i });

    fireEvent.change(name, { target: { value: "New Todo" } });

    fireEvent.mouseDown(priority);
    const priorityOption = await screen.findByRole("option", { name: /high/i });
    fireEvent.click(priorityOption);

    fireEvent.change(tags, { target: { value: "networking" } });
    const tagOption = await screen.findByText(/networking/i, { exact: true });
    fireEvent.click(tagOption);

    fireEvent.click(add);

    // await waitFor(() => {
    expect(mockAddTodo).toHaveBeenCalledWith({
        name: "New Todo",
        priority: "high",
        tags: ["networking"],
    });
    // });
});

test("should not call addTodo when form is submitted with empty fields", () => {
    fireEvent.click(screen.getByRole("button", { name: /add/i }));
    expect(mockAddTodo).not.toHaveBeenCalled();
});

test("should communicate that the fields are required", async () => {
    fireEvent.click(screen.getByRole("button", { name: /add/i }));

    // await waitFor(() => {
        expect(screen.getByLabelText(/todo name/i).parentElement).toHaveClass(
            "Mui-error"
        );
        expect(screen.getByLabelText(/priority/i).parentElement).toHaveClass(
            "Mui-error"
        );
    // });
});
