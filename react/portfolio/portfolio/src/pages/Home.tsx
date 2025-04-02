import Navbar from "../components/Navbar";
import styled from "@emotion/styled";
import IAm from "../components/IAm";
import Socials from "../components/Socials";

const Container = styled.div`
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    height: 90vh;
    background-color: #333;
`;

const Name = styled.h1`
    color: #f4f4f4;
    font-size: 3rem;
`;

const Home = () => {
    return (
        <>
            <Navbar />
            <Container>
                <Name>Dominik Kiełbowicz</Name>
                <IAm />
                <Socials />
            </Container>
        </>
    );
};

export default Home;
