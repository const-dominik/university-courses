import styled from "@emotion/styled";

export type EducationItem = {
    school: string;
    years: string;
    description: string;
};

export type ExperienceItem = {
    company: string;
    position: string;
    years: string;
    description: string;
};

type ListItem = EducationItem | ExperienceItem;

const StyledList = styled.ul`
    list-style-type: none;
    margin-top: 2rem;
    color: #f4f4f4;
    padding: 0;
    overflow-y: auto;

    &::-webkit-scrollbar {
        width: 10px;
    }

    &::-webkit-scrollbar-track {
        background: #f1f1f1;
    }

    &::-webkit-scrollbar-thumb {
        background: #888;
    }

    &::-webkit-scrollbar-thumb:hover {
        background: #555;
    }
`;

const StyledListItem = styled.li`
    padding: 1rem;
    color: #f4f4f4;
    border-bottom: 1px solid #f4f4f4;

    &:last-child {
        border-bottom: none;
    }

    p {
        margin: 0.5em 0;
    }

    p:first-child {
        font-weight: bold;
        font-size: 1.2em;
    }
`;

const AboutList = ({ items }: { items: ListItem[] }) => {
    const isEducation = "school" in items[0];

    return (
        <StyledList>
            {isEducation
                ? (items as EducationItem[]).map((item, index) => (
                      <StyledListItem key={index}>
                          <p>{item.school}</p>
                          <p>{item.years}</p>
                          <p>{item.description}</p>
                      </StyledListItem>
                  ))
                : (items as ExperienceItem[]).map((item, index) => (
                      <StyledListItem key={index}>
                          <p>{item.company}</p>
                          <p>{item.position}</p>
                          <p>{item.years}</p>
                          <p>{item.description}</p>
                      </StyledListItem>
                  ))}
        </StyledList>
    );
};

export default AboutList;
