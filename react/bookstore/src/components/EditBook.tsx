import type { Book } from "../types";
import useBook from "../hooks/useBook";
import EditForm from "./AddEditForm";

type BookFormModalProps = {
    onClose: () => void;
    onSave: (book: Book) => void;
    bookId: string;
};

const EditFormModal: React.FC<BookFormModalProps> = ({
    onClose,
    onSave,
    bookId,
}) => {
    const bookQuery = useBook(bookId);

    if (bookQuery.isLoading) {
        return <p>Loading...</p>;
    }
    if (bookQuery.isError) {
        return <p>Error loading book.</p>;
    }

    return (
        <EditForm
            onClose={onClose}
            onSave={onSave}
            initialState={bookQuery.data}
        />
    );
};

export default EditFormModal;
