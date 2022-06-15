//program do obliczania fajrantu na podstawie wyniku 1 zadania domowego
const maxPoints = {
    lists: 140,
    homeworks: 20
} as const;

const currentPoints = {
    lists: 28,
    homeworks: 8
}

const percentageFromLists = (points: number) => points/maxPoints.lists;
const percentageFromHomeworks = (points: number) => points/maxPoints.homeworks;
const mainPercentage = (lists: number, homeworks: number) => 8 * percentageFromLists(lists)/10 + 2 * percentageFromHomeworks(homeworks)/10;

const findFajrantListPoints = (pointsFromSecondHomework: number, extraListsPoints: number = 0): number => {
    const newListsPoints = currentPoints.lists + extraListsPoints;
    const newHomeworksPoints = currentPoints.homeworks + pointsFromSecondHomework;
    const newPercentage = mainPercentage(newListsPoints, newHomeworksPoints);
    if (newPercentage >= 0.4) 
        return extraListsPoints;
    return findFajrantListPoints(pointsFromSecondHomework, extraListsPoints + 1);
}

for (let i = 0; i <= 10; i++)
    console.log(`${i} za drugie zadanie to ${findFajrantListPoints(i)} z list`);
