export type Book = {
    id: string;
    title: string;
    author: string;
    year: string;
    copies: number;
    price: number;
    genreId: string;
};

export type BookWithGenre = Book & {
    genre: {
        id: string;
        name: string;
    };
};

export type Genre = {
    id: string;
    name: string;
};
