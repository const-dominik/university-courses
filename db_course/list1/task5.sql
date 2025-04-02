SELECT 
    SalesLT.SalesOrderHeader.SalesOrderID, 
    SalesLT.SalesOrderHeader.SalesOrderNumber, 
    SalesLT.SalesOrderHeader.PurchaseOrderNumber,
    SUM(SalesLT.SalesOrderDetail.LineTotal) AS TotalWithDiscount,
    SUM(SalesLT.SalesOrderDetail.OrderQty * SalesLT.SalesOrderDetail.UnitPrice) AS TotalWithoutDiscount,
	SUM(SalesLT.SalesOrderDetail.OrderQty) AS ALLItemsInOrder,
	COUNT(*) AS AllDifferentItemsInOrder
FROM SalesLT.SalesOrderHeader
JOIN SalesLT.SalesOrderDetail 
ON SalesLT.SalesOrderHeader.SalesOrderID = SalesLT.SalesOrderDetail.SalesOrderID
GROUP BY SalesLT.SalesOrderHeader.SalesOrderID, SalesLT.SalesOrderHeader.SalesOrderNumber, SalesLT.SalesOrderHeader.PurchaseOrderNumber;