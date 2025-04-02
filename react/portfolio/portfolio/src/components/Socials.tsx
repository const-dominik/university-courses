import GitHubIcon from "@mui/icons-material/GitHub";
import LinkedInIcon from "@mui/icons-material/LinkedIn";
import styled from "@emotion/styled";

const Container = styled.div`
    display: flex;
    justify-content: center;
    align-items: center;
    gap: 20px;
    margin-top: 20px;
`;

const IconLink = styled.a`
    color: #f4f4f4;
    &:visited {
        color: #f4f4f4;
    }
`;

const Socials = () => {
    return (
        <Container>
            <IconLink href="https://github.com/const-dominik/" target="_blank">
                <GitHubIcon fontSize="large" />
            </IconLink>

            <IconLink
                href="https://www.linkedin.com/in/dominik-kie%C5%82bowicz-44b043213/"
                target="_blank"
            >
                <LinkedInIcon fontSize="large" />
            </IconLink>
        </Container>
    );
};

export default Socials;
