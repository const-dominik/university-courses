DROP TABLE IF EXISTS Customer_Backup


DECLARE @StartTime DATETIME
DECLARE @EndTime DATETIME
DECLARE @Duration INT
SET @StartTime = GETDATE()

CREATE TABLE Customer_Backup ( CustomerID INT, FirstName NAME, LastName NAME )

DECLARE @CustomerId INT
DECLARE @FirstName Name
DECLARE @LastName Name

DECLARE CustomerCursor CURSOR FOR
SELECT CustomerID, FirstName, LastName
FROM SalesLT.Customer

OPEN CustomerCursor

FETCH NEXT FROM CustomerCursor
INTO @CustomerId, @FirstName, @LastName

WHILE @@FETCH_STATUS = 0
BEGIN
    INSERT INTO Customer_Backup (CustomerID, FirstName, LastName) 
    VALUES (@CustomerId, @FirstName, @LastName)

    FETCH NEXT FROM CustomerCursor
    INTO @CustomerId, @FirstName, @LastName
END

CLOSE CustomerCursor
DEALLOCATE CustomerCursor

SET @EndTime = GETDATE()
SET @Duration = DATEDIFF(MILLISECOND, @StartTime, @EndTime)
PRINT 'Total execution time (ms): ' + CAST(@Duration AS NVARCHAR(10))