SELECT
       City, 
       COUNT(DISTINCT Customer.CustomerID),
       COUNT(DISTINCT Customer.SalesPerson)
FROM SalesLT.CustomerAddress
JOIN SalesLT.Address ON Address.AddressID = CustomerAddress.AddressID
JOIN SalesLT.Customer ON Customer.CustomerID = CustomerAddress.CustomerID
GROUP BY City
