import styled from "@emotion/styled";
import CodeIcon from "@mui/icons-material/Code";

export type Item = {
    name: string;
    description: string;
    technologies: string[];
    codelink: string;
    screenshot: string;
};

const Container = styled.div`
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    height: 70vh;
`;

const AppScreenshot = styled.img`
    width: 45%;
    height: 100%;
    object-fit: contain;
    border-radius: 20px;
`;

const AppInfo = styled.div`
    display: flex;
    flex-direction: column;
    width: 50%;
    margin: 20px;
    color: #f4f4f4;
`;

const Technologies = styled.div`
    display: flex;
    flex-direction: row;
    align-items: center;
    gap: 10px;
    margin: 10px 0;
    flex-wrap: wrap;
`;

const Technology = styled.div`
    padding: 0.5rem;
    display: inline-block;
    width: fit-content;
    border-radius: 5px;
    border: 1px solid #f4f4f4;
    color: #f4f4f4;
`;

const ProjectLink = styled.a`
    display: flex;
    align-items: center;
    gap: 10px;
    text-decoration: none;
    color: green;
    margin-top: 0.8rem;
`;

const ProjectItem = ({ item }: { item: Item }) => {
    return (
        <Container>
            <AppScreenshot src={item.screenshot} alt={item.name} />
            <AppInfo>
                <h1 style={{ color: "green" }}>{item.name}</h1>
                <Technologies>
                    {item.technologies.map((tech, i) => (
                        <Technology key={i}>{tech}</Technology>
                    ))}
                </Technologies>
                <p>{item.description}</p>

                <ProjectLink href={item.codelink} target="_blank">
                    <CodeIcon /> View Code
                </ProjectLink>
            </AppInfo>
        </Container>
    );
};

export default ProjectItem;
