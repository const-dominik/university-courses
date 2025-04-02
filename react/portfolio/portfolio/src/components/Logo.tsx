import styled from "@emotion/styled";
import { Link } from "react-router-dom";

const Logo = styled(Link)`
    font-size: 1.5em;
    color: green;
    display: inline-block;
    cursor: pointer;
    user-select: none;
    text-decoration: none;
`;

const MyLogo = () => <Logo to="/">const_dominik</Logo>;

export default MyLogo;
