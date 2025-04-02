import React from "react";
import styled from "styled-components";

export const ModalOverlay = styled.div`
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
`;

export const ModalContainer = styled.div`
    background: white;
    padding: 20px;
    border-radius: 5px;
    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
    max-width: 500px;
    width: 100%;
    text-align: center;
`;

export const ModalHeader = styled.h2`
    margin-bottom: 10px;
`;

export const ModalActions = styled.div`
    display: flex;
    justify-content: space-around;
    margin-top: 20px;
`;

export const Button = styled.button`
    padding: 10px 20px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    font-size: 16px;

    &:hover {
        opacity: 0.8;
    }

    &.confirm {
        background: red;
        color: white;
    }

    &.cancel {
        background: gray;
        color: white;
    }
`;

type ConfirmDeleteModalProps = {
    onClose: () => void;
    onConfirm: () => void;
};

const ConfirmDeleteModal: React.FC<ConfirmDeleteModalProps> = ({
    onClose,
    onConfirm,
}) => {
    return (
        <ModalOverlay>
            <ModalContainer>
                <ModalHeader>Confirm Delete</ModalHeader>
                <p>Are you sure you want to delete this book?</p>
                <ModalActions>
                    <Button className="cancel" onClick={onClose}>
                        Cancel
                    </Button>
                    <Button className="confirm" onClick={onConfirm}>
                        Delete
                    </Button>
                </ModalActions>
            </ModalContainer>
        </ModalOverlay>
    );
};

export default ConfirmDeleteModal;
