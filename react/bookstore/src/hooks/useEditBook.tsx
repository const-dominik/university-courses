import { Book } from "../types";
import { useMutation, useQueryClient } from "@tanstack/react-query";

const editBook = async (updatedBook: Book) => {
    const response = await fetch(
        `http://localhost:3000/books/${updatedBook.id}`,
        {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify(updatedBook),
        }
    );
    if (!response.ok) {
        throw new Error("Error editing book.");
    }
    return await response.json();
};

const useEditBook = () => {
    const queryClient = useQueryClient();

    return useMutation({
        mutationFn: (book: Book) => editBook(book),
        onSuccess: () => {
            queryClient.invalidateQueries({
                queryKey: ["books"],
            });
        },
    });
};

export default useEditBook;
