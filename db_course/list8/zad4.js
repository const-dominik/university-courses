const env = require("dotenv").config({ path: __dirname+'/.env'});

var neo4j = require('neo4j-driver');
(async () => {
  const URI = 'neo4j+s://c174b5c7.databases.neo4j.io'
  const USER = 'neo4j'
  const PASSWORD = process.env.PASSWORD;
  let driver

    try {
        driver = neo4j.driver(URI, neo4j.auth.basic(USER, PASSWORD))

        const { records, summary, keys } = await driver.executeQuery(
            `MATCH (p:Person)-[r:ACTED_IN]->(movie)
            RETURN p, r, movie`,
            { database: 'neo4j' }
        )

        for (const record of records) {
            console.log(record.get("p"), record.get("r"), record.get("movie"))
            console.log("-------------------")
        }
    } catch(err) {
        console.log(`Connection error\n${err}\nCause: ${err.cause}`)
    }
})();