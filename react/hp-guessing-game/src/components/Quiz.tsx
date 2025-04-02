import type { HpData, Question } from "../utils/utils";
import { generateQuestion } from "../utils/utils";
import { useState, useEffect } from "react";
import styled from "styled-components";
import useLocalState from "../hooks/useLocalState";

const Container = styled.div`
    height: 40vh;
    width: 30vw;
    border-radius: 10px;
`;

const Header = styled.div`
    background-color: #d3756b;
    font-size: 1.3rem;
    width: 100%;
    height: 40%;
    display: flex;
    justify-content: center;
    align-items: center;
    text-align: center;
    border-top-left-radius: 10px;
    border-top-right-radius: 10px;
    color: #ffc3a1;
    padding: 1rem;
`;

const AnswersContainer = styled.div`
    display: flex;
    justify-content: space-around;
    align-items: center;
    flex-wrap: wrap;
    height: 60%;
`;

const Answer = styled.div`
    background-color: #ffc3a1;
    color: #a75d5d;
    display: flex;
    align-items: center;
    justify-content: center;
    text-align: center;
    cursor: pointer;
    width: 50%;
    height: 50%;
    border: 1px solid #d3756b;
    padding: 0.7rem;
`;

const AnswerFeedback = styled.div`
    background-color: #d3756b;
    height: 10%;
    width: 100%;
    text-align: center;
`;

const CorrectAnswer = styled.p`
    color: green;
`;

const IncorrectAnswer = styled.p`
    color: #9b1f1f;
`;

const ChangeCategory = styled.div`
    color: #ffc3a1;
    cursor: pointer;

    &:hover {
        text-decoration: underline;
    }
`;

const Streak = styled.div`
    background-color: #d3756b;
    height: 10%;
    width: 100%;
    display: flex;
    justify-content: space-between;
    align-items: center;
    border-bottom-left-radius: 10px;
    border-bottom-right-radius: 10px;
`;

const StreakInfo = styled.div`
    margin: 0.7rem;
    color: #ffc3a1;
`;

const Quiz = ({
    data,
    hpData,
    setCategory,
    setHpData,
}: {
    data:
        | [questionProperty: string, answersProperty: string, question: string]
        | undefined;
    hpData: HpData;
    setCategory: (category: string | null) => void;
    setHpData: (data: HpData | null) => void;
}) => {
    if (!data) {
        return null;
    }
    const [questionProperty, answersProperty, question] = data;
    const [questionData, setQuestionData] = useState<Question>(
        generateQuestion(hpData, questionProperty, answersProperty, question)
    );
    const [answerCorrect, setAnswerCorrect] = useState<
        "correct" | "incorrect" | "none" | "change"
    >("change");
    const [streak, setStreak] = useLocalState("streak", 0);
    const [maxStreak, setMaxStreak] = useLocalState("maxStreak", 0);

    // useEffect(() => {
    //     setQuestion();
    // }, []);

    // useEffect(() => {
    //     if (streak > maxStreak) {
    //         setMaxStreak(streak);
    //     }
    // }, [streak]);

    const setQuestion = () => {
        setQuestionData(
            generateQuestion(
                hpData,
                questionProperty,
                answersProperty,
                question
            )
        );
    };

    const handleAnswer = (e: React.MouseEvent<HTMLDivElement>) => {
        if (
            !questionData ||
            answerCorrect === "correct" ||
            answerCorrect === "incorrect"
        ) {
            return;
        }
        const answer = e.currentTarget.textContent;
        if (answer === questionData.correctAnswer) {
            setAnswerCorrect("correct");
            if (streak + 1 > maxStreak) {
                setMaxStreak(streak + 1);
            }
            setStreak(streak + 1);
            setTimeout(() => {
                setAnswerCorrect("change");
                setQuestion();
            }, 1000);
        } else {
            setAnswerCorrect("incorrect");
            setStreak(0);
            setTimeout(() => {
                setAnswerCorrect("none");
            }, 1000);
        }
    };

    return (
        <Container>
            {questionData && (
                <>
                    <Header>{questionData.question}</Header>
                    <AnswersContainer>
                        {questionData.answers.map((answer) => (
                            <Answer key={answer} onClick={handleAnswer}>
                                {answer}
                            </Answer>
                        ))}
                    </AnswersContainer>
                    <AnswerFeedback>
                        {answerCorrect === "correct" && (
                            <CorrectAnswer>Correct answer!</CorrectAnswer>
                        )}
                        {answerCorrect === "incorrect" && (
                            <IncorrectAnswer>Wrong answer!</IncorrectAnswer>
                        )}
                        {answerCorrect === "change" && (
                            <ChangeCategory
                                onClick={() => {
                                    setCategory(null);
                                    setHpData(null);
                                }}
                            >
                                Change category
                            </ChangeCategory>
                        )}
                    </AnswerFeedback>
                    <Streak>
                        <StreakInfo>Current streak: {streak}</StreakInfo>
                        <StreakInfo>Max streak: {maxStreak}</StreakInfo>
                    </Streak>
                </>
            )}
        </Container>
    );
};

export default Quiz;
