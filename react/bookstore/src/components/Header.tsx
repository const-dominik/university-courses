import styled from "styled-components";

const Logo = styled.div`
    display: flex;
    align-items: center;
`;

const StyledHeader = styled.header`
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 1rem;
    background-color: #333;
    color: white;
    height: 10vh;

    img {
        width: 50px;
        height: 50px;
        margin-right: 1rem;
    }
`;

const Header = () => {
    return (
        <StyledHeader>
            <Logo>
                <img src="/logo.png" alt="logo" />
                <h1>Epic Tales</h1>
            </Logo>
        </StyledHeader>
    );
};

export default Header;
