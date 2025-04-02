import styled from "@emotion/styled";

const skills = [
    "React",
    "TypeScript",
    "Node.js",
    "Express",
    "PostgreSQL",
    "HTML",
    "CSS",
    "JavaScript",
    "Python",
    "C++",
    "Java",
    "Git",
    "Docker",
    "Kubernetes",
    "Jenkins",
    "AWS",
    "Azure",
    "GCP",
    "Terraform",
    "Ansible",
    "Linux",
    "Windows",
    "MacOS",
    "Bash",
    "PowerShell",
    "REST",
    "gRPC",
    "GraphQL",
    "Agile",
    "Scrum",
];

const SkillsContainer = styled.div`
    display: flex;
    flex-wrap: wrap;
    margin-top: 3rem;
    padding: 1rem;
    gap: 0.7rem;
`;

const SkillItem = styled.div`
    padding: 10px;
    border: 1px solid #f4f4f4;
    color: #f4f4f4;
    border-radius: 20px;
`;

const Skills = () => {
    return (
        <div>
            <SkillsContainer>
                {skills.map((skill, index) => (
                    <SkillItem key={index}>{skill}</SkillItem>
                ))}
            </SkillsContainer>
        </div>
    );
};

export default Skills;
