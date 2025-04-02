import { useMutation, useQueryClient } from "@tanstack/react-query";

const removePost = async (id: string) => {
    const res = await fetch(`http://localhost:3000/books/${id}`, {
        method: "DELETE",
        headers: {
            "Content-Type": "application/json",
        },
    });
    return await res.json();
};

const useRemoveBook = () => {
    const queryClient = useQueryClient();

    return useMutation({
        mutationFn: (id: string) => removePost(id),
        onSuccess: () => {
            queryClient.invalidateQueries({
                queryKey: ["books"],
            });
        },
    });
};

export default useRemoveBook;
