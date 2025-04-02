SELECT
    Customer.LastName,
    Customer.FirstName,
    SUM(SalesOrderDetail.UnitPriceDiscount * SalesOrderDetail.OrderQty * SalesOrderDetail.UnitPrice) AS TotalMoneySaved
FROM SalesLT.Customer
JOIN SalesLT.SalesOrderHeader ON Customer.CustomerID = SalesOrderHeader.CustomerID
JOIN SalesLT.SalesOrderDetail ON SalesOrderHeader.SalesOrderID = SalesOrderDetail.SalesOrderID
GROUP BY Customer.LastName, Customer.FirstName;