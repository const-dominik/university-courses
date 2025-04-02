import { useEffect, useState } from "react";
import { getData, getEndpointByCategory, getQuestionData } from "./utils/utils";
import type { HpData, PotterDbEndpoint } from "./utils/utils";
import CategorySelect from "./components/CategorySelect";
import Quiz from "./components/Quiz";
import styled from "styled-components";

const Container = styled.div`
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height: 100vh;
    width: 100vw;
    background-color: #a75d5d;
`;

const Loader = styled.div`
    border: 16px solid #ffc3a1;
    border-radius: 50%;
    border-top: 16px solid #d3756b;
    width: 120px;
    height: 120px;
    animation: spin 1s linear infinite;

    @keyframes spin {
        0% {
            transform: rotate(0deg);
        }
        100% {
            transform: rotate(360deg);
        }
    }
`;

const GuessingGame = () => {
    const [hpData, setHpData] = useState<HpData | null>(null);
    const [category, setCategory] = useState<string | null>(null);

    useEffect(() => {
        if (category) {
            const endpoint = getEndpointByCategory(
                category
            ) as PotterDbEndpoint;
            if (!endpoint) {
                throw new Error("Invalid category");
            }
            getData(endpoint).then((data) => setHpData(data));
        }
    }, [category]);

    return (
        <Container>
            {!category && <CategorySelect setCategory={setCategory} />}
            {category && !hpData && <Loader />}
            {category && hpData && (
                <Quiz
                    data={getQuestionData(category)}
                    hpData={hpData}
                    setCategory={setCategory}
                    setHpData={setHpData}
                />
            )}
        </Container>
    );
};

export default GuessingGame;
