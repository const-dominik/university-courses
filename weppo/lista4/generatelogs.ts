import fs from "node:fs";

type TimeFormat = `${number}:${number}:${number}`;
type IPFormat = `${number}.${number}.${number}.${number}`;
type RequestType = typeof requests[number];
type Log = `${TimeFormat} ${IPFormat} ${RequestType} ${string} ${number}`;

const requests = ["PUT", "GET", "DELETE", "POST"] as const;

const random = (min: number, max: number) => Math.floor(Math.random() * (max - min + 1) + min);

const getRandomHour = (): TimeFormat => {
    const hour = random(0, 23);
    const minute = random(0, 59);
    const secs = random(0, 59);
    [hour, minute, secs].map(el => el < 10 ? "0" + String(el) : String(el));
    return `${hour}:${minute}:${secs}`;
}

const getRandomIPAddress = (): IPFormat => {
    const randomHost = random(0, 255);
    return `192.168.0.${randomHost}`; // so that we have lot of ip addresses repeating
}

const getRandomRequestType = (): RequestType => {
    const ind = random(0, 3);
    return requests[ind];
}

const getRandomHTTPCode = () => random(100, 599);

const generateLog = (): Log => {
    return `${getRandomHour()} ${getRandomIPAddress()} ${getRandomRequestType()} /TheApplication/WebResource.axd ${getRandomHTTPCode()}`;
};

const generateLogs = (filePath: string, amount: number): void => {
    const logs = Array.from({ length: amount }, generateLog);
    fs.writeFileSync(filePath, logs.join("\n"));
}

generateLogs("./logs.txt", 10000);