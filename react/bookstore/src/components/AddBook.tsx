import type { Book } from "../types";
import { v4 } from "uuid";
import AddBookForm from "./AddEditForm";

type BookFormProps = {
    onClose: () => void;
    onSave: (book: Book) => void;
};

const AddBook: React.FC<BookFormProps> = ({ onClose, onSave }) => {
    const initialState = {
        id: v4(),
        title: "",
        author: "",
        year: "",
        copies: 1,
        price: 1,
        genreId: "",
    };

    return (
        <AddBookForm
            onClose={onClose}
            onSave={onSave}
            initialState={initialState}
        />
    );
};

export default AddBook;
