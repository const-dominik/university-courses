DROP TABLE IF EXISTS firstnames
DROP TABLE IF EXISTS surnames
DROP TABLE IF EXISTS fldata
GO

CREATE TABLE firstnames (
	id INT PRIMARY KEY IDENTITY,
	firstname VARCHAR(20)
);

CREATE TABLE surnames (
	id INT PRIMARY KEY IDENTITY,
	surname VARCHAR(20)
);

CREATE TABLE fldata
(
    firstname VARCHAR(20),
    surname VARCHAR(20),
    PRIMARY KEY (firstname, surname)
);

INSERT INTO firstnames
VALUES 
    ('Philip'),
    ('Katy'),
    ('Lucas'),
    ('Matthew'),
    ('Taylor'),
    ('Cynthia')

INSERT INTO surnames
VALUES 
    ('Smith'),
    ('Johnson'),
    ('Brown'),
    ('Williams'),
    ('Jones'),
    ('Davis');
GO

DROP PROCEDURE IF EXISTS insertRandomPairs;
GO

CREATE PROCEDURE insertRandomPairs(@n INT) AS
BEGIN
	TRUNCATE TABLE fldata;

	DECLARE @possibilites INT = (SELECT COUNT(*) FROM firstnames) * (SELECT COUNT(*) FROM surnames)

	IF (@n > @possibilites)
		THROW 50000, 'Argument to big', 0;

	DECLARE @i INT = 0
	WHILE (@i < @n)
	BEGIN
	--NEWID generates random id, so ordering by newid() sorts in random order
		DECLARE @firstname VARCHAR(20) = (SELECT TOP 1 firstnames.firstname FROM firstnames ORDER BY NEWID())
		DECLARE @surname VARCHAR(20) = (SELECT TOP 1 surnames.surname FROM surnames ORDER BY NEWID())		
		
		IF NOT EXISTS (SELECT 1 FROM fldata WHERE @firstname = fldata.firstname AND @surname = fldata.surname)
		BEGIN
			INSERT INTO fldata VALUES (@firstname, @surname)
			SET @i = @i + 1
		END
	END
END
GO

EXEC insertRandomPairs @n=20
SELECT * FROM fldata;