import { useQuery } from "@tanstack/react-query";

const fetchBook = async (id: string) => {
    const response = await fetch(`http://localhost:3000/books/${id}`);
    if (!response.ok) {
        throw new Error("Error fetching book.");
    }
    return await response.json();
};

const useBook = (id: string) => {
    return useQuery({
        queryKey: ["book", id],
        queryFn: () => fetchBook(id),
    });
};

export default useBook;
