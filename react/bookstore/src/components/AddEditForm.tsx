import {
    ModalActions,
    ModalContainer,
    ModalHeader,
    ModalOverlay,
    Button,
} from "./ConfirmDelete";
import styled from "styled-components";
import type { Book } from "../types";
import { useState } from "react";
import useGenres from "../hooks/useGenres";

const Form = styled.form`
    display: flex;
    flex-direction: column;
    gap: 10px;
`;

const Input = styled.input`
    padding: 10px;
    border: 1px solid #ddd;
    border-radius: 5px;
    font-size: 16px;
`;

const Select = styled.select`
    padding: 10px;
    border: 1px solid #ddd;
    border-radius: 5px;
    font-size: 16px;
`;

const ValidationMessage = styled.p`
    color: red;
`;

type BookFormModalProps = {
    onClose: () => void;
    onSave: (book: Book) => void;
    initialState: Book;
};

const validateState = (state: Book) => {
    let message = "";
    if (!Object.values(state).every((value) => value !== "")) {
        message = "All fields are required.";
    } else if (isNaN(+state.copies) || isNaN(+state.price)) {
        message = "Copies and price must be numbers.";
    } else if (state.copies < 1 || state.price < 1) {
        message = "Copies and price must be greater than 0.";
    } else if (state.year.length !== 4) {
        message = "Year must be 4 digits.";
    } else if (isNaN(+state.year)) {
        message = "Year must be a number.";
    }
    return message === "" ? null : message;
};

const BookFormModal: React.FC<BookFormModalProps> = ({
    onClose,
    onSave,
    initialState,
}) => {
    const [formState, setFormState] = useState<Book>(initialState);
    const [validationMessage, setValidationMessage] = useState<string | null>(
        null
    );
    const genres = useGenres();

    if (genres.isLoading) {
        return <p>Loading...</p>;
    }
    if (genres.isError) {
        return <p>Error loading genres.</p>;
    }

    if (!formState.genreId) {
        setFormState({
            ...formState,
            genreId: genres.data[0].id,
        });
    }

    const handleChange = (
        e: React.ChangeEvent<HTMLInputElement | HTMLSelectElement>
    ) => {
        const { name, value } = e.target;
        setFormState({
            ...formState,
            [name]: name === "copies" || name === "price" ? +value : value,
        });
    };

    const handleSubmit = (e: React.FormEvent) => {
        e.preventDefault();
        const validationMessage = validateState(formState);
        if (validationMessage) {
            setValidationMessage(validationMessage);
            return;
        }
        onSave(formState);
    };

    const handleCancel = () => {
        setFormState(initialState);
        onClose();
    };

    return (
        <ModalOverlay>
            <ModalContainer>
                <ModalHeader>{}</ModalHeader>
                {validationMessage && (
                    <ValidationMessage>{validationMessage}</ValidationMessage>
                )}
                <Form onSubmit={handleSubmit}>
                    <Input
                        name="title"
                        value={formState.title || ""}
                        onChange={handleChange}
                        placeholder="Title"
                        required
                    />
                    <Input
                        name="author"
                        value={formState.author || ""}
                        onChange={handleChange}
                        placeholder="Author"
                        required
                    />
                    <Input
                        name="year"
                        value={formState.year || ""}
                        onChange={handleChange}
                        placeholder="Year"
                        required
                    />
                    <Input
                        name="copies"
                        type="number"
                        value={formState.copies || 0}
                        onChange={handleChange}
                        placeholder="Copies"
                        required
                    />
                    <Input
                        name="price"
                        type="number"
                        value={formState.price || 0}
                        onChange={handleChange}
                        placeholder="Price"
                        required
                    />
                    <Select
                        name="genreId"
                        value={formState.genreId || ""}
                        onChange={handleChange}
                    >
                        {genres.data.map(
                            (genre: { id: string; name: string }) => (
                                <option key={genre.id} value={genre.id}>
                                    {genre.name}
                                </option>
                            )
                        )}
                    </Select>
                    <ModalActions>
                        <Button className="cancel" onClick={handleCancel}>
                            Cancel
                        </Button>
                        <Button className="confirm" type="submit">
                            Save
                        </Button>
                    </ModalActions>
                </Form>
            </ModalContainer>
        </ModalOverlay>
    );
};

export default BookFormModal;
