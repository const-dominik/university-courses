type PotterDbEndpoint = "characters" | "spells" | "potions";
type UnwrapPromise<T> = T extends Promise<infer U> ? U : T;
type HpData = UnwrapPromise<ReturnType<typeof fetchPotterData>>;
type Question = {
    question: string;
    answers: string[];
    correctAnswer: string;
};
type Category = string;

const questionTypes: Record<
    PotterDbEndpoint,
    Record<
        Category,
        [questionProperty: string, answersProperty: string, question: string]
    >
> = {
    characters: {
        "Character alias names": [
            "alias_names",
            "name",
            "Who is also known as $val?",
        ],
        "Character romances": ["romances", "name", "Who romanced $val?"],
    },
    spells: {
        "Spell effect": [
            "effect",
            "name",
            'Which spell effect can be described as: "$val"?',
        ],
    },
    potions: {
        "Potion effect": [
            "effect",
            "name",
            'Which potion effect can be described as: "$val"?',
        ],
    },
};

const categories = Object.fromEntries(
    Object.entries(questionTypes).map(([key, value]) => {
        return [key, Object.keys(value)];
    })
);

const getEndpointByCategory = (category: Category) => {
    for (const [key, value] of Object.entries(categories)) {
        if (value.includes(category)) {
            return key;
        }
    }
};

const getQuestionData = (category: Category) => {
    for (const [, value] of Object.entries(questionTypes)) {
        if (Object.keys(value).includes(category)) {
            return value[category];
        }
    }
};

const requiredAttributes: Record<PotterDbEndpoint, string[]> = Object.entries(
    questionTypes
).reduce((acc, [endpoint, categories]) => {
    const attributes = Object.values(categories).flat();
    acc[endpoint as PotterDbEndpoint] = [...new Set(attributes)];
    return acc;
}, {} as Record<PotterDbEndpoint, string[]>);

const getEndpoint = (endpoint: PotterDbEndpoint, page: number = 1) =>
    `https://api.potterdb.com/v1/${endpoint}?page[number]=${page}`;

const fetchPotterData = async (endpoint: PotterDbEndpoint) => {
    const attrs = requiredAttributes[endpoint];
    // array of objects with only required attributes, where values are strings or arrays of strings
    const data: Record<(typeof attrs)[number], string | string[]>[] = [];
    let next = 1;
    while (next) {
        const response = await fetch(getEndpoint(endpoint, next));
        const json = await response.json();
        const onlyRequired = json.data.map((item: { attributes: object }) => {
            return Object.fromEntries(
                Object.entries(item.attributes).filter(([key]) =>
                    attrs.includes(key)
                )
            );
        }) as Record<(typeof attrs)[number], string | string[]>[];
        data.push(...onlyRequired);
        next = json.meta.pagination.next;
    }
    return data;
};

const getData = async (endpoint: PotterDbEndpoint) => {
    const lsData = localStorage.getItem(endpoint);
    if (lsData) {
        const data: HpData = JSON.parse(lsData);
        const required = requiredAttributes[endpoint];
        if (Object.keys(data[0]).every((attr) => required.includes(attr))) {
            return data;
        }
    }
    const data = await fetchPotterData(endpoint);
    localStorage.setItem(endpoint, JSON.stringify(data));
    return data;
};

const isItemString = (item: string | string[]): item is string =>
    typeof item === "string";

const isItemArray = (item: string | string[]): item is string[] =>
    Array.isArray(item);

const shuffle = (array: any[]) => {
    let counter = array.length;

    while (counter > 0) {
        let index = Math.floor(Math.random() * counter);

        counter--;

        let temp = array[counter];
        array[counter] = array[index];
        array[index] = temp;
    }

    return array;
};

const generateQuestion = (
    data: HpData,
    questionProperty: string,
    answersProperty: string,
    question: string
): Question => {
    const filteredData = data.filter(
        (item) =>
            item[questionProperty] &&
            item[answersProperty] &&
            item[questionProperty].length &&
            item[answersProperty].length
    );

    const randomIndex = Math.floor(Math.random() * filteredData.length);
    const randomItem = filteredData[randomIndex];
    const randomAnswers = [randomItem];
    while (randomAnswers.length < 4) {
        const randomIndex = Math.floor(Math.random() * filteredData.length);
        const randomItem = filteredData[randomIndex];
        if (!randomAnswers.includes(randomItem)) {
            randomAnswers.push(randomItem);
        }
    }

    const questionPropertyValue = randomItem[questionProperty];
    let filledQuestion = "";

    if (isItemString(questionPropertyValue)) {
        filledQuestion = question.replace("$val", questionPropertyValue);
    } else if (isItemArray(questionPropertyValue)) {
        filledQuestion = question.replace(
            "$val",
            questionPropertyValue.slice(0, 2).join(", ")
        );
    }

    return {
        question: filledQuestion,
        answers: shuffle(
            randomAnswers.map((item) => item[answersProperty]) as string[]
        ),
        correctAnswer: randomItem[answersProperty] as string,
    };
};

export {
    categories,
    questionTypes,
    getData,
    generateQuestion,
    getEndpointByCategory,
    getQuestionData,
};
export type { PotterDbEndpoint, Category, HpData, UnwrapPromise, Question };
