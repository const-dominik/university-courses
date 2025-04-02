import { ReactTyped } from "react-typed";
import styled from "@emotion/styled";

const StyledTyped = styled(ReactTyped)`
    color: green;
    font-size: 2rem;
`;

const StyledP = styled.p`
    color: #f4f4f4;
    font-size: 1.2rem;
    margin-top: 30px;
`;

const Container = styled.div`
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    width: 50vw;
    margin: 0 auto;
`;

const IAm = () => {
    const specializations = [
        "Fullstack Developer",
        "CS Student",
        "IT Enthusiast",
    ];

    return (
        <Container>
            <h2>
                <StyledTyped
                    strings={specializations}
                    typeSpeed={100}
                    backSpeed={50}
                    backDelay={1000}
                    cursorChar="|"
                    showCursor={true}
                    loop
                />
            </h2>

            <StyledP>
                I am a student of Computer Science at the University of Wrocław.
                I am passionate about programming and technology. I enjoy
                learning new things and solving problems.
            </StyledP>
        </Container>
    );
};

export default IAm;
