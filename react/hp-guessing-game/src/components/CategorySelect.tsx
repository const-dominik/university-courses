import { categories } from "../utils/utils";
import styled from "styled-components";

const Container = styled.div`
    height: 50vh;
    width: 30vw;
    border-radius: 10px;
    background-color: #f0997d;
`;

const Header = styled.h1`
    font-size: 2.3rem;
    background-color: #d3756b;
    width: 100%;
    height: 20%;
    display: flex;
    align-items: center;
    justify-content: center;
    border-top-left-radius: 10px;
    border-top-right-radius: 10px;
    color: #ffc3a1;
`;

const CategoriesContainer = styled.div`
    display: flex;
    justify-content: center;
    flex-wrap: wrap;
    max-height: 80%;
    overflow-y: auto;

    &::-webkit-scrollbar {
        width: 10px;
    }

    &::-webkit-scrollbar-track {
        background: #f0997d;
        border-bottom-right-radius: 15px;
    }

    &::-webkit-scrollbar-thumb {
        background: #ffc3a1;
        border-bottom-right-radius: 15px;
    }
`;

const Category = styled.div`
    background-color: #ffc3a1;
    margin-top: 10px;
    display: flex;
    align-items: center;
    justify-content: center;
    width: 80%;
    border-radius: 5px;
    cursor: pointer;
    height: 50px;
    border: 1px solid #d3756b;
    color: #a75d5d;

    &:last-child {
        margin-bottom: 10px;
    }
`;

const CategorySelect = ({
    setCategory,
}: {
    setCategory: (category: string) => void;
}) => {
    return (
        <Container>
            <Header>Select a category</Header>
            <CategoriesContainer>
                {Object.values(categories)
                    .flat()
                    .map((category) => (
                        <Category
                            key={category}
                            onClick={() => setCategory(category)}
                        >
                            {category}
                        </Category>
                    ))}
            </CategoriesContainer>
        </Container>
    );
};

export default CategorySelect;
