DROP TABLE IF EXISTS Customer_Backup

DECLARE @StartTime DATETIME
DECLARE @EndTime DATETIME
DECLARE @Duration INT
SET @StartTime = GETDATE()

SELECT CustomerID, FirstName, LastName INTO Customer_Backup FROM SalesLT.Customer;

SET @EndTime = GETDATE()
SET @Duration = DATEDIFF(MILLISECOND, @StartTime, @EndTime)
PRINT 'Total execution time (ms): ' + CAST(@Duration AS NVARCHAR(10))

