import { useState } from "react";

import Navbar from "../components/Navbar";
import styled from "@emotion/styled";
import Avatar from "@mui/material/Avatar";
import AboutList from "../components/aboutpages/AboutList";
import Skills from "../components/aboutpages/Skills";
import Tabs from "@mui/material/Tabs";
import Tab from "@mui/material/Tab";
import type {
    EducationItem,
    ExperienceItem,
} from "../components/aboutpages/AboutList";

const Container = styled.div`
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    height: 90vh;
    background-color: #333;
`;

const HalfPage = styled.div`
    display: flex;
    flex-direction: column;
    position: relative;
    justify-content: center;
    align-items: center;
    width: 50%;
    height: 100%;
`;

const InfoSection = styled.div`
    display: flex;
    flex-direction: column;
    position: relative;
    width: 90%;
    height: 75%;
    border: 1px solid black;
`;

type Page = "education" | "experience" | "skills";

const educationList: EducationItem[] = [
    {
        school: "I Liceum Ogólnokształcące im. Mikołaja Kopernika",
        years: "2018-2021",
        description:
            "Extended mathematics, physics, computer science and English.",
    },
    {
        school: "University of Wrocław",
        years: "2021-2025",
        description: "Engineering degree in computer science.",
    },
    {
        school: "Oxford University",
        years: "2025-2028",
        description: "Master's degree in computer science.",
    },
    {
        school: "Harvard University",
        years: "2028-2030",
        description: "PhD in computer science.",
    },
];

const experienceList: ExperienceItem[] = [
    {
        company: "Google",
        position: "Junior Software Engineer",
        years: "2025-2028",
        description: "Worked on the Google search engine.",
    },
    {
        company: "Facebook",
        position: "Mid-level Software Engineer",
        years: "2028-2030",
        description: "Worked on the Facebook social media platform.",
    },
    {
        company: "Amazon",
        position: "Senior Software Engineer",
        years: "2030-2032",
        description: "Worked on the Amazon e-commerce platform.",
    },
    {
        company: "SpaceX",
        position: "Lead Software Engineer",
        years: "2032-2035",
        description: "Worked on the SpaceX Mars mission.",
    },
];

const About = () => {
    const [page, setPage] = useState<Page>("education");

    return (
        <>
            <Navbar />
            <Container>
                <HalfPage>
                    <Avatar
                        alt="cute dog"
                        src="https://avatars.githubusercontent.com/u/46941390"
                        sx={{
                            width: 500,
                            height: 500,
                            border: "1px solid black",
                        }}
                    />
                </HalfPage>
                <HalfPage>
                    <InfoSection>
                        <Tabs
                            value={page}
                            onChange={(_, value) => setPage(value)}
                            variant="fullWidth"
                            sx={{
                                position: "absolute",
                                top: 0,
                                backgroundColor: "#282828",
                                width: "100%",
                                "& .MuiTab-root": {
                                    color: "green",
                                },
                                "& .MuiTabs-indicator": {
                                    backgroundColor: "green",
                                },
                                "& .MuiTouchRipple-root": {
                                    color: "green",
                                },
                            }}
                        >
                            <Tab
                                label="Education"
                                value="education"
                                sx={{ "&.Mui-selected": { color: "green" } }}
                            />
                            <Tab
                                label="Experience"
                                value="experience"
                                sx={{ "&.Mui-selected": { color: "green" } }}
                            />
                            <Tab
                                label="Skills"
                                value="skills"
                                sx={{ "&.Mui-selected": { color: "green" } }}
                            />
                        </Tabs>

                        {page === "education" && (
                            <AboutList items={educationList} />
                        )}
                        {page === "experience" && (
                            <AboutList items={experienceList} />
                        )}
                        {page === "skills" && <Skills />}
                    </InfoSection>
                </HalfPage>
            </Container>
        </>
    );
};

export default About;
