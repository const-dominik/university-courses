import { useState } from "react";
import useBooks from "../hooks/useBooks";
import useRemoveBook from "../hooks/useRemoveBook";
import ConfirmDelete from "./ConfirmDelete";
import EditBook from "./EditBook";
import AddBook from "./AddBook";
import useAddBook from "../hooks/useAddBook";
import useEditBook from "../hooks/useEditBook";
import styled from "styled-components";
import type { BookWithGenre, Book } from "../types";

const Container = styled.div`
    height: 70vh;
`;

const Table = styled.table`
    width: 100%;
    border-collapse: collapse;
    font-family: Arial, sans-serif;
`;

const Thead = styled.thead`
    background-color: #007bff;
    color: white;
`;

const Th = styled.th`
    padding: 12px 15px;
    text-align: left;
    border-bottom: 1px solid #ddd;
`;

const Tbody = styled.tbody`
    & tr:nth-child(even) {
        background-color: #f2f2f2;
    }
`;

const Td = styled.td`
    padding: 12px 15px;
    border-bottom: 1px solid #ddd;
`;

const Pagination = styled.div`
    display: flex;
    justify-content: center;
    align-items: center;
    margin-top: 20px;
`;

const Button = styled.button`
    margin: 0 5px;
    padding: 5px 10px;
    cursor: pointer;
    border: none;
    background-color: #007bff;
    color: white;
    border-radius: 5px;

    &:disabled {
        background-color: #d6d6d6;
        cursor: not-allowed;
    }
`;

const PageInfo = styled.span`
    margin: 0 10px;
`;

const AddBookButton = styled.div`
    background-color: #007bff;
    color: white;
    padding: 0.5rem 1rem;
    border-radius: 5px;
    cursor: pointer;
    width: 10rem;
    text-align: center;
`;

const BookTable = () => {
    const [page, setPage] = useState(1);
    const limit = 10;

    const [selectedBookId, setSelectedBookId] = useState<string | null>(null);
    const [isModalOpen, setIsModalOpen] = useState(false);
    const [isFormModalOpen, setIsFormModalOpen] = useState(false);

    const result = useBooks(page, limit);
    const removePostMutation = useRemoveBook();
    const addBookMutation = useAddBook();
    const editBookMutation = useEditBook();

    const removeBook = async (id: string) => {
        removePostMutation.mutate(id);
        closeModal();
    };

    const openModal = (id: string) => {
        setSelectedBookId(id);
        setIsModalOpen(true);
    };

    const closeModal = () => {
        setSelectedBookId(null);
        setIsModalOpen(false);
    };

    const openFormModal = (id?: string) => {
        if (id) {
            setSelectedBookId(id);
        }
        setIsFormModalOpen(true);
    };

    const closeFormModal = () => {
        setSelectedBookId(null);
        setIsFormModalOpen(false);
    };

    const handleSave = (book: Book) => {
        closeFormModal();
        if (selectedBookId !== book.id) {
            addBookMutation.mutate(book);
        } else {
            editBookMutation.mutate(book);
        }
    };

    if (result.isLoading || !result.data) return <div>Loading...</div>;
    if (result.isError) return <div>Error loading books.</div>;

    const totalPages = Math.ceil(result.data.total / limit);

    return (
        <Container>
            <Table>
                <Thead>
                    <tr>
                        <Th>Title</Th>
                        <Th>Author</Th>
                        <Th>Year</Th>
                        <Th>Copies</Th>
                        <Th>Price</Th>
                        <Th>Genre</Th>
                        <Th>Actions</Th>
                    </tr>
                </Thead>
                <Tbody>
                    {result.data.books.map((book: BookWithGenre) => (
                        <tr key={book.id}>
                            <Td>{book.title}</Td>
                            <Td>{book.author}</Td>
                            <Td>{book.year}</Td>
                            <Td>{book.copies}</Td>
                            <Td>{book.price.toFixed(2)}$</Td>
                            <Td>{book.genre.name}</Td>
                            <Td>
                                <Button onClick={() => openFormModal(book.id)}>
                                    Edit
                                </Button>
                                <Button onClick={() => openModal(book.id)}>
                                    Delete
                                </Button>
                            </Td>
                        </tr>
                    ))}
                </Tbody>
            </Table>
            <Pagination>
                <Button onClick={() => setPage(page - 1)} disabled={page === 1}>
                    Previous
                </Button>
                <PageInfo>
                    Page {page} of {totalPages}
                </PageInfo>
                <Button
                    onClick={() => setPage(page + 1)}
                    disabled={page === totalPages}
                >
                    Next
                </Button>
            </Pagination>
            <AddBookButton onClick={() => openFormModal()}>
                Add book
            </AddBookButton>
            {isModalOpen && (
                <ConfirmDelete
                    onClose={() => closeModal()}
                    onConfirm={() => removeBook(selectedBookId!)}
                />
            )}
            {isFormModalOpen && !selectedBookId && (
                <AddBook onClose={closeFormModal} onSave={handleSave} />
            )}
            {isFormModalOpen && selectedBookId && (
                <EditBook
                    onClose={closeFormModal}
                    onSave={handleSave}
                    bookId={selectedBookId}
                />
            )}
        </Container>
    );
};
export default BookTable;
