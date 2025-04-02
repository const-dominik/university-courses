import Navbar from "../components/Navbar";
import Carousel from "react-material-ui-carousel";
import styled from "@emotion/styled";
import ProjectItem from "../components/ProjectItem";
import type { Item } from "../components/ProjectItem";

const items: Item[] = [
    {
        name: "Chess.com",
        description:
            "Chess.com is an online chess platform that allows you to play, learn, and watch live games. Highly encourages you to pay them for basic features.",
        screenshot: "apps/chess.png",
        codelink: "https://github.com/chesscom",
        technologies: ["HTML", "CSS", "JavaScript", "PHP"],
    },
    {
        name: "lichess.org",
        description:
            "lichess.org is a free online chess platform that allows you to play, learn, and watch live games. It is open-source and free to use. You can have lots of fun here without paying a dime.",
        screenshot: "apps/lichess.png",
        codelink: "https://github.com/lichess-org",
        technologies: ["Rust", "Scala", "TypeScript", "Python", "Dart"],
    },
    {
        name: "Google",
        description:
            "The most popular search engine on the internet. It is used to search for information on the Wide Web World. For example, you can ask it how tall is a kangaroo, and it will tell you. It is very smart and knows everything, except for the things it doesn't know.",
        screenshot: "apps/google.png",
        codelink: "https://github.com/google",
        technologies: ["React", "TypeScript", "Go", "Python"],
    },
    {
        name: "ChatGPT",
        description:
            "ChatGPT is a chatbot that uses the GPT-3.5 model to generate human-like responses. You can have very captivating conversations with it. Also, it helps you with your homework.",
        screenshot: "apps/chatgpt.png",
        codelink: "https://github.com/openai/chatgpt",
        technologies: ["Python", "TypeScript", "Vue", "Dart"],
    },
    {
        name: "Netflix",
        description:
            "Netflix is a streaming service that offers a wide variety of TV shows, movies, anime, documentaries, and more on thousands of internet-connected devices. Allows you to watch fun shows like Cunk on Earth. However, it's more expensive than free services.",
        screenshot: "apps/netflix.png",
        codelink: "https://github.com/netflix",
        technologies: ["React", "TypeScript", "Python", "Go", "Java", "Kotlin"],
    },
];

const Container = styled.div`
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    height: 90vh;
    background-color: #333;
`;

const Projects = () => {
    return (
        <>
            <Navbar />
            <Container>
                <Carousel
                    sx={{
                        width: "100vw",
                        height: "80vh",
                        margin: "auto",
                    }}
                >
                    {items.map((item, i) => (
                        <ProjectItem key={i} item={item} />
                    ))}
                </Carousel>
            </Container>
        </>
    );
};

export default Projects;
