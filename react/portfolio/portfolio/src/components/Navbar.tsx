import Logo from "./Logo";
import styled from "@emotion/styled";
import { Link, useLocation } from "react-router-dom";

const NavbarContainer = styled.div`
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 0 20px;
    background-color: #333;
    color: #fff;
    height: 10vh;
    border-bottom: 1px solid black;
`;

const StyledLink = styled(Link)`
    color: green;
    margin: 0 10px;
    text-decoration: none;
    font-size: 1.2rem;
`;

const CurrentLink = styled(StyledLink)`
    text-decoration: underline;
`;

const Navbar = () => {
    const location = useLocation();

    return (
        <NavbarContainer>
            <Logo />
            <div>
                {location.pathname === "/" ? (
                    <CurrentLink to="/">home</CurrentLink>
                ) : (
                    <StyledLink to="/">home</StyledLink>
                )}
                {location.pathname === "/about" ? (
                    <CurrentLink to="/about">about</CurrentLink>
                ) : (
                    <StyledLink to="/about">about</StyledLink>
                )}
                {location.pathname === "/projects" ? (
                    <CurrentLink to="/projects">projects</CurrentLink>
                ) : (
                    <StyledLink to="/projects">projects</StyledLink>
                )}
            </div>
        </NavbarContainer>
    );
};

export default Navbar;
