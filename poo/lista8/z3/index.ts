abstract class DataAccessHandler {
    public execute(): any {
        this.connect();
        const data = this.retrieveData();
        const processedData = this.processData(data);
        this.closeConnection();
        return processedData;
    }

    protected abstract connect(): void;
    protected abstract retrieveData(): any;
    protected abstract processData(data: any): any;

    private closeConnection(): void {
        console.log("closing connection");
    }
}

class DatabaseHandler extends DataAccessHandler {
    protected connect(): void {
        console.log("Connecting to the database");
    }

    protected retrieveData(): any {
        console.log("retrieve data from the database");
        return [1, 2, 3, 4, 5];
    }

    protected processData(data: any): any {
        return data.reduce((acc: number, curr: number) => acc + curr, 0);
    }
}

class XMLFileHandler extends DataAccessHandler {
    protected connect(): void {
        console.log("read xml file");
        // this.file = fs.readFileSync("file.xml");
    }

    protected retrieveData(): any {
        // get data from this.file
        return ["node1", "node22", "node333"];
    }

    protected processData(data: any): any {
        return data.reduce(
            (max: string, current: string) =>
                current.length > max.length ? current : max,
            ""
        );
    }
}

const dbHandler = new DatabaseHandler();
console.log("db:", dbHandler.execute());

const xmlHandler = new XMLFileHandler();
console.log("xml:", xmlHandler.execute());
