import { useQuery } from "@tanstack/react-query";

const fetchBooks = async (page: number, limit: number) => {
    const booksResponse = await fetch(
        `http://localhost:3000/books?_expand=genre&_page=${page}&_limit=${limit}`
    );

    const books = await booksResponse.json();

    const total = booksResponse.headers.get("x-total-count");
    return { books: books, total: Number(total) };
};

const useBooks = (page: number, limit: number) => {
    return useQuery({
        queryKey: ["books", page, limit],
        queryFn: () => fetchBooks(page, limit),
    });
};

export default useBooks;
