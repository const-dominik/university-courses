WITH Discounts AS (
    SELECT 
		SalesLT.SalesOrderHeader.SalesOrderID, 
		SalesLT.SalesOrderHeader.SalesOrderNumber, 
		SalesLT.SalesOrderHeader.PurchaseOrderNumber,
		SUM(SalesLT.SalesOrderDetail.OrderQty * SalesLT.SalesOrderDetail.UnitPrice - SalesLT.SalesOrderDetail.LineTotal) AS Discount
	FROM SalesLT.SalesOrderHeader
	JOIN SalesLT.SalesOrderDetail 
	ON SalesLT.SalesOrderHeader.SalesOrderID = SalesLT.SalesOrderDetail.SalesOrderID
	GROUP BY SalesLT.SalesOrderHeader.SalesOrderID, SalesLT.SalesOrderHeader.SalesOrderNumber, SalesLT.SalesOrderHeader.PurchaseOrderNumber
)
SELECT *
FROM Discounts
WHERE Discount = (SELECT MAX(Discount) FROM Discounts);