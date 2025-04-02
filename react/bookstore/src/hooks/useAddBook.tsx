import { Book } from "../types";
import { useMutation, useQueryClient } from "@tanstack/react-query";

const addBook = async (newBook: Book) => {
    const response = await fetch("http://localhost:3000/books", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({ ...newBook }),
    });
    if (!response.ok) {
        throw new Error("Error adding book.");
    }
    return await response.json();
};

const useAddBook = () => {
    const queryClient = useQueryClient();

    return useMutation({
        mutationFn: addBook,
        onSuccess: () => {
            queryClient.invalidateQueries({
                queryKey: ["books"],
            });
        },
    });
};

export default useAddBook;
